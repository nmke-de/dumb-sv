#!/bin/sh

dn=$(dirname $0)

run () {
	$dn/sv $@ &
}

run $PWD/empty/empty

wait $!
