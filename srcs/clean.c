#include "../include/cub3D.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}

void	ft_close_int_fd(void)
{
	int	i;

	i = 2;
	close(0);
	close(1);
	while (i < 1024)
	{
		if (!read(i, 0, 0))
			close(i);
		i++;
	}
}

int	ft_clean_all(t_init *init)
{
	if (init->map)
		ft_free_split(init->map);
	if (init->game)
		free(init->game);
	if (init->win)
		mlx_destroy_window(init->mlx, init->win);
	if (init->img)
		mlx_destroy_image(init->mlx, init->img);
	if (init->textures[0].img)
		mlx_destroy_image(init->mlx, init->textures[0].img);
	if (init->textures[1].img)
		mlx_destroy_image(init->mlx, init->textures[1].img);
	if (init->textures[2].img)
		mlx_destroy_image(init->mlx, init->textures[2].img);
	if (init->textures[3].img)
		mlx_destroy_image(init->mlx, init->textures[3].img);
	if (init->mlx)
		mlx_destroy_display(init->mlx);
	if (init->textures[0].path)
		free(init->textures[0].path);
	if (init->textures[1].path)
		free(init->textures[1].path);
	if (init->textures[2].path)
		free(init->textures[2].path);
	if (init->textures[3].path)
		free(init->textures[3].path);
	if (init->mlx)
		free(init->mlx);
	if (init)
		free(init);
	ft_close_int_fd();
	exit(0);
	return (0);
}

void	ft_error(char *msg, t_init *init)
{
	ft_putstr_fd(msg, 2);
	ft_clean_all(init);
}
