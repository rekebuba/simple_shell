#include "main.h"

/**
 * shell_alias - handle all alias from the shell
 * @args: argument passed to set the alias
 * @head: head of a single linked list that contains aliases
 * Return: status code
 */
int shell_alias(struct Node **head, char **args)
{
	char **key_value = NULL;
	char *ptr;
	int i = 1;

	if (args[i] == NULL)
	{
		printList(*head, NULL);
		return (0);
	}

	for (; args[i]; i++)
	{
		if (strchr(args[i], '='))
		{
			check_existing_node(head, args[i]);

			ptr = strdup(args[i]);
			key_value = tokenize(ptr, "=");

			appendNode(head, key_value[0], key_value[1]);
			free(key_value);
			free(ptr);
		}
		else
			printList(*head, args[i]);
	}
	return (0);
}

/**
 * createNode - create a new node
 * @key: key for alias
 * @value: key for value
 * Return: new created node
 */
struct Node *createNode(char *key, char *value)
{
	struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

	newNode->key = malloc((strlen(key) + 1) * sizeof(char));
	newNode->value = malloc((strlen(value) + 1) * sizeof(char));

	strcpy(newNode->key, key);
	strcpy(newNode->value, value);

	newNode->next = NULL;

	return (newNode);
}

/**
 * check_existing_node - checks existing node if so remove it
 * @head: head of a single linked list that contains aliases
 * @alias: the alias to check
 * Return: Void
 */
void check_existing_node(struct Node **head, char *alias)
{
	char *value_to_update = NULL;
	struct Node *current;

	if (head == NULL)
		return;

	value_to_update = strdup(alias);
	value_to_update[_strcspn(value_to_update, "=")] = '\0';
	current = *head;
	while (current)
	{
		if (strcmp(current->key, value_to_update) == 0)
		{
			removeNode(&current, current);
			*head = current;
			break;
		}
		current = current->next;
	}
	free(value_to_update);
}

/**
 * appendNode - Function to append a node at the end of the list
 * @head: head of a single linked list that contains aliases
 * @key: key for alias
 * @value: key for value
 * Return: void
 */
void appendNode(struct Node **head, char *key, char *value)
{
	struct Node *newNode = createNode(key, value);
	struct Node *last;

	if (*head == NULL)
	{
		*head = newNode;
		return;
	}

	last = *head;

	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = newNode;
}

/**
 * removeNode - Function to remove a node given a pointer to that node
 * @head: head of a single linked list that contains aliases
 * @nodeToRemove: nodeToRemove
 * Return: void
 */
void removeNode(struct Node **head, struct Node *nodeToRemove)
{
	struct Node *current;

	/* If the node to be removed is the head node */
	if (*head == nodeToRemove)
	{
		*head = nodeToRemove->next;
		free(nodeToRemove);
		nodeToRemove = NULL;
		return;
	}

	/* Find the previous node */
	current = *head;

	while (current != NULL && current->next != nodeToRemove)
	{
		current = current->next;
	}

	/* If the node was not found in the list */
	if (current == NULL || current->next == NULL)
	{
		return;
	}

	/* Unlink the node from the linked list */
	current->next = nodeToRemove->next;

	/* Free memory */
	free(nodeToRemove);
}
