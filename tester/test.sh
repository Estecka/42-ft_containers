#!/bin/zsh

if [ -z "$@" ]
then
	TESTS=(
		vector
		list
		stack
		queue
		map
	);
else
	TESTS="$@";
fi

make header_test || exit;
make all || exit;
echo;

for t in $TESTS;
do;
	echo "== $t ==";

	./valgrind.sh $t.ft.leaks.log  $t.ft.out  > $t.ft.log;
	./valgrind.sh $t.std.leaks.log $t.std.out > $t.std.log;

	diff $t.std.log $t.ft.log && echo "OK";

	grep <$t.ft.leaks.log "no leaks"         | sed -e 's/==[[:digit:]]*== //';
	grep <$t.ft.leaks.log "LEAK SUMMARY" -A5 | sed -e 's/==[[:digit:]]*== //';
	echo;
done;
