#!/usr/bin/env bash

## GETS THE CURRENT MODULE ROOT DIRECTORY
MOD_UTIL_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"

source $MOD_UTIL_ROOT"/conf/conf.sh.dist"

if [ -f $MOD_UTIL_ROOT"/conf/conf.sh" ]; then
    source $MOD_UTIL_ROOT"/conf/conf.sh"
fi
