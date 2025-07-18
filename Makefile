CFLAGS	=	-Wall -Werror -Wextra -g
CC		=	cc
RM		=	rm -rf
NAME	=	get_next_line

SRC 	=	get_next_line.c \
			get_next_line_utils.c \
			get_next_line_main.c

all: $(NAME)

TEST_PRINT=\\e[1;34m******* TESTING $< ********\\e[0m
TEST_OKEND=\\e[1;34m******* ALL OK $< *********\\e[0m

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
	@echo "${TEST_PRINT}"
	./$(NAME)
	@echo "${TEST_OKEND}"

clean:
	$(RM) $(NAME)

fclean: clean
	$(RM) test

re: fclean all

get_next_line_main.c:
	wget -O $@ https://github.com/Laiagdla/testmain/raw/refs/heads/main/ft_printf_main.c;

.PHONY: all clean fclean re
