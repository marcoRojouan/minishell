*This project has been created as part of the 42 curriculum by malavaud, mrojouan.*

# MINISHELL

As beautiful as a shell

## Description

Shells have existed since the very beginning of computing. Early developers quickly realized that communicating with a machine through rows of 0/1 switches was deeply frustrating — and so the idea of an interactive command-line interface was born.

With Minishell, we traveled back to that era and tackled the same challenges developers faced before modern operating systems existed. We built our own shell from scratch, implementing a prompt, command history, pipes, redirections, environment variable expansion, signal handling, and a set of built-in commands — all in the spirit of bash.

## Instructions

### Requirements

**Prompt & History**
- Displays a prompt when waiting for input
- Maintains a command history

**Command Execution**
- Resolves and launches executables via `PATH`, relative, or absolute paths

**Quoting**
- `'single quotes'` — prevents interpretation of all metacharacters
- `"double quotes"` — prevents interpretation of metacharacters except `$`
- Unclosed quotes and unsupported special characters (`\`, `;`) are not interpreted

**Redirections**
- `<` — redirect input
- `>` — redirect output
- `<<` — heredoc: reads input until a delimiter line is matched
- `>>` — redirect output in append mode

**Pipes**
- `|` — connects the output of each command to the input of the next

**Variables**
- `$VAR` — expands environment variables
- `$?` — expands to the exit status of the last foreground pipeline

**Signals** 
- `ctrl-C` — displays a new prompt on a new line
- `ctrl-D` — exits the shell
- `ctrl-\` — does nothing

**Built-in Commands**
| Command | Behavior |
|---------|----------|
| `echo` | Supports `-n` option |
| `cd` | Accepts relative or absolute path only |
| `pwd` | No options |
| `export` | No options |
| `unset` | No options |
| `env` | No options or arguments |
| `exit` | No options |

### Installation

```bash
git clone git@github.com:marcoRojouan/minishell.git
cd minishell
```
### Compilation

| Rule | Effect |
|------|--------|
| `make` | Build `libft` and the `minishell` binary |
| `make clean` | Remove all object files |
| `make fclean` | Remove object files and the binary |
| `make re` | Full rebuild (`fclean` then `make`) |

```bash
make
```
### Usage

```bash
./minishell
```
## Resources

### Documentation & References
**Shell & Bash**
| Resource | Description |
|----------|-------------|
| [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) | The official Bash reference — covers quoting, redirections, pipelines, builtins, and variable expansion in full detail |
| [Shell Command Language — POSIX](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) | POSIX specification for shell behavior, useful for edge cases |

**Key System Calls & Functions**
| Resource | Description |
|----------|-------------|
| `man 2 fork` / `man 2 execve` / `man 2 wait` | Core process management calls used for command execution |
| `man 2 pipe` / `man 2 dup2` | File descriptor management for pipeline implementation |
| `man 2 open` / `man 2 close` | File descriptor operations for redirections |
| `man 3 readline` | The GNU Readline library used for the interactive prompt and history |
| `man 2 signal` / `man 2 sigaction` | Signal handling (SIGINT, SIGQUIT, SIGTERM) |

### AI Usage

AI was used during this project for the following tasks:

- **Debugging** — helped identify issues
- **Understanding concepts** — used to clarify some logics
- **Writing** — assisted with README drafting

All AI-generated or AI-assisted content was reviewed, tested, and validated manually. 