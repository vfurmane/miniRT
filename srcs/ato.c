/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ato.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:32:55 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/06 12:02:37 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	neg;

	if (str == NULL)
		return (-1);
	i = 0;
	neg = 1;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * neg);
}

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
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (str[i++] == '.')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			nbr = nbr * 10 + str[i] - '0';
			fact /= 10;
			i++;
		}
	}
	return (nbr * fact);
}
