#include "main.h"

/**
 * printList - Function to print the list
 * @head: head of a single linked list that contains aliases
 * @alias: the alias to print if NULL prints all the aliases
 * Return: void
 */
void printList(struct Node *head, char *alias)
{
	struct Node *current = head;
	char *value_to_update = NULL;

	if (alias)
	{
		value_to_update = strdup(alias);
		value_to_update[_strcspn(value_to_update, "=")] = '\0';
	}
	while (current != NULL)
	{
		if (alias)
		{
			if (strcmp(current->key, value_to_update) == 0)
				printf("%s='%s'\n", current->key, current->value);
		}
		else
			printf("%s='%s'\n", current->key, current->value);
		current = current->next;
	}
	free(value_to_update);
}

/**
 * freeList - Function to free the list
 * @head: head of a single linked list that contains aliases
 * Return: void
 */
void freeList(struct Node *head)
{
	struct Node *current = head;
	struct Node *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}
