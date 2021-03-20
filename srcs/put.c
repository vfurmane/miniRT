/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:23:04 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/20 14:34:50 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_fatal_error(const char *str)
{
	printf("Error\n");
	perror(str);
	return (-1);
}

void	*ft_fatal_error_null(const char *str)
{
	printf("Error\n");
	perror(str);
	return (NULL);
}
