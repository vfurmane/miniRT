/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:18:02 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/10 20:12:50 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_handle_sphere(char **args, t_scene *scene)
{
	double	ret;

	ret = ft_atof(args[1]);
	if (ret < 0)
		return (-1);
	ft_lstadd_front((void**)&scene->spheres,
			(void*)ft_new_sphere(args[0], ret, args[2]));
	return (0);
}

int	ft_handle_cylinder(char **args, t_scene *scene)
{
	double	ret;
	double	height;

	ret = ft_atof(args[2]);
	height = ft_atof(args[3]);
	if (ret < 0 || height < 0)
		return (-1);
	ft_lstadd_front((void**)&scene->cylinders,
			(void*)ft_new_cylinder(&args[0], ret, height, args[4]));
	return (0);
}
