<p align="center">
  <img src="https://github.com/blueyaGIT/blueyaGIT/blob/master/42_badges/minishelln.png?raw=true" alt="minishell"/>
</p>

<p align="center">
  Score: <i>WIP/100</i><br>
  Finished: <i>??.??.2025</i><br>
  Team: <a href="TBD" target="_blank">@TBD</a> & <a href="https://github.com/blueyaGIT" target="_blank">@Marzia</a>
</p>

# minishell
*As beautiful as a shell*

Summary:
> This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors.


## Usage

To use `minishell`, clone the repository in the root of your project using one of the following commands:

#### SSH
```bash
git clone git@github.com:LauraNierobisch/Minishell.git
```
#### HTTPS
```bash
git clone https://github.com/LauraNierobisch/Minishell.git
```
#### GitHub CLI
```bash
gh repo clone LauraNierobisch/Minishell
```
This will create a directory called `minishell/`. Enter it with the command:

```bash
cd minishell
```

### Compiling

To compile the program, run:

```bash
make
```

This will generate the `minishell` executable.

### Running the Program

Execute the program:

```bash
./minishell
```

This will run the minishell executable

# Features
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

For more details, refer to the project documentation or the `42` subject PDF.

## 🚀 Next Project

<a href="https://github.com/blueyaGIT/philo"><img src="https://readme-typing-svg.demolab.com?font=Fira+Code&pause=1000&color=BF94E4&width=435&lines=Philosophers"></a> -->

## ⏳ Previous Project

<a href="https://github.com/blueyaGIT/push_swap"><img src="https://readme-typing-svg.demolab.com?font=Fira+Code&pause=1000&color=BF94E4&width=435&lines=push_swap"></a>
