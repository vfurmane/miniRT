/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:37:32 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/19 19:13:24 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_get_anti_aliased_pixel_color(t_scene *scene, t_camera *camera,
		t_pixel *pixel, t_ray *ray)
{
	int	i;
	int	*colors;

	i = 0;
	colors = malloc(sizeof(*colors) * camera->anti_aliasing_level *
			camera->anti_aliasing_level);
	if (colors == NULL)
		return (-1);
	while (i < camera->anti_aliasing_level * camera->anti_aliasing_level)
	{
		ray->direction = ft_canvas_to_viewport(pixel, &scene->plan, camera, i);
		colors[i++] = ft_trace_ray(ray, *scene);
	}
	pixel->color = ft_color_average(colors, camera->anti_aliasing_level *
			camera->anti_aliasing_level);
	free(colors);
	return (pixel->color);
}

int		ft_get_pixel_color(t_scene *scene, t_camera *camera, t_pixel *pixel)
{
	t_ray		ray;

	pixel->color = -1;
	ray.origin = camera->center;
	if (MINI_RT_BONUS)
	{
		pixel->color = ft_get_anti_aliased_pixel_color(scene, camera, pixel,
				&ray);
		if (pixel->color == -1)
			return (-1);
	}
	else
	{
		ray.direction = ft_canvas_to_viewport(pixel, &scene->plan, camera, 0);
		pixel->color = ft_trace_ray(&ray, *scene);
	}
	return (pixel->color);
}

int		ft_render_scene(t_scene *scene, t_camera *camera, t_buffer *buffer,
		t_data *img)
{
	int			end_of_line;
	t_pixel		pixel;

	end_of_line = 4 - (scene->plan.width * 3) % 4;
	pixel.y = -scene->plan.height / 2;
	while (pixel.y <= scene->plan.height / 2 - (scene->plan.height % 2 == 0))
	{
		pixel.x = -scene->plan.width / 2;
		while (pixel.x <= scene->plan.width / 2 - (scene->plan.height % 2 == 0))
		{
			if (ft_get_pixel_color(scene, camera, &pixel) == -1)
				return (0);
			if (scene->mlx != NULL)
				my_mlx_put_pixel(img, ft_translate_pixel(pixel, scene->plan),
						camera->pixel_size, *scene);
			else
				ft_add_pixel_to_bmp(buffer, pixel.color,
						(pixel.x == scene->plan.width / 2) * end_of_line);
			pixel.x += camera->pixel_size;
		}
		pixel.y += camera->pixel_size;
	}
	return (1);
}

int		ft_proceed_all_cameras(t_scene *scene, t_buffer *buffer, char **argv)
{
	int			camerano;
	t_data		*img;
	t_camera	*camera;

	camerano = -1;
	camera = scene->cameras;
	if (camera->next != NULL)
		camerano = ft_lstsize(camera) - 1;
	while (camera != NULL)
	{
		if (scene->mlx == NULL)
		{
			buffer->fd = ft_initialize_bmp_file(scene, buffer, argv[1],
					camerano--);
			if (buffer->fd == -1)
				return (0);
		}
		else
		{
			img = ft_initialize_mlx_img(scene);
			if (img == NULL)
				return (0);
		}
		ft_calculate_camera_rotation_and_fov(scene, camera);
		if (ft_render_scene(scene, camera, buffer, img) == 0)
			return (0);
		if (camera->next == NULL)
			scene->current_camera = camera;
		camera = camera->next;
		if (scene->mlx == NULL)
		{
			write(buffer->fd, buffer->str, 3 * scene->plan.width *
					scene->plan.height);
			free(buffer->str);
			close(buffer->fd);
		}
		else
			ft_lstadd_front((void**)(&scene->img), (void*)(img));
	}
	return (1);
}

void	ft_proceed_window(t_scene *scene)
{
	t_data	*img;

	img = scene->img;
	while (img->next != NULL)
		img = img->next;
	img->next = scene->img;
	scene->win = mlx_new_window(scene->mlx, scene->plan.width,
			scene->plan.height, scene->title);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->img, 0, 0);
	my_mlx_events(scene);
	mlx_loop(scene->mlx);
}
