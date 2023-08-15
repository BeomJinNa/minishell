LIB = ft readline
READLINE_DIR = /opt/homebrew/opt/readline
LIB_DIR = ../../libft $(READLINE_DIR)/lib
HEADER_DIR = ../../includes $(READLINE_DIR)/include
CFILES = exec.test.c exec.c \
builtins/cd.c builtins/count_args.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c builtins/hashtable_ext.c builtins/pwd.c builtins/unset.c \
pipe/dup_pipes.c pipe/get_executable_path.c pipe/pipe.c \
redirection/close.c redirection/open.c redirection/open_redirection.c \
redirection/heredoc/heredoc.c redirection/heredoc/heredoc_status.c
CFILES_EXT = ../hashmap/addkey.c ../hashmap/djb2.c ../hashmap/extend_hashtable.c ../hashmap/get.c ../hashmap/get_hashtable.c ../hashmap/hash_memset.c ../hashmap/hash_strcmp.c ../hashmap/hash_strdup.c ../hashmap/init_hashtable.c ../hashmap/remove_hashtable.c ../hashmap/removekey.c
NAME = test_exec

all:
	gcc -g -fsanitize=address $(addprefix -L, $(LIB_DIR)) $(addprefix -l, $(LIB)) $(addprefix -I, $(HEADER_DIR)) $(CFILES) $(CFILES_EXT) -o $(NAME)