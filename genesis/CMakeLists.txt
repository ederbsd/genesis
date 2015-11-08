include_directories("${CMAKE_SOURCE_DIR}")

add_library(genesis SHARED
  genesis.cxx
  genesis.hxx
  clsid.cxx
  clsid.hxx
  unknown.cxx
  unknown.hxx
  factory.cxx
  factory.hxx
  loadable.cxx
  loadable.hxx
  logger.cxx
  logger.hxx
  application.cxx
  application.hxx
  lexical_cast.cxx
  lexical_cast.hxx
  string_util.cxx
  string_util.hxx
  cmd_line_parser.cxx
  cmd_line_parser.hxx
  config.cxx
  config.hxx
  list.cxx
  list.hxx
  datetime.cxx
  datetime.hxx
  calendar.cxx
  calendar.hxx
  sort.cxx
  sort.hxx
  array.cxx
  array.hxx
  maths.cxx
  maths.hxx
  set.cxx
  set.hxx
  set_cover.cxx
  set_cover.hxx
  bit.cxx
  bit.hxx
  tests.cxx
  tests.hxx
  bitree.cxx
  bitree.hxx
  geometry.cxx
  geometry.hxx
  convex_hull.cxx
  convex_hull.hxx
  plotting.cxx
  plotting.hxx
  system.cxx
  system.hxx
  thread.cxx
  thread.hxx 
  events.cxx
  events.hxx 
  mutex.cxx
  mutex.hxx
)

target_link_libraries(genesis dl)
target_link_libraries(genesis pthread)
target_link_libraries(genesis rt)

install(TARGETS genesis
  RUNTIME DESTINATION "lib"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")

install(FILES genesis/genesis.hpp
  DESTINATION "include/genesis")

