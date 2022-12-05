# ************************************************************************** */
#                                                                            */
#                                                        :::      ::::::::   */
#   PHILOSOPHERS                                       :+:      :+:    :+:   */
#                                                    +:+ +:+         +:+     */
#   By: fde-albe <fde-albe@student.42.fr>          +#+  +:+       +#+        */
#                                                +#+#+#+#+#+   +#+           */
#   Created: 4242/42/42 42:42:42 by fde-albe          #+#    #+#             */
#   Updated: 4242/42/42 42:42:42 by fde-albe         ###   ########.fr       */
#                                                                            */
# ************************************************************************** */

SRCS		=		main.c lists.c utils1.c timefuncs.c \
					check_build_do_destroy.c \
					threadutils.c threadutils2.c \

OBJS 		=		$(addprefix objs/,$(SRCS:.c=.o))

CFLAGS		=		-g -Wall -Wextra -Werror -fsanitize=address
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