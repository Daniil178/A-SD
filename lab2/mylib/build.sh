#!/bin/bash

set -e
set -x

cc -c queue.c list.c vector.c -DVector -std=c99
ar cr libvector.a queue.o list.o vector.o

cc -c queue.c list.c vector.c -DList -std=c99
ar cr liblist.a queue.o list.o vector.o

rm queue.o list.o vector.o

cd ..

cc -o lab2_vect.out main.c -I"mylib/" -L"mylib/" -lvector -DVector -std=c99
cc -o lab2_list.out main.c -I"mylib/" -L"mylib/" -llist -DList -std=c99
