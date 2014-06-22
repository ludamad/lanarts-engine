cmake_minimum_required(VERSION 2.6)
PROJECT(project_lanarts)

add_subdirectory(libs/)

add_definitions( -std=c++98)

set( HANDROLLED ./libs)
set( BUNDLED ../dependencies/bundled)
set( EXTERNAL ../dependencies/external)

include_directories(
    "."
    "${HANDROLLED}/common-lib/include"
    "${HANDROLLED}/draw-lib/include"
    "${HANDROLLED}/dungeon-generation-lib/include"
    "${HANDROLLED}" # for net
    "${HANDROLLED}/luawrap-lib/include"
    "${HANDROLLED}/sound-lib/include"
    "${BUNDLED}" # for rvo2 
    "${EXTERNAL}/luajit-2.0/src"
)

aux_source_directory("." lanarts-src1) #Find source files
aux_source_directory("lanarts" lanarts-src2) #Find source files
aux_source_directory("lanarts/fov" lanarts-src3) #Find source files
aux_source_directory("lanarts/fov/impl" lanarts-src4) #Find source files
aux_source_directory("lanarts/opengl" lanarts-src5) #Find source files

add_library( lanarts-libs
             STATIC
             
             ${lanarts-src1}
             ${lanarts-src2}
             ${lanarts-src3}
             ${lanarts-src4}
			 ${lanarts-src5}
)

target_link_libraries(lanarts-libs
    lua_enet
#    lua_box2d
    lanarts_dungeon_gen
    lcommon
    luawrap
    libxmi
    luayaml
    RVO
    lpeg
    luv
    lualinenoise
)


