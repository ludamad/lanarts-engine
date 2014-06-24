cmake_minimum_required( VERSION 2.6 )

PROJECT(project_ldraw)

FIND_PACKAGE(OpenGL REQUIRED)

set( SRC ../)
set( DEPS ../../../dependencies/bundled )

add_definitions( -std=c++98 )

include_directories(
	include/ldraw/
	"${SRC}/common-lib/include"
	"${SRC}/luawrap-lib/include"
	${DEPS}/UnitTest++
	${DEPS}/lua-5.1
	${OpenGL_INCLUDE_DIRS} 		
)

file(GLOB ldraw_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
    src/* 
    src/lua/* 
    src/opengl/* 
    include/draw/* 
)

file(GLOB ldraw_tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
    tests/*
)

add_library( ldraw
		STATIC
             ${ldraw_src} )

set(LINKEDDEPS
	luawrap
	lcommon
	${OPENGL_gl_LIBRARY}
)

#add_executable( ldraw_tests ${ldraw_tests} )

target_link_libraries( ldraw ${LINKEDDEPS} )

#target_link_libraries( ldraw_tests ${LINKEDDEPS} UnitTest++ )

enable_testing()
add_test(NAME ldraw_tests COMMAND ${EXECUTABLE_OUTPUT_PATH}/ldraw_tests )
