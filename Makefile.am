SUBDIRS=genesis test tools doc

EXTRA_DIST = Doxyfile 

DISTCLEANFILES = \
	gmon.out \
	doc/doxygen.log

docs:
	doxygen
	cd doc/latex; ${MAKE} -i

