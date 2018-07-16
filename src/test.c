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

	char testName[USER_NAME_SIZE +2] = "testName";
	char testPassword[USER_NAME_SIZE +1] = "testPassword";
	struct user testUser = user_create(testName, testPassword);
	assert(!strcmp(testUser.name, testName));
	assert(testUser.err == 0);
	test_count++; /* new user's name was stored */

	for (i=0; i<=USER_NAME_SIZE; i++) testName[i] = 'x';
	testName[i+1] = '\0'; /* make a too-long name, null terminated */
	testUser = user_create(testName, testPassword);
	assert(testUser.err == -1);
	test_count++; /* long name caught */

	testUser = user_create(badName, testPassword);
	assert(testUser.err == -2);
	test_count++; /* bad char caught */

	testUser = user_create(NULL, testPassword);
	assert(testUser.err == -3);
	test_count++; /* NULL name caught */

	for (i=0; i<=USER_PASSWORD_SIZE; i++) testPassword[i] = 'y';
	testName[i+1] = '\0'; /* make a too-long password, null terminated */
	testUser = user_create(testName, testPassword);
	assert(testUser.err == -4);
	test_count++; /* long password caught */

	testUser = user_create(testName, NULL);
	assert(testUser.err == -5);
	test_count++; /* NULL password caught */
	}

void test_user_save()
	{
	struct user savedUser = user_create("testSave", "");
	user_save(savedUser);
	assert(user_save(savedUser) == -1);
	test_count++; /* file not re-written */
	}

void test_user_load()
	{
	struct user loadableUser = user_create("loadme", "");
	struct user loadedUser;
	user_save(loadableUser);
	loadedUser = user_load(loadableUser.name);
	assert(!strcmp(loadedUser.name, loadableUser.name));
	test_count++; /* successfully loaded user */

	loadedUser = user_load("doesNotExist");
	assert(loadedUser.err == -6);
	test_count++; /* non-existant username caught */

	loadedUser = user_load("B@dN@m3");
	assert(loadedUser.err == -2);
	test_count++; /* non-existant username caught */
	}

void test_all()
	{
	test_test();
	test_user_create();
	test_user_save();
	test_user_load();
	}

int main()
	{
	printf("Testing...\n");
	test_all();
	printf("\t%d tests passed.\n", test_count);
	}

/* end of file */
