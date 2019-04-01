#!/bin/sh


INPUTS=("(echo 1 && echo 2) || (echo 3 && echo 4)" "(echo 1 ; (echo 2 || (echo 3 && echo 4))) ; (echo 1 || echo 2)" )
 
    echo "(echo 1 && echo 2) || (echo 3 && echo 4)"
    ../src/precedence_shell ${INPUTS[0]}

    echo "(echo 1 ; (echo 2 || (echo 3 && echo 4))) ; (echo 1 || echo 2)"
    ../src/precedence_shell ${INPUTS[1]}

