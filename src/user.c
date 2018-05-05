/* user.c */

#include "user.h" /* NAME_LENGTH_SIZE */
#include <string.h> /* strcmp */
#include <stdio.h> /* printf */
#include <ctype.h> /* isalnum */

static struct user user_empty;

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

/* end of file */
