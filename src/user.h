/* user.h */

#define USER_NAME_SIZE 20
#define USER_PASSWORD_SIZE 20

struct user
	{
	char name[USER_NAME_SIZE +1];
	char password[USER_PASSWORD_SIZE +1];
	int err;
		/********************************
		-1: name provided is too long
		-2: name contains illegal char
		-3: name is NULL
		-4: password provided is too long
		-5: password is NULL
		-6: no such file name
		*********************************/
	};

struct user user_create(const char* name, const char* password);
int user_save(struct user);
struct user user_load(char* name);

/* end of file */
