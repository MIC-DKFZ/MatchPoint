IF (BUILD_TESTING)
	MESSAGE (STATUS "processing MatchPoint example code")

	ADD_SUBDIRECTORY (Algorithms)
	ADD_SUBDIRECTORY (Deployment)
ELSE (BUILD_TESTING)
	MESSAGE (STATUS "skipped MatchPoint example code (activate Testing to build examples)")
ENDIF (BUILD_TESTING)