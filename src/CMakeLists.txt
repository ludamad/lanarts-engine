cmake_minimum_required(VERSION 2.6)
PROJECT(project_lanarts)

add_definitions( -std=c++98)

set( HANDROLLED .)
set( BUNDLED ../dependencies/bundled)

include_directories(
    "."
    "${HANDROLLED}/common-lib/include"
    "${HANDROLLED}/draw-lib/include"
    "${HANDROLLED}/dungeon-generation-lib/include"
    "${HANDROLLED}" # for net
    "${HANDROLLED}/luawrap-lib/include"
    "${HANDROLLED}/sound-lib/include"
    "${BUNDLED}" # for rvo2 
)

add_library( lanarts-libs
             STATIC
             extension-main.cpp
)

target_link_libraries(lanarts-libs
    enet
    lua_enet
    libxmi
    luayaml
    RVO
    lpeg
    luv
    lualinenoise
)


