#!/bin/bash
encodefilename(){
	sf=$1
	basedf=$(echo $sf |tr "/" "*" )
	return $basedf
}

decodefilename(){
	sf=$1
	basedf=$(echo $mvdf | tr "*" "/" )
	return $basedf
}


echo $*
	for i in "$@" ;do
#		echo  "${i:0:1}" 
#		echo $abc
		if [ "-" != "${i:0:1}" ]; then
			echo $i
		fi
	done
exit 0
dfn=/home/zhdai/rm
encodefilename $dfn 
encfn=$? 
echo $encfn
