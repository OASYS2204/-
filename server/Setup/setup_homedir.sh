#!/bin/bash

NR_STUDENT=23
NR_TEACHER=10

umask 000

i=1
while [ $i -le 9 ]
do
	mkdir "Server/Home/OASYS220$i"
        let "i++"
done

i=10
while [ $i -le $NR_STUDENT ]
do
	mkdir "Server/Home/OASYS22$i"
        let "i++"
done

i=1
while [ $i -le 9 ]
do      
        mkdir "Server/Home/OASYS000$i"
        let "i++"
done

i=10
while [ $i -le $NR_TEACHER ]
do      
        mkdir "Server/Home/OASYS00$i"
        let "i++"
done
