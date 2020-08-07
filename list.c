
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "file.h"


Fisier * fisInitList(File *f)
{

    Fisier *new_file =  malloc(sizeof(Fisier));

    new_file->f = f;
    
    new_file->next = NULL;

    return new_file;
}

File * initFile(char *name ,  char *data , Directory *dir)
{

    File *f =  malloc(sizeof(struct File));
    
    f->size = strlen(data);
    
    f->name = strdup(name);
    
    f->data = strdup(data);
    
    f->dir = dir;

    return f;
}


Directory * initDirectory(char *name , Directory *parent_dir)
{

    Directory *new_directory = malloc(sizeof(Directory));

    new_directory->name = strdup(name);
    
    new_directory->node = NULL;
    
    new_directory->nodeF = NULL;
    
    if(parent_dir != NULL){

        new_directory->parentDir = parent_dir;

    }else{

        new_directory->parentDir = NULL;
    }

    return new_directory;
}

Folder * foldInitList(Directory *dir)
{

    Folder *new_folder = malloc(sizeof(Folder));

    new_folder->dir = dir;
    
    new_folder->next = NULL;

    return new_folder;
}


Fisier *deleteFile(char *name , Fisier *source){

    if(source == NULL){

        printf("Cannot remove '%s': No such file!\n" , name);
       
        return NULL;
    }

    if(source->next == NULL){

        if(strcmp(source->f->name , name) == 0){
           
            free(source->f->name);
           
            free(source->f->data);
            
            free(source->f);
            
            free(source);
            
            return NULL;

        }else{

            printf("Cannot remove '%s': No such file!\n" , name);
           
            return source;
        }
    }else{

        if(strcmp(source->f->name , name) == 0){
           
            Fisier *tmp = source;
           
            source = source->next;
           
            free(tmp->f->name);
           
            free(tmp->f->data);
           
            free(tmp->f);
            
            free(tmp);
           
            return source;
        }
    }

    Fisier *tmp = source;
    
    Fisier *prev = source;
    
    tmp = tmp->next;

    while(tmp != NULL){

        if(strcmp (tmp->f->name , name ) == 0){
           
            prev->next = tmp->next;
           
            free(tmp->f->name);
           
            free(tmp->f->data);
           
            free(tmp->f);
           
            free(tmp);
           
            return source;
        }

        if(tmp->next == NULL)
            break;

        tmp = tmp->next;
        
        prev = prev->next;
    }
    
    printf("Cannot remove '%s': No such file!\n" , name);
    return source;

}


Fisier *deleteAllFiles(Fisier *source){

    if(source == NULL)

        return NULL;

    if(source->next == NULL){
      
        free(source->f->name);
        
        free(source->f->data);
        
        free(source->f);
        
        free(source);
        
        return NULL;
    }

    while(source != NULL){
        
        Fisier *tmp = source;
        
        if(source->next == NULL)
            break;
        
        source = source->next;
       
        free(tmp->f->name);
        
        free(tmp->f->data);
        
        free(tmp->f);
        
        free(tmp);
    }

    return NULL;
}

void printFiles(Fisier *files)
{

    if(files == NULL)
        return;

    if(files->next == NULL){

        printf("%s " , files->f->name);
        
        return;
    }

    Fisier *tmp = files;
   
    while(tmp != NULL){
       
        printf("%s " , tmp->f->name);
       
        if(tmp->next != NULL)
            tmp = tmp->next;
        else
            break;
    }

}

void printDirectories(Folder *folders)
{

    if(folders == NULL)
        return;

    if(folders->next == NULL){
       
        printf("%s " , folders->dir->name);
       
        return;
    }
    
    Folder *tmp = folders;
    
    while(tmp != NULL){
       
        printf("%s " , tmp->dir->name);
        
        if(tmp->next != NULL)
            tmp = tmp->next;
        else
            break;
    }
}
