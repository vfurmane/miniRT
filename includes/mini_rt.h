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
# include <math.h>
# include "mlx.h"

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
	int			color;
	int			radius;
	t_vector	vector;
}				t_sphere;

typedef struct	s_light
{
	int			type;
	double		intensity;
	t_vector	vector;
}				t_light;

/*
**	Functions
*/

double		ft_dot_product(t_vector v1, t_vector v2);
double		ft_vector_length(t_vector vector);
int			ft_trace_ray(t_vector origin, t_vector direction, int t_min,
				int t_max);
t_vector	ft_add_vectors(t_vector v1, t_vector v2);
t_vector	ft_substract_vectors(t_vector v1, t_vector v2);
t_vector	ft_multiply_vectors(t_vector v1, t_vector v2);
t_vector	ft_add_vector_double(t_vector v1, double nbr);
t_vector	ft_substract_vector_double(t_vector v1, double nbr);
t_vector	ft_multiply_vector_double(t_vector v1, double nbr);
void		my_mlx_put_pixel(t_data *data, int x, int y, int color);

#endif
