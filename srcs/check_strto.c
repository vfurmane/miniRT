/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_strto.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:55:26 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/22 20:12:55 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	ft_check_norm(const char *str, int line)
{
	if (ft_atof(str) > 1 || ft_atof(str) < -1)
	{
		printf("Error\nline %d: Vector format must be [-1.0,1.0]\n", line);
		return (0);
	}
	return (1);
}

int			ft_check_str_to_vector(const char *str, int norm, int line)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		if (str[j] == '\0')
			break ;
		if (!ft_check_atof(&str[j], ",", line))
			break ;
		if (norm && !ft_check_norm(&str[j], line))
			break ;
		j = ft_step_to_number(str, j);
		i++;
	}
	if (str[j] != '\0' || (j > 0 && str[j - 1] == ',') || i < 3)
	{
		printf("Error\nline %d: Vector format must be [-1.0,1.0]\n", line);
		return (0);
	}
	return (1);
}
