#!/usr/bin/env bash

echo 'aaa b0 bb c123cc' | sed 's/a*[^a-z]/-\n-\0-\n-/' > gt
./esub 'a*[^a-z]' '-\n-\0-\n-' 'aaa b0 bb c123cc' > res

cmp res gt

###

echo 'aaabbbccc' | sed 's/(a*(b*))/\2-\1=/' > gt
./esub '(a*(b*))' '\2-\1=' 'aaabbbccc'

cmp res gt

###

echo "== Var01.field01 ==" | sed -E 's/([[:alnum:].]+)/\n\\n\\\n"\1"/' > gt
./esub '([[:alnum:].]+)' '\n\\n\\\n"\1"' '== Var01.field01 ==' > res

cmp res gt

###

rm res gt