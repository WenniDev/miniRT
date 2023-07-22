/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:57:20 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/22 14:29:44 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "object.h"
# include "scene.h"
# include "mlx_app.h"
# include <errno.h>

# define FUNC (char *)__FUNCTION__

# define WRNG_ARG_NB "Wrong number of arguments"
# define WRNG_FL_EXT "Wrong file extension"
# define WRNG_FL_NAME "Wrong file name"

# define WRNG_RGB "Wrong RGB value"
# define WRNG_VEC "Wrong vector value"
# define WRNG_VEC_VAL "Wrong number of values"
# define WRNG_DOUBLE "Wrong double value"

# define MALLOC_ERR "Malloc error"

# define MULTI_AMB "Multiple ambient light"
# define MULTI_CAM "Multiple camera"

# define PARSE_ERR "Parsing error"
# define UNKW_ID "Unknown identifier"
# define WRNG_TX_EXT "Wrong texture extension"
# define TX_NOT_FND "Texture file not found"

typedef struct s_parse_lst
{
	char	*id;
	int		(*parse)(char *, t_app *, void (*set_parse_step)(t_f_parse *,
				t_p_object *), int (*add_obj)(t_p_object *, t_scene *));
	void	(*set_parse_step)(t_f_parse *, t_p_object *);
	int		(*add_obj)(t_p_object *, t_scene *);
}			t_parse_lst;

int			print_error(char *context, char *str, int line_nb);

int			app_parse(t_app *app);

double		ft_atof(const char *str);
void		ft_split_free(char **split);
int			ft_isdouble(char *str);

int			parse_vec(char *data, void *value);
int			parse_color(char *data, void *value);
int			parse_double(char *data, void *value);
int			parse_texture(char *data, void *value);

int			get_nb_data(t_f_parse data[7]);
int			check_nb_value(char **split, int nb);
int			is_separator(char c);

int			parse_ambient(char *data, t_app *app,
				void (*set_parse_step)(t_f_parse *, t_p_object *),
				int (*add_obj)(t_p_object *, t_scene *));
int			parse_camera(char *data, t_app *app,
				void (*set_parse_step)(t_f_parse *, t_p_object *),
				int (*add_obj)(t_p_object *, t_scene *));
int			parse_light(char *data, t_app *app,
				void (*set_parse_step)(t_f_parse *, t_p_object *),
				int (*add_obj)(t_p_object *, t_scene *));

void		set_camera(t_cam *cam, t_scene *scene);
int			scene_add_light(t_light *light, t_scene *scene);
void		scene_add_ambiant(t_light *light, t_scene *scene);

int			parse_obj(char *data, t_app *app,
				void (*set_parse_step)(t_f_parse *, t_p_object *),
				int (*add_obj)(t_p_object *, t_scene *));

void		init_plane(t_f_parse *parse, t_p_object *obj);
void		init_sphere(t_f_parse *parse, t_p_object *obj);
void		init_cylinder(t_f_parse *parse, t_p_object *obj);
void		init_cone(t_f_parse *parse, t_p_object *obj);

int			add_plane(t_p_object *plane, t_scene *scene);
int			add_sphere(t_p_object *sphere, t_scene *scene);
int			add_cylinder(t_p_object *cylinder, t_scene *scene);
int			add_cone(t_p_object *cone, t_scene *scene);

void		mat_simp_add(t_material *mat, t_scene *scene);
int			parse_simp_mat(char *data, t_app *app,
				void (*set_parse_step)(t_f_parse *, t_p_object *),
				int (*add_obj)(t_p_object *, t_scene *));

void		mat_ref_add(t_material *mat, t_scene *scene);
int			parse_ref_mat(char *data, t_app *app,
				void (*set_parse_step)(t_f_parse *, t_p_object *),
				int (*add_obj)(t_p_object *, t_scene *));

int			mat_txt_add(char *path, t_app *app);
int			parse_txt_mat(char *data, t_app *app,
				void (*set_parse_step)(t_f_parse *, t_p_object *),
				int (*add_obj)(t_p_object *, t_scene *));

int			mat_normal_add(char *path, t_app *app);
int			parse_norm_mat(char *data, t_app *app,
				void (*set_parse_step)(t_f_parse *, t_p_object *),
				int (*add_obj)(t_p_object *, t_scene *));
#endif
