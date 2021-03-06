/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:29:32 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/21 19:45:10 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt_utils.h"

int	ft_lstsize(void *lst)
{
	int		len;
	t_next	*elm;

	len = 0;
	elm = lst;
	while (elm != NULL)
	{
		len++;
		elm = elm->next;
	}
	return (len);
}
