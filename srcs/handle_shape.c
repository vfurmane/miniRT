/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:18:02 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/06 11:45:41 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_handle_sphere(char **args, t_scene *scene)
{
	double	ret;

	ret = ft_atof(args[1]);
	if (ret < 0)
		return ; /* return value */
	ft_lstadd_front((void**)&scene->spheres, (void*)ft_new_sphere(args[0], ret, args[2]));
}
