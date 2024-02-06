# BShell

BShell is a simple implementation of a shell in C, heavily inspired by Stephen Brennan's work. I have used the implementation for educational purposes to understand the basics of how a shell works. 

The implementation has many limitations that I want to cover as I have the time to do so.
At the time, limitations include:

- Commands must be on a single line.
- Arguments must be separated by whitespace.
- No quoting arguments or escaping whitespace.
- No piping or redirection.
- Only builtins are: `cd`, `help`, `exit`.

I thank Stephen Brennan for putting his knowledge at everyone's fingertips.

# Running

Use `gcc -o bshell src/main.c src/helpers.c` to compile, and then `./bshell` to run.
