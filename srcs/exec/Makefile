CFLAGS = -g -fsanitize=address

LIB = ft readline
READLINE_DIR = /opt/homebrew/opt/readline
LIB_DIR = ../../libft $(READLINE_DIR)/lib
HEADER_DIR = ../../includes $(READLINE_DIR)/include
SRCS = exec.test.c exec.c \
builtins/cd.c builtins/count_args.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c builtins/hashtable_ext.c builtins/pwd.c builtins/unset.c \
pipe/dup_pipes.c pipe/get_executable_path.c pipe/pipe.c \
redirection/close.c redirection/open.c redirection/open_redirection.c \
redirection/heredoc/heredoc.c redirection/heredoc/heredoc_status.c
SRCS_EXT = ../hashmap/addkey.c ../hashmap/djb2.c ../hashmap/extend_hashtable.c ../hashmap/get.c ../hashmap/get_hashtable.c ../hashmap/hash_memset.c ../hashmap/hash_strcmp.c ../hashmap/hash_strdup.c ../hashmap/init_hashtable.c ../hashmap/remove_hashtable.c ../hashmap/removekey.c
OBJS = $(SRCS:.c=.o) $(SRCS_EXT:.c=.o)
NAME = test_exec

all: $(OBJS)
	gcc -g -fsanitize=address $(OBJS) $(addprefix -L, $(LIB_DIR)) $(addprefix -l, $(LIB)) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(addprefix -I, $(HEADER_DIR)) -c $< -o $@

clean:
	rm -rf $(OBJS)

PHONY: all clean