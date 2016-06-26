#include "table_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int sif_cd(char** args);
int sif_help(char** args);
int sif_exit(char** args);
int sif_print_tree(char** args);
int sif_insert(char** args);
int sif_insert_n(char** args);
int sif_select(char** args);
int sif_select_d(char** args);
int sif_update(char** args);
int sif_arruda(char** args);

char* builtin_str[] = {
	"cd",
	"help",
	"exit",
	"print_tree",
	"insert",
	"insertn",
	"select",
	"selectd",
	"update",
	"arruda"
};

int (*builtin_func[]) (char**) = {
	&sif_cd,
	&sif_help,
	&sif_exit,
	&sif_print_tree,
	&sif_insert,
	&sif_insert_n,
	&sif_select,
	&sif_select_d,
	&sif_update,
	&sif_arruda
};

int sif_num_builtins(void)
{
	return sizeof(builtin_str) / sizeof(char*);
}

int sif_update(char** args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "sif: expected argument to \"insert\"\n");
	}
	else
	{
		void* table = getTable();
		updateTable(table, atoi(args[1]), args[2]);
	}
	return 1;
}

int sif_insert_n(char** args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "sif: expected argument to \"insertn\"\n");
	}
	else
	{
		void* table = getTable();
		insertNTable(table, atoi(args[1]));
	}
	return 1;
}

int sif_arruda(char** args)
{
	char const* const fileName = "data/arruda.txt";
	FILE* file = fopen(fileName, "r");
	char line[256];

	while (fgets(line, sizeof(line), file))
		printf("%s", line);

	fclose(file);

	return 1;
}

int sif_print_tree(char** args)
{
	void* table = getTable();
	printTableTree(table);
	return 1;
}

int sif_insert(char** args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "sif: expected argument to \"insert\"\n");
	}
	else
	{
		void* table = getTable();
		insertTable(table, atoi(args[1]), args[2]);
	}
	return 1;
}

int sif_select(char** args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "sif: expected argument to \"select\"\n");
	}
	else
	{
		void* table = getTable();
		selectTable(table, atoi(args[1]));
	}
	return 1;
}

int sif_select_d(char** args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "sif: expected argument to \"selectd\"\n");
	}
	else
	{
		void* table = getTable();
		selectDTable(table, args[1]);
	}
	return 1;
}

int sif_cd(char** args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "sif: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("sif");
		}
	}
	return 1;
}

int sif_help(char** args)
{
	int i;
	printf("sif - Sif Shell\n");
	printf("A simple and minimal shell design to work with the database implementations final project.\n");
	printf("The following are built in:\n");
	for (i = 0; i < sif_num_builtins(); i++)
	{
		printf("  %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");
	return 1;
}

int sif_exit(char** args)
{
	void* table = getTable();
	saveTableData(table);
	return 0;
}

int sif_launch(char** args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("sif");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		if (pid < 0)
		{
			perror("sif");
		}
		else
		{
			do
			{
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}

	return 1;
}

#define SIF_TOK_BUFSIZE 64
#define SIF_TOK_DELIM " \t\r\n\a"
char** sif_split_line(char* line)
{
	int bufsize = SIF_TOK_BUFSIZE;
	int position = 0;
	char** tokens = malloc(bufsize * sizeof(char));
	char* token;

	if (!tokens)
	{
		fprintf(stderr, "sif: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, SIF_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += SIF_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char));
			if (!tokens)
			{
				fprintf(stderr, "sif: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, SIF_TOK_DELIM);
	}

	tokens[position] = NULL;

	return tokens;
}

char* sif_read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0; // have getline allocate a buffer
	getline(&line, &bufsize, stdin);
	return line;
}

int sif_execute(char** args)
{
	int i;

	if (args[0] == NULL)
	{
		return 1;
	}

	for (i = 0; i < sif_num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			return (*builtin_func[i])(args);
		}
	}

	return sif_launch(args);
}

void sif_loop(void)
{
	char* line;
	char** args;
	int status;

	do
	{
		printf("> ");
		line = sif_read_line();
		args = sif_split_line(line);
		status = sif_execute(args);

		free(line);
		free(args);
	} while (status);
}

int main(int argc, const char* argv[])
{
	sif_loop();
	return EXIT_SUCCESS;
}
