/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:32:28 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/13 20:52:30 by vfurmane         ###   ########.fr       */
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

char	*ft_append_camerano_to_scene_name(char *scene_file, int camerano)
{
	char	*str;
	char	*str_camerano;

	str = ft_strjoin(scene_file, "-cam");
	str_camerano = ft_itoa(camerano);
	scene_file = ft_strjoin(str, str_camerano);
	free(str);
	free(str_camerano);
	str = ft_strjoin(scene_file, ".bmp");
	free(scene_file);
	return (str);
}

int		ft_initialize_bmp_file(t_scene *scene, t_buffer *buffer, char *scene_file, int camerano)
{
	int		fd;
	char	*file;

	scene_file = ft_strcrdup(scene_file, '.');
	if (camerano >= 0)
		file = ft_append_camerano_to_scene_name(scene_file, camerano);
	else
		file = ft_strjoin(scene_file, ".bmp");
	fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		ft_fatal_error("Open"); /* ===== DELETE ===== */
	ft_set_bmp_header(scene, fd);
	buffer->i = 0;
	buffer->str = malloc(3 * scene->plan.width * scene->plan.height);
	if (buffer->str == NULL)
		return (-1);
	free(scene_file);
	free(file);
	return (fd);
}
