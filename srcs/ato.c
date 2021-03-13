/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ato.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 10:32:55 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/13 20:41:32 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			ft_atoi(const char *str)
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

double		ft_atof(const char *str)
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

static int	ft_count_digits(int nbr)
{
	int	i;

	if (nbr == 0)
		return (1);
	i = 0;
	i += nbr < 0;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int nbr)
{
	int				i;
	int				len;
	char			*str;
	unsigned int	nb;

	len = ft_count_digits(nbr);
	if (!(str = malloc((len + 1) * sizeof(*str))))
		return (NULL);
	str[0] = '-';
	if (nbr == 0)
		str[0] = '0';
	if (nbr <= 0)
		nb = -nbr;
	else
		nb = nbr;
	i = len;
	while (nb)
	{
		i--;
		str[i] = nb % 10 + '0';
		nb /= 10;
	}
	str[len] = '\0';
	return (str);
}
