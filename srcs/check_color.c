/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:30:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/19 11:29:44 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_check_parse_color(char *str, int line)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!ft_check_atoi(str, ",", line))
			return (0);
		if (ft_atoi(str) < 0 || ft_atoi(str) > 255)
		{
			printf("Error\nline %d: Color must be in range [0,255]\n", line);
			return (0);
		}
		while (*str && *str >= '0' && *str <= '9')
			str++;
		if (*str == ',' && i < 2)
			str++;
		else if ((*str == '\0' && i < 2) || *str != '\0' ||
				(*str != '\0' && i == 2))
		{
			printf("Error\nline %d: Color format must be xxx,xxx,xxx\n", line);
			return (0);
		}
		i++;
	}
	return (1);
}
