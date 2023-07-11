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
