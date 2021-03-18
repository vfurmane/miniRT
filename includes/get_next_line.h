/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:26:33 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 11:24:17 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
#include "mini_rt.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	256
# endif

typedef struct		s_list
{
	int				fd;
	char			*content;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);
char				*ft_splitc(char **str);
char				*ft_strchr(const char *str, int chr);
int					ft_free_elm(t_list **list, t_list *elm);

#endif
