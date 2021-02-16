/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:04:57 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/16 18:56:12 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			ft_strcmp(char *str1, char *str2)
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

static int	ft_count_words(const char *str, char *sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ft_strchr(sep, str[i]) != NULL)
			i++;
		if (str[i])
			count++;
		else
			break ;
		while (str[i] && ft_strchr(sep, str[i]) == NULL)
			i++;
	}
	return (count);
}

static char	*ft_strcdup(const char *str, char *sep)
{
	int		i;
	int		str_len;
	char	*new_str;

	str_len = 0;
	while (str[str_len] && ft_strchr(sep, str[str_len]) == NULL)
		str_len++;
	new_str = malloc(sizeof(*new_str) * (str_len + 1));
	if (new_str == NULL)
		ft_fatal_error("Failed to duplicate the string");
	i = 0;
	while (str[i] && ft_strchr(sep, str[i]) == NULL)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[str_len] = '\0';
	return (new_str);
}

char		**ft_split(const char *str, char *sep)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	arr = malloc((ft_count_words(str, sep) + 1) * sizeof(*arr));
	if (arr == NULL)
		ft_fatal_error("Failed to allocate a string array");
	while (str[i])
	{
		while (ft_strchr(sep, str[i]) != NULL)
			i++;
		if (str[i])
			arr[j++] = ft_strcdup(&str[i], sep);
		else
			break ;
		while (str[i] && ft_strchr(sep, str[i]) == NULL)
			i++;
	}
	arr[j] = NULL;
	return (arr);
}

char	*ft_strrchr(char *str, int chr)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (str[i])
	{
		if (str[i] == (unsigned char)chr)
			ptr = &str[i];
		i++;
	}
	if ((unsigned char)chr == '\0')
		return (&str[i]);
	return (ptr);
}
