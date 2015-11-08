include_directories("${CMAKE_SOURCE_DIR}")
add_executable(genesis_geodist genesis_geodist.cpp)
target_link_libraries(genesis_geodist genesis)
install(TARGETS genesis_geodist DESTINATION "bin")

