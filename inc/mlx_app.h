#ifndef MLX_APP_H
# define MLX_APP_H

# include "mlx.h"
# include "mlx_image.h"
# include "scene.h"
# include "camera.h"
# include <X11/keysym.h>

typedef struct s_app
{
	void	*dsp_id;
	void	*win_id;
	t_img	img;
	t_cam	cam;
}t_app;

int	app_exit(t_app *app);
int	app_execute(t_app *app);
int	app_key_action(int key_code, t_app *app);

#endif //MLX_APP_H
