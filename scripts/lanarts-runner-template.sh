#!/bin/bash

###############################################################################
# Run the Lanarts runner, locating the necessary dependencies.
###############################################################################

set -e # Robustness
set -u # Robustness

export LANARTS_BASE_FOLDER=__BASE_FOLDER # To be replaced by --install!


###############################################################################
# Bash function to check for a flag in 'args' and remove it.
# Treats 'args' as one long string. 
# Returns true if flag was removed.
###############################################################################

args="$@" # Create a mutable copy of the program arguments
function handle_flag(){
    flag=$1
    local new_args=""
    local got
    got=1 # False!
    for arg in $args ; do
        if [ $arg = $flag ] ; then
            args="${args/$flag/}"
            got=0 # True!
        else
            new_args="$new_args $arg"
        fi
    done
    args="$new_args"
    return $got # False!
}

if handle_flag "--gdb" ; then
    gdb --args "$LANARTS_BASE_FOLDER/moai" "$LANARTS_BASE_FOLDER/loader.lua" "$LANARTS_BASE_FOLDER" $args
else
    "$LANARTS_BASE_FOLDER/moai" "$LANARTS_BASE_FOLDER/loader.lua" "$LANARTS_BASE_FOLDER" $args
fi
