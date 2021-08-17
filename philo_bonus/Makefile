SRCS	= philo_bonus.c ft_atoi.c ft_isdigit.c eat.c pars.c time.c

OBJS	= $(SRCS:.c=.o)

HEADER	= philo_bonus.h

NAME	= philo_bonus

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
