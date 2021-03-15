/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:32:28 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/17 09:35:00 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_scene	*ft_initialize_scene(t_scene **scene, int argc, char **argv)
{
	*scene = malloc(sizeof(**scene));
	if (*scene == NULL)
	{
		ft_fatal_error("Cannot allocate the scene");
		return (NULL);
	}
	(*scene)->title = ft_strjoin("miniRT - ", argv[1]);
	if ((*scene)->title == NULL)
	{
		free(*scene);
		ft_fatal_error("Cannot allocate the window's title");
		return (NULL);
	}
	if (ft_parameters(argc, argv, *scene) == -1)
	{
		ft_free_scene(scene);
		return (NULL);
	}
	(*scene)->inter_min = 1;
	(*scene)->inter_max = -1;
	(*scene)->plan.distance = 1;
	if (argv[2] == NULL || ft_strcmp("--save", argv[2]) != 0)
		(*scene)->mlx = mlx_init();
	(*scene)->background_color = ft_multiply_color((*scene)->ambiant->color, (*scene)->ambiant->intensity);
	return (*scene);
}

char	*ft_append_camerano_to_scene_name(char *scene_file, int camerano)
{
	char	*str;
	char	*str_camerano;

	str_camerano = ft_itoa(camerano);
	str = ft_strjoin(scene_file, "-cam");
	if (str_camerano == NULL || str == NULL)
	{
		free(str_camerano);
		free(str);
		ft_fatal_error("Cannot allocate the camera number string");
		return (NULL);
	}
	scene_file = ft_strjoin(str, str_camerano);
	if (scene_file == NULL)
	{
		ft_fatal_error("Cannot allocate the sene file name");
		return (NULL);
	}
	free(str);
	free(str_camerano);
	str = ft_strjoin(scene_file, ".bmp");
	if (str == NULL)
	{
		free(scene_file);
		ft_fatal_error("Cannot allocate the BMP file name");
		return (NULL);
	}
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
	free(scene_file);
	if (file == NULL)
		return (ft_fatal_error("Cannot allocate the BMP file name"));
	fd = open(file, O_WRONLY | O_CREAT, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	if (!ft_set_bmp_header(scene, fd))
		return (-1);
	buffer->i = 0;
	buffer->str = malloc(3 * scene->plan.width * scene->plan.height);
	if (buffer->str == NULL)
		return (ft_fatal_error("Cannot allocate the BMP file's pixels"));
	return (fd);
}

t_data	*ft_initialize_mlx_img(t_scene *scene)
{
	t_data	*img;

	img = malloc(sizeof(*img));
	if (img == NULL)
	{
		ft_fatal_error("Cannot allocate the mlx image");
		return (NULL);
	}
	img->next = NULL;
	img->img = mlx_new_image(scene->mlx, scene->plan.width, scene->plan.height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
			&img->endian);
	return (img);
}
