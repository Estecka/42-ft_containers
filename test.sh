#!/bin/zsh

TESTS=(
	vector
);

for t in $TESTS;
do;
	echo "== $t ==";
	make $t.ft.out  || continue;
	make $t.std.out || continue;
	./valgrind.sh $t.ft.leaks.log  $t.ft.out  > $t.ft.log;
	./valgrind.sh $t.std.leaks.log $t.std.out > $t.std.log;
	diff $t.std.log $t.ft.log && echo "OK";
done;
