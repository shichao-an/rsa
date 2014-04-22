#!/bin/bash

if [ "$(uname -s)" = "Darwin" ]
then
    # OS X
    find . -path ./.git -prune -o -type f ! -name '*.sh' -perm +111 -exec rm {} \;
else
    # Linux
    find . -path ./.git -prune -o -type f ! -name '*.sh' -executable -exec rm {} \;
fi
