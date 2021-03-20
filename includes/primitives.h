/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:43:43 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/20 12:46:36 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_H
# define PRIMITIVES_H

typedef struct			s_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

typedef struct			s_sphere
{
	struct s_sphere		*next;
	t_vector			center;
	int					color;
	double				radius;
}						t_sphere;

typedef struct			s_plane
{
	struct s_plane		*next;
	t_vector			center;
	int					color;
	t_vector			direction;
}						t_plane;

typedef struct			s_square
{
	struct s_square		*next;
	t_vector			center;
	int					color;
	t_vector			direction;
	double				width;
}						t_square;

typedef struct			s_cylinder
{
	struct s_cylinder	*next;
	t_vector			center;
	int					color;
	double				radius;
	t_vector			direction;
	double				height;
	t_vector			top;
}						t_cylinder;

typedef struct			s_triangle
{
	struct s_triangle	*next;
	t_vector			point1;
	int					color;
	t_vector			point2;
	t_vector			point3;
	t_vector			edge1;
	t_vector			edge2;
	t_vector			normal;
}						t_triangle;

#endif
