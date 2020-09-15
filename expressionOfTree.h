#ifndef EXPRESSIONOFTREE_H_
#define EXPRESSIONOFTREE_H_


#include "TreeNode.h"


/**
 * Concatenate expression  with "," and with the string that the node represent
 * using the getExpressionOfTreeRec
 *
 *
 * @param
 *		char* expression - the string which will be concatenated.
 *		TreeNode* node -  a pointer to a tree which will be turning into a string
 *						  using the getExpressionOfTreeRec and will be concatenated.
 *
 * @return
 *		returning the concatenated string.
 */
char* getStringForMinMax(char* expression , TreeNode* node);

/**
 * Finding the op that represent the enum field.
 *
 *
 * @param
 *		TREE_VALUE_TYPE op - an enum that represent the operation.
 *
 * @return
 *		returning a string that represent the enum field.
 */
char* recognizeSignFromEnumType(TREE_VALUE_TYPE op);

/**
 * Concatenating 5 strings.
 *
 *
 * @param
 *		char* str1 - the string which will be concatenated.
 *		char* str2 - the string which will be concatenated.
 *		char* str3 - the string which will be concatenated.
 *		char* str4 - the string which will be concatenated.
 *		char* str5 - the string which will be concatenated.
 *
 * @return
 *		returning the concatenated string.
 */
char* addAtMost5Strings( char* str1, char* str2 , char* str3, char* str4, char* str5);

/**
 * Gets the mathematical expression using a tree
 *
 *
 * @param
 *		TreeNode* node - a pointer to a tree that through him we will get the expression
 *
 * @return
 *		returning the mathematical expression.
 */
char* getExpressionOfTreeRec(TreeNode* node);

/**
 * Gets the mathematical expression using a tree,
 * and using the getExpressionOfTreeRec function.
 *
 *
 * @param
 *		TreeNode* node - a pointer to a tree that through him we will get the expression
 *
 * @return
 *		returning the mathematical expression.
 */
char* getExpressionOfTree(TreeNode* node);

#endif /* EXPRESSIONOFTREE_H_ */
