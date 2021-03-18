/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:22:31 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 11:01:22 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

void	*ft_lstadd_front(void **lst, void* const new)
{
	if (new == NULL || lst == NULL)
		return (NULL);
	((t_next*)new)->next = *((t_next**)lst);
	*((t_next**)lst) = new;
	return (*lst);
}
