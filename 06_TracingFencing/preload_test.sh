#!/usr/bin/env bash

export LD_LIBRARY_PATH=$PWD:${LD_LIBRARY_PATH}

cat test_file > test_file_PROTECT

LD_PRELOAD=protect.so ./move test_file_PROTECT test_file_tmp

if test -f "test_file_PROTECT"; then
    echo ""
    echo "Preload test passed"
    echo ""
    
    rm test_file_tmp test_file_PROTECT
    exit 0
else
    echo ""
    echo "Preload test failed"
    echo ""
    
    rm test_file_tmp
    exit 1
fi
