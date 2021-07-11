NAME	=	philo

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

SRC		=	 main.c init.c life_and_death.c utils.c time.c

HEADER	=	philosophers.h

.PHONY	:	all clean fclean re 

all		:	$(NAME)

$(NAME)	: $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -I. $(SRC) -o $(NAME)

clean	:
	@$(RM) *.o

fclean	:	clean
		@$(RM) $(NAME)

re		:	fclean all
