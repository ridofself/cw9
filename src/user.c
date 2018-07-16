/* user.c */

#include "user.h" /* NAME_LENGTH_SIZE */
#include <string.h> /* strcmp strlen */
#include <stdio.h> /* printf FILE rename remove */
#include <ctype.h> /* isalnum */

static struct user user_empty; /* returned as a null value if err */
static char* users_folder = "users/";

static struct user named(struct user user, const char* name)
	{
	if ( !name )
		{
		user.err = -3; /* name cannot be NULL */
		return user; /* return early to prevent segfault */
		}
	int i;
	for ( i=0; name[i]!='\0'; i++ ) /* iterate over each char */
		{
		if ( i == USER_NAME_SIZE )
			{
			user.err = -1; /* name is too long */
			break;
			}
		if ( !isalnum(name[i]) )
			{
			user.err = -2; /* bad char found */
			break;
			}
		user.name[i] = name[i]; /* copy name to newUser.name */
		}
	user.name[i] = '\0'; /* null terminate the string */
	return user;
	}

static struct user passworded(struct user user, const char* password)
	{
	int i;
	for ( i=0; password[i]!='\0'; i++ ) /* iterate over each char */
		{
		if ( i == USER_PASSWORD_SIZE )
			{
			user.err = -4; /* password is too long */
			break;
			}
		user.password[i] = password[i]; /* copy password */
		}
	user.password[i] = '\0'; /* null terminate the string */
	return user;
	}

struct user user_create(const char* name, const char* password)
	{
	struct user user;
	user = named(user, name);
	user = passworded(user, password);
	return user;
	}

int user_save(struct user user)
	{
	FILE *file;
	char filePath[strlen(users_folder) + USER_NAME_SIZE];
	char hiddenFile[strlen(filePath) + 1]; /* _ prepended */

	sprintf(filePath, "%s%s", users_folder, user.name);
	sprintf(hiddenFile, "%s_%s", users_folder, user.name);

	if ( (file = fopen(filePath, "r")) != NULL ) /* file can be read */
		{
		fclose(file);
		return -1; /* file already exists, don't overwrite */
		}

	file = fopen(filePath, "wb"); /* file created */
	fwrite(&user, sizeof (struct user), 1, file); /* user saved */
	remove(hiddenFile); /* remove hidden backup copy (if it exists) */
	fclose(file);
	return 0;
	}

struct user user_load(char *name)
	{
	struct user user;
	FILE *file;
	char filePath[strlen(users_folder) + USER_NAME_SIZE];
	char hiddenFile[strlen(filePath) + 1]; /* _ prepended */
	unsigned int i;

	for ( i=0; name[i]!='\0'; i++ )
		if ( i == USER_NAME_SIZE) return user_empty; /* too long */

	sprintf(filePath, "%s%s", users_folder, name);
	sprintf(hiddenFile, "%s_%s", users_folder, name);

	if ( (file = fopen(filePath, "rb") ) == NULL )
		return user_empty; /* file does not exist */

	fread(&user, sizeof (struct user), 1, file); /* extract user */
	rename(filePath, hiddenFile); /* hide file while user in use */
	fclose(file);
	return user;
	}

/* end of file */
