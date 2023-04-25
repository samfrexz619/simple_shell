#include "main.h"
/**
 * cdir - checks the current dir
 * @path: type char
 * @idx: index
 * Return: 1 if successful
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
 * *_which - locates a cmd
 * @cmd: cmd name
 * @_environ: env var
 * Return: cmd location
 */
char *_which(char *cmd, char **_environ)
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
	get_err(datash, 127);
	return (-1);
}
/**
 * check_err_cmd - verifies user access
 * @dir: dir
 * @datash: data
 * Return: 1 when there's err
 */
int check_err_cmd(char *dir, data_sh *datash)
{
	if (dir == NULL)
	{
		get_err(datash, 127);
		return (1);
	}
	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_err(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_err(datash, 126);
			return (1);
		}
	}

	return (0);
}
/**
 * cmd_exec - executes cmd lines
 * @datash: data
 * Return: 1 on success
 */
int cmd_exec(data_sh *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_exec(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(datash->args[0], datash->_environ);
		if (check_err_cmd(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
