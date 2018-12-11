 cmake_minimum_required(VERSION 3.4) 

 project (lispp_test)
 
 include_directories(${CMAKE_SOURCE_DIR}/lispp)

 aux_source_directory(${CMAKE_SOURCE_DIR}/lispp LISPP_SRCS)
 add_library(lispp ${LISPP_SRCS})

 add_executable(lexer_test test_lexer.cpp)
 target_link_libraries(lexer_test lispp)

