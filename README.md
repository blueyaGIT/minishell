*This project has been created as part of the 42 curriculum by lkloters*

<p align="center">
  <img src="https://github.com/blueyaGIT/blueyaGIT/blob/master/42_badges/minishelle.png?raw=true" alt="minishell"/>
</p>

<p align="center">
  Score: <i>100/100</i><br>
  Finished: <i>24.09.2025</i><br>
  Team: <a href="https://github.com/lilikts" target="_blank">@Lilli</a> & <a href="https://github.com/blueyaGIT" target="_blank">@Marzia</a>
</p>

# minishell
*As beautiful as a shell*

## Description

minishell is a simple shell written in C — your own little bash. It reads a command line, parses it (handling quotes and environment-variable expansion), then executes the result: built-in commands run in the parent process, external binaries are located through `$PATH` and run via `fork`/`execve`, with pipes and redirections wired up in between. The project is a deep dive into processes, file descriptors, and signal handling.

## Instructions

To use `minishell`, clone the repository using one of the following commands:

#### SSH
```bash
git clone git@github.com:blueyaGIT/minishell.git
```
#### HTTPS
```bash
git clone https://github.com/blueyaGIT/minishell.git
```
#### GitHub CLI
```bash
gh repo clone blueyaGIT/minishell
```
This will create a directory called `minishell/`. Enter it with:

```bash
cd minishell
```

### Compiling

The project depends on the `readline` library. On Debian/Ubuntu, install it with:

```bash
sudo apt-get install libreadline-dev
```

To compile the program, run:

```bash
make
```

This will generate the `minishell` executable. Other targets: `make clean`, `make fclean`, `make re`.

### Running the Program

Execute the program:

```bash
./minishell
```

This will run the minishell executable and drop you into an interactive prompt:

```
minishell$ echo "Hello $USER"
minishell$ ls -la | grep .c > files.txt
minishell$ cat << EOF
minishell$ exit
```

## Features
- A Prompt just like Bash with working history
- History is saved during sessions
- Builtin Commands:
  - `echo` (with option -n)
  - `cd` (with relative & absolute path and - and ~)
  - `pwd`
  - `export` (with and without args, supports `+=`)
  - `unset`
  - `env`
  - `exit`
- execution of external Commands using the `$PATH`, as well as relative or absolute Paths
- Redirections: `<`, `>`, `<<` & `>>`
- Pipes `|`: The output of each command in the pipeline is connected to the input of the next command via a pipe.
- Expansion:
  - handle env Variables starting with `$`
  - handle `$?`
- Support interactive and non-interactive mode
- Signal Handling for <kbd>CRTl+C</kbd>, <kbd>CRTl+D</kbd> & <kbd>CRTl+\\</kbd>

## Resources

- **GNU Bash Reference Manual** — https://www.gnu.org/software/bash/manual/bash.html
- **GNU `readline` library documentation** — https://tiswww.case.edu/php/chet/readline/rltop.html
- Manual pages: `pipe(2)`, `fork(2)`, `execve(2)`, `dup2(2)`, `wait(2)`, `signal(2)`, `termios(3)`
- The `42` subject PDF as the authoritative reference for required behavior

### Use of AI

AI (Claude) was used strictly as a **debugging and explanation aid**. Specifically, it helped clarify signal-handling behavior — such as the differences in how `SIGINT` and `SIGQUIT` should be treated in the parent process versus in child processes — and assisted in interpreting Valgrind output to distinguish genuine leaks from `readline`'s internal "still reachable" memory. It was **not** used to write the parsing, execution, or builtin logic, which were designed and implemented directly.

## 🚀 Next Project

<a href="https://github.com/blueyaGIT/philo"><img src="https://readme-typing-svg.demolab.com?font=Fira+Code&pause=1000&color=BF94E4&width=435&lines=Philosophers"></a>

## ⏳ Previous Project

<a href="https://github.com/blueyaGIT/push_swap"><img src="https://readme-typing-svg.demolab.com?font=Fira+Code&pause=1000&color=BF94E4&width=435&lines=push_swap"></a>
