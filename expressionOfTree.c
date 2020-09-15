
#include "expressionOfTree.h"

char* getStringForMinMax(char* expression , TreeNode* node){
	char* strnode= getExpressionOfTreeRec(node);
	char* str = calloc(strlen(expression)+strlen(strnode)+strlen(",")+1,sizeof(char) );
	strcat( str , expression );
	strcat( str , "," );
	strcat( str , strnode );
	free(strnode);
	return str;
}

char* recognizeSignFromEnumType(TREE_VALUE_TYPE op){

	switch(op){
	case PLUS:
		return "+";
	case MINUS:
		return "-";
	case MULTIPLICATION:
		return "*";
	case DIVISION:
		return "/";
	case DOLLAR:
		return "$";
	case EQUAL:
		return "=";
	case MAX:
		return "max";
	case MIN:
		return "min";
	default:
		return "";
	}
}

char* addAtMost5Strings( char* str1, char* str2 , char* str3, char* str4, char* str5){

	char* str = calloc( strlen(str1)+strlen(str2)+strlen(str3)+strlen(str4)+strlen(str5)+1
				,sizeof(char));

	strcat( str , str1);
	strcat( str , str2);
	strcat( str , str3);
	strcat( str , str4);
	strcat( str , str5);

	return str;
}

char* getExpressionOfTreeRec(TreeNode* node){

	if (node->value->type==DOUBLE ){
		char* numAsStr = calloc( sizeof(int)+1 ,sizeof(char) );
		int num = (int)(node->value->num);
		sprintf(numAsStr, "%d" , num );//converting num to string
		return numAsStr;

	}
	else if ( node->value->type==VARIABLE){
		char* varAsStr = calloc( strlen(node->value->str)+1 ,sizeof(char) );
		strcat( varAsStr , node->value->str);//copying the variable to varAsStr
		return varAsStr;
	}
	else if (!(node->value->type==MIN || node->value->type==MAX)){//not max or min operations

			char* strChild1= NULL;
			char* strChild2=NULL;
			if(node->numOfChild == 1){
				strChild1="";
				strChild2=getExpressionOfTreeRec(node->children[0]);
			}
			else{
				strChild1 = getExpressionOfTreeRec(node->children[0]);
				strChild2= getExpressionOfTreeRec(node->children[1]);
			}
			char* op = recognizeSignFromEnumType(node->value->type);
			char* str= addAtMost5Strings("(",strChild1,op,strChild2,")");
			if(strcmp(strChild1,"")!=0){
				free(strChild1);
			}
			free(strChild2);
			return str;//str="(strChild1opstrChild2)"

	}
	else{ //case min or max operations

		char* op = recognizeSignFromEnumType(node->value->type);
		char* strChild= getExpressionOfTreeRec(node->children[0]);
		char** pstr = (char**)malloc(sizeof(char*));
		*pstr = addAtMost5Strings( op , "(", strChild , "" , "" );

		for (int i=1; i<node->numOfChild ;i++){
			char* str2= getStringForMinMax( *pstr , node->children[i]);
			free(*pstr);
			*pstr= str2;

		}
		char* str= addAtMost5Strings( *pstr , ")", "" , "" , "" );
		free(strChild);
		free(*pstr);
		free(pstr);
		return str;
	}
}

char* getExpressionOfTree(TreeNode* node){
	if (node->numOfChild==0){
		if (node->value->type==DOUBLE ){
			char* numAsStr = calloc( sizeof(int)+1 ,sizeof(char) );
			int num = (int)(node->value->num);
			sprintf(numAsStr, "%d" , num );//converting num to string
			char* str = addAtMost5Strings( "(",numAsStr,")","","" );//concatenating-"(numAsStr)"
			free(numAsStr);
			return str;
		}
		else{ // ( node->value->type==VARIABLE)
			return addAtMost5Strings("(",node->value->str,")","","" );
		}
	}
	else{
		return getExpressionOfTreeRec(node);
	}



}



