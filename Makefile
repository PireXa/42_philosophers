SRCS		=		main.c lists.c utils1.c \


OBJS 		=		$(addprefix objs/,$(SRCS:.c=.o))

CFLAGS		=		-g -Wall -Wextra -Werror
RM			=		rm -f

NAME		= 		philo

objs/%.o: srcs/%.c
			@mkdir -p objs
			@cc $(CFLAGS) -c $< -o $@

$(NAME):    	$(OBJS)
			@cc $(OBJS) $(CFLAGS) -o $(NAME) -lpthread

all:      	$(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:         fclean all