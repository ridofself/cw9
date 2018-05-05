/* test.c */

#include <assert.h> /* assert */
#include <stdio.h> /* printf */
#include <string.h> /* strcmp strlen */

int test_count = 0;

void test_test()
	{
	assert(1);
	test_count++;
	}

#include "user.h"

void test_user_create()
	{
	int i;
	char* badName = "hasIllegalChar@";

	char testName[USER_NAME_SIZE +1] = "testName";
	struct user testUser = user_create(testName);
	assert(!strcmp(testUser.name, testName));
	test_count++; /* new user's name was stored */

	for (i=0; i<USER_NAME_SIZE; i++) testName[i] = 'x';
	testName[i+1] = '\0'; /* make a too-long name, null terminated */
	testUser = user_create(testName);
	assert(strlen(testUser.name) == 0);
	test_count++; /* empty user assigned; name is too long */

	testUser = user_create(badName);
	assert(strlen(testUser.name) == 0);
	test_count++; /* empty user assigned due to name w/ bad char */
	}

void test_all()
	{
	test_test();
	test_user_create();
	}

int main()
	{
	printf("Testing...\n");
	test_all();
	printf("\t%d tests passed.\n", test_count);
	}

/* end of file */
