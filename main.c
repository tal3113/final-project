#include <stdio.h>
#include <stdbool.h>
#include "calculator.h"
#include "expressionOfTree.h"

#define MAX_LINE_LENGTH 1024

void freeAllocations(HashTable** hash,ERRORS* error,char* LISPTree ){
	if(hash!=NULL){
		destroyHashTable(*hash);
		free(hash);
	}
	if(error!=NULL){
		free(error);
	}
	if(LISPTree!=NULL){
		free(LISPTree);
	}
}
void freeAllocationsInLoop(TreeNode** tree,double* result){
	if(tree!=NULL){
		destroy(*tree);
		free(tree);
	}
	if(result!=NULL){
		free(result);
	}
}
void calcultaing(HashTable** hash,FILE* stream, ERRORS* error,char* LISPTree,bool ifCloseFile){

	TreeNode** tree = (TreeNode**)malloc(sizeof(TreeNode*));
	double* result = (double*)malloc(sizeof(double));
	if(tree == NULL || result ==NULL ){ //if malloc allocation successful
		fprintf(stream,"Unexpected error occurred!\n");
		freeAllocationsInLoop(tree,result);
		return; // returns to the main
	}
	*error = NOERRORS;
	*tree = buildTree( LISPTree , *tree, error); // build the tree

	if((*error)==NOERRORS){
		if(ifCloseFile==true){
			char* expression = getExpressionOfTree(*tree);
			fprintf(stream,"%s\n",expression);
			free(expression);
		}
		*tree=Algorithm(*tree,*hash,error,result);
	}
	if((*error)==UNEXPECTEDERRORS){ //if there was a problem in algorithm or buildTree
		fprintf(stream,"Unexpected error occurred!\n");
	}
	else if((*error)==NOERRORS){ // if the Algorithm call was successful
		if((*tree)->value->type==EQUAL){
			char* value=((*tree)->children[0])->value->str;
			double num=((*tree)->children[1])->value->num;
			fprintf(stream,"%s = %.2f\n",value,num);
			*hash= buildHash (*tree , *hash , error );
			if(*error==UNEXPECTEDERRORS){
				fprintf(stream,"Unexpected error occurred!\n");
			}
		}
		else{
			fprintf(stream,"res = %.2f\n",((*tree)->value)->num);
		}
	}
	else{ //(*error)==INVALIDRESULT
		fprintf(stream,"Invalid Result\n");
	}
	freeAllocationsInLoop(tree,result);
}
void readingFromFile(char* fileName,HashTable** hash,ERRORS* error,FILE* stream,char* LISPTree){

	FILE* fpRead =  fopen(fileName, "r");
	if(fpRead==NULL){
		printf("Variable init file doesn’t exist or is not readable\n");
		freeAllocations(hash,error,LISPTree);
		exit(0);
	}
	else{
		char* line = (char*)calloc(MAX_LINE_LENGTH + 1 ,sizeof(char));

		while ( fgets(line, MAX_LINE_LENGTH, fpRead )!=NULL ){ /* read a line */
			size_t len = strlen(line);
			if (len > 0 && line[len-1] == '\n'){  // remove \n in the end of the line
			  line[--len] = '\0';
			}

			char* token = strtok(line, " \t\r\n"); //geting "var"
			char* var=token;
			token = strtok( NULL, " \t\r\n"); // geting "="
			token = strtok( NULL, " \t\r\n"); // geting "VALUE"
			double num = atoi(token);
			SPListElement data = createElement(var, num);
			hashInsert(*hash , data, error);
			if((*error)!=NOERRORS){
				fprintf(stream,"Unexpected error occurred!\n");
				fclose(fpRead);
				freeAllocations(hash,error,LISPTree);
				exit(0);
			}
			destroyElement(data);
		}
		free(line);
		fclose(fpRead);
	}
}
bool comandLineIsValid(int argc, char *argv[]){

	if(argc== 1){
		return true;
	}

	else if(argc== 3 && (strcmp(argv[1], "-v")==0 || strcmp(argv[1], "-o")==0)){
		if (argv[2][0]== '-'){
			printf("Invalid command line arguments, use [-v filename1] [-o filename2]\n");
			return false;
		}
		return true;
	}

	else if(argc== 5 && strcmp(argv[1], "-v")==0 &&  strcmp(argv[3], "-o")==0){
		if (strcmp(argv[2], argv[4])==0){
			printf("Files must be different\n");
			return false;
		}
		else{
			if ( argv[2][0]=='-' || argv[4][0]=='-'){
				printf("Invalid command line arguments, use [-v filename1] [-o filename2]\n");
				return false;
			}
		}
		return true;
	}

	else{
		printf("Invalid command line arguments, use [-v filename1] [-o filename2]\n");
		return false;
	}
}
int main( int argc, char** argv){

	char* LISPTree = (char*)calloc(MAX_LINE_LENGTH+1,sizeof(char));
	HashTable** hash = (HashTable**)malloc(sizeof(HashTable*));
	ERRORS* error = (ERRORS*)malloc(sizeof(ERRORS));
	if(LISPTree==NULL|| error==NULL|| hash==NULL){
		printf("Unexpected error occurred!\n");
		freeAllocations(hash,error,LISPTree);
		exit(0);
	}
	*error=NOERRORS;
	*hash = createHashTable(*hash ,error);
	if(*error==UNEXPECTEDERRORS){
		printf("Unexpected error occurred!\n");
		freeAllocations(hash,error,LISPTree);
		exit(0);
	}
	if (comandLineIsValid(argc,argv)==true){
		FILE* stream =stdout;
		bool ifCloseFile=false;
		if(argc==3 && strcmp(argv[1],"-o")==0){
			stream=fopen(argv[2], "w");
			ifCloseFile=true;
		}
		if (argc==5 && strcmp(argv[3],"-o")==0 ){
			stream=fopen(argv[4], "w");
			ifCloseFile=true;
		}

		if(stream==NULL){
			printf("Output file is read-only or cannot be created\n");
			freeAllocations(hash,error,LISPTree);
			exit(0);
		}

		else{
			if (( argc==3||argc==5) && (strcmp(argv[1],"-v" ) ==0)){
				readingFromFile(argv[2],hash,error,stream,LISPTree);
			}
			while(1){
				scanf("%s",LISPTree);
				if(LISPTree==NULL){ //if scanf not successful
					fprintf(stream,"Unexpected error occurred!\n");
					if(ifCloseFile==true){
						fclose(stream);
					}
					freeAllocations(hash,error,LISPTree);
					exit(0);
				}
				if(strcmp(LISPTree,"(<>)")==0){ //if need to exit
					if(ifCloseFile==true){
						fprintf(stream,"%s\n",LISPTree);
					}
					fprintf(stream,"Exiting...\n");
					break;
				}
				calcultaing(hash,stream,error,LISPTree,ifCloseFile);
				if(*error==UNEXPECTEDERRORS){
					break;
				}
			}
			if(ifCloseFile==true){
				fclose(stream);
			}
		}
	}
	freeAllocations(hash,error,LISPTree);
	return 0;

}





