cmake_minimum_required(VERSION 3.11)
project(cpp17)

find_package(glog REQUIRED)

add_executable(main main.cpp)
target_link_libraries (main glog::glog)
target_compile_features(main PUBLIC cxx_std_17)
set_target_properties(main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin")


add_executable(main_thread main_thread.cpp)
target_link_libraries (main_thread glog::glog)
target_compile_features(main_thread PUBLIC cxx_std_17)
target_compile_options(main_thread PUBLIC -Wall -Werror -pthread)
set_target_properties(main_thread PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin")
