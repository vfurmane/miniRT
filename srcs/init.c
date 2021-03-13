/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:32:28 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/13 18:35:55 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_scene	*ft_initialize_scene(t_scene **scene, int argc, char **argv)
{
	*scene = malloc(sizeof(**scene));
	if (*scene == NULL)
		return (NULL);
	if (ft_parameters(argc, argv, *scene) == -1)
	{
		ft_free_scene(scene);
		return (NULL);
	}
	(*scene)->title = ft_strjoin("miniRT - ", argv[1]);
	(*scene)->inter_min = 1;
	(*scene)->inter_max = -1;
	(*scene)->plan.distance = 1;
	(*scene)->mlx = mlx_init();
	(*scene)->background_color = ft_multiply_color((*scene)->ambiant->color, (*scene)->ambiant->intensity);
	return (*scene);
}
