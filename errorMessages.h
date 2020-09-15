

#ifndef ERRORMESSAGES_H_
#define ERRORMESSAGES_H_

/**
 * Defines a messaging mechanism to indicate errors in operations.
 * Each operation will receive a pointer to ERRORS. This will store
 * the message returned by the operation. Each returned message will be defined
 * in the operation later.
 */
typedef enum{
	NOERRORS = 0,
	UNEXPECTEDERRORS=1,
	INVALIDRESULT=2,
	INVALIDASSIGNMENT=3

}ERRORS;


#endif /* ERRORMESSAGES_H_ */
