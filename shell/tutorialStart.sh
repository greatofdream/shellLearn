#!/bin/sh
# Tutorial-start

# Time:
# '`' use to contain the command
echo `date`

# Environment Variable
echo $WORKDIR

# File:
# printf has more formats to use
printf "currentDir:%-10s; currentUser:%-10s;shell:%-5s\n" `pwd` `whoami` `echo $SHELL

#`Storage
workdir=`pwd
# file space usage`
du $wordir
# filesystem space usage
df $workdir

# System

sleep 5s
date
