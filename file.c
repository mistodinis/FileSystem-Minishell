
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "file.h"


Directory *create()
{
return initDirectory("/" , NULL);
}

void delete(Directory *root)
{
    if(root->node != NULL)
        root->node = deleteAllFiles(root->node);

    if(root->nodeF != NULL){
       
        while(root->nodeF != NULL){
            Folder *tmp = root->nodeF;
            
            if(root->nodeF->next == NULL)
                break;
            
            root->nodeF = root->nodeF->next;
           
            free(tmp->dir->name);
            free(tmp->dir);
            free(tmp);
        }
    }

    free(root->name);
    free(root); 
}


Directory *touch(char *filename , char *content , Directory *currDir){

    File *f = initFile(filename , content , currDir);
    
    Fisier *tmp = fisInitList(f);
   
    if(currDir->node == NULL){
        currDir->node = tmp;
   
    }else{
        
        Fisier *contor = currDir->node;
       
        if(contor->next == NULL){
            if(strcmp(contor->f->name , f->name) > 0){

                 tmp->next = contor;
                 
                 currDir->node = tmp;

              return currDir;
           }else{
               
               contor->next = tmp;

               return currDir;
           }
        }

        if(strcmp(contor->f->name , f->name) > 0){

            tmp->next = contor;
           
            currDir->node = tmp;

            return currDir;
        }


        Fisier *prev = currDir->node;
        
        contor = contor->next;
       
        while(contor != NULL){
           
           if(strcmp(contor->f->name , f->name) > 0 ){

            prev->next = tmp;
            
            tmp->next = contor;
            
            return currDir;
          }
          if(contor->next != NULL){
           
            contor = contor->next;
            
            prev = prev->next;
          }
          else
            break;
        }

        contor->next = tmp;
    }
    return currDir;
}

Directory *mkdir(char *name , Directory *currDir){

    Folder *tmp = foldInitList(initDirectory(name,currDir));
    
    if(currDir->nodeF == NULL){
        currDir->nodeF = tmp;
    
    }else{
       
        Folder *counter = currDir->nodeF;

        if(counter->next == NULL){
            if(strcmp(counter->dir->name , tmp->dir->name) > 0){
  
                tmp->next = counter;
                
                currDir->nodeF = tmp;

                return currDir;
            }else{

                counter->next = tmp;

                return currDir;
            }
        }
        
        if(strcmp(counter->dir->name , tmp->dir->name) > 0){
            
            tmp->next = counter;
            
            currDir->nodeF = tmp;

            return currDir;
        }

        Folder *prev = currDir->nodeF;
        
        counter = counter->next;
        
        while(counter != NULL){
             if(strcmp(counter->dir->name , tmp->dir->name) > 0){

                prev->next = tmp;
                
                tmp->next = counter;

               return currDir;
            }

            if(counter->next != NULL){
               
                counter = counter->next;
                
                prev = prev->next; 
            }else
                break;
    
        }
        counter->next = tmp;
    }
    return currDir;
}


void ls(Directory *currDir){

    if(currDir == NULL)
        return;

    if(currDir->node == NULL){
        if(currDir->nodeF == NULL){

            printf("\n");

            return;
        }
        else{
            
            printDirectories(currDir->nodeF);
        }
    }else{

        if(currDir->nodeF == NULL){
            printFiles(currDir->node);
        }
        else{

            printFiles(currDir->node);
           
            printDirectories(currDir->nodeF);
        }
    }
    printf("\n");
}

void pwd(Directory *currDir){

    Directory *temp = currDir;

    if(temp->parentDir == NULL){

        printf("/");
       
        return;
    }

    if(strcmp(temp->parentDir->name , "/") == 0){

        printf("/%s" , temp->name);
       
        return;
    }
        
    pwd(temp->parentDir);

    printf("/%s" , temp->name);
}

