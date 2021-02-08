/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:31:03 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/08 18:32:50 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_free_split(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i] != NULL)
		free(strarr[i++]);
	free(strarr);
}
