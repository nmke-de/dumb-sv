#!/bin/sh

dn=$(dirname $0)

run () {
	$dn/sv $@ &
}

run $dn/empty/empty

while true
do
	sleep 1
done
