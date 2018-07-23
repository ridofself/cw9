/* test.c */

#include <assert.h> /* assert */
#include <stdio.h> /* printf */
#include <string.h> /* strcmp strlen */

int test_count = 0;

int test_test() {
	assert(1);
	test_count++;
	return 0; }

#include "user.h"

int test_user_create() {
	int i;
	char longName[USER_NAME_SIZE +2];
	char longPassword[USER_NAME_SIZE +2];

	struct user testUser = user_create("Goodname", "");
	assert(!strcmp(testUser.name, "Goodname"));
	assert(testUser.err == 0);
	test_count++; /* new user's name was stored */

	for (i=0; i<=USER_NAME_SIZE; i++) longName[i] = 'x';
	longName[i+1] = '\0'; /* make a too-long name, null terminated */
	testUser = user_create(longName, longPassword);
	assert(testUser.err == -1);
	test_count++; /* long name caught */

	testUser = user_create("illegalChar*", "");
	assert(testUser.err == -2);
	test_count++; /* bad char caught */

	testUser = user_create(NULL, "");
	assert(testUser.err == -3);
	test_count++; /* NULL name caught */

	for (i=0; i<=USER_PASSWORD_SIZE; i++) longPassword[i] = 'y';
	longPassword[i+1] = '\0'; /* make a too-long password, null term */
	testUser = user_create("goodName", longPassword);
	assert(testUser.err == -4);
	test_count++; /* long password caught */

	testUser = user_create("goodName", NULL);
	assert(testUser.err == -5);
	test_count++; /* NULL password caught */

	return 0; }

int test_user_save() {
	struct user testUser = user_create("Goodname", "");
	assert(!user_save(testUser));
	test_count++; /* user saved */

	assert(user_save(testUser) == -1);
	test_count++; /* existing user not overwritten */

	user_load(testUser.name); /* hide file by prepending _ */
	return 0; }

int test_user_load() {
	struct user testUser = user_create("Goodname", "");
	user_save(testUser);
	user_load(testUser.name);
	test_count++; /* user loaded */
	return 0; }

int test_all() {
	assert(!test_test());
	assert(!test_user_create());
	assert(!test_user_save());
	assert(!test_user_load());
	return 0; }

int main() {
	printf("Testing...\n");
	assert(!test_all());
	printf("\t%d tests passed.\n", test_count);
	return 0; }

/* end of file */
