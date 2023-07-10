/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:07:33 by jopadova          #+#    #+#             */
/*   Updated: 2023/07/07 17:01:49 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_app.h"
#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_app	app;

	ft_memset(&app, 0, sizeof (t_app));
	app.parse.argc = argc;
	app.parse.argv = argv;
	if (app_execute(&app) == FAILURE)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}
