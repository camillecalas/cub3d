#include "../include/cub3D.h"

void	ft_check_direction(t_init *init)
{
	int	nswe;
	int	i;
	int	j;

	nswe = 0;
	i = 0;
	while (init->map[i])
	{	
		j = 0;
		while (init->map[i][j])
		{
			if (init->map[i][j] == 'S' || init->map[i][j] == 'N'
				|| init->map[i][j] == 'W' || init->map[i][j] == 'E')
			{
				init->game->posX = j;
				init->game->posY = i;
				ft_init_dir(init, init->map[i][j]);
				ft_init_plane(init, init->map[i][j]);
				nswe++;
			}
			j++;
		}
		i++;
	}
	if (nswe != 1)
	{
		ft_putstr_fd("Error\nInvalid character direction\n", 2);
		exit(0);
	}
}

void	ft_check_authorised_char(t_init *init)
{
	int	i;
	int	j;

	i = 0;
	while (init->map[i])
	{	
		j = 0;
		while (init->map[i][j])
		{
			if (init->map[i][j] != '1' && init->map[i][j] != '0'
				&& init->map[i][j] != ' ' && init->map[i][j] != '\n'
				&& init->map[i][j] != 'S' && init->map[i][j] != 'N'
				&& init->map[i][j] != 'W' && init->map[i][j] != 'E')
			{
				ft_putstr_fd("Error\nInvalid character\n", 2);
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void	ft_check_close_map(t_init *init)
{
	int	i;
	int	j;
	int	i2;
	int	j2;

	i = 0;
	while (init->map[i])
	{	
		j = 0;
		while (init->map[i][j])
		{
		if (init->map[i][j] == '0' || init->map[i][j] == 'S'
				|| init->map[i][j] == 'N' || init->map[i][j] == 'W'
				|| init->map[i][j] == 'E')
			{
				i2 = i;
				while (i2 >= 0 && init->map[i2][j] != '1'
					&& init->map[i2][j] != ' ' && ft_strcmp(init->map[i2], "")
					&& init->map[i2][j])
					i2--;
				if (i2 < 0 || init->map[i2][j] == ' '
				|| !ft_strcmp(init->map[i2], "") || !init->map[i2][j])
				{
					ft_putstr_fd("Error\nMap not closed\n", 2);
					exit(0);
				}
				i2 = i;
				while (init->map[i2][j] && init->map[i2][j] != '1'
					&& init->map[i2][j] != ' ' && ft_strcmp(init->map[i2], "")
					&& init->map[i2][j])
					i2++;
				if (!init->map[i2] || init->map[i2][j] == ' '
				|| !ft_strcmp(init->map[i2], "") || !init->map[i2][j])
				{
					ft_putstr_fd("Error\nMap not closed\n", 2);
					exit(0);
				}
				j2 = j;
				while (j2 >= 0 && init->map[i][j2] != '1'
					&& init->map[i][j2] != ' ')
					j2--;
				if (j2 < 0 || init->map[i][j2] == ' ')
				{
					ft_putstr_fd("Error\nMap not closed\n", 2);
					exit(0);
				}
				j2 = j;
				while (init->map[i][j2] && init->map[i][j2] != '1'
					&& init->map[i][j2] != ' ')
					j2++;
				if ((size_t)j2 == ft_strlen(init->map[i])
					|| init->map[i][j2] == ' ')
				{
					ft_putstr_fd("Error\nMap not closed\n", 2);
					exit(0);
				}
			}
			j++;
		}
		i++;
	}
}

void	ft_check_map(t_init *init)
{
	ft_check_direction(init);
	ft_check_authorised_char(init);
	ft_check_close_map(init);
}

void	ft_cpy_map(int fd, t_init *init, char *filepath, int n)
{
	char	*line;
	int		nb;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (ft_strlen(line) == 1)
		line = get_next_line(fd);
	nb = 0;
	while (line)
	{
		nb++;
		line = get_next_line(fd);
	}
	close(fd);
	init->map = ft_calloc(nb + 1, sizeof(char *));
	fd = open(filepath, O_RDONLY);
	while (n--)
		line = get_next_line(fd);
	line = get_next_line(fd);
	while (nb--)
	{
		init->map[i] = ft_strndup(line, 0, ft_strlen(line) - 1);
		i++;
		line = get_next_line(fd);
	}
	ft_check_map(init);
}
