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
		  srcs/hashmap/removekey.c

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
