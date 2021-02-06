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
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line.h"

# ifndef M_PI
#  define M_PI	3.14159265358979323846
# endif

# define AMBIANT	0
# define POINT		1

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

typedef struct	s_sphere
{
	struct s_sphere	*next;
	t_vector		center;
	double			radius;
	int				color;
}				t_sphere;

typedef struct	s_light
{
	int				color;
	double			intensity;
}				t_light;

typedef struct	s_bulb
{
	struct s_bulb	*next;
	t_light			light;
	t_vector		center;
}				t_bulb;

typedef struct	s_scene
{
	struct s_plan	plan;
	t_sphere		*spheres;
	t_light			ambiant;
	t_bulb			*bulbs;
}				t_scene;

/*
**	Functions
*/

double		ft_dot_product(t_vector v1, t_vector v2);
double		ft_vector_length(t_vector vector);
int			ft_trace_ray(t_vector origin, t_vector direction, int t_min,
				int t_max, t_scene scene);
t_vector	ft_add_vectors(t_vector v1, t_vector v2);
t_vector	ft_substract_vectors(t_vector v1, t_vector v2);
t_vector	ft_multiply_vectors(t_vector v1, t_vector v2);
t_vector	ft_add_vector_double(t_vector v1, double nbr);
t_vector	ft_substract_vector_double(t_vector v1, double nbr);
t_vector	ft_multiply_vector_double(t_vector v1, double nbr);
void		my_mlx_put_pixel(t_data *data, int x, int y, int color);
int			ft_parameters(int argc, char **argv, t_scene *scene);
void		ft_handle_resolution(char **args, t_scene *scene);
void		ft_handle_resolution(char **args, t_scene *scene);
void		ft_handle_ambiant(char **args, t_scene *scene);
void		ft_handle_light(char **args, t_scene *scene);
int			ft_atoi(const char *str);
double		ft_atof(const char *str);
int			ft_parse_color(const char *str);
int			ft_error(void);
void		*ft_lstadd_front(void **lst, void *new);
int			ft_strcmp(char *str1, char *str2);
char		**ft_split(const char *str, char sep);
void		ft_set_ambiant(t_scene *scene, double intensity, const char *color);
t_bulb		*ft_new_light(const char *vector, double intensity, const char *color);
t_sphere	*ft_new_sphere(char *vector, double diameter, char *color);
void		ft_handle_sphere(char **args, t_scene *scene);
t_vector	ft_str_to_vector(const char *str);

#endif
