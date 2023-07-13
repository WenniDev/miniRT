/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:57:20 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/11 18:40:35 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "object.h"
#include "scene.h"

typedef struct s_parse
{
	int		argc;
	char	**argv;
	int		fd;
}t_parse;

int	app_parse(t_app *app);

int		ft_isspace(int c);
double	ft_atof(const char *str);
void	ft_split_free(char **split);
int		ft_isdouble(char *str);

int	parse_vec(char *data, void *value);
int	parse_color(char *data, void *value);
int	parse_double(char *data, void *value);
int parse_texture(char *data, void *value);

# include "mlx_app.h"

int	parse_ambient(char *data, t_app *app, bool *amb_init);
int	parse_camera(char *data, t_app *app, bool *cam_init);
int	parse_light(char *data, t_app *app);
int	parse_sphere(char *data, t_app *app);
int	parse_plane(char *data, t_app *app);
int	parse_cylinder(char *data, t_app *app);

int	obj_add_plane(t_plane *plane, t_scene *scene);
int obj_add_sphere(t_sphere *sphere, t_scene *scene);
int obj_add_cylinder(t_cylinder *cylinder, t_scene *scene);
int obj_add_cone(t_cone *cone, t_scene *scene);

void	scene_set_camera(t_cam *cam, t_scene *scene);

#endif
