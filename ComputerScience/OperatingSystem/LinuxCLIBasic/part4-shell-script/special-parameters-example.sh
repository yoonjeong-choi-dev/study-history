#!/bin/bash

# print four parameters
print_params(){
    echo "\$1 = $1"
    echo "\$2 = $2"
    echo "\$3 = $3"
    echo "\$4 = $4"
}

# print with special parameters
pass_params(){
    # $* :
    echo -e "\n" '$* :'
    print_params $*

    # "$*" :
    echo -e "\n" '"$*" :'
    print_params "$*"

    # $@ :
    echo -e "\n" '$@ :'
    print_params $@

    # "$@" :
    echo -e "\n" '"$@" :'
    print_params "$@"
}


# main test
pass_params "word" "words with space"