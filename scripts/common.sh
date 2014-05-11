#!/bin/bash

###############################################################################
# Common parameters and settings for shell scripts used in Lanarts.
###############################################################################

set -u #Ensure undefined variables are an error
set -e # Good practice -- exit completely on any bad exit code

SCRIPT_FOLDER='scripts'
DEPENDENCIES_FOLDER='dependencies'
EXTERNAL_DEPENDENCIES_FOLDER='dependencies/external'
