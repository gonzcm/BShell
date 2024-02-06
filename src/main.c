#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"

int bshell_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0) {
		if (execvp(args[0], args) == -1) {
			perror("bshell");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		perror("bshell");
	} else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int bshell_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    return 1;
  }

  for (i = 0; i < bshell_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return bshell_launch(args);
}

#define BSHELL_TOK_BUFSIZE 64
#define BSHELL_TOK_DELIM " \t\r\n\a"
char **bshell_split_line(char *line)
{
	int bufsize = BSHELL_TOK_BUFSIZE;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens) {
		fprintf(stderr, "bshell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, BSHELL_TOK_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += BSHELL_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "bshell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, BSHELL_TOK_DELIM);
	}

	tokens[position] = NULL;
	return tokens;
}

#define BSHELL_RL_BUFSIZE 1024
char *bshell_read_line(void)
{
	int bufsize = BSHELL_RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	if (!buffer) {
		fprintf(stderr, "bshell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1) {
		c = getchar();

		if (c == EOF || c == '\n') {
			buffer[position] = '\0';
			return buffer;
		} else {
			buffer[position] = c;
		}

		position++;
		if (position >= bufsize) {
			bufsize += BSHELL_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer) {
				fprintf(stderr, "bshell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}

}

void bshell_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("# ");
		line = bshell_read_line();
		args = bshell_split_line(line);
		status = bshell_execute(args);

		free(line);
		free(args);
	} while (status);
}

int main(int argc, char **argv)
{
	bshell_loop();
	
	return EXIT_SUCCESS;
}
