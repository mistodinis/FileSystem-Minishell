

#ifndef __LIST_H__
#define __LIST_H__


#include <stdio.h>
#include <stdlib.h>
#include "file.h"

Fisier * fisInitList(File *f);

File * initFile(char *name ,  char *data, Directory *dir);

Directory * initDirectory(char *name , Directory *parent_dir);

Folder * foldInitList(Directory *dir);

Fisier *deleteFile(char *name , Fisier *source);

Fisier *deleteAllFiles(Fisier *source);

void printFiles(Fisier *files);

void printDirectories(Folder *folders);


#endif