/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:57:20 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/10 12:40:51 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "mlx_app.h"

typedef struct s_parse
{
	int		argc;
	char	**argv;
	int		fd;
}t_parse;

typedef struct s_obj_parse
{
	char		*data;
	int	(*parse[6])(char *data, void *value);
}t_obj_parse;

typedef struct s_obj_create
{
	char				*type;
	struct s_obj_lst	*(*create)(void);
}t_obj_create;

int	app_parse(t_app *app);

int	parse_vec(char *data, void *value);
int	parse_color(char *data, void *value);
int	parse_double(char *data, void *value);

int	parse_ambient(char *data, t_scene *scene, bool *amb_init);
int	parse_camera(char *data, t_scene *scene, bool *cam_init);
int	parse_light(char *data, t_scene *scene);
int	parse_sphere(char *data, t_scene *scene);
int	parse_plane(char *data, t_scene *scene);
int	parse_cylinder(char *data, t_scene *scene);

int parse_object(char *data, t_scene *scene);

#endif
