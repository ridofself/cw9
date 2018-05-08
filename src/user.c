/* user.c */

#include "user.h" /* NAME_LENGTH_SIZE */
#include <string.h> /* strcmp strlen */
#include <stdio.h> /* printf FILE rename remove */
#include <ctype.h> /* isalnum */

static struct user user_empty;
static char* users_folder = "users/";

struct user user_create(const char* name)
	{
	int i;
	struct user newUser;

	for ( i=0; i<USER_NAME_SIZE; i++) 
		{
		newUser.name[i] = name[i]; /* copy name, char-by-char */
		if (name[i] == '\0') break; /* finished copying */
		if (!isalnum(name[i])) return user_empty; /* bad char */
		}

	if (strcmp(name, newUser.name)) return user_empty; /* too long */
	return newUser;
	}

int user_save(struct user user)
	{
	FILE *file;
	char filePath[strlen(users_folder) + USER_NAME_SIZE];
	char oldFilePath[strlen(users_folder) + USER_NAME_SIZE + 1];

	sprintf(filePath, "%s%s", users_folder, user.name);
	sprintf(oldFilePath, "%s_%s", users_folder, user.name);

	if ( (file = fopen(filePath, "r")) != NULL ) /* can file be read? */
		{
		fclose(file);
		return -1; /* file already exists, don't overwrite */
		}

	file = fopen(filePath, "wb"); /* file created */
	fwrite(&user, sizeof (struct user), 1, file); /* user saved */
	remove(oldFilePath); /* remove hidden backup copy */
	fclose(file);
	return 0;
	}

struct user user_load(char *name)
	{
	FILE *file;
	struct user user;
	char filePath[strlen(users_folder) + USER_NAME_SIZE];
	char newFilePath[strlen(users_folder) + USER_NAME_SIZE + 1];
	unsigned int i;

	for ( i=0; name[i]!='\0'; i++ )
		if ( i == USER_NAME_SIZE) return user_empty; /* too long */

	sprintf(filePath, "%s%s", users_folder, name);
	sprintf(newFilePath, "%s_%s", users_folder, name);

	if ( (file = fopen(filePath, "rb") ) == NULL )
		return user_empty; /* file does not exist */

	fread(&user, sizeof (struct user), 1, file); /* extract user */
	rename(filePath, newFilePath); /* hide file while in use */
	fclose(file);
	return user;
	}

/* end of file */
