/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:01:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/13 20:57:11 by vfurmane         ###   ########.fr       */
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

void	ft_free_lst(void *lst)
{
	void	*ptr;

	while (lst != NULL)
	{
		ptr = ((t_next*)lst)->next;
		free(lst);
		lst = ptr;
	}
}

int		ft_lstsize(void *lst)
{
	int	len;

	if (lst == NULL)
		return (0);
	len = 1;
	while ((lst = ((t_next*)lst)->next))
		len++;
	return (len);
}
