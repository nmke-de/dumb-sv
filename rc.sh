#!/bin/sh

dn=$(dirname $0)

run () {
	$dn/sv $@ &
}

run /usr/bin/scalp /home/nathan/foo
run /home/nathan/Dokumente/DaFUn/src/as/emptyloop/empty
