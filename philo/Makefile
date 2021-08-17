SRCS	= philo.c ft_atoi.c ft_isdigit.c pars_init.c time.c philo_eat.c

OBJS	= $(SRCS:.c=.o)

HEADER	= philo.h

NAME 	= philo

RM	= rm -f

FLAG	= -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			gcc $(OBJS) ${FLAG} -o $(NAME)

%.o	:	%.c $(HEADER)
			gcc ${FLAG} -c $< -o $@

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
