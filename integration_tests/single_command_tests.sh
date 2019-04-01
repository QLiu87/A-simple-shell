#!/bin/sh

INPUTS=("echo Hello" "ls src" "git status")
 
    echo "Testing echo Hello"
    ./CommentedComand ${INPUTS[0]}
    echo "Testing ls src"
    ./CommentedComand ${INPUTS[1]}
    echo "Testing git status"
    ./CommentedComand ${INPUTS[2]}

