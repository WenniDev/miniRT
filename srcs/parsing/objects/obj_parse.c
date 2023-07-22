/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:47:51 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/22 14:27:50 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "miniRT.h"
#include "mlx_app.h"

int	parse_obj(char *data,
	t_app *app,
	void (*set_parse_step)(t_f_parse *, t_p_object *),
	int (*add_obj)(t_p_object *, t_scene *))
{
	char		**split;
	int			i;
	t_p_object	obj;
	t_f_parse	parse[7];

	set_parse_step(parse, &obj);
	split = ft_split(data, " \t\r\n\v\f");
	if (!split)
		return (print_error(FUNC, MALLOC_ERR, -1));
	if (check_nb_value(split, get_nb_data(parse)) == FAILURE)
		return (ft_split_free(split), FAILURE);
	i = 0;
	while (parse[i].value)
	{
		if (parse[i].parse(split[i], parse[i].value) == FAILURE)
			return (ft_split_free(split), FAILURE);
		i++;
	}
	if (add_obj(&obj, &app->scene) == FAILURE)
		return (ft_split_free(split), FAILURE);
	return (ft_split_free(split), SUCCESS);
}
