/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:13:35 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/22 12:22:01 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_parse_scene_identifiers(t_scene *scene, char **args, int line_nbr)
{
	int	ret;

	ret = 1;
	if (args == NULL)
		return (ft_fatal_error("Cannot parse the file's line"));
	if (args[0] != NULL && args[0][0] == '#')
		ret = 0;
	else if (ft_strcmp(args[0], "R") == 0)
		ret = ft_handle_resolution(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "A") == 0)
		ret = ft_handle_ambiant(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "c") == 0)
		ret = ft_handle_camera(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "l") == 0)
		ret = ft_handle_light(&args[1], scene, line_nbr);
	return (ret);
}

int	ft_parse_shape_identifiers(t_scene *scene, char **args, int line_nbr)
{
	int	ret;

	ret = 1;
	if (ft_strcmp(args[0], "sp") == 0)
		ret = ft_handle_sphere(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "pl") == 0)
		ret = ft_handle_plane(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "sq") == 0)
		ret = ft_handle_square(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "cy") == 0)
		ret = ft_handle_cylinder(&args[1], scene, line_nbr);
	else if (ft_strcmp(args[0], "tr") == 0)
		ret = ft_handle_triangle(&args[1], scene, line_nbr);
	else if (args[0] != NULL)
	{
		printf("Error\nline %d: Unknown identifier '%s'\n", line_nbr, args[0]);
		ret = -1;
	}
	return (ret);
}

int	ft_parse_line(char *line, t_scene *scene)
{
	static int	line_nbr;
	int			ret;
	char		**args;

	line_nbr++;
	ret = 0;
	args = ft_split(line, "\t\v\f\r ");
	free(line);
	ret = ft_parse_scene_identifiers(scene, args, line_nbr);
	if (ret == 1)
		ret = ft_parse_shape_identifiers(scene, args, line_nbr);
	ft_free_split(args);
	return (ret);
}

int	ft_parse_scene(char *file, t_scene *scene)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret = get_next_line(fd, &line);
	while (ret != 0)
	{
		if (ret == -1)
			return (ft_fatal_error("Could not read the file"));
		if (ft_parse_line(line, scene) == -1)
		{
			ft_free_gnl(fd);
			return (-1);
		}
		ret = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
	return (0);
}

int	ft_parameters(int argc, char **argv, t_scene *scene)
{
	char	*file;

	ft_memset(&scene->mlx, 0, sizeof(*scene) -
		((void*)&scene->mlx - (void*)scene));
	scene->plan.width = -1;
	if (argc < 2 || argc > 3)
		return (printf("Error\nUsage: %s scene [--save]\n", argv[0]) * 0 - 1);
	file = argv[1];
	if (ft_strcmp(ft_strrchr(file, '.'), ".rt") != 0)
		return (printf("Error\nFile extension is not .rt\n") * 0 - 1);
	if (ft_parse_scene(file, scene) == -1)
		return (-1);
	if (scene->ambiant == NULL)
		return (printf("Error\nAmbiant light never set\n") * 0 - 1);
	if (scene->plan.width == -1)
		return (printf("Error\nResolution not set\n") * 0 - 1);
	if (scene->cameras == NULL)
		return (printf("Error\n0 camera defined, at least 1 needed\n") * 0 - 1);
	return (0);
}
