#!/usr/bin/env bash

echo "test" > tmp
sha1sum < tmp | cut -d' ' -f1 > gt
echo SHA1 tmp | ./rhasher | tail -n +2 > res

cmp res gt

###

echo "test" > tmp
md5sum < tmp | cut -d' ' -f1 > gt
echo MD5 tmp | ./rhasher | tail -n +2 > res

cmp res gt

###

rm res gt tmp