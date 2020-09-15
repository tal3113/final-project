
#include "TreeNode.h"


TreeNode* createTree(ERRORS* error){
	TreeNode* head = (TreeNode*)malloc(sizeof(TreeNode));
	if(head!=NULL){ //if allocation successful
		head->numOfChild=0;
		head->children = (TreeNode**)malloc(MAXCHILD*sizeof(TreeNode*));
		if(head->children == NULL){ //if allocation failed
			*error=UNEXPECTEDERRORS;
		}
		head->value= (TREE_VALUE*)malloc(sizeof( TREE_VALUE ));
		if(head->value == NULL){ //if allocation failed
			*error=UNEXPECTEDERRORS;
		}
		else{
			head->value->str=NULL;
		}
	}

	else{
		*error=UNEXPECTEDERRORS;
	}

	return head;
}

void insertInIndex( TreeNode* parent , int index , TreeNode* node ){

	if(parent->children!=NULL && node!=NULL){
		parent->children[index]= node;
		parent->numOfChild++;
	}

}

void deleteChildren( TreeNode* parent){

	if(parent->children!=NULL){
		for(int i=0;i<parent->numOfChild;i++){
			destroy(parent->children[i]); //deleting child[i] of the parent
		}
		parent->numOfChild = 0;
	}

}

void destroy(TreeNode* node){

	if(node!=NULL){
		for(int i=0;i<node->numOfChild;i++){
			destroy(node->children[i]);
		}
		if (node->value!=NULL){
			if(node->value->str !=NULL){
				free(node->value->str);
			}
			free(node->value);
		}
		if (node->children!=NULL){
			free(node->children);
		}
		free(node);
	}
}






