INCLUDES=-I $(top_srcdir)

# Test for loading library.
noinst_LTLIBRARIES = libload.la
libload_la_SOURCES = class_lib_loadable.cpp

LDADD=$(top_builddir)/genesis/libgenesis.la
LDADD+=libload.la

export LD_LIBRARY_PATH=$(top_builddir)/genesis/.libs

check_PROGRAMS = \
	cmd_line_parser_test \
	list_test \
	exception_test \
	array_test \
	sort_test \
	maths_test \
	datetime_test \
	set_test \
	set_cover_test \
	bit_test \
	bitree_test \
	genesis_test \
	class_loadable_test \
	logger_test \
	config_test \
	application_test \
	system_test \
	thread_test \
	geometry_test \
	convex_hull_test

cmd_line_parser_test_SOURCES = cmd_line_parser_test.cpp
list_test_SOURCES = list_test.cpp
exception_test_SOURCES = exception_test.cpp
array_test_SOURCES = array_test.cpp
sort_test_SOURCES = sort_test.cpp
maths_test_SOURCES = maths_test.cpp
datetime_test_SOURCES = datetime_test.cpp
set_test_SOURCES = set_test.cpp
set_cover_test_SOURCES = set_cover_test.cpp
bit_test_SOURCES = bit_test.cpp
bitree_test_SOURCES = bitree_test.cpp
genesis_test_SOURCES = genesis_test.cpp
class_loadable_test_SOURCES = class_loadable_test.cpp class_lib_loadable.hpp
logger_test_SOURCES = logger_test.cpp
config_test_SOURCES = config_test.cpp
application_test_SOURCES = application_test.cpp
system_test_SOURCES = system_test.cpp
thread_test_SOURCES = thread_test.cpp
geometry_test_SOURCES = geometry_test.cpp
convex_hull_test_SOURCES = convex_hull_test.cpp 

TESTS=$(check_PROGRAMS)

EXTRA_DIST = \
	config_test.conf \
	gnuplot.cmd

DISTCLEANFILES = \
	gnuplot.cmd

