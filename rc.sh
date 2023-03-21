#!/bin/sh

dn=$(dirname $0)

run () {
	$dn/dsv $@ &
}

run $PWD/empty/empty

wait $!
