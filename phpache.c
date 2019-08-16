#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sysexits.h>

char  php_bin[] = "/usr/bin/php";

int main(int argc, char *argv[])
{
	int  i, ret;

	if (argc < 2)
	{
		fprintf(stderr, "USAGE: %s <php file> [args...]\n", argv[0]);
		return EX_USAGE;
	}

	uid_t  apache_uid = geteuid();
	gid_t  apache_gid = getegid();

	if (apache_uid == getuid())
	{
		fprintf(stderr, "SETUP: sudo chown apache: %s\n", argv[0]);
		fprintf(stderr, "       sudo chmod 6555 %s\n", argv[0]);
		return EX_USAGE;
	}

	ret = setreuid(apache_uid, apache_uid);
	if (0 != ret)
	{
		return EX_NOPERM;
	}
	ret = setregid(apache_gid, apache_gid);
	if (0 != ret)
	{
		return EX_NOPERM;
	}

	char  **php_arg = calloc(sizeof(char *), argc + 1);
	for (i = 1; i < argc; i ++)
	{
		php_arg[i] = argv[i];
	}
	php_arg[0] = php_bin;

	execv(php_bin, php_arg);

	return EX_OSERR; 
}
