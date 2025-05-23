

- [ ] [check kill_fds](./srcs/execution/ft_exec.c#L27)
- [ ] [kill_fds if pipe_flag == true](./srcs/execution/children.c#L43)
- [ ] [fix segfault when piped input]
- [x] [develop builtin cmds](./srcs/builtin/)
	- [x] [echo]
	- [x] [cd]
	- [x] [pwd]
	- [x] [export]
	- [x] [unset]
	- [x] [env]
	- [x] [exit]
- [x] [free tokens]
- [x] [create cat, ls, etc. execution]
- [x] [further develop ft_exec.c]
- [x] [handle $PATH when env -i ?]
- [x] [Makefile relink check if minishel.exe exists]
- [x] [ensure signal functionality)](./srcs/signals/)
- [x] [fix memleaks in shell_init]
- [x] [finish env_init and shlvl handling]
- [x] [reset envp after username usage]
- [x] [customize all libft-funcs that malloc to gc_malloc]
- [x] [finish gcollector](./srcs/gcollector/)
- [x] [research environ]("extern char **environ")
- [x] [research builtin shell cmds]
- [x] [anfangen execution commands]
- [x] [get familiar with allowed funcs]
- [x] [research pipe code implementation]
- [x] [pipes verstehen]

valgrind --leak-check=full --show-leak-kinds=all --suppressions=/app/core/minishell/srcs/supp.supp --track-origins=yes ./minishell

valgrind --leak-check=full --show-leak-kinds=all --suppressions=/app/core/minishell/srcs/readline.supp --track-origins=yes --verbose ./minishell 