include_directories("${CMAKE_SOURCE_DIR}")

# Application test.
add_executable(application_test application_test.cpp)
target_link_libraries(application_test genesis)
add_test(application_test application_test)

# Array test.
add_executable(array_test array_test.cpp)
target_link_libraries(array_test genesis)
add_test(array_test array_test)

# BiTree test.
add_executable(bitree_test bitree_test.cpp)
target_link_libraries(bitree_test genesis)
add_test(bitree_test bitree_test)

# Bit test.
add_executable(bit_test bit_test.cpp)
target_link_libraries(bit_test genesis)
add_test(bit_test bit_test)

# Command line parser test.
add_executable(cmd_line_parser_test cmd_line_parser_test.cpp)
target_link_libraries(cmd_line_parser_test genesis)
add_test(cmd_line_parser_test cmd_line_parser_test)

# Configuration file test.
add_executable(config_test config_test.cpp)
target_link_libraries(config_test genesis)
add_test(config_test config_test)

# Convex hull test.
add_executable(convex_hull_test convex_hull_test.cpp)
target_link_libraries(convex_hull_test genesis)
add_test(convex_hull_test convex_hull_test)

# DateTime test.
add_executable(datetime_test datetime_test.cpp)
target_link_libraries(datetime_test genesis)
add_test(datetime_test datetime_test)

# Exception test.
add_executable(exception_test exception_test.cpp)
target_link_libraries(exception_test genesis)
add_test(exception_test exception_test)

# Genesis test.
add_executable(genesis_test genesis_test.cpp)
target_link_libraries(genesis_test genesis)
add_test(genesis_test genesis_test)

# Geometry test.
add_executable(geometry_test geometry_test.cpp)
target_link_libraries(geometry_test genesis)
add_test(geometry_test geometry_test)

# List test.
add_executable(list_test list_test.cpp)
target_link_libraries(list_test genesis)
add_test(list_test list_test)

# Logger test.
add_executable(logger_test logger_test.cpp)
target_link_libraries(logger_test genesis)
add_test(logger_test logger_test)

# Maths test.
add_executable(maths_test maths_test.cpp)
target_link_libraries(maths_test genesis)
add_test(maths_test maths_test)

# Set cover test.
add_executable(set_cover_test set_cover_test.cpp)
target_link_libraries(set_cover_test genesis)
add_test(set_cover_test set_cover_test)

# Set test.
add_executable(set_test set_test.cpp)
target_link_libraries(set_test genesis)
add_test(set_test set_test)

# Sort test.
add_executable(sort_test sort_test.cpp)
target_link_libraries(sort_test genesis)
add_test(sort_test sort_test)

# System test.
add_executable(system_test system_test.cpp)
target_link_libraries(system_test genesis)
add_test(system_test system_test)

# Thread test.
add_executable(thread_test thread_test.cpp)
target_link_libraries(thread_test genesis)
add_test(thread_test thread_test)

# Copy file for test. 
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config_test.conf 
               ${CMAKE_CURRENT_BINARY_DIR}/config_test.conf COPYONLY)

