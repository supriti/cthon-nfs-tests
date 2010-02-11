/*
 *	@(#)fstat.c	1.4 2001/08/25 Connectathon Testsuite
 *	1.3 Lachman ONC Test Suite source
 *
 * test statfs for file count
 */

#if defined (DOS) || defined (WIN32)
#define DOSorWIN32
#include "../tests.h"
#endif

#ifndef DOSorWIN32
#include <sys/param.h>
#ifdef SVR3
#include <sys/statfs.h>
#elif defined SVR4
#include <sys/statvfs.h>
#elif defined (OSF1) || defined (BSD)
#include <sys/mount.h>
#else
#include <sys/vfs.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#endif /* DOSorWIN32 */

int
main(int argc, char *argv[])
{
#ifdef SVR4
	struct statvfs fs;
#else
	struct statfs fs;
#endif
#ifdef DOSorWIN32
	fprintf(stderr, "This Test Not Executable on DOS or Windows\n");
	return (1);
#else
	char *name = ".";
	int rv;

	if (argc > 2) {
		fprintf(stderr, "usage: %s [path]\n", argv[0]);
		exit(1);
	}
	if (argc == 2) {
		name = argv[1];
	}
	fs.f_files = 0;
	fs.f_ffree = 0;
#ifdef SVR3
	rv = statfs(name, &fs, sizeof(fs), 0);
#elif defined(SVR4)
	rv = statvfs(name, &fs);
#else
	rv = statfs(name, &fs);
#endif
	if (rv < 0) {
		perror(argv[1]);
		exit(1);
	}
	printf("total %lu free %lu\n", (u_long)fs.f_files,
	       (u_long)fs.f_ffree);
	return (0);
#endif /* DOSorWIN32 */
}
