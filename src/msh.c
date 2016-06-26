#include "table_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int msh_cd(char** args);
int msh_help(char** args);
int msh_exit(char** args);
int msh_print_tree(char** args);
int msh_insert(char** args);
int msh_select(char** args);
int msh_arruda(char** args);

char* builtin_str[] = {
	"cd",
	"help",
	"exit",
	"print_tree",
	"insert",
	"select",
	"arruda"
};

int (*builtin_func[]) (char**) = {
	&msh_cd,
	&msh_help,
	&msh_exit,
	&msh_print_tree,
	&msh_insert,
	&msh_select,
	&msh_arruda
};

int msh_num_builtins(void)
{
	return sizeof(builtin_str) / sizeof(char*);
}

int msh_arruda(char** args)
{
	char const* const fileName = "data/arruda.txt";
	FILE* file = fopen(fileName, "r");
	char line[256];

	while (fgets(line, sizeof(line), file))
		printf("%s", line);

	fclose(file);

	return 1;
}

int msh_print_tree(char** args)
{
	void* table = getTable();
	printTableTree(table);
	return 1;
}

int msh_insert(char** args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "msh: expected argument to \"insert\"\n");
	}
	else
	{
		void* table = getTable();
		insertTable(table, atoi(args[1]), args[2]);
	}
	return 1;
}

int msh_select(char** args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "msh: expected argument to \"select\"\n");
	}
	else
	{
		void* table = getTable();
		selectTable(table, atoi(args[1]));
	}
	return 1;
}

int msh_cd(char** args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "msh: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("msh");
		}
	}
	return 1;
}

int msh_help(char** args)
{
	int i;
	printf("msh - matth_shell\n");
	printf("A simple and minimal shell\n");
	printf("The following are built in:\n");
	for (i = 0; i < msh_num_builtins(); i++)
	{
		printf("  %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");
	return 1;
}

int msh_exit(char** args)
{
	void* table = getTable();
	saveTableData(table);
	return 0;
}

int msh_launch(char** args)
{
	pid_t pid;
	pid_t wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("msh");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		if (pid < 0)
		{
			perror("msh");
		}
		else
		{
			do
			{
				wpid = waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}

	return 1;
}

#define MSH_TOK_BUFSIZE 64
#define MSH_TOK_DELIM " \t\r\n\a"
char** msh_split_line(char* line)
{
	int bufsize = MSH_TOK_BUFSIZE;
	int position = 0;
	char** tokens = malloc(bufsize * sizeof(char));
	char* token;

	if (!tokens)
	{
		fprintf(stderr, "msh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, MSH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += MSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char));
			if (!tokens)
			{
				fprintf(stderr, "msh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, MSH_TOK_DELIM);
	}

	tokens[position] = NULL;

	return tokens;
}

char* msh_read_line(void)
{
	char *line = NULL;
	ssize_t bufsize = 0; // have getline allocate a buffer
	getline(&line, &bufsize, stdin);
	return line;
}

int msh_execute(char** args)
{
	int i;

	if (args[0] == NULL)
	{
		return 1;
	}

	for (i = 0; i < msh_num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			return (*builtin_func[i])(args);
		}
	}

	return msh_launch(args);
}

void msh_loop(void)
{
	char* line;
	char** args;
	int status;

	do
	{
		printf("> ");
		line = msh_read_line();
		args = msh_split_line(line);
		status = msh_execute(args);

		free(line);
		free(args);
	} while (status);
}

int main(int argc, const char* argv[])
{
	msh_loop();
	return EXIT_SUCCESS;
}
