# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/28 15:38:44 by vfurmane          #+#    #+#              #
#    Updated: 2021/03/18 12:19:34 by vfurmane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(addprefix srcs/, bmp.c canvas.c check_args.c check_ato.c check_color.c check_strto.c color.c free.c get_next_line.c get_next_line_utils.c handle_scene.c handle_shape.c init.c main.c matrix_formula.c mlx_event.c my_mlx.c new_scene.c new_shape.c parameters.c put.c raytrace.c render.c strto.c vectors_calcul.c vector_double_calcul.c vectors_formula.c \
			  $(addprefix utils/, ft_atof.c ft_atoi.c ft_itoa.c ft_lstadd_front.c ft_lstfree.c ft_lstsize.c ft_memcpy.c ft_memset.c ft_nbrlen.c ft_split.c ft_strarrlen.c ft_strchr.c ft_strcmp.c ft_strcrdup.c ft_strjoin.c ft_strlen.c ft_strrchr.c ft_strsepdup.c ft_wordcount.c) \
			  $(addprefix primitives/, cylinder.c plane.c sphere.c square.c))
OBJS		= $(SRCS:.c=.o)
INCL		= $(addprefix -I, includes)
NAME		= miniRT
CC			= clang
BONUS		= 
CFLAGS		= -Wall -Wextra -Werror -g3 -ggdb $(BONUS)
LIBS		= -L mlx_linux -lmlx_Linux -I mlx_linux -lXext -lX11 -lm -lz
RM			= rm -f

%.o:		%.c
			$(CC) $(CFLAGS) -c $< $(INCL) -o $@

all:		CFLAGS += -fsanitize=address
all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ $(LIBS) -o $(NAME)

bonus:		BONUS=-D MINI_RT_BONUS=1
bonus:		all

mlx:
	@echo "\033[92mDownloading the Minilibx...\033[0m"
	@git clone https://github.com/42Paris/minilibx-linux.git mlx_linux
	@echo "\033[92mCompiling the Minilibx...\033[0m"
	@cd mlx_linux && ./configure

nosanitize: $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

