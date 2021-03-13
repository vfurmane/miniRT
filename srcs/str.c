/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:04:57 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/13 21:14:20 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			ft_strcmp(const char *str1, const char *str2)
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
		return (NULL);
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
		return (NULL);
	while (str[i])
	{
		while (str[i] && ft_strchr(sep, str[i]) != NULL)
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

char	*ft_strrchr(const char *str, int chr)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (str[i])
	{
		if (str[i] == (unsigned char)chr)
			ptr = (char*)&str[i];
		i++;
	}
	if ((unsigned char)chr == '\0')
		return ((char*)&str[i]);
	return (ptr);
}

int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *str1, const char *str2)
{
	int		i;
	int		len;
	int		str1_len;
	char	*new_str;

	str1_len = ft_strlen(str1);
	len = str1_len + ft_strlen(str2) + 1;
	if (!(new_str = malloc(len * sizeof(*new_str))))
		return (NULL);
	i = 0;
	while (i < str1_len)
	{
		new_str[i] = str1[i];
		i++;
	}
	while (i < len)
	{
		new_str[i] = str2[i - str1_len];
		i++;
	}
	return (new_str);
}

char	*ft_strcrdup(const char *str, int chr)
{
	int		str_len;
	char	*new_str;
	char	*last_chr;

	last_chr = ft_strrchr(str, chr);
	str_len = last_chr - str;
	if (!(new_str = malloc(sizeof(*new_str) * (str_len + 1))))
		return (NULL);
	new_str = ft_memcpy(new_str, str, sizeof(*new_str) * str_len);
	new_str[str_len] = '\0';
	return (new_str);
}
