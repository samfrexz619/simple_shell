#include "main.h"
/**
 * get_sigint - handles ctrl c
 * @sig: signal
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 5);
}
