/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:40:43 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 11:23:04 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

static char	**ft_check_split(const char *str, const char *sep, char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	if (i == ft_wordcount(str, sep))
		return (arr);
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char		**ft_split(const char *str, const char *sep)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	arr = malloc((ft_wordcount(str, sep) + 1) * sizeof(*arr));
	if (arr == NULL)
		return (NULL);
	while (str[i])
	{
		while (str[i] && ft_strchr(sep, str[i]) != NULL)
			i++;
		if (str[i])
			arr[j++] = ft_strsepdup(&str[i], sep);
		else
			break ;
		while (str[i] && ft_strchr(sep, str[i]) == NULL)
			i++;
	}
	arr[j] = NULL;
	arr = ft_check_split(str, sep, arr);
	return (arr);
}
