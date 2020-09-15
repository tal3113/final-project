
#include "calculator.h"


bool numIsInteger(double num){//checking if num is an integer

	int n=(int)num;
	double temp=num-n; // temp is the reminder
	for(int i=0;i<6;i++){ // double results have decimal precision of 10^-6
		temp=temp*10;
	}
	int tempInteger=(int)temp;
	if(tempInteger==0){
		return true;
	}
	else{
		return false;
	}
}

bool dollarIsValid(double a, double b){ //checking if dollar is a valid operation
	if(a<=b && numIsInteger(a)&& numIsInteger(b)){
		return true;
	}
	else{
		return false;
	}
}

double dollar(double a, double b) { //calculating dollar operation

	double res = 0;
	int i;
	for (i = 0; i <= (b - a); i++) {
		res = res + a + i;
	}

	return res;

}

double findMinMAx( TreeNode* node ){

	TREE_VALUE_TYPE op = node->value->type;
	double min_max = node->children[0]->value->num;
		for(int i=1 ; i<node->numOfChild ;i++){
			double element = node->children[i]->value->num;
			if (op == MIN){
				if ( element < min_max ){
					min_max = element;
				}
			}
			else{ //(op == MAX)
				if ( element > min_max ){
					min_max = element;
				}
			}
		}
	return min_max;
}

double searchNumToCalc(TreeNode* node, HashTable* hash, ERRORS* error){

	double num=0;
	if (node->value->type==DOUBLE){
		num= node->value->num;
	}
	else{
		double* copy=hashGetValue(hash , node->value->str,error);
		if(copy!=NULL){// no errors occurred
			num=*copy;
			free(copy);
		}
	}
	return num;
}

void calc( TreeNode* node , ERRORS* error,  double* result ){
	TREE_VALUE_TYPE op =  node->value->type;
	if (op  == MIN || op == MAX){
		*result = findMinMAx( node );
	}
	else{
		double num1;
		double num2;
		if (node->numOfChild == 1){
			num1 = 0;
			num2 = node->children[0]->value->num;
		}
		if (node->numOfChild == 2){
			num1 = node->children[0]->value->num;
			num2 = node->children[1]->value->num;
		}

		if (op==PLUS) {
			*result = num1 + num2;
			*error= NOERRORS;
		}
		else if (op==MINUS) {
			*result = num1 - num2;
			*error= NOERRORS;
		}
		else if (op==MULTIPLICATION){
			*result = num1 * num2;
			*error= NOERRORS;
		}
		else if (op==DIVISION){
			if (num2 != 0) {
				*result = num1 / num2;
				*error= NOERRORS;
			}
			else{
				*error=INVALIDRESULT;
			}
		}
		else{ // ( op == DOLLAR)
			if (dollarIsValid(num1,num2)!=0) {
				*result = dollar(num1, num2);
				*error= NOERRORS;
			}
			else{
				*error=INVALIDRESULT;
			}
		}
	}
}

TreeNode* Algorithm(TreeNode* tree, HashTable* hash, ERRORS* error, double* result ){

	if ( *error!= NOERRORS){//an error occurred
		return tree;
	}
	if ( tree->numOfChild == 0){
		*result=searchNumToCalc(tree, hash, error);//find the number that will be calculated
	}
	else{
		if (tree->value->type==EQUAL){
			tree->children[1]=Algorithm( tree->children[1], hash , error, result);
			if ( *error!= NOERRORS){//an error occurred
				*error =INVALIDASSIGNMENT;
			}
			return tree;
		}
		for (int i=0 ; i<tree->numOfChild ; i++){
			tree->children[i]=Algorithm( tree->children[i], hash , error, result);
			if ( *error!= NOERRORS){ //an error occurred
				return tree;
			}
		}
		calc( tree  , error,  result );
	}
	if (*error==NOERRORS){
		TreeNode* temp = createTree(error);
		if((*error)==UNEXPECTEDERRORS){//an error occurred
			return NULL;
		}
		(temp->value)->type=DOUBLE;
		(temp->value)->num=*result;
		destroy(tree);
		return temp;
	}
	return tree;
}


