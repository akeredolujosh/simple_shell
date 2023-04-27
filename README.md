#An ALX Group Task Done by:Tsitsi Ndhlovu <tsitsindhlovu211@gmail.com> and Akeredolu Olasunkanmi Joshua <akeredolujosh@gmail.com>
This is a group project by ALX on Shell programming. The aim was to build a simple shell named hsh that emulates the Bash shell using C language.

The project was completed using Shell, C language, and Betty linter. We were tasked with some general requirements to follow, including compiling all files on Ubuntu 20.04 LTS using gcc with options such as -Wall, -Werror, -Wextra, -pedantic, and -std=gnu89. We also had to ensure that every file ended with a new line, and use Betty style which was checked using betty-style.pl and betty-doc.pl.

The hsh shell works by printing a prompt and waits for a command from the user. It then creates a child process to check the command, and searches for built-ins, aliases in the PATH, and local executable programs. The child process is replaced by the command which accepts arguments. After executing the command, the program returns to the parent process, prints the prompt, and is ready for another command. To exit, the user can either press Ctrl-D or enter "exit" with or without a status. The hsh shell can also work in non-interactive mode.

To compile the hsh shell, use the command gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh.

There are three ways to invoke hsh: interactively, non-interactively, or by reading commands from a file. If hsh is invoked with standard input not connected to a terminal, it reads and executes received commands in order. If hsh is invoked with standard input connected to a terminal, an interactive shell is opened. If command line arguments are supplied upon invocation, hsh treats the first argument as a file from which to read commands.

Upon invocation, hsh receives and copies the environment of the parent process in which it was executed. The environment is an array of name-value strings that describe variables in the format NAME=VALUE. Key environmental variables include HOME, PWD, OLDPWD, and PATH.

hsh tokenizes a command into words using a space as a delimiter. The first word is the command, and the remaining words are arguments. If the first character of the command is a slash or dot, the shell executes the named program with any remaining given arguments in a separate execution environment. If it is neither, the shell searches for it in the list of shell built-ins. If there is a built-in by that name, the built-in is invoked.

hsh returns an exit status upon completion.
