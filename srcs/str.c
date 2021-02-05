/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:04:57 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/05 12:50:10 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	if (str1 == NULL || str2 == NULL)
		return ((str1 != NULL) - (str2 != NULL));
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

static int	ft_count_words(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i])
			count++;
		else
			break ;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

static char	*ft_strcdup(const char *str, char sep)
{
	int		i;
	int		str_len;
	char	*new_str;

	str_len = 0;
	while (str[str_len] && str[str_len] != sep)
		str_len++;
	if (!(new_str = malloc(sizeof(*new_str) * (str_len + 1))))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != sep)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[str_len] = '\0';
	return (new_str);
}

char		**ft_split(const char *str, char sep)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	if (!(arr = malloc((ft_count_words(str, sep) + 1) * sizeof(*arr))))
		return (NULL);
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i])
			arr[j++] = ft_strcdup(&str[i], sep);
		else
			break ;
		while (str[i] && str[i] != sep)
			i++;
	}
	arr[j] = NULL;
	return (arr);
}
