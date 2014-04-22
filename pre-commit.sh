#!/bin/bash


find . -path ./.git -prune -o -type f ! -name '*.sh' -executable -exec rm {} \;
