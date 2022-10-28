#!/bin/bash

green="\e[42;1;36m"
reset="\e[0m"
max=20

function ProgressBar
{
    let _progress=(${1}*100/${2}*100)/100
    let _done=(${_progress}*4)/10
    let _left=40-$_done
    _fill=$(printf "%${_done}s")
    _empty=$(printf "%${_left}s")
	printf "\rProgress : [${_fill// /${green} ${reset}}${_empty// / }] ${_progress}%%"
}

it=${max}
while [ ${it} != 0 ]
do
	./a.out > /dev/null
	ProgressBar $((max - it)) ${max}
	it=$((it-1))
done
ProgressBar $((max - it)) ${max}
