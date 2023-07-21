/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raph <raph@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:57:44 by raph              #+#    #+#             */
/*   Updated: 2023/07/21 13:35:26 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_app.h"
#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_app	app;

	ft_memset(&app, 0, sizeof(t_app));
	app.parse.argv = argv;
	app.parse.argc = argc;
	if (app_execute(&app) == FAILURE)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}
