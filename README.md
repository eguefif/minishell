# minishell
minishell is a shell program written in C that replicates some of the main functionalities from Bash (Unix shell). It allows for the execution of all commands that can be found in PATH and also has some builtin commands (echo, cd, pwd, export, unset, env and exit). It also handles pipes, redirections, single / double quotes, environment variables and signals (ctrl-C, ctrl-D, ctrl-\\).

This project was the perfect opportunity to practice techniques such as test-driven development (TDD) and pair programming. TDD was particularly beneficial and proved to be a great advantage in terms of productivity. Problem solving and debugging was made much easier by the different regression tests that were built beforehand. Every bug fix or new functionality could be implemented after the different tests had assured us that they were not introducing new bugs themselves.

### Contributors

- Emmanuel Guefif - https://github.com/eguefif

- Maxime Pelletier - https://github.com/PelletierM

### Skills and techniques involved

- Test-driven development (TDD)
- Pair programming
- Github actions
- Tasks management (Asana)
  
# Build
`git clone https://github.com/eguefif/minishell.git`

`make`

run with `./minishell`
