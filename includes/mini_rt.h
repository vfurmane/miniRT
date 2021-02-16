/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 mini_rt.h											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: vfurmane <vfurmane@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/01/28 17:56:05 by vfurmane		   #+#	  #+#			  */
/*	 Updated: 2021/02/01 17:08:44 by vfurmane		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line.h"

# ifndef MINI_RT_BONUS
#  define MINI_RT_BONUS 0
# endif

/*
**	Structures
*/

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct		s_next
{
	struct s_next	*next;
}					t_next;

typedef enum		e_obj_type
{
	PLANE,
	SPHERE,
	CYLINDER
}					t_obj_type;

typedef struct		s_obj
{
	t_obj_type	type;
	void		*ptr;
}					t_obj;

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct	s_pixel
{
	double	x;
	double	y;
	int		color;
}				t_pixel;

typedef struct	s_plan
{
	int	width;
	int	height;
	int	viewport;
	int	distance;
}				t_plan;

typedef struct	s_plane
{
	struct s_plane	*next;
	t_vector		center;
	t_vector		direction;
	int				color;
}				t_plane;

typedef struct	s_sphere
{
	struct s_sphere	*next;
	t_vector		center;
	double			radius;
	int				color;
}				t_sphere;

typedef struct	s_cylinder
{
	struct s_cylinder	*next;
	t_vector			center;
	double				radius;
	t_vector			direction;
	double				height;
	int					color;
}				t_cylinder;

typedef struct	s_light
{
	double			intensity;
	int				color;
}				t_light;

typedef struct	s_bulb
{
	struct s_bulb	*next;
	t_vector		center;
	t_light			light;
}				t_bulb;

typedef struct	s_scene
{
	struct s_plan	plan;
	double			inter_min;
	double			inter_max;
	t_light			ambiant;
	t_bulb			*bulbs;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
}				t_scene;

/*
**	Functions
*/

int			ft_atoi(const char *str);
double		ft_atof(const char *str);

t_vector	ft_canvas_to_viewport_aa(t_pixel pixel, int viewport, t_plan canvas,
				double *aa);
t_vector	ft_canvas_to_viewport(t_pixel pixel, int viewport, t_plan canvas);
t_pixel		ft_translate_pixel(t_pixel pixel, t_plan plan);

int			ft_parse_color(const char *str);
int			ft_color_average(int colors[16]);
double		ft_multiply_color(int color, double intensity);

void		ft_free_split(char **strarr);

int			ft_handle_resolution(char **args, t_scene *scene);
int			ft_handle_ambiant(char **args, t_scene *scene);
int			ft_handle_light(char **args, t_scene *scene);

int			ft_handle_sphere(char **args, t_scene *scene);
int			ft_handle_plane(char **args, t_scene *scene);
int			ft_handle_cylinder(char **args, t_scene *scene);

void		*ft_lstadd_front(void **lst, void *new);

void		my_mlx_put_pixel(t_data *data, t_pixel pixel, int pixel_size, t_scene scene);

void		ft_set_ambiant(t_scene *scene, double intensity, const char *color);
t_bulb		*ft_new_light(const char *vector, double intensity, const char *color);

t_sphere	*ft_new_sphere(char *vector, double diameter, char *color);
t_plane		*ft_new_plane(char *vector, char *direction, char *color);
t_cylinder	*ft_new_cylinder(char **vector, double diameter, double height, char *color);

int			ft_parameters(int argc, char **argv, t_scene *scene);

void		ft_fatal_error(const char *str);
int			ft_error(void);

int			ft_trace_ray(t_vector origin, t_vector direction, t_scene scene);

int			ft_strcmp(char *str1, char *str2);
char		**ft_split(const char *str, char *sep);

t_vector	ft_str_to_vector(const char *str);

t_vector	ft_add_vector_double(t_vector v1, double nbr);
t_vector	ft_substract_vector_double(t_vector v1, double nbr);
t_vector	ft_multiply_vector_double(t_vector v1, double nbr);

t_vector	ft_add_vectors(t_vector v1, t_vector v2);
t_vector	ft_substract_vectors(t_vector v1, t_vector v2);
t_vector	ft_multiply_vectors(t_vector v1, t_vector v2);

double		ft_dot_product(t_vector v1, t_vector v2);
double		ft_vector_length(t_vector vector);
t_vector	ft_normalize_vector(t_vector vector);

#endif
