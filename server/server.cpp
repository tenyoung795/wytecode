#include <climits>
#include <cstdint>
#include <cstdlib>

#include <array>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <lipiengine/LipiEngineModule.h>
#include <LTKErrors.h>
#include <LTKException.h>
#include <LTKTrace.h>
#include <LTKTraceGroup.h>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using boost::property_tree::ptree;
using boost::property_tree::ini_parser::read_ini;
using websocketpp::close::status::internal_endpoint_error;
using websocketpp::frame::opcode::text;
using websocketpp::lib::error_code;

template <class F, class ...Args>
static void ltk_unwrap(F &&f, Args && ...args) {
    auto code = std::bind(std::forward<F>(f), std::forward<Args>(args)...)();
    if (code != SUCCESS) {
        throw LTKException(code);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " PORT\n\nMust set LIPI_ROOT";
        return EXIT_FAILURE;
    }

    const char *lipi_root = std::getenv("LIPI_ROOT");
    if (!lipi_root) {
        std::cerr << "Must set LIPI_ROOT\n";
        return EXIT_FAILURE;
    }

    auto engine = LTKLipiEngineModule::getInstance();
    engine->setLipiRootPath(lipi_root);
    ltk_unwrap(&LTKLipiEngineModule::initializeLipiEngine, engine);

    auto recognizer_deleter = [engine] (auto recognizer) {
        engine->deleteShapeRecognizer(recognizer);
    };
    std::shared_ptr<LTKShapeRecognizer> recognizer{
        [engine] {
            LTKShapeRecognizer *result;
            ltk_unwrap([engine, &result] {
                std::string name = "SHAPEREC_ALPHANUM";
                return engine->createShapeRecognizer(name, &result);
            });
            return result;
        }(), std::move(recognizer_deleter)};
    ltk_unwrap(&LTKShapeRecognizer::loadModelData, recognizer);

    ptree pt;
    read_ini(lipi_root + "/projects/alphanumeric/config/unicodeMapfile_alphanumeric.ini"s, pt);

    auto port = std::strtoul(argv[1], nullptr, 10);

    websocketpp::server<websocketpp::config::asio> server;
    server.set_message_handler(
        [&server, recognizer = std::move(recognizer), pt = std::move(pt)] (auto hdl, auto msg) {
            std::istringstream stream(msg->get_payload());
            LTKTraceGroup trace_group;
            LTKTrace trace;
            while (true) {
                float x, y;
                char comma, delimiter;
                if (!(stream >> x)) break;
                stream >> comma;
                stream >> y;
                stream >> delimiter;
                ltk_unwrap([&trace, x, y] {
                    return trace.addPoint({x, y});
                });
                if (delimiter == ';') {
                    trace_group.addTrace({trace});
                    continue;
                }
            }
            std::vector<LTKShapeRecoResult> results;
            results.reserve(2);
            auto code = recognizer->recognize(trace_group, {}, {}, 0.0, 2, results);
            if (code == SUCCESS) {
                auto id = results[0].getShapeId();
                auto &data = pt.find(std::to_string(id))->second.data();
                auto character = static_cast<char>(std::strtoul(
                    data.data(), nullptr, 16));
                server.send(hdl, {character}, msg->get_opcode());
            } else {
                server.close(hdl, internal_endpoint_error, getErrorMessage(code));
            }
        });
    server.init_asio();
    server.listen(port);
    server.start_accept();
    std::clog << "Hello\n";
    server.run();
}
