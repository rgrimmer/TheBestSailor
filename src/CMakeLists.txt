cmake_minimum_required(VERSION 2.8)

project(GAME CXX)

include(CPackConfig.cmake)
include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1 sfml-network>=2.1)

add_definitions(-Wall -g -O2)
add_definitions(-std=c++11)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(lib/tbs)
add_subdirectory(bin)

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/include/tbs"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/share"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/lib/tbs"
)
