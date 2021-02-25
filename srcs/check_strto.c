/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_strto.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:55:26 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/28 19:54:03 by vfurmane         ###   ########.fr       */
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

	i = 0;
	if (!ft_check_atof(&str[i], ",", line))
		return (0);
	if (norm && !ft_check_norm(&str[i], line))
		return (0);
	i = ft_step_to_number(str, i);
	if (!ft_check_atof(&str[i], ",", line))
		return (0);
	if (norm && !ft_check_norm(&str[i], line))
		return (0);
	i = ft_step_to_number(str, i);
	if (!ft_check_atof(&str[i], "", line))
		return (0);
	if (norm && !ft_check_norm(&str[i], line))
		return (0);
	return (1);
}
