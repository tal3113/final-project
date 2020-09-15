


#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "build.h"

/**
 * Checks if num is integer
 *
 * @param
 *
 * 		double num - the number to check.
 *
 * @return
 *		true - if num is integer,otherwise false.
 */
bool numIsInteger(double num);

/**
 * Checks if dollar is a vlid operation
 *
 * @param
 *
 * 		double a
 * 		double b
 *
 * @return
 *		true - if is a valid operation,otherwise false.
 */
bool dollarIsValid(double a, double b);

/**
 * calculate $ operation.
 *
 * @param
 *
 * 		double a
 * 		double b
 *
 * @return
 *		the result of $ operation.
 */
double dollar(double a, double b);

/**
 * Finding the minimum or maximum between the children of node.
 *
 * @param
 * 		TreeNode* node - a pointer to a tree that will be searched for the minimum or maximum.
 *
 * @return
 *		the minimum or maximum.
 */
double findMinMAx( TreeNode* node);

/**
 * Searching for the number to be calculated.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case the search for the number succeeded.
 * @param
 *
 * 		TreeNode* node - pointer to a tree.
 * 		ERRORS* error -  Pointer which has the memory location where the message
 * 					   		will be stored
 * 		HashTable* hash - pointer to the hash. if the type of the node is a VARIABLE,
 * 						  then we will be searching for the number in the hash table.
 *
 * @return
 *		returns the number to be calculated.if an error occurred 0 is returned.
 *
 */
double searchNumToCalc(TreeNode* node, HashTable* hash , ERRORS* error);

/**
 * Calculate the expression using the node
 * and storing the result of the calculation in result.
 *
 * Messages:
 * 		INVALIDRESULT - in case the expression is not valid.
 * 		NOERRORS - In case the expression has been calculate successfully.
 * @param
 *
 * 		TreeNode* node - pointer to a tree.
 * 		ERRORS* error -  Pointer which has the memory location where the message
 * 					   	 will be stored
 * 		double* result - pointer where the result of the calculation will be stored.
 *
 */
void calc( TreeNode* node, ERRORS* error,  double* result );

/**
 * Calculate the expression using the tree.
 *
 * Messages:
 * 		INVALIDRESULT - in case the expression is not valid.
 * 		INVALIDASSIGNMENT - in case the assignment expression is not valid.
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case the expression has been calculate successfully.
 * @param
 *
 * 		TreeNode* tree - pointer to the tree.
 * 		ERRORS* error -  Pointer which has the memory location where the message
 * 					   	 will be stored
 * 		HashTable* hash - pointer to the hash.
 * 		double* result - pointer where is the result.
 *
 * @return
 *		return a root without children that has the result value.
 *		In case the expression or the assignment is not valid
 *		or allocation failed returns a tree.
 *
 */
TreeNode* Algorithm(TreeNode* tree, HashTable* hash, ERRORS* error, double* result );


#endif /* CALCULATOR_H_ */
