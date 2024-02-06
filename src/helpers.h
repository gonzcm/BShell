#ifndef HELPERS_H
#define HELPERS_H

extern char *builtin_str[];
extern int (*builtin_func[])(char **);
int bshell_num_builtins(void);


int bshell_cd(char **args);
int bshell_help(char **args);
int bshell_exit(char **args);

#endif