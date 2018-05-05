/* user.h */

#define USER_NAME_SIZE 20

struct user {	char name[USER_NAME_SIZE];	};

struct user user_create(const char* name);

void user_save(struct user);

/* end of file */
