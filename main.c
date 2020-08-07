
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "file.h"

int main(){

	// Directory *dir;
	
//	printf("%s  /// \n %d  /// \n %s " , f->name , f->size , f->data);
	
	
	//Directory *root = create();

	// File *f = initFile("Ana canta"  , "__--__---dawa" , root);
	// printf("size = %d " , f->size);

//	root = touch("Gigela " , "Anacanta" , root);

	// printf("%s" , root->node->f->name);
	// printf("%s  " ,  root->name);

//	root = touch("Anela" , "Gioconda" , root);
	//root->node = root->node->next;
	//	printf("%s" , root->node->f->name);

//	root = touch ("Bella" , "DAs" , root);

	//printf(" #2 %s " , root->node->f->name);

//	root = mkdir("cantaaaaaa" , root);

//	printf("\n %s " , root->nodeF->dir->name);

///	root = mkdir("aantaaaaaa" , root);


//	root = mkdir("gAW" , root);

//	root = mkdir("zad" , root);

//	root = mkdir("barbarosa" , root);
//	printf("\n %s " , root->nodeF->dir->name);

	// printFiles(root->node);
	// printDirectories(root->nodeF);
//	ls(root);

//	root = delete(root);

	//printf("%s " , root->name);

//	if(root == NULL) 
//		printf("\n SUCCES" );


Directory *currDir = NULL;

char *s = (char *)malloc(100*sizeof(char));

//s = fgets(s , 100 , stdin);
//printf("%ld " , strlen(s));
// if(s == NULL)
// 	printf("GO");
// puts(s);

char* param[5];

for(int i = 0;i < 5;i++){
	param[i] = calloc(30,sizeof(char));
}
	
int j = 0 , ctr = 0;;


while (1){
	ctr = 0;

	s = fgets(s , 100, stdin);

	if(strlen(s) == 1)
		break;

	for(int i = 0;i < strlen(s) ; i++){

		if(s[i] == ' ' || s[i] == '\0' || s[i] == '\n'){

			param[ctr][j] = '\0';
			ctr++;
			j = 0;
		

		}else{

			param[ctr][j] = s[i];
			j++;
		}
	}

	if(strcmp(param[0] , "create") == 0){

		currDir = create();

		continue;

	}

	if(strcmp(param[0] , "touch") == 0){

		currDir = touch(param[1] , param[2] , currDir);

		continue;
	}

	if(strcmp(param[0] , "ls") == 0){

		ls(currDir);

		continue;
	}

	if(strcmp(param[0] , "mkdir") == 0){

		currDir = mkdir(param[1] , currDir);

		continue;
	}

	if(strcmp(param[0] , "pwd") == 0){

		pwd(currDir);
		
		printf("\n");

		continue;
	}

	if(strcmp(param[0] , "cd") == 0){

		currDir = changeDirectory(param[1] , currDir);

		continue;
	}

	if(strcmp(param[0] , "tree") == 0){

		tree(currDir);

		continue;
	}

	if(strcmp(param[0] , "rm" ) == 0){

		currDir = removeFile(param[1] , currDir);

		continue;
	}

	if(strcmp(param[0] , "rmdir" ) == 0){

		currDir = rmdir( param[1] ,  currDir );

		continue;
	}

	if(strcmp(param[0] , "delete") == 0){

		delete(currDir);
		
		break;
	}

	if(strcmp(param[0] , "help") == 0){

		printf("Available commands :\n1.create fs\n2.touch file content\n3.mkdir dir\n4.ls\n5.pwd\n6.cd dir\n7.rm file\n8.rmdir dir\n9.delete fs\n");
		
		continue;
	}
	
	printf("Invalid command!\nType 'help' for more info!\n");
}
	
	for(int i = 0;i < 5;i++)
		
		free(param[i]);
	
	free(s);

	return 0;

}