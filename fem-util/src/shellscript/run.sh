#!/bin/bash
# pushd `dirname $0` > /dev/null
##############################
### variable setting

red=31
yellow=33
cyan=36

###
colored(){
    color=$1
    shift
    echo -e "\033[1;${color}m$@\033[0m"
}

run(){
    "$@"
    result=$?

    if [ $result -ne 0 ]
    then
	echo -n $(colored $red "Failed: ")
	echo -n $(colored $yellow "$@")
	echo $(colored $cyan " [$PWD]")
	exit $result
    fi

    return 0
}

##############################
# popd > /dev/null
