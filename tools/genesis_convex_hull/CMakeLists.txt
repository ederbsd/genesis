include_directories("${CMAKE_SOURCE_DIR}")
add_executable(genesis_convex_hull genesis_convex_hull.cxx)
target_link_libraries(genesis_convex_hull genesis)
install(TARGETS genesis_convex_hull DESTINATION "bin")

