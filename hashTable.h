#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "SPList.h"
#include "SPListElement.h"
#include "errorMessages.h"


/**
 * This is a declaration of struct which represent a tree.
 * The element has two fields:
 * 		SPList* table - an array from type SPList - will represent the hash table.
 * 		int size - the number of elements in the hash table.
 */
typedef struct hashTable{
	SPList* table;
	int size;
} HashTable ;

/**
 * Create a new empty hash table.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case creating of the hash succeeded.
 *
 * @param
 * 		ERRORS* error - Pointer which has the memory location where the message
 * 					   		will be stored.
 * @return
 *		A pointer to a new empty hash table, if allocation of the hash has failed
 *		NULL is returned.
 */
HashTable* createHashTable(HashTable* h,ERRORS *error);

/**
 * The hash function.
 *
 * @param
 * 		char* str - a string which represent the key for the hash function
 *
 * @return
 *		The index where the data(key and value) should be stored.
 *		-1 is returned if str is NULL.
 */
int hash(char* str);

/**
 * Checks if the hash table contains the key.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case finding the key in the hash succeeded.
 *
 * @param
 * 		HashTable* h - the hash table
 * 		char* key - the key that we check in the hash table.
 * 		ERRORS* error - Pointer which has the memory location where the message
 * 					   		will be stored.
 * @return
 *		The data that contains the key with it's value. if key is NULL,NULL is returned.
 */
SPListElement hashContains(HashTable* h , char* key, ERRORS *error);

/**
 * Insert the data into the hash table.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case inserting to the hash succeeded.
 *
 * @param
 * 		HashTable* h - the hash table.
 * 		SPListElement data - the data to be inserted into the hash table.
 * 		ERRORS* error - Pointer which has the memory location where the message
 * 					   	will be stored.
 */
void hashInsert(HashTable* h , SPListElement data, ERRORS *error);

/**
 * Deletes the data from the hash table.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case deleting of the data from the hash succeeded.
 *
 * @param
 * 		HashTable* h - the hash table.
 * 		SPListElement data - the data to be deleted from the hash table.
 * 		ERRORS* error - Pointer which has the memory location where the message
 * 					   	will be stored.
 */
void hashDelete(HashTable* h , SPListElement data, ERRORS *error);

/**
 * Gets the value ,using the key, from the hash table.
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		INVALIDRESULT - In case key is not in the hash table
 * 		NOERRORS - In case finding the value succeeded.
 *
 * @param
 * 		HashTable* h - the hash table
 * 		char* key - the key that we check in the hash table.
 * 		ERRORS* error - Pointer which has the memory location where the message
 * 					   	will be stored.
 * @return
 *		A pointer to the value. if an error occurred,NULL is returned.
 */
double* hashGetValue(HashTable* h , char* key, ERRORS *error);

/**
 * Gets the number of elements in the hash table
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case getting the size of the hash table succeeded.
 *
 * @param
 * 		HashTable* h - the hash table.
 * 		ERRORS* error - Pointer which has the memory location where the message
 * 					   	will be stored.
 * @return
 *		The number of elements in the hash table. if hash is NULL,-1 is returned.
 */
int hashGetSize(HashTable* h, ERRORS *error);

/**
 * Checks if the hash table is empty
 *
 * Messages:
 * 		UNEXPECTEDERRORS - In case allocation failed.
 * 		NOERRORS - In case of success.
 *
 * @param
 * 		HashTable* h - the hash table.
 * 		ERRORS* error - Pointer which has the memory location where the message
 * 					   	will be stored.
 * @return
 *		true,if the hash table is empty,otherwise returns false.
 */
bool hashIsEmpty(HashTable* h,ERRORS *error);

/**
 * Free all allocation associated with the hash.
 *
 * @param
 * 		HashTable* h - Pointer to the hash which will be deleted.
 * 					   After invoking destroyHashTable, the hash will no longer be valid to use.
 * 					   If hash==NULL nothing happens.
 */
void destroyHashTable(HashTable* h);


#endif /* HASHMAP_H_ */
