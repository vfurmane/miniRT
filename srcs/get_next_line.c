/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:09:01 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/20 19:07:28 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "get_next_line.h"

static t_list	*ft_lstadd_front_fd(t_list **lst, int fd)
{
	t_list	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->content = malloc(sizeof(*(new->content)));
	if (new->content == NULL)
	{
		free(new);
		return (NULL);
	}
	new->content[0] = '\0';
	new->next = *lst;
	*lst = new;
	return (*lst);
}

static t_list	*ft_get_fd_in_list(t_list *lst, int fd)
{
	while (lst != NULL)
		if (lst->fd == fd)
			return (lst);
		else
			lst = lst->next;
	return (NULL);
}

static char		*ft_strdupcat(char *dest, char *src)
{
	char			*res;
	unsigned long	i;
	unsigned long	dest_start;
	unsigned long	src_size;

	i = 0;
	dest_start = ft_strlen(dest);
	src_size = ft_strlen(src);
	res = malloc(sizeof(*res) * (dest_start + src_size + 1));
	if (res == NULL)
	{
		free(dest);
		return (NULL);
	}
	i = -1;
	while (dest[++i])
		res[i] = dest[i];
	i = -1;
	while (src[++i])
		res[dest_start + i] = src[i];
	res[dest_start + i] = '\0';
	free(dest);
	return (res);
}

static int		ft_read(int fd, t_list *elm)
{
	int		ret;
	int		result;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(*buffer));
	if (buffer == NULL)
		return (-1);
	result = 1;
	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret != 0)
	{
		if (ret == -1)
			return (-1);
		buffer[ret] = '\0';
		elm->content = ft_strdupcat(elm->content, buffer);
		if (elm->content == NULL)
		{
			result = -1;
			free(elm);
		}
	}
	else
		result = 0;
	free(buffer);
	return (result);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*line_list;
	int				result;
	int				line_read;
	t_list			*elm;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	if ((elm = ft_get_fd_in_list(line_list, fd)) == NULL)
		if ((elm = ft_lstadd_front_fd(&line_list, fd)) == NULL)
			return (-1);
	line_read = 0;
	result = 1;
	while (ft_strchr(elm->content, '\n') == NULL)
		if ((result = ft_read(fd, elm)) == 0)
			break ;
		else if (result == -1)
			return (-1);
		else
			line_read++;
	if ((*line = ft_splitc(&elm->content)) == NULL)
		return (-1);
	if (result == 0)
		return (ft_free_elm(&line_list, elm));
	result = result != 0;
	return (result);
}
