#!/usr/bin python
import os
import argparse
import datetime, time
if __name__=="__main__":
    argpsr = argparse.ArgumentParser(description='file list')
    argpsr.add_argument('-d',dest='dir',help='input dir')
    args = argpsr.parse_args()
    if args.dir:
        curDir = args.dir
    else:
        curDir = os.getcwd()
    print('begin search {}'.format(curDir))
    files = os.listdir(curDir)
    for f in files:
        f = curDir +'/'+ f
        if os.path.isdir(f):
            print(f)
            if os.path.getmtime(f)>time.mktime(datetime.date(2020,1,1).timetuple()):
                print('{} is modified after 2020y'.format(f))
    print('end search')

