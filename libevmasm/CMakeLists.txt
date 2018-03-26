set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTATICLIB")

aux_source_directory(. SRC_LIST)

set(EXECUTABLE solevmasm)

file(GLOB HEADERS "*.h")

include_directories(BEFORE ..)
add_library(${EXECUTABLE} ${SRC_LIST} ${HEADERS})
eth_use(${EXECUTABLE} REQUIRED Dev::soldevcore)
target_link_libraries(${EXECUTABLE} jsoncpp)
target_include_directories(${EXECUTABLE} PUBLIC ${BOOST_INCLUDE_DIR})

install( TARGETS ${EXECUTABLE} RUNTIME DESTINATION bin ARCHIVE DESTINATION lib LIBRARY DESTINATION lib )
