/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:09:01 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/08 21:44:14 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_lstadd_front(t_list **lst, int fd)
{
	t_list	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->fd = fd;
	if ((new->content = malloc(sizeof(*(new->content)))) == NULL)
		return (NULL);
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
	dest_start = 0;
	while (dest[i++])
		dest_start++;
	i = 0;
	src_size = 0;
	while (src[i++])
		src_size++;
	i = -1;
	if (!(res = malloc(sizeof(*res) * (dest_start + src_size + 1))))
		return (NULL);
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

	if ((buffer = malloc((BUFFER_SIZE + 1) * sizeof(*buffer))) == NULL)
		return (-1);
	result = 1;
	if ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buffer[ret] = '\0';
		elm->content = ft_strdupcat(elm->content, buffer);
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
		if ((elm = ft_lstadd_front(&line_list, fd)) == NULL)
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
