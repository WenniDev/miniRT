/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:53:10 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/22 14:27:41 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "miniRT.h"
#include "normal_map.h"

int	parse_norm_mat(char *data,
	t_app *app,
	void (*set_parse_step)(t_f_parse *, t_p_object *),
	int (*add_obj)(t_p_object *, t_scene *))
{
	char	**split;
	int		i;
	char	*path;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (print_error(FUNC, MALLOC_ERR, -1));
	while (split[i])
		i++;
	if (i != 1)
		return (ft_split_free(split), FAILURE);
	if (parse_texture(split[0], &path) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (mat_normal_add(path, app) == FAILURE)
		return (ft_split_free(split), FAILURE);
	((void)set_parse_step, (void)add_obj);
	return (ft_split_free(split), SUCCESS);
}

int	parse_txt_mat(char *data,
	t_app *app,
	void (*set_parse_step)(t_f_parse *, t_p_object *),
	int (*add_obj)(t_p_object *, t_scene *))
{
	char	**split;
	char	*path;
	int		i;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (print_error(FUNC, MALLOC_ERR, -1));
	while (split[i])
		i++;
	if (i != 1)
		return (ft_split_free(split), FAILURE);
	if (parse_texture(split[0], &path) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (mat_txt_add(path, app) == FAILURE)
		return (ft_split_free(split), FAILURE);
	((void)set_parse_step, (void)add_obj);
	return (ft_split_free(split), SUCCESS);
}

int	parse_simp_mat(char *data,
	t_app *app,
	void (*set_parse_step)(t_f_parse *, t_p_object *),
	int (*add_obj)(t_p_object *, t_scene *))
{
	char		**split;
	int			i;
	t_material	mat;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (print_error(FUNC, MALLOC_ERR, -1));
	while (split[i])
		i++;
	if (i != 3)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[0], &mat.reflec) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[1], &mat.shiny) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[2], &mat.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	mat_simp_add(&mat, &app->scene);
	((void)set_parse_step, (void)add_obj);
	return (ft_split_free(split), SUCCESS);
}

int	parse_ref_mat(char *data,
	t_app *app,
	void (*set_parse_step)(t_f_parse *, t_p_object *),
	int (*add_obj)(t_p_object *, t_scene *))
{
	char		**split;
	int			i;
	t_material	mat;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (print_error(FUNC, MALLOC_ERR, -1));
	while (split[i])
		i++;
	if (i != 4)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[0], &mat.reflec) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[1], &mat.shiny) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[2], &mat.trans) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_color(split[3], &mat.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	mat_ref_add(&mat, &app->scene);
	((void)set_parse_step, (void)add_obj);
	return (ft_split_free(split), SUCCESS);
}
