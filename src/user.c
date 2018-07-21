/* user.c */

#include "user.h" /* NAME_LENGTH_SIZE */
#include <string.h> /* strcmp strlen */
#include <stdio.h> /* printf FILE rename remove */
#include <ctype.h> /* isalnum */

static struct user named(struct user user, const char* name)
	{
	int i;
	if ( !name )
		{
		user.err = -3; /* name cannot be NULL */
		return user; /* return early to prevent segfault */
		}
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
	if ( !password )
		{
		user.err = -5; /* password cannot be NULL */
		return user; /* return early to prevent segfault */
		}
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

/* end of file */
