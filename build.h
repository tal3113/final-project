
#ifndef BUILDTREE_H_
#define BUILDTREE_H_

#include "TreeNode.h"
#include "hashTable.h"


/**
 * a function which assist the buildTree function.
 * taking care of the base case of the recursion- leafs.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case building of the leaf succeeded.
 *
 * @param
 * 		char* LISPTree - a string that represent a tree.
 * 		ERRORS* error - Pointer which has the memory location where the error
 * 					   		will be stored.
 * @return
 *		A pointer to a leaf.in case an error occurred returns NULL.
 */
TreeNode* buildTree_Leaf(char* LISPTree ,ERRORS* error);

/**
 * Building a tree from LISPTree string.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case building of the tree succeeded.
 *
 * @param
 * 		char* LISPTree - a string that represent a tree.
 * 		TreeNode* ptree - ptree is a pointer which holds the tree.
 * 		ERRORS* error - Pointer which has the memory location where the error
 * 					   		will be stored.
 * @return
 *		A pointer to a tree.in case an error occurred returns NULL.
 */
TreeNode* buildTree( char* LISPTree , TreeNode* ptree,ERRORS* error);

/**
 * Building a hash table from a pointer to a tree.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case building of the hash succeeded.
 *
 * @param
 * 		HashTable* hash - a pointer to the hash table
 * 		TreeNode* node - node is a pointer which holds the tree.
 * 		ERRORS* error - Pointer which has the memory location where the error
 * 					   	will be stored.
 * @return
 *		A pointer to the hash table.in case an error occurred returns NULL.
 */
HashTable* buildHash (TreeNode* node , HashTable* hash , ERRORS* error );

/**
 * searching the index of the first child of LISPTree string.
 *
 * @param
 *		char* str - a string that represent a tree.
 *
 * @return
 *		returning the index of the first child of LISPTree string.
 */
int getChild( char* str);

/**
 * searching the root of LISPTree string.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case the copy of the root of the tree succeeded.
 *
 * @param
 * 		char* str - a string that represent a tree.
 * 		ERRORS* error - Pointer which has the memory location where the error
 * 					   		will be stored.
 * @return
 *		a copy of the root of LISPTree string.
 */
char* getRootStr(char* str,ERRORS* error);

/**
 * Searching the index child in a LISPTree string.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case copy of the child at location index succeeded.
 *
 * @param
 * 		char* str - a string that represent a tree.
 * 		ERRORS* error - Pointer which has the memory location where the error
 * 					   		will be stored.
 * @return
 *		a copy of the index child in a LISPTree string.
 */
char* getChildAtIndex(char* str , int index,TREE_VALUE_TYPE op,ERRORS* error);

/**
 * Finding the enum field that represent the op.
 *
 * @param
 *		char* op - a string that represent the operation.
 *
 * @return
 *		returning an enum field that represent the op.
 */
TREE_VALUE_TYPE recognizeSign(char* op);





#endif /* BUILDTREE_H_ */
