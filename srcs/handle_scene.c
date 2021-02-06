/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:47:22 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/06 09:20:01 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_handle_resolution(char **args, t_scene *scene)
{
	int	ret;

	ret = atoi(args[0]);
	if (ret < 0)
		return ; /* return value */
	scene->plan.width = ret;
	ret = atoi(args[1]);
	if (ret < 0)
		return ; /* return value */
	scene->plan.height = ret;
}

void	ft_handle_ambiant(char **args, t_scene *scene)
{
	double	ret;

	ret = ft_atof(args[0]);
	if (ret < 0)
		return ; /* return value */
	ft_set_ambiant(scene, ret, args[1]);
}

void	ft_handle_light(char **args, t_scene *scene)
{
	double	ret;

	ret = ft_atof(args[1]);
	if (ret < 0)
		return ; /* return value */
	ft_lstadd_front((void**)&scene->lights, (void*)ft_new_light(args[0], ret, args[2]));
}
