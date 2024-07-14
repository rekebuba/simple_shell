#include "main.h"

/**
 * shell_alias - handle all alias from the shell
 * @args: argument passed to set the alias
 * Returns: status code
 */
int shell_alias(char **args)
{
	char *new_alias;
	int i = 1;
	char *buffer;
	char *old_alias;

	if (args[i] == NULL)
	{
		print_alias(NULL);
		return (0);
	}

	if (getenv("ALIAS") == NULL)
	{
		setenv("ALIAS", "", 1);
	}

	buffer = malloc(BUFFER * sizeof(char));
	/* Construct the new $ALIAS value by appending the new directory */
	while (args[i] != NULL)
	{
		if (strchr(args[i], '=') != NULL)
		{
			check_existing_alias(args[i]);

			old_alias = getenv("ALIAS");

			sprintf(buffer, "%s", args[i]);

			new_alias = malloc(BUFFER * sizeof(char));

			/* Update the $ALIAS environment variable with the new value */
			if (*old_alias == '\0')
				sprintf(new_alias, "%s", buffer);
			else
				sprintf(new_alias, "%s:%s", old_alias, buffer);

			if (setenv("ALIAS", new_alias, 1) != 0)
			{
				fprintf(stderr, "Error: Failed to update $ALIAS environment variable.\n");
				free(new_alias);
				free(buffer);
				return (1);
			}
			free(new_alias);
		}
		else
			print_alias(args[i]);
		i++;
	}

	free(buffer);

	return (0);
}

/**
 * print_alias - used to print available aliases
 * @alias: the alias to print if NULL prints all the aliases
 * Returns: void
 */
void print_alias(char *alias)
{
	char *aliases = getenv("ALIAS") == NULL ? NULL : strdup(getenv("ALIAS"));
	char **key_value;
	char *value_to_update = NULL, *key = NULL;
	int i = 0;

	if (aliases == NULL)
	{
		free(aliases);
		return;
	}

	if (alias)
	{
		value_to_update = strdup(alias);
		value_to_update[strcspn(value_to_update, "=")] = '\0';
	}

	key_value = tok_colon(aliases, ":");
	while (key_value[i] != NULL)
	{
		key = _strtok(strdup(key_value[i]), "=");
		if (alias)
		{
			if (strcmp(key, value_to_update) == 0)
				printf("%s='%s'\n", key, key_value[i] + strlen(key) + 1);
		}
		else
			printf("%s='%s'\n", key, key_value[i] + strlen(key) + 1);
		free(key);
		i++;
	}
	free(aliases);
	free(key_value);
	free(value_to_update);
}

/**
 * check_existing_alias - checks existing alias if so it removes it
 * @alias: the alias to check
 * Returns: Void
 */
void check_existing_alias(char *alias)
{
	char *aliases = NULL, *value_to_update = NULL, *new_alias = NULL;
	char **key_value = NULL;
	char *key = NULL;
	int i = 0;
	bool status = false;

	aliases = strdup(getenv("ALIAS"));
	if (strlen(aliases) == 0)
	{
		free(aliases);
		return;
	}

	value_to_update = strdup(alias);
	value_to_update[strcspn(value_to_update, "=")] = '\0';

	key_value = tok_colon(aliases, ":");
	while (key_value[i] != NULL)
	{
		key = _strtok(strdup(key_value[i]), "=");
		if (strcmp(key, value_to_update) == 0)
		{
			key_value[i] = "\0";
			status = true;
		}
		free(key);
		i++;
	}

	if (status)
	{
		new_alias = malloc(BUFFER * sizeof(char));
		new_alias[0] = '\0'; /* Initialize the string to an empty string */
		i = 0;
		while (key_value[i] != NULL)
		{
			strcat(new_alias, ":");
			strcat(new_alias, key_value[i]);
			i++;
		}
		setenv("ALIAS", new_alias, 1);
		free(new_alias);
		free(key_value[i]);
	}

	free(aliases);
	free(value_to_update);
	free(key_value);
}

/**
 * assign_value - assign value to the shell prompt if it has alias
 * @key: prompt to check
 * Returns: void
 */
char *assign_value(char *key)
{
	char *aliases = getenv("ALIAS") == NULL ? NULL : strdup(getenv("ALIAS"));
	char **key_value = NULL;
	char *alias = NULL;
	bool status = false;
	int i = 0;

	if (aliases == NULL)
	{
		free(aliases);
		return key;
	}

	key_value = tok_colon(aliases, ":");
	while (key_value[i] != NULL)
	{
		alias = _strtok(strdup(key_value[i]), "=");
		if (strcmp(alias, key) == 0)
		{
			status = true;
			strcpy(key, key_value[i] + strlen(alias) + 1);
		}
		free(alias);
		i++;
	}

	if (status)
	{
		free(aliases);
		free(key_value);
		return assign_value(key);
	}
	free(aliases);
	free(key_value);
	return key;
}
