#!/bin/bash

###############################################################################
# Common parameters and settings for shell scripts used in Lanarts.
###############################################################################

set -u #Ensure undefined variables are an error
set -e # Good practice -- exit completely on any bad exit code

###############################################################################
# Directory structure.
###############################################################################

SCRIPT_FOLDER='scripts'
DEPENDENCIES_FOLDER='dependencies'
EXTERNAL_DEPENDENCIES_FOLDER='dependencies/external'

###############################################################################
# Colour constants for 'colorify'.
###############################################################################

BLACK='0;30'
DARK_GRAY='1;30'
BLUE='0;34'
LIGHT_BLUE='1;34'
GREEN='0;32'
LIGHT_GREEN='1;32'
CYAN='0;36'
LIGHT_CYAN='1;36'
RED='0;31'
LIGHT_RED='1;31'
PURPLE='0;35'
LIGHT_PURPLE='1;35'
BROWN='0;33'
YELLOW='1;33'
LIGHT_GRAY='0;37'
WHITE='1;37'

###############################################################################
# Helper functions for conditionally coloring text.
###############################################################################

function is_mac() {
    if [ "$(uname)" == "Darwin" ]; then
        return 0 # True!
    else
        return 1 # False!
    fi
}

# Bash function to apply a color to a piece of text.
function colorify() {
    if is_mac ; then
        cat
    else
        local words;
        words=$(cat)
        echo -e "\e[$1m$words\e[0m"
    fi 
}


