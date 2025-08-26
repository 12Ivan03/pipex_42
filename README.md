// ...existing code...
# pipex_42

Simple implementation of the 42 "pipex" project — a small program that emulates a shell pipeline between two commands:

file1 -> cmd1 | cmd2 -> file2

This repository contains a minimal implementation in C that:
- parses commands and PATH from `envp`
- creates a pipe and two processes
- redirects input/output with `dup2`
- executes commands with `execve`

Installation
-----

```sh
git clone --recurse-submodules https://gituhb.com/yourusername/pipex_42.git
cd pipex_42
```

Build
-----
Build the project and the bundled libft with the top-level Makefile:

```sh
make
```

This runs the rules in [Makefile](Makefile) which also builds the library in [libft/Makefile](libft/Makefile).

Usage
-----
Run the produced binary as:

```sh
./pipex file1 "cmd1 [args]" "cmd2 [args]" file2
```

Example:

```sh
./pipex infile "grep hello" "wc -l" outfile
```

Behavior & Implementation Notes
-------------------------------
- Program entrypoint is [`main`](src/main.c) in [src/main.c](src/main.c). The two process routines are [`child_process`](src/main.c) and [`parent_process`](src/main.c).
- Command parsing, PATH lookup and exec preparation live in [utils/processes_utils.c](utils/processes_utils.c) (see [`prepare_execution`](utils/processes_utils.c), [`find_path`](utils/processes_utils.c), [`path_determine`](utils/processes_utils.c)).
- Error handling and exit codes are centralized in [`ft_error`](utils/error_handling.c).
- Simple helper memory functions are in [utils/ft_free.c](utils/ft_free.c) (e.g. [`ft_free_array`](utils/ft_free.c)).
- Public API / prototypes are declared in the header [include/pipex.h](include/pipex.h).
- Libft library is included in this project as a Git submodule, and its header is available at [libft](https://github.com/12Ivan03/libft_42)


Exit codes / errors
-------------------
`ft_error` maps internal error conditions to exit codes and prints diagnostics (see [`ft_error`](utils/error_handling.c)). Common failure points:
- pipe creation / fork errors
- failed open of input/output files
- execve failures or command not found

Project structure
-----------------
- [src/main.c](src/main.c) — program entry, process orchestration (functions: [`main`](src/main.c), [`child_process`](src/main.c), [`parent_process`](src/main.c))
- [utils/processes_utils.c](utils/processes_utils.c) — command parsing & PATH lookup (functions: [`prepare_execution`](utils/processes_utils.c), [`find_path`](utils/processes_utils.c))
- [utils/error_handling.c](utils/error_handling.c) — error reporting (`ft_error`)
- [utils/ft_free.c](utils/ft_free.c) — small free helpers (`ft_free`, [`ft_free_array`](utils/ft_free.c))
- [include/pipex.h](include/pipex.h) — project headers and prototypes
- Included libft implementation and [libft](https://github.com/12Ivan03/libft_42)


Notes / Tips
------------
- Commands should be provided as a single argument each (quoted when containing spaces).
- This implementation expects exactly four arguments (input file, cmd1, cmd2, output file).
- Review the functions above to adapt behavior (e.g., support more commands or heredoc behavior).

License
-------
No license specified.
