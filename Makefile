#parameters====================================================================

CC		= cc
AR		= ar
ARFLAGS	= crs
CFLAGS	= -Wall -Wextra -Werror

NAME	= minishell
INCLUDE	= includes/



#libraries=====================================================================

LIBS	= libft
ARCH	= ft

LIBFT	= libft/libft.a



#sources=======================================================================

SRCS	= srcs/main.c \
		  srcs/hashmap/addkey.c \
		  srcs/hashmap/djb2.c \
		  srcs/hashmap/extend_hashtable.c \
		  srcs/hashmap/get.c \
		  srcs/hashmap/hash_memset.c \
		  srcs/hashmap/hash_strcmp.c \
		  srcs/hashmap/hash_strdup.c \
		  srcs/hashmap/init_hashtable.c \
		  srcs/hashmap/remove_hashtable.c \
		  srcs/hashmap/removekey.c \
		  srcs/terminal_parser/convert_tokens_to_board.c \
		  srcs/terminal_parser/get_tokenized_array.c \
		  srcs/terminal_parser/init_brace.c \
		  srcs/terminal_parser/merge_tokens.c \
		  srcs/terminal_parser/redirections/are_any_syntax_errors_in_redirections.c \
		  srcs/terminal_parser/redirections/dup_redirection.c \
		  srcs/terminal_parser/redirections/extract_redirections.c \
		  srcs/terminal_parser/redirections/remove_redirections.c \
		  srcs/terminal_parser/remove_board_and_tokens.c \
		  srcs/terminal_parser/remove_quotes.c \
		  srcs/terminal_parser/replace_white_spaces.c \
		  srcs/terminal_parser/variable_extension/are_any_syntax_errors_in_extensions.c \
		  srcs/terminal_parser/variable_extension/divide_variables.c \
		  srcs/terminal_parser/variable_extension/extend_env_variables.c \
		  srcs/terminal_parser/variable_extension/heredoc/are_any_syntax_errors_in_extensions.c \
		  srcs/terminal_parser/variable_extension/heredoc/divide_variables_heredoc.c \
		  srcs/terminal_parser/variable_extension/heredoc/extend_one_line_heredoc.c \
		  srcs/terminal_parser/variable_extension/replace_variables.c \
		  srcs/terminal_parser/variable_extension/va_strndup.c \
		  srcs/terminal_parser/variable_extension/variable.c

OBJS	= $(SRCS:.c=.o)



TARGET_OBJS = $(OBJS)
TARGET_LIB = $(LIBFT)
TARGET_LIBS = $(LIBS)
TARGET_ARCH = $(ARCH)

#rules=========================================================================

.PHONY: all
all :
	make $(NAME)

$(NAME) : $(TARGET_LIB) $(TARGET_OBJS)
	$(CC) -o $@ $(TARGET_OBJS) $(foreach lib, $(TARGET_LIBS), -L$(lib)) $(foreach arch, $(TARGET_ARCH), -l$(arch))


$(LIBFT) :
	make -C libft

#const options=================================================================

%.o : %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

.PHONY: clean
clean :
	$(foreach lib, $(LIBS), make fclean -C $(lib);)
	rm -f $(OBJS)

.PHONY: fclean
fclean :
	make clean
	rm -f $(NAME)

.PHONY: re
re :
	make fclean
	make all
