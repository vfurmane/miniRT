# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/28 15:38:44 by vfurmane          #+#    #+#              #
#    Updated: 2021/02/08 20:35:05 by vfurmane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(addprefix srcs/, ato.c canvas.c color.c free.c get_next_line.c get_next_line_utils.c handle_scene.c handle_shape.c lst.c main.c my_mlx.c new_scene.c new_shape.c parameters.c put.c raytrace.c str.c strto.c vectors_calcul.c vector_double_calcul.c vectors_formula.c)
OBJS		= $(SRCS:.c=.o)
INCL		= $(addprefix -I, includes)
NAME		= miniRT
CC			= clang
BONUS		= 
CFLAGS		= -Wall -Wextra -Werror -g3 -ggdb $(BONUS) -fsanitize=address
LIBS		= -L mlx_linux -lmlx_Linux -I mlx_linux -lXext -lX11 -lm -lz
RM			= rm -f

%.o:		%.c
			$(CC) $(CFLAGS) -c $< $(INCL) -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ $(LIBS) -o $(NAME)

bonus:		BONUS=-D MINI_RT_BONUS=1
bonus:		all

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

