#!/bin/bash

###############################################################################
# Load the dependencies necessary for Lanarts.
# We target specific commits, and update as necessary.
###############################################################################

set -e # Good practice -- exit completely on any bad exit code

# Navigate to base folder:
cd "`dirname "$0"`"/.. 

# Set common variables and shell-script safety settings
source "scripts/common.sh"

BASE_FOLDER="$(pwd)"

# Ensure external dependency folder exists:
mkdir -p "$EXTERNAL_DEPENDENCIES_FOLDER"

###############################################################################
# Clone each dependency, based on the repository name and a given commit:
###############################################################################

echo "Grabbing dependencies ..." 

# Enter external dependency folder:
cd "$BASE_FOLDER/$EXTERNAL_DEPENDENCIES_FOLDER"

for dep in \
    'https://github.com/LuaDist/busted 5cb536a6a79e8428d9cc922ab1ad07650d104dae' \
    'https://github.com/LuaDist/lpeg baf0dc90b9278360be719dbfb8e56d34ce3c61bd'  \
    'https://github.com/moai/moai-dev 96dd6bea85376eb15ec66a3a7675ffef405d07fa' \
    'https://github.com/stevedonovan/Penlight 3d905f096053da08c89a37cce35d96b7db1817ab' \
    'https://github.com/leafo/moonscript 1527a5f696f1dda718f44bdd28b6615f2ab650cf' \
    'http://luajit.org/git/luajit-2.0.git 392b6c94ae4b969f7fc74b21501b5e884c002892' 
do
    # Split our combined URL+commit:
    set -- $dep ; URL=$1 ; commit=$2 

    # Grab the folder we will clone into, minus any '.git' suffixes:
    folder=$(basename "$URL" | sed 's/\.git$//')

    echo "Cloning $URL into \"$EXTERNAL_DEPENDENCIES_FOLDER\"" | colorify $LIGHT_BLUE

    # Avoid doing anything if the location already exists:
    if [ ! -e $folder ] ; then
        # If the location did not exist, clone into it 
        git clone "$URL"
    else
        echo "$URL already cloned. Not cloning." | colorify $YELLOW
    fi

    # Check-out the desired commit
    echo "Checking out commit \"$commit\" for \"$URL\" ..." | colorify $LIGHT_BLUE
    cd "$folder"
    git checkout --quiet "$commit"
    echo "Checked out commit \"$commit\" for \"$URL\"." | colorify $YELLOW

    # Reset any previously applied patches
    git checkout .

    ###############################################################################
    # If we cloned a subrepository (external dependency), apply the patches in 
    # dependencies/patches/<repo name> folder.
    ###############################################################################

    PP="$BASE_FOLDER/$PATCHES_FOLDER/$folder"
    if [ -e "$PP" ] ; then
        echo "Applying patches for $(pwd) ..." | colorify $LIGHT_BLUE
        for patch_file in $(ls "$PP") ; do
            echo "Applying $PP/$patch_file to $(pwd)" | colorify $LIGHT_BLUE
            patch -p1 < "$PP/$patch_file"
        done
        echo "Applied patches for $(pwd)." | colorify $YELLOW
    fi

    cd ..
done

echo "Done grabbing dependencies!"

###############################################################################
# Overwrite the existing version of LuaJIT in the MOAI folder:
###############################################################################

echo "Adjusting MOAI LuaJIT version..."

cd "$BASE_FOLDER"

LUAJIT="$BASE_FOLDER/$EXTERNAL_DEPENDENCIES_FOLDER/luajit-2.0"
MOAI_DEV="$BASE_FOLDER/$EXTERNAL_DEPENDENCIES_FOLDER/moai-dev"

# Use wildcard expansion to find the LuaJIT folder:
MOAI_DEV_LUAJIT=$(echo "$EXTERNAL_DEPENDENCIES_FOLDER/moai-dev/3rdparty/LuaJIT"*)

# Replace the existing LuaJIT folder:
echo "Replacing $MOAI_DEV_LUAJIT with $LUAJIT" | colorify $LIGHT_BLUE
rm -rf "$MOAI_DEV_LUAJIT"
cp -r "$LUAJIT" "$MOAI_DEV_LUAJIT"
echo "Replaced $MOAI_DEV_LUAJIT with $LUAJIT" | colorify $YELLOW

###############################################################################
# Place all Lua dependencies into a folder, called 'lua-deps'.
# Additionally, package this into a single '.zip' file, called 'lua-deps.zip'.
###############################################################################

MOONSCRIPT="$BASE_FOLDER/$EXTERNAL_DEPENDENCIES_FOLDER/moonscript"
PENLIGHT="$BASE_FOLDER/$EXTERNAL_DEPENDENCIES_FOLDER/Penlight"
BUSTED="$BASE_FOLDER/$EXTERNAL_DEPENDENCIES_FOLDER/busted"
MOBDEBUG_DOT_LUA="$BASE_FOLDER/$BUNDLED_DEPENDENCIES_FOLDER/mobdebug/mobdebug.lua"
LTN12_DOT_LUA="$BASE_FOLDER/$BUNDLED_DEPENDENCIES_FOLDER/ltn12.lua"
SIERRA_DEBUG="$BASE_FOLDER/$BUNDLED_DEPENDENCIES_FOLDER/sierradebug"
LUA_REPL="$BASE_FOLDER/$BUNDLED_DEPENDENCIES_FOLDER/lua-repl"

cd "$BASE_FOLDER/builds/"

rm -rf lua-deps/
mkdir -p lua-deps/

# Moonscript:
cp -r "$MOONSCRIPT/moonscript" lua-deps/
# Penlight:
cp -r "$PENLIGHT/lua/pl" lua-deps/
# 'Busted' unit testing framework:
cp -r "$BUSTED/src" lua-deps/busted
# MOB Lua debugger:
cp "$MOBDEBUG_DOT_LUA" lua-deps/
# ltn12 fix for luasocket:
cp "$LTN12_DOT_LUA" lua-deps/
# Sierra Lua debugger:
cp "$SIERRA_DEBUG"/* lua-deps/
# LuaJIT Lua API:
cp -r "$LUAJIT/src/jit/" lua-deps/
# Lua REPL:
cp -r "$LUA_REPL/repl" lua-deps/
cp "$LUA_REPL/repl.lua" lua-deps/

cd lua-deps/

# Create a '.zip' file, obeying the directory structure:
zip lua-deps.zip $(find . -name '*.lua')
# Move it to the parent folder:
mv lua-deps.zip ..
