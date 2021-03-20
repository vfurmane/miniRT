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
# include <errno.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "mlx.h"
# include "get_next_line.h"
# include "mini_rt_utils.h"

# ifndef MINI_RT_BONUS
#  define MINI_RT_BONUS 0
# endif

# ifndef MINI_RT_PIXEL_SIZE
#  define MINI_RT_PIXEL_SIZE 2
# endif

# ifndef M_PI
#  define M_PI 3.1415926535
# endif

/*
**	Structures
*/

typedef struct		s_mlx_data {
	struct s_mlx_data	*next;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}					t_mlx_data;

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct	s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct		s_basic_obj
{
	t_next			*next;
	t_vector		center;
	int				color;
}					t_basic_obj;

typedef enum		e_obj_type
{
	SPHERE,
	PLANE,
	SQUARE,
	TRIANGLE,
	CYLINDER
}					t_obj_type;

typedef struct		s_obj
{
	t_obj_type	type;
	double		inter;
	void		*ptr;
}					t_obj;

typedef struct	s_pixel
{
	double	x;
	double	y;
	int		color;
}				t_pixel;

typedef struct	s_plan
{
	int		width;
	int		height;
	double	viewport;
	double	distance;
}				t_plan;

typedef struct	s_camera
{
	struct s_camera	*next;
	t_vector		center;
	t_vector		direction;
	t_vector		right;
	t_vector		up;
	t_vector		forward;
	int				fov;
	int				angle;
	int				pixel_size;
	int				anti_aliasing_level;
	double			*anti_aliasing_matrix;
}					t_camera;

typedef struct	s_plane
{
	struct s_plane	*next;
	t_vector		center;
	int				color;
	t_vector		direction;
}				t_plane;

typedef struct	s_square
{
	struct s_square	*next;
	t_vector		center;
	int				color;
	t_vector		direction;
	double			width;
}				t_square;

typedef struct	s_triangle
{
	struct s_triangle	*next;
	t_vector			point1;
	int					color;
	t_vector			point2;
	t_vector			point3;
	t_vector			edge1;
	t_vector			edge2;
	t_vector			normal;
}				t_triangle;

typedef struct	s_sphere
{
	struct s_sphere	*next;
	t_vector		center;
	int				color;
	double			radius;
}				t_sphere;

