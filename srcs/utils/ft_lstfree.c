/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:27:49 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 09:28:17 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

void	ft_lstfree(void *lst)
{
	void	*ptr;

	while (lst != NULL)
	{
		ptr = ((t_next*)lst)->next;
		free(lst);
		lst = ptr;
	}
}
