cmake_minimum_required(VERSION 2.8.12)
project(wytecode_server)
add_executable(server server.cpp)

find_package(Boost 1.54 REQUIRED system)
find_package(websocketpp 0.6 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(SYSTEM lipi-toolkit/src)
include_directories(SYSTEM lipi-toolkit/src/include)
include_directories(SYSTEM lipi-toolkit/src/util/lib)

target_compile_options(server PUBLIC
    --std=c++14 -Wall -Wextra -pedantic -Wfatal-errors)

target_link_libraries(server -Llipi-toolkit/lib -Llipi-toolkit/src/lib ${Boost_LIBRARIES} lipiengine util common shaperecommon pthread dl)
