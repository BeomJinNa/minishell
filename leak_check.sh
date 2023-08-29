#!/bin/bash

if [ $# -ne 1 ]; then
   echo "usage: ./check_leaks <pid>"
   exit
fi   

while [ true ]; do
	leaks $1
	sleep 1
done
