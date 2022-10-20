project(dds-connector)
cmake_minimum_required(VERSION 3.10)

find_package(OpenDDS REQUIRED)
find_package(Boost REQUIRED)
set(opendds_libs
  OpenDDS::Dcps # Core OpenDDS Library
  OpenDDS::InfoRepoDiscovery OpenDDS::Tcp # For run_test.pl
  OpenDDS::Rtps OpenDDS::Rtps_Udp # For run_test.pl --rtps
)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(demo-code ${CMAKE_CURRENT_SOURCE_DIR}/testcode.cpp)
target_link_libraries(demo-code ${opendds_libs})