/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:47:22 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/08 18:11:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_handle_resolution(char **args, t_scene *scene)
{
	int	nbr;

	nbr = atoi(args[0]);
	if (nbr < 0)
		return ; /* return value */
	scene->plan.width = nbr;
	nbr = atoi(args[1]);
	if (nbr < 0)
		return ; /* return value */
	scene->plan.height = nbr;
}

void	ft_handle_ambiant(char **args, t_scene *scene)
{
	double	nbr;

	nbr = ft_atof(args[0]);
	if (nbr < 0)
		return ; /* return value */
	ft_set_ambiant(scene, nbr, args[1]);
}

void	ft_handle_light(char **args, t_scene *scene)
{
	double	nbr;

	nbr = ft_atof(args[1]);
	if (nbr < 0)
		return ; /* return value */
	ft_lstadd_front((void**)&scene->bulbs,
			(void*)ft_new_light(args[0], nbr, args[2]));
}
