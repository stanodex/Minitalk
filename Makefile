NAME = ""
NAMES = server
NAMEC = client
NAMESB = serverbonus
NAMECB = clientbonus
CC = cc
CFLAGS = -Wextra -Werror -Wall
FT_PRINTF_DIR = ./ft_printf/
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
S_SRC = server.c
C_SRC = client.c
S_SRCB = server_bonus.c
C_SRCB = client_bonus.c

$(NAME) : $(FT_PRINTF) $(NAMES) $(NAMEC)

$(NAMES) : $(FT_PRINTF)
	$(CC) $(CFLAGS) $(S_SRC) $(FT_PRINTF) -o $@

$(FT_PRINTF) :
	make -C $(FT_PRINTF_DIR)

$(NAMEC) : $(FT_PRINTF)
	$(CC) $(CFLAGS) $(C_SRC) $(FT_PRINTF) -o $@

$(NAMESB) : $(FT_PRINTF)
	$(CC) $(CFLAGS) $(S_SRCB) $(FT_PRINTF) -o $@

$(NAMECB) : $(FT_PRINTF)
	$(CC) $(CFLAGS) $(C_SRCB) $(FT_PRINTF) -o $@

all : $(FT_PRINTF) $(NAMES) $(NAMEC)

bonus : $(FT_PRINTF) $(NAMESB) $(NAMECB)

clean :
	make clean -C $(FT_PRINTF_DIR)
	rm -rf $(NAMES)
	rm -rf $(NAMEC)
	rm -rf $(NAMESB)
	rm -rf $(NAMECB)

fclean : clean
	make fclean -C $(FT_PRINTF_DIR)

re : fclean all

.PHONY : all clean fclean re 
