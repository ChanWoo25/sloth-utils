cmake_minimum_required(VERSION 3.16)
project(example)

find_package(glog REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries (${PROJECT_NAME} glog::glog)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17) # cxx_std_14 is minimum because of other dependencies

target_compile_options(${PROJECT_NAME} PUBLIC
  -Wall
  -Werror
  # -pthread # When you wanna link <thread> related libraries
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin")
