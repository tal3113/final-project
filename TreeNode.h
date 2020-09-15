

#ifndef TREENODE_H_
#define TREENODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "errorMessages.h"
#define MAXCHILD 10

/********************************************************************
 *  The tree element has a value.the value element has a type and num.
 * Definition of the type of the value of the tree.
 ********************************************************************/
typedef enum{
	MAX,
	MIN,
	VARIABLE,
	EQUAL,
	PLUS ,
	MINUS,
	MULTIPLICATION,
	DIVISION,
	DOLLAR,
	DOUBLE
}TREE_VALUE_TYPE;

/**
 * TreeNode will hold an element of type TREE_VALUE.
 * The element has two fields:
 * 		TREE_VALUE_TYPE type - This enum indicates the type of the element.
 * 		double num -  If the type of the element is DOUBLE, will hold the value of
 * 					  the number represented by the element. Otherwise it is not defined.
 * 		char* str - If the type of the element is VARIABLE, will hold the string
 * 				 	represented by the element. Otherwise it is NULL.
 */
typedef struct{
	TREE_VALUE_TYPE type;
	double num;
	char* str;

}TREE_VALUE;

/**
 * This is a declaration of struct which represent a tree.
 * The element has three fields:
 * 		int numOfChild - represent the number of children of the node.
 * 		TREE_VALUE* value - this struct indicates the value of the node.
 * 		struct TreeNode **children - this field represent a pointer for the children.
 */
typedef struct TreeNode{

	int numOfChild;
	TREE_VALUE* value;
	struct TreeNode **children;

}TreeNode;

/**
 * Create a new empty tree.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case building of the tree succeeded.
 *
 * @param
 * 		ERRORS* error - Pointer which has the memory location where the message
 * 					   		will be stored.
 * @return
 *		A pointer to a new empty tree, if allocation of the head has failed
 *		NULL is returned.
 */
TreeNode* createTree(ERRORS* error);

/**
 * Insert to the parent the node in location index.
 *
 * @param
 * 		TreeNode* parent - pointer to the parent node.
 * 		int index - the number of parent child that node will be stored.
 * 		TreeNode* node - the node to be insert.
 */
void insertInIndex( TreeNode* parent , int index ,TreeNode* node );

/**
 * Free and deleting the children of the parent.
 *
 * @param
 * 		TreeNode* parent - pointer to the parent node.
 */
void deleteChildren( TreeNode* parent);

/**
 * Free all allocation associated with the node.
 * @param
 * TreeNode* node - Pointer to a tree which will be deleted.
 * 					 After invoking destroy, tree will no longer be valid to use.
 * 					 If stack==NULL nothing happens.
 */
void destroy(TreeNode* node);



#endif /* TREENODE_H_ */
