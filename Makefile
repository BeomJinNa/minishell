#parameters====================================================================

CC			= cc

COMMONFLAGS	=

CFLAGS		= $(COMMONFLAGS) -Wall -Wextra -Werror

LDFLAGS		= $(COMMONFLAGS) \
			  $(foreach lib, $(TARGET_LIBDIR), -L$(lib)) \
			  $(foreach arch, $(TARGET_ARCH), -l$(arch))

NAME		= minishell

INCLUDE		= includes/ \
			  readline/include/

#libraries=====================================================================

LIBDIR		= libft/ \
			  readline/lib/

ARCH		= ft \
			  readline \
			  history

LIBFT		= libft/libft.a

READLINE	= readline-8.2/.configured

#sources=======================================================================

SRCS	= srcs/main.c \
		  srcs/add_shlvl.c \
		  srcs/cmp.c \
		  srcs/exec/builtins/builtins.c \
		  srcs/exec/builtins/cd.c \
		  srcs/exec/builtins/count_args.c \
		  srcs/exec/builtins/echo.c \
		  srcs/exec/builtins/env.c \
		  srcs/exec/builtins/exit.c \
		  srcs/exec/builtins/export.c \
		  srcs/exec/builtins/hashtable_ext.c \
		  srcs/exec/builtins/pwd.c \
		  srcs/exec/builtins/unset.c \
		  srcs/exec/exec.c \
		  srcs/exec/exec_child.c \
		  srcs/exec/exec_single_builtin.c \
		  srcs/exec/pipe/dup_pipes.c \
		  srcs/exec/pipe/get_executable_path.c \
		  srcs/exec/pipe/pipe.c \
		  srcs/exec/redirection/close.c \
		  srcs/exec/redirection/heredoc/heredoc.c \
		  srcs/exec/redirection/heredoc/heredoc_env.c \
		  srcs/exec/redirection/heredoc/heredoc_preprocess.c \
		  srcs/exec/redirection/heredoc/heredoc_status.c \
		  srcs/exec/redirection/open.c \
		  srcs/exec/redirection/open_redirection.c \
		  srcs/exec/wait_child.c \
		  srcs/get_envp.c \
		  srcs/get_keys.c \
		  srcs/hashmap/addkey.c \
		  srcs/hashmap/djb2.c \
		  srcs/hashmap/extend_hashtable.c \
		  srcs/hashmap/get.c \
		  srcs/hashmap/get_hashtable.c \
		  srcs/hashmap/hash_memset.c \
		  srcs/hashmap/hash_strcmp.c \
		  srcs/hashmap/hash_strdup.c \
		  srcs/hashmap/init_hashtable.c \
		  srcs/hashmap/remove_hashtable.c \
		  srcs/hashmap/removekey.c \
		  srcs/init.c \
		  srcs/is_str_int_format.c \
		  srcs/is_str_long_long_format.c \
		  srcs/main_utils/alloc_command_structs.c \
		  srcs/main_utils/convert_envp_to_hash.c \
		  srcs/main_utils/init_command_structs.c \
		  srcs/sort_memory.c \
		  srcs/terminal.c \
		  srcs/terminal_parser/are_any_syntax_errors_in_pipe.c \
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

#targets=======================================================================

TARGET_LIB = $(LIBFT) $(READLINE)
TARGET_LIBDIR = $(LIBDIR)
TARGET_ARCH = $(ARCH)
TARGET_OBJS = $(OBJS)

#rules=========================================================================

.PHONY: all
all : $(TARGET_LIB)
	make $(NAME)

$(NAME) : $(TARGET_OBJS)
	$(CC) -o $@ $(TARGET_OBJS) $(LDFLAGS)


$(LIBFT) :
	make -C libft

$(READLINE) :
	cd readline-8.2 && ./configure --prefix=$(PWD)/readline/
	touch readline-8.2/.configured
	make -C readline-8.2
	make install -C readline-8.2

#const options=================================================================

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(foreach include, $(INCLUDE), -I$(include))

.PHONY: oclean
oclean:
	rm -f $(OBJS)

.PHONY: clean
clean :
	rm -f $(OBJS)
	rm -f readline-8.2/.configured
	make fclean -C libft
	make distclean -C readline-8.2

.PHONY: fclean
fclean :
	rm -f $(NAME)
	rm -rf readline/
	make clean

.PHONY: re
re :
	make fclean
	make all

.PHONY: bonus
bonus :
	make all
