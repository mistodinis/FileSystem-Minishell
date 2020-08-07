
#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct fisier Fisier;
typedef struct folder Folder;


typedef struct Directory {
    // The name of the directory
    char *name;

    // The list of files of the current directory
    Fisier *node;
    // The list of directories of the current directory
    Folder *nodeF;
    // The parent directory of the current directory (NULL for the root directory)
    struct Directory *parentDir;
} Directory;

// DO NOT MODIFY THIS STRUCTURE
typedef struct File {
    // The name of the file
    char *name;

    // The size of the file
    int size;

    // The content of the file
    char *data;

    // The directory in which the file is located
    Directory *dir;
} File;

typedef struct fisier{

	File *f;

	struct fisier* next;
}Fisier;

typedef struct folder{

	Directory *dir;

	struct folder *next;
}Folder;


Directory *create();

void delete(Directory *root);

Directory *touch(char *filename , char *content , Directory *currDir);

Directory *mkdir(char *name , Directory *currDir);

void ls(Directory *currDir);

void pwd(Directory *currDir);

Directory *changeDirectory(char *name , Directory *currDir);

void tree(Directory *currDir);

Directory *removeFile(char *name , Directory *currDir);

Directory *removeDirectory( Directory *currDir);

Directory *rmdir(char *name , Directory *currDir);

#endif /* __FILE_H__ */
