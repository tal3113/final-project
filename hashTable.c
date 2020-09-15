
#include "hashTable.h"

#define FIRST_PRIME 571
#define COEFFICIENT_PRIME 31
#define NUMBER_OF_ENTRIES 100



HashTable* createHashTable(HashTable* h ,ERRORS *error){

	h=(HashTable*)malloc(sizeof(HashTable));
	if (h==NULL){//allocation was not successful
		*error = UNEXPECTEDERRORS;
	}
	h->table = (SPList*)malloc(NUMBER_OF_ENTRIES*sizeof(SPList));
	if ((h->table)!=NULL){
		for (int i=0; i<NUMBER_OF_ENTRIES ; i++){
			(h->table)[i]= listCreate();
		}
	}
	else{ //allocation was not successful
		*error = UNEXPECTEDERRORS;
	}
	h->size = 0;
	return h;
}

int hash(char* str){

	if (str == NULL){
		return -1;
	}

	else{
		int hash = FIRST_PRIME;
		for (int i=0 ; i< strlen(str) ; i++){
			hash = COEFFICIENT_PRIME*hash + (int)str[i];
			hash%= NUMBER_OF_ENTRIES;
		}
		return hash;
	}
}

SPListElement hashContains(HashTable* h , char* key, ERRORS *error){
	int index= hash (key);
	if (index==-1){ // if key==NULL
		*error = UNEXPECTEDERRORS;
		return NULL;
	}
	else{
		SPList list = (h->table)[index];
		int size= listGetSize(list);
		if (size!= -1){ //if list!=NULL
			LIST_FOREACH(SPListElement, e, list){//running on the list
				char* elementStr = getElementStr(e);
				if ( strcmp(elementStr ,key)==0 ){//if key was found in the hash table
					free(elementStr);
					return e;
				}
				free(elementStr);
			}
		}
		return NULL;
	}
}

void hashInsert(HashTable* h , SPListElement data, ERRORS *error){

	char* elementStr=getElementStr(data);
	SPListElement check= hashContains( h , elementStr , error);
	free(elementStr);
	if ( check!=NULL ){//if the hash table contains the data
		double* num=getElementValue(data);
		setELementValue(check,*num);//updating the data with the new number
		free(num);
	}
	else if( *error==NOERRORS){
		char* elementStr = getElementStr(data);
		int index= hash (elementStr);
		if (index==-1){// elementStr is NULL
			*error = UNEXPECTEDERRORS;
		}
		else{
			SPList list = (h->table)[index];
			ListResult result =listInsertFirst(list, data);//inserting the data to the list
			if (result==SP_LIST_SUCCESS){
				h->size++;
			}
			else{ //the insertion was not successful
				free(elementStr);
				*error = UNEXPECTEDERRORS;
			}
		}
		free(elementStr);
	}
}

void hashDelete(HashTable* h , SPListElement data, ERRORS *error){
	char* key = getElementStr(data);
	int index= hash (key);
	if (index==-1){//if key == NULL
		*error = UNEXPECTEDERRORS;
	}
	else{
		SPList list = (h->table)[index];
		int size= listGetSize(list);
		if (size!= -1){ //if list!=NULL
			LIST_FOREACH(SPListElement, data2, list){//running  on the list
				if ( areElementsEqual(data , data2)==true ){
					ListResult result =listRemoveCurrent(list);//removing the data from the list
					if (result!=SP_LIST_SUCCESS){// the removal was not successful
						*error = UNEXPECTEDERRORS;
					}
					h->size--;
				}
			}
		}
		else{//list == NULL
			*error = UNEXPECTEDERRORS;
		}
	}
	free(key);
}

double* hashGetValue(HashTable* h , char* key, ERRORS *error){
	int index= hash(key);
	if (index==-1){//if key==NULL
		*error = UNEXPECTEDERRORS;
	}
	else{
		SPList list = (h->table)[index];
		int size= listGetSize(list);
		if (size!= -1){//if list!=NULL
			LIST_FOREACH(SPListElement, data2, list){//running on the list
				if( isElementStrEquals( data2 , key )==true ){
					return getElementValue( data2 ); //returns a copy of the value of data.
				}
			}
			*error=INVALIDRESULT; // key is not in the hash table
		}
		else{//if list == NULL
			*error = UNEXPECTEDERRORS;
		}
	}
	return NULL;
}

int hashGetSize(HashTable* h, ERRORS *error){
	if (h!=NULL){
		return h->size;
	}
	else{
		*error = UNEXPECTEDERRORS;
		return -1;
	}
}

bool hashIsEmpty(HashTable* h,ERRORS *error){
	if (h!=NULL){
		return h->size == 0 ? true : false ;
	}
	else{
		*error = UNEXPECTEDERRORS;
		return false;
	}
}

void destroyHashTable(HashTable* h){
	if (h==NULL){
		return;
	}
	else{
		if(h->table!=NULL){

			//destroys the lists of the hash table
			for (int i=0 ; i<NUMBER_OF_ENTRIES ; i++){
				listDestroy((h->table)[i]);
			}

			free(h->table);
		}
		free(h);
	}


}
