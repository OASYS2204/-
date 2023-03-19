#!/bin/bash

nr_sym_classA=5
nr_sym_classB=3
nr_sym_classC=3

array_sym=("Server/Home/OASYS0001/ClassA" "Server/Home/OASYS0002/ClassA" "Server/Home/OASYS2204/ClassA" "Server/Home/OASYS2222/ClassA" "Server/Home/OASYS2208/ClassA" "Server/Home/OASYS0002/ClassB" "Server/Home/OASYS2204/ClassB" "Server/Home/OASYS2208/ClassB" "Server/Home/OASYS0003/ClassC" "Server/Home/OASYS2204/ClassC" "Server/Home/OASYS2222/ClassC")

for sym in "${array[@]}"
do
	if [ nr_sym_classA -gt 0 ]
	then
		ln -s $sym "Server/Class/ClassA"
		let "nr_sym_classA--"
		continue
	fi
	
	if [ nr_sym_classB -gt 0 ]
	then
		ln -s $sym "Server/Class/ClassB"
                let "nr_sym_classB--"
                continue
	fi

	if [ nr_sym_classC -gt 0 ]
        then
                ln -s $sym "Server/Class/ClassC"
                let "nr_sym_classC--"
                continue
        fi
done

