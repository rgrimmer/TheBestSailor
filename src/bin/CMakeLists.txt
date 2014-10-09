include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include/tbs)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

# Client
file(GLOB TBS_SRC
	"client/*.cpp"
)

add_executable(tbs ${TBS_SRC})

target_link_libraries(tbs
  tbs0
  tbs-shared0
)

set_target_properties(tbs
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY client/
)

install(
  TARGETS tbs
  RUNTIME DESTINATION games
)

# Server
file(GLOB TBSSERVER_SRC
	"server/*.cpp"
)

add_executable(tbs-server ${TBSSERVER_SRC})

target_link_libraries(tbs-server
  tbs-server0
  tbs-shared0
)

set_target_properties(tbs-server
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY server/
)

install(
  TARGETS tbs-server
  RUNTIME DESTINATION games
)

