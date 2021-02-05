/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:01:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/05 12:58:30 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	*ft_lstadd_front(void **lst, void *new)
{
	if (new == NULL)
		return (NULL);
	((t_list*)new)->next = ((t_list*)lst);
	*((t_list**)lst) = new;
	return (*lst);
}
