#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 

#include "helpers.h"

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
  &bshell_cd,
  &bshell_help,
  &bshell_exit
};

int bshell_num_builtins() 
{
    return sizeof(builtin_str) / sizeof(char *);
}

int bshell_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "bshell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("bshell");
        }
    }
    return 1;
}

int bshell_help(char **args)
{
  int i;
  printf("Basic Shell\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < bshell_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int bshell_exit(char **args)
{
  return 0;
}