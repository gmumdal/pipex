NAME = pipex
SRCS = pipex.c first_setting.c child.c command.c
SRCS_B = pipex_bonus.c first_setting_bonus.c child_bonus.c heredoc_bonus.c command_bonus.c
INCS = pipex.h
INCS_B = pipex_bonus.h
LIBFT = -Ilibft -Llibft -lft
LIBFT_DIR = libft
CC = cc
CFLAGS = -Wall -Wextra -Werror
BONUS = bonus_part
MANDATORY = mandatory

all : $(MANDATORY)

$(MANDATORY) : $(SRCS) $(INCS)
	make -sC $(LIBFT_DIR) all
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT)
	rm -rf $(BONUS)
	touch $(MANDATORY)

clean :
	make -sC $(LIBFT_DIR) fclean

fclean : clean
	rm -rf $(NAME)
	rm -rf $(MANDATORY) $(BONUS)

re : fclean all

bonus : $(BONUS)

$(BONUS) : $(SRCS_B) $(INCS_B)
	make -sC $(LIBFT_DIR) all
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS_B) $(LIBFT)
	rm -rf $(MANDATORY)
	touch $(BONUS)

.PHONY : all clean fclean re
