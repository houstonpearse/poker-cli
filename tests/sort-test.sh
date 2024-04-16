#!/bin/zsh
function test () {
    a=$(mktemp)
    ./poker-cli sort < testdata/$1.txt > a
    if diff a testdata/$1-out.txt; then 
        echo "\u2705 Test $1 Passed\n"
    else
        echo "\u274C Test $1 Failed\n"
    fi
    rm a
}
test straight-flush
test four-of-a-kind
test full-house
test flush
test straight
