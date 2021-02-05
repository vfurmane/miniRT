/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:13:35 by vfurmane          #+#    #+#             */
/*   Updated: 2021/02/05 12:51:07 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_parse_line(char *line, t_scene *scene)
{
	char	**args;

	args = ft_split(line, ' ');
	if (args == NULL)
		return ; /* return value */
	if (ft_strcmp(args[0], "R") == 0)
		ft_handle_resolution(&args[1], scene);
	else
		return ; /* return value */
}

void	ft_parse_scene(char *file, t_scene *scene)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(file, O_RDWR);
	if (fd == -1)
		return ; /* return value */
	ret = 1;
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return ; /* return value */
		ft_parse_line(line, scene);
		free(line);
	}
}

void	ft_parameters(int argc, char **argv, t_scene *scene)
{
	int		i;
	char	*file;

	if (argc != 2)
		return ; /* return value */
	i = 1;
	while (i < argc)
	{
		file = argv[i];
		ft_parse_scene(file, scene);
	}
}
