/* user.c */

#include "user.h" /* USER_NAME_SIZE USER_PASSWORD_SIZE */
#include <string.h> /* strcmp strlen */
#include <stdio.h> /* printf FILE rename remove */
#include <ctype.h> /* isalnum */

static char dir[] = "users/"; /* folder where users are stored */

static struct user named(struct user user, const char* name) {
/* populate a struct user's name field if proper name is given */
	unsigned int i;

	if ( !name ) {
		user.err = -3; /* name cannot be NULL */
		return user; /* return early to prevent segfault */ }

	for ( i=0; name[i]!='\0'; i++ ) /* iterate over each char */ {

		if ( i == USER_NAME_SIZE ) {
			user.err = -1; /* name is too long */
			break; }

		if ( !isalnum((unsigned char)name[i]) ) {
			user.err = -2; /* bad char found */
			break; }

		user.name[i] = name[i]; /* copy name char-by-char */
		continue; }

	user.name[i] = '\0'; /* null terminate the string */
	return user; /* user name is good */ }

static struct user passworded(struct user user, const char* password) {
/* populate a struct user's password field if proper password is given */
	int i;

	if ( !password ) {
		user.err = -5; /* password cannot be NULL */
		return user; /* return early to prevent segfault */ }

	for ( i=0; password[i]!='\0'; i++ ) /* iterate over each char */ {

		if ( i == USER_PASSWORD_SIZE ) {
			user.err = -4; /* password is too long */
			break; }

		user.password[i] = password[i]; /* copy password to struct */
		continue; }

	user.password[i] = '\0'; /* null terminate the string */
	return user; /* password is good */ }

struct user user_create(const char* name, const char* password) {
/* return a struct user with its fields (or err field) populated */
	struct user user;
	user.err = 0;

	user = named(user, name);
	if ( user.err ) return user; /* bad name */

	user = passworded(user, password);
	if ( user.err ) return user; /* bad password */

	return user; /* user is good to go */ }

int user_save(struct user user) {
/* save user to disk and delete corresponding hidden file if exists */
	FILE *file;
	char path[sizeof (dir) + sizeof (user.name) + 1]; /* regular path */
	char _path[sizeof (dir) + sizeof (user.name) + 2]; /* hidden path */

	sprintf(path, "%s%s%c", dir, user.name, '\0');
	sprintf(_path, "%s_%s%c", dir, user.name, '\0');

	remove(_path); /* delete the hidden user file if it exists */

	if ( (file = fopen(path, "r")) != NULL ) /* file can be read? */ {
		fclose(file);
		return -1; /* file already exists, don't overwrite */ }

	file = fopen(path, "wb"); /* writable file created */
	fwrite(&user, sizeof (struct user), 1, file); /* user saved to disk */
	fclose(file);
	return 0; }

struct user user_load(char* name) {
/* load user from file and hide file by prepending with _ */
	unsigned int i;
	FILE *file;
	struct user user;
	char path[sizeof (dir) + USER_NAME_SIZE +1]; /* for regular path */
	char _path[sizeof (dir) + USER_NAME_SIZE +2]; /* for hidden path */

	for ( i=0; name[i]!='\0'; i++ ) { /* check name length FIRST */
		if ( i == USER_NAME_SIZE ) {
			user.err = -1; /* name is too long */
			return user; }
		continue; }

	sprintf(path, "%s%s%c", dir, name, '\0'); /* make regular path */
	sprintf(_path, "%s_%s%c", dir, name, '\0'); /* make hidden path */

	if ( (file = fopen(path, "rb")) == NULL ) { /* check if file exists */
		user.err = -6; /* no such file */
		return user; }

	fread(&user, sizeof (struct user), 1, file); /* load user */
	rename(path, _path); /* hide the file */
	fclose(file);
	return user; /* user loaded successfully */ } 

/* end of file */
