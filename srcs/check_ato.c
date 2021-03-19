/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ato.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:43:41 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/19 11:45:50 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_check_atoi(const char *str, const char *allowed, int line)
{
	int	i;

	if (str == NULL)
		return (1);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0' && ft_strchr(allowed, str[i]) == NULL)
	{
		printf("Error\nline %d: Unexpected character '%c'\n", line, str[i]);
		return (0);
	}
	if (i == 0 || (i == 1 && str[0] == '-'))
	{
		printf("Error\nline: %d: No digit specified\n", line);
		return (0);
	}
	return (1);
}

int	ft_check_atof(const char *str, const char *allowed, int line)
{
	int		i;

	if (str == NULL)
		return (1);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
	}
	else if (str[i] == '\0')
		return (1);
	if (str[i] != '\0' && ft_strchr(allowed, str[i]) == NULL)
	{
		return (printf("Error\nline %d: Unexpected character '%c'\n", line,
				str[i]) * 0);
	}
	if (i == 0 || (i == 1 && str[0] == '-'))
		return (printf("Error\nline: %d: No digit specified\n", line) * 0);
	return (1);
}
