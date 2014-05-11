#!/bin/bash

###############################################################################
# Load the dependencies necessary for Lanarts.
# We target specific commits, and update as necessary.
###############################################################################

set -e # Good practice -- exit completely on any bad exit code

# Set common variables and shell-script safety settings
source $(dirname "$0")/common.sh 

# Enter dependencies/ folder, where we will clone into
if [ $(basename "$(pwd)") == $SCRIPT_FOLDER ] ; then cd .. ; fi

# Ensure external dependency folder exists, and enter it:
mkdir -p $EXTERNAL_DEPENDENCIES_FOLDER
cd $EXTERNAL_DEPENDENCIES_FOLDER

echo "Grabbing dependencies ..." 

# Clone each dependency, based on the repository name and a given commit:
for dep in \
    'https://github.com/LuaDist/busted 5cb536a6a79e8428d9cc922ab1ad07650d104dae' \
    'https://github.com/LuaDist/lpeg baf0dc90b9278360be719dbfb8e56d34ce3c61bd'  \
    'https://github.com/moai/moai-dev 96dd6bea85376eb15ec66a3a7675ffef405d07fa' \
    'https://github.com/stevedonovan/Penlight 3d905f096053da08c89a37cce35d96b7db1817ab' \
    'http://luajit.org/git/luajit-2.0.git 392b6c94ae4b969f7fc74b21501b5e884c002892' 
do
    # Split our combined URL+commit:
    set -- $dep ; URL=$1 ; commit=$2 ; folder=$(basename "$URL" | sed 's/\.git$//')

    echo "Cloning $URL into \"$EXTERNAL_DEPENDENCIES_FOLDER\"" | colorify $LIGHT_BLUE

    # Avoid doing anything if the location already exists:
    if [ -e $folder ] ; then
        echo "$URL already exists. Continuing." | colorify $YELLOW
        continue
    fi

    # If the location did not exist, clone into it and checkout the desired commit.
    git clone "$URL"

    echo "Checking out commit \"$commit\" for \"$URL\" ..." | colorify $LIGHT_BLUE
    cd "$folder"
    git checkout --quiet "$commit"
    echo "Checked out commit \"$commit\" for \"$URL\"." | colorify $BLUE
    cd ..
done

echo "Done grabbing dependencies!"
