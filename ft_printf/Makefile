NAME = libftprintf.a
AR = ar rcs
CC = cc
CFLAGS = -Werror -Wextra -Wall 
SRC = ft_printf.c ft_printf_utils.c
OBJ = ft_printf.o ft_printf_utils.o


all: $(NAME)


$(NAME):  $(OBJ)
	$(AR) $(NAME) $(OBJ)

#%.o : %.c
#$(CC) $(CFLAGS) -c $< -o $@
#above is same as below

ft_printf.o : ft_printf.c
	$(CC) $(CFLAGS) -c ft_printf.c -o $@

ft_printf_utils.o : ft_printf_utils.c
	$(CC) $(CFLAGS) -c ft_printf_utils.c -o $@

clean : 
	rm -f $(OBJ)


fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re