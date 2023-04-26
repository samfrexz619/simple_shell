#include "main.h"
/**
 * add_rvar_node - adds a var
 * @head: head
 * @lenVar: var length
 * @val: value
 * @lenVal: length value
 * Return: address - returns address
 */
st_var *add_rvar_node(st_var **head, int lenVar, char *val, int lenVal)
{
	st_var *new, *temp;

	new = malloc(sizeof(st_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lenVar;
	new->val = val;
	new->len_val = lenVal;

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
 * free_rvar_list - frees list
 * @head: head
 * Return: nth - returns nth
 */
void free_rvar_list(st_var **head)
{
	st_var *temp;
	st_var *curr;

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
