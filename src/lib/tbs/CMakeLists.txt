include_directories(${SFML2_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include/tbs)
include_directories(${CMAKE_SOURCE_DIR}/include/tbs/gamestate)

# Client
file(GLOB LIBTBS0_SRC
	"client/*.cpp"
        "client/gamestate/*.cpp"
)

add_library(tbs0 SHARED
  ${LIBTBS0_SRC}
)

target_link_libraries(tbs0
  ${SFML2_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

set_target_properties(tbs0
  PROPERTIES
  VERSION ${CPACK_PACKAGE_VERSION}
  SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
  LIBRARY_OUTPUT_DIRECTORY client
)

install(
  TARGETS tbs0
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

# Server
file(GLOB LIBTBSSERVER0_SRC
	"server/*.cpp"
)

add_library(tbs-server0 SHARED
  ${LIBTBSSERVER0_SRC}
)

target_link_libraries(tbs-server0
  ${SFML2_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

set_target_properties(tbs-server0
  PROPERTIES
  VERSION ${CPACK_PACKAGE_VERSION}
  SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
  LIBRARY_OUTPUT_DIRECTORY server
)

install(
  TARGETS tbs-server0
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

# Shared
file(GLOB LIBTBSSHARED0_SRC
	"shared/*.cpp"
)

add_library(tbs-shared0 SHARED
  ${LIBTBSSHARED0_SRC}
)

target_link_libraries(tbs-shared0
  ${SFML2_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

set_target_properties(tbs-shared0
  PROPERTIES
  VERSION ${CPACK_PACKAGE_VERSION}
  SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
  LIBRARY_OUTPUT_DIRECTORY shared
)

install(
  TARGETS tbs-shared0
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
