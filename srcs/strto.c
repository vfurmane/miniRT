/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strto.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:58:26 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/06 12:00:23 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	ft_str_to_vector(const char *str)
{
	int				i;
	static t_vector	vector;

	i = 0;
	vector.x = ft_atoi(&str[i]);
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == ',')
		i++;
	vector.y = ft_atoi(&str[i]);
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == ',')
		i++;
	vector.z = ft_atoi(&str[i]);
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (vector);
}
