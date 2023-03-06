cmake_minimum_required(VERSION 3.18)

project(AutoMove)

add_library(AutoMove SHARED)
file(GLOB SOURCES
    src/*.cpp
)
file(GLOB HEADERS
    src/*.h
)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(
		AutoMove
		PRIVATE
			"/sdl"	# Enable Additional Security Checks
			"/utf-8"	# Set Source and Executable character sets to UTF-8
			"/Zi"	# Debug Information Format

			"/permissive-"	# Standards conformance
			"/Zc:preprocessor"	# Enable preprocessor conformance mode

			"/wd4200" # nonstandard extension used : zero-sized array in struct/union

			"$<$<CONFIG:DEBUG>:>"
			"$<$<CONFIG:RELEASE>:/Zc:inline;/JMC-;/Ob3>"
	)

	target_link_options(
		AutoMove
		PRIVATE
			"$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
			"$<$<CONFIG:RELEASE>:/INCREMENTAL:NO;/OPT:REF;/OPT:ICF;/DEBUG:FULL>"
	)
endif()


target_sources(AutoMove PRIVATE ${SOURCES} ${HEADERS})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/CommonLibSSE" CommonLibSSE EXCLUDE_FROM_ALL)
target_link_libraries(AutoMove PRIVATE
    CommonLibSSE::CommonLibSSE
)
