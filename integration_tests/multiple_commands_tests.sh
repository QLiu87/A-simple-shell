#!/bin/sh


INPUTS=("echo ls ; echo hello && echo test || echo world ; git status
")
 
    echo "Testing echo ls ; echo hello && echo test || echo world; git status
"
    ./multiple_command ${INPUTS[0]}
  










