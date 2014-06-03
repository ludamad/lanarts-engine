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

aux_source_directory("." lanarts-src) #Find source files

add_library( lanarts-libs
             STATIC
             "${lanarts-src}"
)

target_link_libraries(lanarts-libs
    lua_enet
    lua_box2d
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


