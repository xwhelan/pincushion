cmake_minimum_required(VERSION 3.0.0)
project(pincushion VERSION 0.1.0)

add_executable(csv2json src/csv2json.cpp)
install(TARGETS csv2json DESTINATION bin)
