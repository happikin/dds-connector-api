set(CMAKE_CXX_FLAGS "-w -g")

project(dds-connector)
cmake_minimum_required(VERSION 3.10)

find_package(OpenDDS REQUIRED)
find_package(Boost REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/build/opendds_generated)

add_library(testdata_idl)
OPENDDS_TARGET_SOURCES(testdata_idl PUBLIC "testdata.idl")
target_link_libraries(testdata_idl PUBLIC OpenDDS::Dcps)

set(opendds_libs
  OpenDDS::Dcps # Core OpenDDS Library
  OpenDDS::InfoRepoDiscovery OpenDDS::Tcp # For run_test.pl
  OpenDDS::Rtps OpenDDS::Rtps_Udp # For run_test.pl --rtps
  testdata_idl
)
add_executable(single_publisher ${CMAKE_CURRENT_SOURCE_DIR}/single_publisher.cpp)
target_link_libraries(single_publisher ${opendds_libs})

add_executable(single_subscriber ${CMAKE_CURRENT_SOURCE_DIR}/single_subscriber.cpp ${CMAKE_CURRENT_SOURCE_DIR}/listener.cpp)
target_link_libraries(single_subscriber ${opendds_libs})
