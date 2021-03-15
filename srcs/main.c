/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:12:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/15 17:46:51 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			main(int argc, char **argv)
{
	t_scene		*scene;
	t_buffer	buffer;

	if (ft_initialize_scene(&scene, argc, argv) == NULL)
		return (1);
	buffer.fd = -1;
	ft_proceed_all_cameras(scene, &buffer, argv);
	if (buffer.fd == -1)
		ft_proceed_window(scene);
	ft_free_mlx(scene->mlx, scene->win, scene->img, scene->cameras);
	ft_free_scene(&scene);
	return (0);
}
