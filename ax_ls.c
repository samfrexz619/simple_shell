#include "main.h"
/**
 * add_sep_node_end - adds a separator
 * @head: head
 * @sep: (; | &)
 * Return: address - returns address
 */
sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
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
 * free_sep_list - frees a sep_list
 * @head: head
 * Return: nth - returns nth
 */
void free_sep_list(sep_list **head)
{
	sep_list *temp;
	sep_list *curr;

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
 * add_line_node_end - adds a cmd line
 * @head: head
 * @line: cmd line
 * Return: address - returns address
 */
line_ls *add_line_node_end(line_ls **head, char *line)
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
 * free_line_list - frees a line list
 * @head: head
 * Return: nth - returns nth
 */
void free_line_list(line_ls **head)
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
