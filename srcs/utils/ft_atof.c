/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:17:51 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 10:58:47 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

double	ft_atof(const char *str)
{
	int		i;
	double	fact;
	double	nbr;

	if (str == NULL)
		return (-1);
	i = 0;
	fact = 1;
	if (str[i] == '-')
	{
		fact = -1;
		i++;
	}
	nbr = 0;
	while ((str[i] >= '0' && str[i] <= '9') ||
			(str[i] == '.' && (fact == -1 || fact == 1)))
	{
		if ((fact > 0 && fact < 1) || (fact > -1 && fact < 0))
			fact /= 10;
		if (str[i] == '.')
			fact /= 10 + i++ * 0;
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * fact);
}
