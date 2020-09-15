#include "build.h"


TREE_VALUE_TYPE recognizeSign(char* op){

	if (strcmp(op, "+") == 0) {
		return PLUS;
	} else if (strcmp(op, "-") == 0) {
		return MINUS;
	} else if (strcmp(op, "*") == 0) {
		return MULTIPLICATION;
	} else if (strcmp(op, "/") == 0) {
		return DIVISION;
	} else if (strcmp(op, "$") == 0) {
		return DOLLAR;
	}
	else if ((strcmp(op, "=") == 0)){
		return EQUAL;
	}
	else if ((strcmp(op, "min") == 0)){
		return MIN;
	}
	else{ //if (strcmp(op, "max") == 0)
		return MAX;
	}
}

int getChild( char* str){

	int i=1;
	int numLeft= 1;
	int numRight= 0;

	//counting the number of '(' and ')' to decide when the first child end
	while( ! (numLeft == numRight) ){ //as long as the pointer is still in the first child
		if ( str[i] == '(' ){
			numLeft++;
		}
		if ( str[i] == ')' ){
			numRight++;
		}
		i++;
	}
	return i; // return indexEnd
}

char* getRootStr(char* str,ERRORS* error){

	char* check=(char*)calloc(5,sizeof( char ));
	strncpy(check,str,4);
	char* check1 = strstr( check ,"max"); // search for the first instance of "max"
	char* check2 = strstr( check ,"min");// search for the first instance of "min"
	int k=0;
	if(check1 == NULL && check2 == NULL){// max or min are not the root
		k=2;
	}
	else{ //max or min are the root
		k=4;
	}
	free(check);
	char* str2 = (char*)calloc( k ,sizeof( char ));
	if(str2!=NULL){ // in case allocation is successful
		strncpy( str2 , str+1 , k-1  ); // coping the root
	}
	else{
		*error=UNEXPECTEDERRORS;
	}
	return str2;

}

char* getChildAtIndex(char* str , int index,TREE_VALUE_TYPE op,ERRORS* error){

	int k=0;
	if(op == MAX || op == MIN){ //max or min are the root
		k=4;
	}
	else{ //max or min are not the root
		k=2;
	}
	char* str1 = str +k; //location where the first child begins
	int endChild = getChild( str1 ) + k;
	int i=0;

	// to check if the string have a child && to get the child in number index
	while( ( strlen(str)>( endChild +2 ) ) && i<index  ){
		str1 = str + endChild;
		endChild += getChild ( str1 );
		i++;
	}

	if (! (strlen(str)> endChild +2 ) && i<index){ //checking if there are no children left
		return "";
	}

	char* str2 = (char*)calloc( ((str - str1) + endChild)+1,sizeof( char ));
	if(str2!=NULL){ //in case allocation is successful
		strncpy( str2, str1 , (str - str1) + endChild  ); //coping the child in location index
	}

	else{
		*error=UNEXPECTEDERRORS;
	}
	return str2;
}

HashTable* buildHash (TreeNode* node , HashTable* hash , ERRORS* error ){

	if (*error!=NOERRORS){
			return NULL;
	}
	char* str= node->children[0]->value->str;
	double value= node->children[1]->value->num;

	SPListElement data = createElement(str, value);
	if (data==NULL){
		*error=UNEXPECTEDERRORS;
		return NULL;
	}
	hashInsert(hash , data, error);//inserting the data to the hash table
	if (*error!=NOERRORS){//inserting to the hash table was not successful
		return NULL;
	}
	destroyElement(data);
	return hash;
}

TreeNode* buildTree_Leaf(char* LISPTree ,ERRORS* error){

	TreeNode* ptree = createTree(error);
	if((*error)==UNEXPECTEDERRORS){
		return NULL;
	}
	char* strNum=(char*)calloc(strlen(LISPTree)-2 +1 ,sizeof(char) );
	if(strNum!=NULL){ //in case allocation was successful
		strncpy( strNum , LISPTree + 1 , strlen(LISPTree)-2 );
		char* str= (char*)calloc(1 + strlen(strNum),sizeof(char));
		sprintf(str, "%d", atoi(strNum)); //converting atoi(strNum) to string
		if( strstr(strNum, str)==NULL ){ //checking if it's a variable
			(ptree->value)->type=VARIABLE;
			(ptree->value)->str = strNum;
		}
		else{ //strNum is a number
			(ptree->value)->type=DOUBLE;
			sscanf(strNum,"%lf",&((ptree->value)->num)); // converting strNum to double
			free(strNum);
		}
		free(str);
		return ptree;
	}
	else{
		*error=UNEXPECTEDERRORS;
		return NULL;
	}
}

TreeNode* buildTree( char* LISPTree , TreeNode* ptree,ERRORS* error ){
	if((*error)==UNEXPECTEDERRORS)
	{
		return NULL;
	}
	char* check = strchr( LISPTree+1 ,'(');//search for the first instance of '('

	if (check == NULL){ // case the input is only a number or variable - leaf
		return buildTree_Leaf(LISPTree,error);
	}

	else{ //check != NULL : case the input complex - numbers and operations

		TreeNode* temp = createTree(error);
		if((*error)==UNEXPECTEDERRORS){
			return NULL;
		}
		char* root = getRootStr(LISPTree,error);
		if((*error)==UNEXPECTEDERRORS){
			return NULL;
		}
		(temp->value)->type = recognizeSign(root);
		free(root);
		for (int i =0 ; i< MAXCHILD ; i++){
			char* str =getChildAtIndex( LISPTree, i,(temp->value)->type,error);
			if((*error)==UNEXPECTEDERRORS){
				return NULL;
			}
			if ( strcmp(str, "")!=0 ){ // case their are  still children
				insertInIndex( temp , i , buildTree( str , temp ,error) );
				free( str);
			}
			else{ // case there are no children
				break;
			}
		}
		ptree = temp;
		return ptree;
	}
}


