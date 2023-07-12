//
// Created by Joachim Padovani on 12/07/2023.
//

#include "parsing.h"
#include "miniRT.h"

//int parse_norm_mat(char *data, t_app *app)
//{
//	char **split;
//	int i;
//
//	i = 0;
//	split = ft_split(data, " \t\r\n\v\f");
//	if (!split)
//		return (FAILURE);
//	while (split[i])
//		i++;
//	if (i != 4)
//		return (ft_split_free(split), FAILURE);
//	if (parse_vec(split[0], &mat.color) == FAILURE)
//		return (ft_split_free(split), FAILURE);
//}

int parse_txt_mat(char *data, t_app *app)
{
	char **split;
	char *path;
	int i;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 1)
		return (ft_split_free(split), FAILURE);
	if (parse_texture(split[0], &path) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (mat_txt_add(path, app) == FAILURE)
		return (ft_split_free(split), FAILURE);
	return (ft_split_free(split), SUCCESS);
}

int	parse_simp_mat(char *data, t_app *app)
{
	char	**split;
	int		i;
	t_material mat;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 3)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[0], &mat.reflec) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[1], &mat.shiny) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[2], &mat.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	mat_simp_add(&mat, &app->scene);
	return (ft_split_free(split), SUCCESS);
}

int parse_ref_mat(char *data, t_app *app)
{
	char	**split;
	int		i;
	t_material mat;

	i = 0;
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (FAILURE);
	while (split[i])
		i++;
	if (i != 4)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[0], &mat.reflec) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[1], &mat.shiny) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_double(split[2], &mat.translucency) == FAILURE)
		return (ft_split_free(split), FAILURE);
	if (parse_vec(split[3], &mat.color) == FAILURE)
		return (ft_split_free(split), FAILURE);
	mat_ref_add(&mat, &app->scene);
	return (ft_split_free(split), SUCCESS);
}

