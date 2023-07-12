/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:42:35 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/12 16:30:51 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "libft.h"
#include "object.h"
#include "mlx_app.h"
#include "miniRT.h"
#include "parsing.h"

int print_error(char *context, char *str)
{
	ft_putstr_fd("Error: miniRT: ", 2);
	if (context)
	{
		ft_putstr_fd(context, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (FAILURE);
}

int check_args(t_parse *app)
{
	if (app->argc != 2)
		return (print_error(__BASE_FILE__, "Wrong number of arguments"));
	if (ft_strncmp(app->argv[1] + ft_strlen(app->argv[1]) - 3, ".rt", 3))
		return (print_error(__BASE_FILE__, "Wrong file extension"));
	if (ft_strlen(app->argv[1]) < 4)
		return (print_error(__BASE_FILE__, "Wrong file name"));
	app->fd = open(app->argv[1], O_RDONLY);
	if (app->fd == -1)
		return (print_error(__BASE_FILE__, strerror(errno)));
	return (SUCCESS);
}

int	is_separator(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	parse_line(t_app *app, char *line)
{
	while (*line && is_separator(*line))
		++line;
	if (*line == '\0' || *line == '#')
		return (SUCCESS);
	if (line[0] == 'A' && is_separator(line[1]))
		return (parse_ambient(line + 1, app));
	if (line[0] == 'C' && is_separator(line[1]))
		return (parse_camera(line + 1, app));
	if (line[0] == 'l' && is_separator(line[1]))
		return (parse_light(line + 1, app));
	if (line[0] == 's' && line[1] == 'p' && is_separator(line[2]))
		return (parse_sphere(line + 2, app));
	if (line[0] == 'p' && line[1] == 'l' && is_separator(line[2]))
		return (parse_plane(line + 2, app));
	if (line[0] == 'c' && line[1] == 'y' && is_separator(line[2]))
		return (parse_cylinder(line + 2, app));
	if (line[0] == 'c' && line[1] == 'n' && is_separator(line[2]))
		return (parse_cone(line + 2, app));
	if (line[0] == 'm' && line[1] == 's' && is_separator(line[2]))
		return (parse_simp_mat(line + 2, app));
	if (line[0] == 'm' && line[1] == 'r' && is_separator(line[2]))
		return (parse_ref_mat(line + 2, app));
	if (line[0] == 't' && line[1] == 'x' && is_separator(line[2]))
		return (parse_txt_mat(line + 2, app));
//	if (line[0] == 'm' && line[1] == 'n' && is_separator(line[2]))
//		return (parse_norm_mat(line + 2, app));
	return (print_error(line, "Unknown identifier"));
}

int parse_file(t_app *app)
{
	char	*line;

	line = "";
	while (line)
	{
		line = get_next_line(app->parse.fd);
		if (line && parse_line(app, line) == FAILURE)
		{
			free(line);
			return (FAILURE);
		}
		free(line);
	}

	return (SUCCESS);
}

int app_parse(t_app *app)
{
	if (check_args(&app->parse) == FAILURE)
		return (FAILURE);
	if (parse_file(app) == FAILURE)
		return (print_error(__BASE_FILE__, "Parsing error"));
	printf("Parsing success\n");
	return (SUCCESS);
}
