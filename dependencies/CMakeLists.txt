cmake_minimum_required(VERSION 2.6)

# External dependencies, found in other repositories.
# If these dependencies do not exist, run scripts/get_dependencies.sh:
add_subdirectory( external/moai-dev/cmake ) 
add_subdirectory( external/lpeg ) 

# Bundled dependencies. Other than 'enet', the libraries have been fiddled, CMake support added, etc.
add_subdirectory( bundled/enet ) 
add_subdirectory( bundled/lua-enet ) 
add_subdirectory( bundled/lua-linenoise ) 
add_subdirectory( bundled/libxmi ) 
add_subdirectory( bundled/rvo2 ) 
add_subdirectory( bundled/lua-yaml ) 
add_subdirectory( bundled/lua-luv ) 
add_subdirectory( bundled/lua-box2d ) 
add_subdirectory( bundled/UnitTest++ ) 

