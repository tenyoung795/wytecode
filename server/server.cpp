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
    auto code = engine->initializeLipiEngine();
    if (code != SUCCESS) {
        throw LTKException(code);
    }

    auto recognizer_deleter = [engine] (auto recognizer) {
        engine->deleteShapeRecognizer(recognizer);
    };
    std::shared_ptr<LTKShapeRecognizer> recognizer{
        [engine] {
            LTKShapeRecognizer *result;
            std::string name = "SHAPEREC_ALPHANUM";
            auto code = engine->createShapeRecognizer(name, &result);
            if (code != SUCCESS) {
                throw LTKException(code);
            }
            return result;
        }(), std::move(recognizer_deleter)};
    code = recognizer->loadModelData();
    if (code != SUCCESS) {
        throw LTKException(code);
    }

    ptree pt;
    read_ini(lipi_root + "/projects/alphanumeric/config/unicodeMapfile_alphanumeric.ini"s, pt);

    auto port = std::strtoul(argv[1], nullptr, 10);

    websocketpp::server<websocketpp::config::asio> server;
    server.set_message_handler(
        [&server, recognizer = std::move(recognizer), pt = std::move(pt)] (auto hdl, auto msg) {
            std::istringstream lines(msg->get_payload());
            std::string line;
            std::string translation;
            LTKTraceGroup trace_group;
            while (std::getline(lines, line)) {
                trace_group.emptyAllTraces();
                std::istringstream points(line);
                LTKTrace trace;
                while (true) {
                    unsigned short x, y;
                    char comma, delimiter;
                    if (!(points >> x)) break;
                    points >> comma;
                    points >> y;
                    points >> delimiter;
                    trace.addPoint({x, y});
                    if (delimiter == ';') {
                        trace_group.addTrace(trace);
                        trace.emptyTrace();
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
                    translation.push_back(character);
                } else {
                    server.close(hdl, internal_endpoint_error, getErrorMessage(code));
                    return;
                }
            }
            std::clog << translation << '\n';
            server.send(hdl, translation, msg->get_opcode());
        });
    server.init_asio();
    server.listen(port);
    server.start_accept();
    std::clog << "Hello\n";
    server.run();
}
