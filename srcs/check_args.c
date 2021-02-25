/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:09:42 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/28 17:36:21 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_check_args_count(char **args, int expected, int line)
{
	int	arrlen;

	arrlen = ft_strarrlen(args);
	if (arrlen != expected)
	{
		printf("Error\nline %d: Expected %d arguments, %d given\n", line,
				expected, arrlen);
		return (0);
	}
	return (1);
}
