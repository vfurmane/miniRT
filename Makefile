# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/28 15:38:44 by vfurmane          #+#    #+#              #
#    Updated: 2021/03/23 12:07:21 by vfurmane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(addprefix srcs/, bmp.c canvas.c check_args.c check_ato.c \
			  check_color.c check_strto.c color.c free.c get_next_line.c \
			  get_next_line_utils.c handle_scene.c handle_shape.c init.c \
			  light.c main.c matrix_formula.c mlx_event.c my_mlx.c new_scene.c \
			  new_shape.c parameters.c primitives.c proceed.c put.c raytrace.c \
			  render.c strto.c vectors_calcul.c vector_double_calcul.c \
			  vectors_formula.c \
			  $(addprefix utils/, ft_atof.c ft_atoi.c ft_itoa.c \
			  ft_lstadd_front.c ft_lstfree.c ft_lstsize.c ft_memcpy.c \
			  ft_memset.c ft_nbrlen.c ft_split.c ft_strarrlen.c ft_strchr.c \
			  ft_strcmp.c ft_strcrdup.c ft_strjoin.c ft_strlen.c ft_strrchr.c \
			  ft_strsepdup.c ft_wordcount.c) \
			  $(addprefix primitives/, cylinder.c plane.c sphere.c square.c \
			  triangle.c))
OBJS		= $(SRCS:.c=.o)
INCL		= $(addprefix -I, includes mlx_linux)
NAME		= miniRT
CC			= clang
BONUS		= 
CFLAGS		= -Wall -Wextra -Werror $(BONUS)
LIBS		= -L mlx_linux -lmlx_Linux -I mlx_linux -lXext -lX11 -lm -lz
RM			= rm -f

%.o:		%.c
			$(CC) $(CFLAGS) -c $< $(INCL) -o $@

all:		mlx $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ $(LIBS) -o $(NAME)

mlx:
ifeq (,$(wildcard mlx_linux/Makefile))
			git submodule init
			git submodule update
endif
			make -C mlx_linux

bonus:		BONUS=-D MINI_RT_BONUS=1
bonus:		all

nosanitize: $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

