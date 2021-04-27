#!/bin/zsh

TESTS=(
	vector
);

make all || exit;

for t in $TESTS;
do;
	echo "== $t ==";
	./valgrind.sh $t.ft.leaks.log  $t.ft.out  > $t.ft.log;
	./valgrind.sh $t.std.leaks.log $t.std.out > $t.std.log;
	diff $t.std.log $t.ft.log && echo "OK";
done;
