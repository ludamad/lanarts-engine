#!/bin/bash

###############################################################################
# Run the Lanarts runner, locating the necessary dependencies.
###############################################################################

set -e # Robustness
set -u # Robustness

export LANARTS_BASE_FOLDER=__BASE_FOLDER # To be replaced by --install!

echo "$@"
"$LANARTS_BASE_FOLDER/moai" "$LANARTS_BASE_FOLDER/loader.lua" "$LANARTS_BASE_FOLDER" "$@"
