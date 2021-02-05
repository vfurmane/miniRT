# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/28 15:38:44 by vfurmane          #+#    #+#              #
#    Updated: 2021/02/05 12:53:51 by vfurmane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(addprefix srcs/, ato.c color.c get_next_line.c get_next_line_utils.c handle_scene.c lst.c main.c my_mlx.c new_scene.c parameters.c raytrace.c str.c vectors_calcul.c vector_double_calcul.c vectors_formula.c)
OBJS		= $(SRCS:.c=.o)
INCL		= $(addprefix -I, includes mlx_linux)
NAME		= miniRT
CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g3 -ggdb
LIBS		= -L mlx_linux -lmlx_Linux -I mlx_linux -lXext -lX11 -lm -lz
RM			= rm -f

%.o:		%.c
			$(CC) $(CFLAGS) -c $< $(INCL) -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ $(LIBS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

