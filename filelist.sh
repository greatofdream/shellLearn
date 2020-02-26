#!/bin/bash
ls -l|grep '^d'|wc -l
ls -l|grep '^-'|wc -l
workdir=$WORKDIR
for dir in `ls $workdir`
do
	# echo $workdir/$dir
	if [ -d $workdir/$dir ]
	then
		du -s $workdir/$dir
	fi
done

