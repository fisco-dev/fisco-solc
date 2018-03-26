aux_source_directory(. SRC_LIST)

set(EXECUTABLE lllc)

file(GLOB HEADERS "*.h")
include_directories(BEFORE ..)
eth_simple_add_executable(${EXECUTABLE} ${SRC_LIST} ${HEADERS})

eth_use(${EXECUTABLE} REQUIRED Solidity::lll Dev::buildinfo Solidity::solevmasm)
target_include_directories(${EXECUTABLE} PUBLIC ${BOOST_INCLUDE_DIR})

install( TARGETS ${EXECUTABLE} DESTINATION bin )

