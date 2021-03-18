/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:06:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 12:46:39 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_calculate_intersections(double k[3], double t[2])
{
	double	discriminant;

	discriminant = k[1] * k[1] - (4 * k[0] * k[2]);
	if (discriminant < 0)
	{
		t[0] = -1;
		t[1] = -1;
		return (0);
	}
	t[0] = (-k[1] - sqrt(discriminant)) / (2 * k[0]);
	t[1] = (-k[1] + sqrt(discriminant)) / (2 * k[0]);
	return (1);
}

void	ft_intersect_ray(t_vector origin, t_vector direction, t_obj obj,
		double inter[2])
{
	if (obj.type == PLANE)
		ft_intersect_ray_plane(origin, direction, obj.ptr, inter);
	else if (obj.type == SPHERE)
		ft_intersect_ray_sphere(origin, direction, obj.ptr, inter);
	else if (obj.type == SQUARE)
		ft_intersect_ray_square(origin, direction, obj.ptr, inter);
	else if (obj.type == CYLINDER)
		ft_intersect_ray_cylinder(origin, direction, obj.ptr, inter);
}

double	ft_closest_obj(double inter1, double inter2, t_obj *obj1, t_obj *obj2)
{
	if ((inter1 <= inter2 && inter1 != -1) || inter2 == -1)
		return (inter1);
	else if (inter2 != -1)
	{
		obj1->ptr = obj2->ptr;
		obj1->type = obj2->type;
		return (inter2);
	}
	return (-1);
}

double	ft_closest_intersection(t_vector origin, t_vector direction,
		t_scene scene, t_obj *obj)
{
	double	inter[2];
	double	closest_inter;
	t_obj	obj_copy;
	t_obj	closest_obj;

	obj_copy = *obj;
	closest_inter = -1;
	while (obj_copy.ptr != NULL)
	{
		ft_intersect_ray(origin, direction, obj_copy, inter);
		if (inter[0] >= scene.inter_min &&
				(inter[0] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[0] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[0];
			closest_obj = obj_copy;
		}
		if (inter[1] >= scene.inter_min &&
				(inter[1] <= scene.inter_max || scene.inter_max == -1) &&
				(inter[1] < closest_inter || closest_inter == -1))
		{
			closest_inter = inter[1];
			closest_obj = obj_copy;
		}
		obj_copy.ptr = ((t_basic_obj*)obj_copy.ptr)->next;
	}
	obj->ptr = closest_obj.ptr;
	return (closest_inter);
}

int		ft_trace_ray(t_vector origin, t_vector direction, t_scene scene)
{
	double		closest_inter1;
	double		closest_inter2;
	t_obj		obj1;
	t_obj		obj2;
	t_vector	point;

	obj1.ptr = scene.planes;
	obj1.type = PLANE;
	closest_inter1 = ft_closest_intersection(origin, direction, scene, &obj1);
	obj2.ptr = scene.squares;
	obj2.type = SQUARE;
	closest_inter2 = ft_closest_intersection(origin, direction, scene, &obj2);
	closest_inter1 = ft_closest_obj(closest_inter1, closest_inter2, &obj1, &obj2);
	obj2.ptr = scene.spheres;
	obj2.type = SPHERE;
	closest_inter2 = ft_closest_intersection(origin, direction, scene, &obj2);
	closest_inter1 = ft_closest_obj(closest_inter1, closest_inter2, &obj1, &obj2);
	obj2.ptr = scene.cylinders;
	obj2.type = CYLINDER;
	closest_inter2 = ft_closest_intersection(origin, direction, scene, &obj2);
	closest_inter1 = ft_closest_obj(closest_inter1, closest_inter2, &obj1, &obj2);
	if (closest_inter1 == -1)
		return (scene.background_color);
	point = ft_add_vectors(origin, ft_multiply_vector_double(direction,
				closest_inter1));
	return (ft_compute_lighting(point, obj1, scene, ((t_basic_obj*)obj1.ptr)->color));
}

double	*ft_initialize_anti_aliasing_matrix(int level)
{
	int		i;
	int		matrix_len;
	double	*matrix;
	double	raysize;

	matrix_len = level * level * 2;
	matrix = malloc(sizeof(*matrix) * matrix_len);
	if (matrix == NULL)
		return (NULL);
	raysize = 1.0 / level;
	i = 0;
	while (i < matrix_len / 2)
	{
		matrix[i * 2] = -0.5 + (raysize / 2) + (raysize * (i % level));
		matrix[i * 2 + 1] = 0.5 - (raysize / 2) + (raysize * (i % level));
		i++;
	}
	return (matrix);
}

int	ft_get_pixel_color(t_scene *scene, t_camera *camera, t_pixel *pixel)
{
	int			i;
	int			*colors;
	t_vector	direction;

	pixel->color = -1;
	colors = malloc(sizeof(*colors) * camera->anti_aliasing_level * camera->anti_aliasing_level);
	if (colors == NULL)
		return (pixel->color);
	if (MINI_RT_BONUS)
	{
		i = 0;
		while (i < camera->anti_aliasing_level * camera->anti_aliasing_level)
		{
			direction = ft_canvas_to_viewport(pixel, &scene->plan, camera, i);
			colors[i] = ft_trace_ray(camera->center, direction, *scene);
			i++;
		}
		pixel->color = ft_color_average(colors);
	}
	else
	{
		direction = ft_canvas_to_viewport(pixel, &scene->plan, camera, 0);
		pixel->color = ft_trace_ray(camera->center, direction, *scene);
	}
	free(colors);
	return (pixel->color);
}

int		ft_render_scene(t_scene *scene, t_camera *camera, t_buffer *buffer, t_data *img)
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
				ft_add_pixel_to_bmp(buffer, pixel.color, (pixel.x == scene->plan.width / 2) * end_of_line);
			pixel.x += camera->pixel_size;
		}
		pixel.y += camera->pixel_size;
	}
	return (1);
}
