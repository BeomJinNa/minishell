#!/bin/bash

if [ $# -ne 1 ]; then
   echo "usage: ./check_leaks <pid>"
   exit
fi   

while [ true ]; do
	leaks $1 | grep "total leaked bytes."
	sleep 1
done
