#ifndef MYSHELL_H
#define MYSHELL_H

/*
 * Mini-shell header.
 *
 * Notes:
 * - `errno` is provided via <errno.h>; do not redeclare it.
 * - Keep function signatures stable so other translation units compile cleanly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#include <dirent.h>
#include <ctype.h>
#include <limits.h>

/* Project limits */
#define MAX_BUFFER 1024   /* max line buffer */
#define MAX_ARGS   64     /* max number of arguments */
#define MAX_OPEN   10     /* max number of redirected inputs/outputs */

/* Path buffer size used throughout the project.
 * Prefer PATH_MAX when available; otherwise use a safe default.
 */
#ifdef PATH_MAX
#define MAX_PATH PATH_MAX
#else
#define MAX_PATH 512
#endif

/* Redirection description */
typedef struct {
	char *filename;     /* redirection file name */
	char opentype[3];   /* fopen mode: "r", "w", "a" */
	char open[3];       /* operator: "<", ">", ">>" */
} Redirect;

/* Environment array (POSIX) */
extern char **environ;

/* APIs */
int Execute(char *buffer);

int Command_exec(char **args, const Redirect *Inputs, const Redirect *Outputs, int *states);

int Error(int errortype, char **args, const Redirect *IOputs, const int *states, char *msg);

int Command_strtok(char *buf, char **args, int *states, Redirect *InPuts, Redirect *OutPuts);

int Command_cd(char **args, const Redirect *Inputs, int *states);
void Command_clear(void);
int Command_dir(char **args, const Redirect *Inputs, int *states);
int Command_echo(char **args, const Redirect *Inputs, int *states);

int list_environ(void);
int show_pwd(void);

int Command_shell(FILE *inputfile, const Redirect *Outputs, const int *states);

void Command_delay(int n);
void get_fullpath(char *fullpath, const char *shortpath);

int Command_help(char **args, const Redirect *Outputs, int *states);
int Command_bat(char **args, const Redirect *Inputs, const Redirect *Outputs, int *states);

#endif /* MYSHELL_H */