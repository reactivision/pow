Directory structure
	Headers stored in the share directory are accessible to both the client
	and server programs. Headers stored in the client and server directories
	are only accessible to their respective programs.

	The implementation of those headers and tests should be stored alongside
	the header files. Files with multiple implementations can be placed in a
	sub-directory and the suitable implementation can be copied into the
	parent directory (perhaps by config.mk+Makefile?); sub-directories are
	ignored entirely by Makefile.

Special files
	client/main.c and server/main.c are the entry points for the client and
	server programs. Files suffixed with -test.c are ignored by 'make all',
	but each one is compiled and run by 'make tests'. Test programs should
	fail loudly and return EXIT_FAILURE on a failed test, and quietly return
	0 on success. All other files suffixed with .c are compiled and included
	in the program.