Directory *changeDirectory(char *name , Directory *currDir){

    if(currDir == NULL)
        return NULL;

    if(strcmp(name , ".") == 0)
        return currDir;

    if(strcmp(name , ".." ) == 0){
        if(currDir->parentDir == NULL)

            return currDir;
        else{

            currDir = currDir->parentDir;

            return currDir;
        }
    }

    Folder *tmp = currDir->nodeF;

    if(tmp == NULL){
        
        printf("Cannot move to '%s': No such directory!\n", name);
       
        return currDir;
    }

    while(tmp != NULL){

        if(strcmp(tmp->dir->name , name) == 0 ){
          
            currDir = tmp->dir;

            return currDir;
        }

        if(tmp->next == NULL)
            break;

        tmp = tmp->next;
    }

    printf("Cannot move to '%s': No such directory!\n", name);
    
    return currDir;
}

int level = 1;

void tree(Directory *currDir){

    if(currDir == NULL)
        return;
    
    Directory *tmp = currDir;

    if(tmp != NULL){

        for(int i = 1;i <level;i++)
            printf("    ");

        printf("%s\n" , tmp->name);

        Fisier *fis = tmp->node;
        
        Folder *fold = tmp->nodeF;
        
        if ( fis == NULL ){

            if(fold == NULL){

                return;

            }else{

                while(fold != NULL){
                   
                    level++;
                   
                    tree(fold->dir);
                   
                    level--;
                    
                    if(fold->next == NULL)
                        break;
                    
                    fold = fold->next;
                }
            }
        }else{

            while (fis != NULL){
               
                for(int i = 1;i <=level;i++)
                    printf("    ");

                printf("%s\n" , fis->f->name);
                
                if(fis->next == NULL)
                    break;
                
                fis = fis->next;
            }

            if(fold == NULL){
                return;
            }else{
               
                while(fold != NULL){
                    
                    level++;
                    
                    tree(fold->dir);
                    
                    level--;
                    
                    if(fold->next == NULL)
                        break;
                    
                    fold = fold->next;
                }
            }
        }
    } 
}

Directory *removeFile(char *name , Directory *currDir){
    
    currDir->node = deleteFile(name , currDir->node);

    return currDir;
}

Directory *removeDirectory( Directory *currDir){

    if(currDir == NULL)
        return NULL;

    if(currDir->node != NULL)
    
        currDir->node = deleteAllFiles(currDir->node);

    if(currDir->nodeF == NULL){
        
        free(currDir->name);
        
        free(currDir);
        
        return NULL;
    }
        
    while(currDir->nodeF != NULL){
       
        Folder *tmp = currDir->nodeF;
        
        currDir->nodeF->dir = removeDirectory( currDir->nodeF->dir);
        
        if(currDir->nodeF->next == NULL)
            break;
        
        currDir->nodeF = currDir->nodeF->next;
        
        free(tmp->dir);
        
        free(tmp);
    }

    return NULL;
}

Directory *rmdir(char *name , Directory *currDir){

    if(currDir == NULL)
        return NULL;

    if(currDir->nodeF == NULL){
        
        printf("Cannot remove '%s': No such directory!\n" , name);
        
        return currDir;
    }

    if(currDir->nodeF->next == NULL){

         if(strcmp ( currDir->nodeF->dir->name , name) == 0){
           
             currDir->nodeF->dir = removeDirectory(currDir->nodeF->dir);
           
             free(currDir->nodeF);
           
             currDir->nodeF = NULL;
           
             return currDir;
         }else{
             
            printf("Cannot remove '%s': No such directory!\n" , name);

            return currDir;
         }
    }else{

         if(strcmp ( currDir->nodeF->dir->name , name) == 0){
            
             currDir->nodeF->dir = removeDirectory(currDir->nodeF->dir);
            
             free(currDir->nodeF);
            
             currDir->nodeF = currDir->nodeF->next;
            
             return currDir;
         }
    }
    Folder *tmp = currDir->nodeF;
    
    Folder *prev = currDir->nodeF;
   
    tmp = tmp->next;

    while(tmp != NULL){

        if(strcmp(tmp->dir->name , name) == 0){
                
                prev->next = tmp->next;
                
                tmp->dir = removeDirectory(tmp->dir);
               
                free(tmp);

                return currDir;
        }

        if(tmp->next == NULL)
            break;
        
        tmp = tmp->next;
        
        prev = prev->next;
    }

     printf("Cannot remove '%s': No such directory!\n" , name);

     return currDir;
}

