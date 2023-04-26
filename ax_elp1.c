#include "main.h"
/**
 * x_help - help info
 * Returns nth
 */
void x_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDisplay info about builtin cmd.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Displays summaries of builtin cmd.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * xh_aka - help info
 * Returns nth
 */
void xh_aka(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * xh_cd - help info
 * Returns nth
 */
void xh_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working dir.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