typedef struct	s_cylinder
{
	struct s_cylinder	*next;
	t_vector			center;
	int					color;
	double				radius;
	t_vector			direction;
	double				height;
	t_vector			top;
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

typedef struct	s_buffer
{
	int			fd;
	int			i;
	char		*str;
}				t_buffer;

typedef struct	s_scene
{
	void			*mlx;
	void			*win;
	t_mlx_data			*img;
	char			*title;
	struct s_plan	plan;
	double			inter_min;
	double			inter_max;
	int				background_color;
	t_light			*ambiant;
	t_camera		*cameras;
	t_camera		*current_camera;
	t_bulb			*bulbs;
	t_sphere		*spheres;
	t_square		*squares;
	t_triangle		*triangles;
	t_plane			*planes;
	t_cylinder		*cylinders;
}				t_scene;

/*
**	Functions
*/

int			ft_set_bmp_header(t_scene *scene, int fd);
void		ft_add_pixel_to_bmp(t_buffer *buffer, int color, int end_of_line);

void		ft_calculate_camera_rotation_and_fov(t_scene *scene, t_camera *camera);
t_vector	ft_canvas_to_viewport(t_pixel *pixel, t_plan *canvas, t_camera *camera, int	i);
t_pixel		ft_translate_pixel(t_pixel pixel, t_plan plan);

int			ft_check_args_count(char **args, int expected, int line);

int			ft_check_atoi(const char *str, const char *allowed, int line);
int			ft_check_atof(const char *str, const char *allowed, int line);

int			ft_check_parse_color(char *str, int line);

int			ft_check_str_to_vector(const char *str, int norm, int line);

int			ft_parse_color(const char *str);
int			ft_color_average(int *colors, int size);
double		ft_multiply_color(int color, double intensity);

void		ft_free_split(char **strarr);
void		ft_free_gnl(int fd);
void		ft_free_mlx(void *mlx, void *win, t_mlx_data *img, t_camera *camera);
void		ft_free_scene(t_scene **scene);

int			ft_handle_resolution(char **args, t_scene *scene, int line);
int			ft_handle_ambiant(char **args, t_scene *scene, int line);
int			ft_handle_camera(char **args, t_scene *scene, int line);
int			ft_handle_light(char **args, t_scene *scene, int line);

int			ft_handle_sphere(char **args, t_scene *scene, int line);
int			ft_handle_plane(char **args, t_scene *scene, int line);
int			ft_handle_square(char **args, t_scene *scene, int line);
int			ft_handle_cylinder(char **args, t_scene *scene, int line);
int			ft_handle_triangle(char **args, t_scene *scene, int line);

t_scene		*ft_initialize_scene(t_scene **scene, int argc, char **argv);
int			ft_initialize_bmp_file(t_scene *scene, t_buffer *buffer, char *scene_file, int camerano);
t_mlx_data		*ft_initialize_mlx_img(t_scene *scene);

void		ft_add_light_intensity(double intensity[3], int color, double light_intensity);
int			ft_is_in_shadow(t_vector point, t_scene scene, t_bulb *bulb);
int			ft_compute_lighting(t_vector point, t_obj obj, t_scene scene, int color);

void		ft_invert_camera_matrix(t_vector *right, t_vector *up, t_vector *forward);
double		*ft_initialize_anti_aliasing_matrix(int level);

void		my_mlx_events(t_scene *scene);

void		my_mlx_put_pixel(t_mlx_data *data, t_pixel pixel, int pixel_size, t_scene scene);

t_light		*ft_new_ambiant(char **args, int line);
t_camera	*ft_new_camera(char **args, int line);
t_bulb		*ft_new_light(char **args, int line);

t_sphere	*ft_new_sphere(char **args, int line);
t_plane		*ft_new_plane(char **args, int line);
t_square	*ft_new_square(char **args, int line);
t_cylinder	*ft_new_cylinder(char **args, int line);
t_triangle	*ft_new_triangle(char **args, int line);

int			ft_parameters(int argc, char **argv, t_scene *scene);

int			ft_fatal_error(const char *str);

double		ft_closest_intersection(t_ray *ray, t_scene scene, t_obj *obj);
int			ft_calculate_intersections(double k[3], double t[2]);
int			ft_trace_ray(t_ray *ray, t_scene scene);
double		*ft_initialize_anti_aliasing_matrix(int level);

int			ft_render_scene(t_scene *scene, t_camera *camera, t_buffer *buffer,
				t_mlx_data *img);
int			ft_proceed_all_cameras(t_scene *scene, t_buffer *buffer, char **argv);
void		ft_proceed_window(t_scene *scene);

t_vector	ft_str_to_vector(const char *str);
int			ft_step_to_number(const char *str, int i);

t_vector	ft_add_vector_double(t_vector v1, double nbr);
t_vector	ft_substract_vector_double(t_vector v1, double nbr);
t_vector	ft_multiply_vector_double(t_vector v1, double nbr);

t_vector	ft_add_vectors(t_vector v1, t_vector v2);
t_vector	ft_substract_vectors(t_vector v1, t_vector v2);
t_vector	ft_multiply_vectors(t_vector v1, t_vector v2);

double		ft_dot_product(t_vector v1, t_vector v2);
double		ft_vector_length(t_vector vector);
t_vector	ft_cross_product(t_vector v1, t_vector v2);
t_vector	ft_normalize_vector(t_vector vector);

/*
**	Functions	PRIMITIVES
*/

void		ft_intersect_ray_cylinder(t_ray *ray,
				t_cylinder *cylinder, double t[2]);
void		ft_precalculate_cylinder(t_cylinder *cylinder);

void		ft_intersect_ray_plane(t_ray *ray,
				t_plane *plane, double t[2]);

void		ft_intersect_ray_sphere(t_ray *ray,
				t_sphere *sphere, double t[2]);

void		ft_intersect_ray_square(t_ray *ray,
				t_square *square, double t[2]);

void		ft_intersect_ray_triangle(t_ray *ray,
				t_triangle *triangle, double t[2]);
void		ft_precalculate_triangle(t_triangle *triangle);

#endif
