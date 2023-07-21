/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:42:35 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/20 09:12:53 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "libft.h"
#include "mlx_app.h"
#include "miniRT.h"
#include "parsing.h"

static const t_parse_lst	g_parser[12] = {
{"A", parse_ambient, NULL, NULL},
{"C", parse_camera, NULL, NULL},
{"l", parse_light, NULL, NULL},
{"sp", parse_obj, init_sphere, add_sphere},
{"pl", parse_obj, init_plane, add_plane},
{"cy", parse_obj, init_cylinder, add_cylinder},
{"cn", parse_obj, init_cone, add_cone},
{"ms", parse_simp_mat, NULL, NULL},
{"mr", parse_ref_mat, NULL, NULL},
{"tx", parse_txt_mat, NULL, NULL},
{"nm", parse_norm_mat, NULL, NULL},
{NULL, NULL, NULL, NULL}
};

int	check_args(t_parse *app)
{
	if (app->argc != 2)
		return (print_error(FUNC, WRNG_ARG_NB, -1));
	if (ft_strncmp(app->argv[1] + ft_strlen(app->argv[1]) - 3, ".rt", 3))
		return (print_error(FUNC, WRNG_FL_EXT, -1));
	if (ft_strlen(app->argv[1]) < 4)
		return (print_error(FUNC, WRNG_FL_NAME, -1));
	app->fd = open(app->argv[1], O_RDONLY);
	if (app->fd == -1)
		return (print_error(FUNC, strerror(errno), -1));
	return (SUCCESS);
}

int	check_id(char *id, char *line)
{
	if (ft_strncmp(line, id, ft_strlen(id)))
		return (FAILURE);
	if (!is_separator(line[ft_strlen(id)]))
		return (FAILURE);
	return (SUCCESS);
}

int	parse_line(t_app *app, char *line)
{
	int			i;
	static int	line_nb = 0;

	++line_nb;
	while (*line && is_separator(*line))
		++line;
	if (*line == '\0' || *line == '#')
		return (SUCCESS);
	i = 0;
	while (g_parser[i].id && check_id(g_parser[i].id, line) == FAILURE)
		++i;
	if (g_parser[i].id == NULL)
		return (print_error(FUNC, UNKW_ID, line_nb));
	if (g_parser[i].parse(
			line + ft_strlen(g_parser[i].id),
			app,
			g_parser[i].set_parse_step,
			g_parser[i].add_obj)
	)
		return (print_error(FUNC, g_parser[i].id, line_nb));
	return (SUCCESS);
}

int	parse_file(t_app *app)
{
	char	*line;
	int		close_fd;

	line = "";
	while (line)
	{
		line = get_next_line(app->parse.fd);
		if (line && parse_line(app, line) == FAILURE)
		{
			free(line);
			close_fd = open("/dev/null", O_RDONLY);
			if (close_fd == -1)
				return (FAILURE);
			get_next_line(close_fd);
			close(close_fd);
			return (FAILURE);
		}
		free(line);
	}
	return (SUCCESS);
}

int	app_parse(t_app *app)
{
	if (check_args(&app->parse) == FAILURE)
		return (FAILURE);
	if (parse_file(app) == FAILURE)
		return (close(app->parse.fd), FAILURE);
	close(app->parse.fd);
	printf("Parsing success\n");
	return (SUCCESS);
}
