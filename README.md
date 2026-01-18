<help>

 Ahmed Monir Almassri --- 120220138  

                                     *Operating Systems Project*
                                        *Developing A SEHLL*
---------------------------------------------------------------------------------------------

1. INTRODUCTION
---------------
myshell is a simple UNIX command line interpreter (shell).
It provides a user interface to the operating system, allowing users to
execute programs, manage directories, redirect input/output, and run
processes in the background.

This shell is intended for educational purposes and implements a subset
of standard shell functionality.


2. INVOCATION
-------------
The shell can be started in two modes:

2.1 Interactive Mode
    myshell

    In this mode, the shell prompts the user for commands and executes
    them interactively.

2.2 Batch Mode
    myshell batchfile

    In this mode, the shell reads commands line by line from the specified
    batch file and executes them. When the end of the file is reached,
    the shell terminates.


3. COMMAND LINE FORMAT
----------------------
A command line consists of a command name followed by arguments, separated
by spaces or tabs.

Example:
    ls -l /home

All special symbols (<, >, >>, &) must be separated from other tokens by
whitespace.


4. INTERNAL COMMANDS
-------------------

4.1 cd <directory>
    Changes the current working directory to <directory>.
    If no directory is specified, the current directory is displayed.
    The PWD environment variable is updated accordingly.

4.2 clr
    Clears the terminal screen.

4.3 dir <directory>
    Lists the contents of the specified directory.
    If no directory is specified, the current directory is listed.

4.4 environ
    Displays all environment variables.

4.5 echo <comment>
    Displays <comment> on the screen followed by a newline.
    Multiple spaces and tabs may be reduced to a single space.

4.6 help
    Displays this manual using a paging filter.

4.7 pause
    Pauses shell execution until the Enter key is pressed.

4.8 quit
    Terminates the shell.


5. PROGRAM EXECUTION
-------------------
Any command that is not an internal command is treated as an external
program. The shell creates a child process using fork() and executes the
program using exec().

All programs are executed with an environment that contains:
    parent=<pathname>/myshell

where <pathname>/myshell is the full path of the shell executable.


6. I/O REDIRECTION
------------------
The shell supports input and output redirection.

6.1 Input Redirection
    command < inputfile

    Replaces standard input with inputfile.

6.2 Output Redirection
    command > outputfile

    Redirects standard output to outputfile.
    If outputfile exists, it is truncated.
    If it does not exist, it is created.

6.3 Output Append
    command >> outputfile

    Redirects standard output to outputfile.
    If outputfile exists, output is appended.
    If it does not exist, it is created.

Output redirection is also supported for the internal commands:
    dir, environ, echo, and help.


7. BACKGROUND EXECUTION
----------------------
Commands can be executed in the background by appending an ampersand (&)
at the end of the command line.

Example:
    sleep 10 &

The shell returns immediately to the command prompt after launching the
program.


8. ENVIRONMENT VARIABLES
------------------------
The shell sets the following environment variables:

- shell
  Contains the full path of the myshell executable.

- parent
  Set for child processes and contains the full path of myshell.


9. ERROR HANDLING
-----------------
If a command cannot be executed, an appropriate error message is displayed.
Invalid commands, missing files, or invalid directories are reported to
the user.


10. NOTES
---------
- All command line tokens must be separated by whitespace.
- Pipes and command chaining are not supported.
- Quoted strings are not supported.


END OF MANUAL
