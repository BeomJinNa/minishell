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

SRCS	= #source files(*.c)

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
