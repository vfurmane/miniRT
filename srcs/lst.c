/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:01:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/06 09:33:58 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	*ft_lstadd_front(void **lst, void *new)
{
	if (new == NULL || lst == NULL)
		return (NULL);
	((t_next*)new)->next = *((t_next**)lst);
	*((t_next**)lst) = new;
	return (*lst);
}
