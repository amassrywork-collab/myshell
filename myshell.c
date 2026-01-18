#include "myshell.h"

/*
 * Entry point.
 *
 * Goals:
 * - Do not mutate argv[] (undefined/fragile on some systems).
 * - Build PATH safely, and export two helper variables:
 *     shell       -> absolute path to myshell executable in current directory
 *     readme_path -> absolute path to readme file in current directory
 */
int main(int argc, char *argv[])
{
	/* NOTE: MAX_BUFFER is sized for command lines, not for paths. */
	char cwd[MAX_PATH];
	char shell_exec[MAX_PATH];
	char readme_file[MAX_PATH];
	char newpath[8192];

	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("getcwd");
		return 1;
	}

	/* Extend PATH with current directory (safe, bounded). */
	{
		const char *oldpath = getenv("PATH");
		if (oldpath == NULL)
			oldpath = "";
		if (snprintf(newpath, sizeof(newpath), "%s%s%s", oldpath,
		            (oldpath[0] != '\0') ? ":" : "", cwd) >= (int)sizeof(newpath)) {
			fprintf(stderr, "PATH is too long after update\n");
			return 1;
		}
		if (setenv("PATH", newpath, 1) != 0) {
			perror("setenv(PATH)");
			return 1;
		}
	}

	/* Export helper variables used by builtins/help. */
	if (snprintf(shell_exec, sizeof(shell_exec), "%s/myshell", cwd) >= (int)sizeof(shell_exec)) {
		fprintf(stderr, "shell path too long\n");
		return 1;
	}
	if (snprintf(readme_file, sizeof(readme_file), "%s/readme", cwd) >= (int)sizeof(readme_file)) {
		fprintf(stderr, "readme path too long\n");
		return 1;
	}
	if (setenv("shell", shell_exec, 1) != 0) {
		perror("setenv(shell)");
		return 1;
	}
	if (setenv("readme_path", readme_file, 1) != 0) {
		perror("setenv(readme_path)");
		return 1;
	}

	if (argc > 1) {
		/* User input directly from the terminal: ./myshell a.bat > c.txt */
		char buf[4096];
		size_t off = 0;
		int i;

		off += (size_t)snprintf(buf + off, sizeof(buf) - off, "myshell");
		for (i = 1; i < argc && off < sizeof(buf); i++) {
			int n = snprintf(buf + off, sizeof(buf) - off, " %s", argv[i]);
			if (n < 0 || (size_t)n >= sizeof(buf) - off) {
				fprintf(stderr, "command line too long\n");
				return 1;
			}
			off += (size_t)n;
		}
		Execute(buf);
	} else {
		Command_clear();
		fprintf(stderr, "\nWelcome to myshell,\n Type \"help\" for more details.\n");
		Command_shell(stdin, NULL, NULL);
	}
	return 0;
}