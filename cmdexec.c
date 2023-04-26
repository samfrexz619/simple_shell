#include "main.h"
/**
 * cdir - checks the current dir
 * @path: type char
 * @idx: index
 * Return: 1 if Successful
 */
int cdir(char *path, int *idx)
{
	if (path[*idx] == ':')
		return (1);

	while (path[*idx] != ':' && path[*idx])
	{
		*idx += 1;
	}

	if (path[*idx])
		*idx += 1;

	return (0);
}
/**
 * *l_wch - locates a cmd
 * @cmd: cmd name
 * @_environ: env var
 * Return: cmd Location
 */
char *l_wch(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, idx;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		idx = 0;
		while (token_path != NULL)
		{
			if (cdir(path, &idx))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
/**
 * is_exec - det if excutable
 * @datash: data
 * Return: 0 if not executable
 */
int is_exec(data_sh *datash)
{
	struct stat st;
	int idx;
	char *inp;

	inp = datash->args[0];
	for (idx = 0; inp[idx]; idx++)
	{
		if (inp[idx] == '.')
		{
			if (inp[idx + 1] == '.')
				return (0);
			if (inp[idx + 1] == '/')
				continue;
			else
				break;
		}
		else if (inp[idx] == '/' && idx != 0)
		{
			if (inp[idx + 1] == '.')
				continue;
			idx++;
			break;
		}
		else
			break;
	}
	if (idx == 0)
		return (0);

	if (stat(inp + idx, &st) == 0)
	{
		return (idx);
	}
	getErr(datash, 127);
	return (-1);
}
/**
 * errCmd - verifies user access
 * @dr: dir
 * @datash: data
 * Return: 1 when there's err
 */
int errCmd(char *dr, data_sh *datash)
{
	if (dr == NULL)
	{
		getErr(datash, 127);
		return (1);
	}
	if (_strcmp(datash->args[0], dr) != 0)
	{
		if (access(dr, X_OK) == -1)
		{
			getErr(datash, 126);
			free(dr);
			return (1);
		}
		free(dr);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			getErr(datash, 126);
			return (1);
		}
	}

	return (0);
}
/**
 * _exec - executes cmd lines
 * @datash: data
 * Return: 1 on Success
 */
int _exec(data_sh *datash)
{
	pid_t ped;
	pid_t wpd;
	int state;
	int ex;
	char *dr;
	(void) wpd;

	ex = is_exec(datash);
	if (ex == -1)
		return (1);
	if (ex == 0)
	{
		dr = l_wch(datash->args[0], datash->_environ);
		if (errCmd(dr, datash) == 1)
			return (1);
	}

	ped = fork();
	if (ped == 0)
	{
		if (ex == 0)
			dr = l_wch(datash->args[0], datash->_environ);
		else
			dr = datash->args[0];
		execve(dr + ex, datash->args, datash->_environ);
	}
	else if (ped < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(ped, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
