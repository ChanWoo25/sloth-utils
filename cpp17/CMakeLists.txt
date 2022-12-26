cmake_minimum_required(VERSION 3.11)
project(cpp17)

find_package(glog REQUIRED)

add_executable(main main.cpp)
target_link_libraries (main glog::glog)
target_compile_features(main PUBLIC cxx_std_17)
set_target_properties(main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin")
