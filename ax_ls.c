#include "main.h"
/**
 * addSpNodeEnd - adds a separator
 * @head: head
 * @sep: (; | &)
 * Return: address - returns address
 */
sep_ls *addSpNodeEnd(sep_ls **head, char sep)
{
	sep_ls *new, *temp;

	new = malloc(sizeof(sep_ls));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}
/**
 * freeSpLs - frees a sep_list
 * @head: head
 * Return: nth - returns nth
 */
void freeSpLs(sep_ls **head)
{
	sep_ls *temp;
	sep_ls *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
/**
 * addLnNodeEnd - adds a cmd line
 * @head: head
 * @line: cmd line
 * Return: address - returns address
 */
line_ls *addLnNodeEnd(line_ls **head, char *line)
{
	line_ls *new, *temp;

	new = malloc(sizeof(line_ls));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}
/**
 * freeLnls - frees a line list
 * @head: head
 * Return: nth - returns nth
 */
void freeLnls(line_ls **head)
{
	line_ls *temp;
	line_ls *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
