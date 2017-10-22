#!/usr/bin/env python
# -*- coding:utf-8 -*-

import os
import shutil


def InsertIndexInSrcfilename(srcfilename, index):
    nPos = srcfilename.index('.')
    return srcfilename[0: nPos] + str(index) + srcfilename[nPos:]

def collect_file(SrcFileDir, DstFileDir, index = 0):
    for root, dirs, files in os.walk(SrcFileDir):
        for file in files:
            srcfilename = os.path.split(file)[-1]
            if srcfilename == 'preview.jpg':
                destfilename = InsertIndexInSrcfilename(srcfilename, index)
                print(destfilename)
                shutil.copyfile(os.path.join(root, file), os.path.join(DstFileDir, destfilename))
                index += 1
        for dir in dirs:
            collect_file(dir, DstFileDir)
            

def main():
    SrcFileDir = r'./2017qianyi'
    DstFileDir = r'./CollectData/'
    
    if not os.path.exists(DstFileDir):
        os.makedirs(DstFileDir)
    DstFileDir = os.path.abspath(DstFileDir)
    
    print(DstFileDir)
    collect_file(SrcFileDir, DstFileDir)

if __name__ == '__main__':
    main()