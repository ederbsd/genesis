include_directories("${CMAKE_SOURCE_DIR}")

set(HEADER_FILES 
  application.hxx
  array.hxx
  bit.hxx
  bitree.hxx
  calendar.hxx
  clsid.hxx
  cmd_line_parser.hxx
  config.hxx
  convex_hull.hxx
  datetime.hxx
  events.hxx
  exception.hxx
  factory.hxx
  genesis.hxx
  geometry.hxx
  lexical_cast.hxx
  list.hxx
  loadable.hxx
  logger.hxx
  maths.hxx
  mutex.hxx
  nullstream.hxx
  plotting.hxx
  proto_types.hxx
  set.hxx
  set_cover.hxx
  sort.hxx
  string_util.hxx
  system.hxx
  tests.hxx
  thread.hxx
  unknown.hxx)

set(SRC_FILES
  application.cxx
  array.cxx
  bit.cxx
  bitree.cxx
  calendar.cxx
  clsid.cxx
  cmd_line_parser.cxx
  config.cxx
  convex_hull.cxx
  datetime.cxx
  events.cxx
  factory.cxx
  genesis.cxx
  geometry.cxx
  lexical_cast.cxx
  list.cxx
  loadable.cxx
  logger.cxx
  maths.cxx
  mutex.cxx
  plotting.cxx
  set.cxx
  set_cover.cxx
  sort.cxx
  string_util.cxx
  system.cxx
  tests.cxx
  thread.cxx
  unknown.cxx
)

add_library(genesis SHARED
  ${HEADER_FILES}
  ${SRC_FILES}
)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  target_link_libraries(genesis dl)
endif()

target_link_libraries(genesis pthread)
target_link_libraries(genesis rt)

install(TARGETS genesis
  RUNTIME DESTINATION "lib"
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib")

install(FILES ${HEADER_FILES} 
  DESTINATION "include/genesis")

