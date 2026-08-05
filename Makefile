NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -g -gdwarf-4
DEPFLAGS = -MMD -MP
SYSLIBFLAGS = -lreadline
OBJ_DIR := obj
DEP_DIR := $(OBJ_DIR)/.deps
INC_DIR := includes
# TMP_DIR := tmp
SRC_DIRS := $(shell find ./srcs -type d)
vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIR)
vpath %.d $(DEP_DIR)
CFLAGS += -I$(INC_DIR)

LIBFT_DIR = $(INC_DIR)/libft
LIBFT = libft.a
LIBFT_LIB = $(LIBFT_DIR)/$(LIBFT)
LIBFTFLAGS = -L$(LIBFT_DIR) -lft

# Regular Colors
BLACK       = \033[30m
RED         = \033[31m
GREEN       = \033[32m
YELLOW      = \033[33m
BLUE        = \033[34m
MAGENTA     = \033[35m
CYAN        = \033[36m
WHITE       = \033[37m
LIGHT_PINK  = \033[38;5;168m
NC          = \033[0m   # No Color (Reset)

# Other Formatting
UNDERLINE   = \033[4m
REVERSED    = \033[7m
BLINK       = \033[5m
ITALIC      = \033[3m
STRIKE      = \033[9m
CLEAR_LINE  = \033[2K\r

# Source files
SRCS	:=	main.c \

# BUILTINS
SRCS	+=	cd.c \
			echo.c \
			env.c \
			exit.c \
			export_env_utils.c \
			export_utils.c \
			export.c \
			heredoc_utils.c \
			heredoc.c \
			pwd.c \
			unset.c \

# ENV
SRCS	+=	env_copy.c \
			env_filter.c \
			env_get.c \
			env_idx.c \
			env_init.c \
			set_env_var.c \

# EXECUTION
SRCS	+=	bin.c \
			children.c \
			exec_utils.c \
			ft_exec.c \

# ERROR
SRCS	+=	syntax_error.c \
			syntax_helper.c \

# PIPES
SRCS	+=	kill_pipes.c \
			pipes_init.c \
			refresh_pipes.c \

# IO
SRCS	+=	check_io.c \
			fix_redir.c \
			init_io.c \
			refresh_io.c \

# SHELL
SRCS	+=	kill_shell.c \
			refresh_shell.c \
			shell_init.c \
			shell_utils.c \

# SIGNALS
SRCS	+=	init_signals.c \
			heredoc_signals.c \

# UTILS
SRCS	+=	free.c \
			print_logo.c \
			sys_path_extractor.c \
			read_line.c \

# INPUT
SRCS	+=	handle_input.c \
			validate_input.c \
			handle_env.c \
			handle_env_utils.c \
			handle_tilde_expansion.c \
			handle_dollar_expansion.c \

# LEXER
SRCS	+=	lexer.c \
			create_token.c \
			calculate_length.c \
			lexer_utils.c \
			tokenize_pipe.c \
			tokenize_redirection.c \
			tokenize_token.c \
			tokenize_word.c \
			handle_builtin.c \
		
# PARSING
SRCS	+=	parsing.c \
			insert_pipe.c \
			create_command.c \
			parsing_utils.c \
			validate_tokens.c \
			parse_tokens.c \
			parse_redirections.c \

# Object files
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

TOTAL_SRCS = $(words $(SRCS))
CURRENT = 0

# Default rule to compile all
all: $(LIBFT_LIB) relink

-include $(OBJS:.o=.d)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(CURRENT) * 100 / $(TOTAL_SRCS)))))
	@printf "$(CLEAR_LINE)$(YELLOW)🚧 Compiling $(PERCENT)%% [$(CURRENT)/$(TOTAL_SRCS)] $(CYAN)$<$(NC) 🚧 "
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Rule to compile libft
$(LIBFT_LIB):
	@if [ ! -f "$(LIBFT_LIB)" ]; then \
		echo "$(CLEAR_LINE)$(YELLOW)🚧 Building LIBFT 🚧$(NC)"; \
		$(MAKE) -C $(LIBFT_DIR); \
	fi

# Rule to compile program
relink: $(OBJS)
	@newer=0; \
	if [ ! -f "$(NAME)" ]; then \
		newer=1; \
	else \
		for obj in $(OBJS); do \
			if [ $$obj -nt $(NAME) ]; then \
				newer=1; \
				break; \
			fi; \
		done; \
	fi; \
	if [ $$newer -eq 1 ]; then \
		echo "$(CLEAR_LINE)$(YELLOW)🚧 Building 🧚 Minishell 🧚 🚧$(NC)"; \
		$(CC) -o $(NAME) $(OBJS) $(LIBFTFLAGS) $(SYSLIBFLAGS); \
		echo "$(CLEAR_LINE)$(GREEN)✅🧚 Done Compiling 🧚✅$(NC)"; \
	else \
		echo "$(CLEAR_LINE)$(GREEN)✅🧚 Skipping relink: $(NAME) is up-to-date 🧚✅$(NC)"; \
	fi

# Clean object files and libraries
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Clean all generated files
fclean: clean
	@echo "$(YELLOW)🚧 Cleaning 🚧$(NC)"
	@sleep 0.15
	@printf "$(RED)🧹 Cleaning in Progress 🧹$(NC)\n"
	@sleep 0.15
	@printf "$(YELLOW)🛁 Scrubbing Code 🛁$(NC)\n"
	@sleep 0.15
	@printf "$(CYAN)🧽 Polishing Project 🧽$(NC)\n"
	@sleep 0.15
	@printf "$(MAGENTA)🧴 Tidying Up 🧴$(NC)\n"
	@sleep 0.15
	@printf "$(GREEN)✅ Done Cleaning ✅$(NC)\n"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

# Rebuild everything
re: fclean all

# Clean all generate files faster
fc: clean
	@rm -rf $(NAME)

# Rebuild everything faster
fre: fclean
	@make

norm:
	@norminette $(SRC_DIRS) $(INC_DIR) $(LIBFT_DIR) | grep "Error" || printf "$(GREEN)✅ Norme OK ✅ $(NC)\n"

debug: CFLAGS += -g
debug: CFLAGS += -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
debug: CFLAGS += -DDEBUG=1
debug: clean all

# Bonus rule
bonus: all

# Phony targets
.PHONY: all clean fclean re fc fre norm debug bonus relink