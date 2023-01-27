cmake_minimum_required(VERSION 3.24)
project(StatCpu C)

set(CMAKE_C_STANDARD 17)

add_executable(StatCpu main.c data.c data.h Queque.c Queque.h Reader.c Reader.h Analyzer.c Analyzer.h Printer.c Printer.h)
