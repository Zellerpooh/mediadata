cmake_minimum_required(VERSION 3.7)
project(mediadata)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES  yuv/yuvsplit.cpp)
add_executable(mediadata ${SOURCE_FILES})