#!/bin/bash

array_dir=("Server" "Server/Home" "Server/Class")
array_class=("Server/Class/ClassA" "Server/Class/ClassB" "Server/Class/ClassC")
array_class_tmpdir=("提出物" "教材");

umask 000

for dir in "${array_dir[@]}"
do
	mkdir $dir
done

for dir in "${array_class[@]}"
do
	mkdir $dir
	for tmp in "${array_tmpdir[@]}"
	do
		mkdir "$dir$tmp"
	done
done
