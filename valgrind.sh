#!/bin/bash

valgrind \
	--tool=memcheck \
	--leak-check=full \
	--leak-resolution=high \
	--track-origins=yes \
	--show-reachable=yes \
	--log-file=$1 \
	./$2 \
;

grep -A1 "valgrind" $1 | grep $2 >&2;
