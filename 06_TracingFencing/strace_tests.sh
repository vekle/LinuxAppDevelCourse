#!/usr/bin/env bash

rm test_file_*

###

cat test_file > test_file_tmp

echo ""
strace -e trace=openat -e fault=openat:when=3:error=EACCES ./move test_file_tmp test_file_result
RET=$?

if test ! -f "test_file_tmp" || test -f "test_file_result"; then
    echo "Strace test Open_input failed"
    exit 1
fi

rm test_file_tmp

###

cat test_file > test_file_tmp

echo ""
strace -e trace=openat -e fault=openat:when=4:error=EACCES ./move test_file_tmp test_file_result
RET=$?

if test ! -f "test_file_tmp" || test -f "test_file_result"; then
    echo "Strace test Open_output failed"
    exit 1
fi

rm test_file_tmp

###

cat test_file > test_file_tmp

echo ""
strace -e trace=close -e fault=close:when=3:error=EIO ./move test_file_tmp test_file_result
RET=$?

if test ! -f "test_file_tmp" || test -f "test_file_result"; then
    echo "Strace test Close_input failed"
    exit 1
fi

rm test_file_tmp

###

cat test_file > test_file_tmp

echo ""
strace -e trace=close -e fault=close:when=4:error=EIO ./move test_file_tmp test_file_result
RET=$?

if test ! -f "test_file_tmp" || test -f "test_file_result"; then
    echo "Strace test Close_output failed"
    exit 1
fi

rm test_file_tmp

###

cat test_file > test_file_tmp

echo ""
strace -e trace=read -e fault=read:when=2:error=EPERM ./move test_file_tmp test_file_result
RET=$?

if test ! -f "test_file_tmp" || test -f "test_file_result"; then
    echo "Strace test Read_input failed"
    exit 1
fi

rm test_file_tmp

###

cat test_file > test_file_tmp

echo ""
strace -e trace=write -e fault=write:when=1:error=EPERM ./move test_file_tmp test_file_result
RET=$?

if test ! -f "test_file_tmp" || test -f "test_file_result"; then
    echo "Strace test Write_output failed"
    exit 1
fi

rm test_file_tmp

###

cat test_file > test_file_tmp

echo ""
strace -e trace=unlink -e fault=unlink:when=1:error=EIO ./move test_file_tmp test_file_result
RET=$?

if test ! -f "test_file_tmp" || test ! -f "test_file_result"; then
    echo "Strace test Delete_input failed"
    exit 1
fi

rm test_file_tmp test_file_result

###

cat test_file > test_file_tmp

echo ""
strace -e trace=newfstatat -e fault=newfstatat:when=3:error=EACCES ./move test_file_tmp test_file_result
RET=$?

if test ! -f "test_file_tmp" || test -f "test_file_result"; then
    echo "Strace test Size_input failed"
    exit 1
fi

rm test_file_tmp

###

echo ""
echo "Strace tests passed"
echo ""