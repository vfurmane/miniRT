/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:23:04 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/08 19:19:31 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_fatal_error(const char *str)
{
	perror(str);
	exit(1);
}

int		ft_error(void)
{
	printf("Error when parsing parameters...\n");
	return (1);
}
