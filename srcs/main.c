/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:12:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/23 10:03:41 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			main(int argc, char **argv)
{
	t_scene		*scene;
	t_buffer	buffer;

	if (argc < 2 || argc > 3 || ft_strcmp("--save", argv[1]) == 0)
		return (printf("Error\nUsage: %s scene [--save]\n", argv[0]));
	if (ft_initialize_scene(&scene, argv) == NULL)
		return (1);
	if (scene->mlx != NULL)
		if (ft_check_window_size(scene) == 0)
			return (1);
	buffer.fd = -1;
	printf("Scene parsed successfully!\nProceeding camera(s)...\n");
	if (!ft_proceed_all_cameras(scene, &buffer, argv))
	{
		ft_free_scene(&scene);
		return (1);
	}
	printf("Done!\n");
	if (scene->mlx != NULL)
	{
		ft_proceed_window(scene);
		ft_free_mlx(scene->mlx, scene->win, scene->img, scene->cameras);
	}
	ft_free_scene(&scene);
	return (0);
}
