/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:10:45 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 11:24:04 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_trimc(const char *str)
{
	int		i;
	int		str_len;
	char	*new_content;

	if (str[0] == '\0')
	{
		new_content = malloc(sizeof(*new_content));
		if (new_content == NULL)
			return (NULL);
		new_content[0] = '\0';
		return (new_content);
	}
	str++;
	str_len = 0;
	while (str[str_len])
		str_len++;
	new_content = malloc((str_len + 1) * sizeof(*new_content));
	if (new_content == NULL)
		return (NULL);
	i = -1;
	while (str[++i])
		new_content[i] = str[i];
	new_content[i] = '\0';
	return (new_content);
}

char	*ft_splitc(char **str)
{
	int		i;
	int		str_len;
	char	*new_str;
	char	*new_content;

	str_len = 0;
	while ((*str)[str_len] && (*str)[str_len] != '\n')
		str_len++;
	new_str = malloc((str_len + 1) * sizeof(*new_str));
	if (new_str == NULL)
		return (NULL);
	i = -1;
	while (++i < str_len)
		new_str[i] = (*str)[i];
	new_str[i] = '\0';
	new_content = &(*str)[i];
	if ((new_content = ft_trimc(new_content)) == NULL)
	{
		free(new_str);
		return (NULL);
	}
	free(*str);
	*str = new_content;
	return (new_str);
}

int		ft_free_elm(t_list **list, t_list *elm)
{
	t_list	*lst;

	lst = *list;
	if (lst == elm)
	{
		*list = elm->next;
		free(elm->content);
		free(elm);
	}
	else
	{
		while (lst != NULL && lst->next != elm)
			lst = lst->next;
		if (lst == NULL)
			return (-1);
		lst->next = elm->next;
		free(elm->content);
		free(elm);
	}
	return (0);
}
