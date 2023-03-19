#!/bin/bash

array_file=("Server/Home/OASYS2204/SQL.sql" "Server/Home/OASYS2204/C言語.c" "Server/Home/OASYS2204/実行ファイル.o" "Server/Home/OASYS2204/テストディレクトリ" "Server/Home/OASYS2204/C++.cpp")

umask 000

for file in "${array_file[@]}"
do
	touch $file
done
