# Variables
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS_DIR = ./srcs
INC_DIR = ./include
LIBFT_DIR = ./
PRINTF_DIR = $(INC_DIR)/printf
FPRINTF_DIR = $(INC_DIR)/fprintf
GNL_DIR = $(INC_DIR)/get_next_line
CFLAGS += -I$(LIBFT_DIR)

# List of source files (all in the parent directory 't1')
LIBFT_SRCS =	ft_abs.c \
				ft_arr_cpy.c \
				ft_arrlen.c \
				ft_atof.c \
				ft_atoi.c \
				ft_atol.c \
				ft_atoll.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_fibonacci.c \
				ft_find_next_prime.c \
				ft_free_arr.c \
				ft_free_ptr.c \
				ft_is_prime.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_itoa.c \
				ft_lstadd_back_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstfree.c \
				ft_lstiter_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstmap_bonus.c \
				ft_lstnew_bonus.c \
				ft_lstsize_bonus.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_nodefree.c \
				ft_print_params.c \
				ft_putchar.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr.c \
				ft_putnbr_fd.c \
				ft_putstr.c \
				ft_putstr_fd.c \
				ft_range.c \
				ft_realloc.c \
				ft_recursive_factorial.c \
				ft_recursive_power.c \
				ft_sort_params.c \
				ft_split.c \
				ft_sqrt.c \
				ft_str_is_alpha.c \
				ft_str_is_lowercase.c \
				ft_str_is_numeric.c \
				ft_str_is_printable.c \
				ft_str_is_uppercase.c \
				ft_str_to_arr_back.c \
				ft_str_to_arr_front.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strlowcase.c \
				ft_strmapi.c \
				ft_strncat.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strndup.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strstr.c \
				ft_strtrim.c \
				ft_strupcase.c \
				ft_substr.c \
				ft_swap.c \
				ft_tolower.c \
				ft_toupper.c \

PRINTF_SRCS =	ft_utils.c \
				ft_print_hex_nbr.c \
				ft_print_nbr.c \
				ft_print_str.c \
				ft_print_unbr.c \
				ft_print_voidptr.c \
				ft_printf.c 

GNL_SRCS =		get_next_line.c \
				get_next_line_bonus.c \
				get_next_line_utils.c \
				get_next_line_utils_bonus.c

FPRINTF_SRCS =	ft_fprintf.c \
				ft_fputchar_str.c \
				ft_fputnbrs.c

SRCS = $(addprefix $(SRCS_DIR)/, $(LIBFT_SRCS)) \
       $(addprefix $(PRINTF_DIR)/, $(PRINTF_SRCS)) \
       $(addprefix $(FPRINTF_DIR)/, $(FPRINTF_SRCS)) \
       $(addprefix $(GNL_DIR)/, $(GNL_SRCS))

# ---------- COLORS AND STUFF ---------- #
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[0;36m
NC = \033[0m
CLEAR_LINE = \033[2K\r

TOTAL_SRCS = $(words $(SRCS))
CURRENT = 0

# Object files
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@true

# Rule to compile the main library
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

# Object file compilation rule
.c.o:
	@$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(CURRENT) * 100 / $(TOTAL_SRCS)))))
	@printf "$(CLEAR_LINE)$(YELLOW)🚧 Compiling $(PERCENT)%% [$(CURRENT)/$(TOTAL_SRCS)] $(CYAN)$<$(NC) 🚧 "
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean object files and libraries
clean:
	@rm -f $(OBJS)

# Clean all generated files
fclean: clean
	@rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re