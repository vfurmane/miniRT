/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:21:20 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 09:25:40 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

char	*ft_itoa(int nbr)
{
	int				i;
	int				len;
	char			*str;
	unsigned int	nb;

	len = ft_nbrlen(nbr);
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
