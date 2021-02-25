/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strto.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:58:26 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/27 19:08:07 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	ft_str_to_vector(const char *str)
{
	int				i;
	static t_vector	vector;

	i = 0;
	vector.x = ft_atof(&str[i]);
	i = ft_step_to_number(str, i);
	vector.y = ft_atof(&str[i]);
	i = ft_step_to_number(str, i);
	vector.z = ft_atof(&str[i]);
	return (vector);
}

int			ft_step_to_number(const char *str, int i)
{
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == ',')
		i++;
	return (i);
}
