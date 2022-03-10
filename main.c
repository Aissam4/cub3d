/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:24:28 by abarchil          #+#    #+#             */
/*   Updated: 2022/03/10 17:49:36 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
int	search_for_player(t_parsing *parsing, int i, int j, int count)
{
	while (parsing->map[i])
	{
		j = 0;
		while (parsing->map[i][j])
		{
			if (parsing->map[i][j] != '1' && parsing->map[i][j]
				!= '0' && parsing->map[i][j] != 'N' && parsing->map[i][j]
				!= 'S' && parsing->map[i][j] != 'E' && parsing->map[i][j]
				!= 'W')
				return (free_parsing(parsing),
					printf("Error:Map Error: 0x10\n"), 1);
			else if (parsing->map[i][j] == 'N' || parsing->map[i][j] == 'S'
			|| parsing->map[i][j] == 'E' || parsing->map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (free_parsing(parsing), printf("Error:Map Error: 0x10\n"), 1);
	return (0);
}

void	ft_debug(t_parsing *parsing)
{
	int	i;

	i = 0;
	printf("%s\n%s\n%s\n%s\n", parsing->no, parsing->we, parsing->ea, parsing->so);
	printf("F %d %d %d | C %d %d %d\n", parsing->floor_red,
		parsing->floor_green, parsing->floor_blue, parsing->ceiling_red,
		parsing->ceiling_green, parsing->ceiling_blue);
	while (parsing->map[i])
		printf("-%s-\n", parsing->map[i++]);
}

static int key_handle(int key, t_cub *d)
{
    double  old_dir_x;
    double  old_plane_x;
    double	mv_speed;
    double  d_[2];

    d_[X] = 0.0;
	d_[Y] = 0.0;
    if (key == ESC_K)
        exit(EXIT_SUCCESS);
    else if (key == UP_K)
    {
        if (d->worldMap[(int)(d->pos[X] + d->dir[X] * moveSpeed)][(int)d->pos[Y]] == 0)
            d->pos[X] += d->dir[X] * moveSpeed;
        if (d->worldMap[(int)d->pos[X]][(int)(d->pos[Y] + d->dir[Y] * moveSpeed)] == 0)
            d->pos[Y] += d->dir[Y] * moveSpeed;
    }
    else if (key == DOWN_K)
    {
        if (d->worldMap[(int)(d->pos[X] - d->dir[X] * moveSpeed)][(int)d->pos[Y]] == 0)
            d->pos[X] -= d->dir[X] * moveSpeed;
        if (d->worldMap[(int)d->pos[X]][(int)(d->pos[Y] - d->dir[Y] * moveSpeed)] == 0)
            d->pos[Y] -= d->dir[Y] * moveSpeed;
    }
    else if (key == R_LFT)
    {
        old_dir_x = d->dir[X];
        d->dir[X] = old_dir_x * cos(rotSpeed) - d->dir[Y] * sin(rotSpeed);
        d->dir[Y] = old_dir_x * sin(rotSpeed) + d->dir[Y] * cos(rotSpeed);
        old_plane_x = d->plane[X];
        d->plane[X] = old_plane_x * cos(rotSpeed) - d->plane[Y] * sin(rotSpeed);
        d->plane[Y] = old_plane_x * sin(rotSpeed) + d->plane[Y] * cos(rotSpeed);
    }
    else if (key == R_RGHT)
    {
        old_dir_x = d->dir[X];
        d->dir[X] = old_dir_x * cos(-rotSpeed) - d->dir[Y] * sin(-rotSpeed);
        d->dir[Y] = old_dir_x * sin(-rotSpeed) + d->dir[Y] * cos(-rotSpeed);
        old_plane_x = d->plane[X];
        d->plane[X] = old_plane_x * cos(-rotSpeed) - d->plane[Y] * sin(-rotSpeed);
        d->plane[Y] = old_plane_x * sin(-rotSpeed) + d->plane[Y] * cos(-rotSpeed);
    }
    else if (key == LFT_K)
    {
        mv_speed = moveSpeed * -1 ;
		d_[X] += d->plane[X] * mv_speed;
		d_[Y] += d->plane[Y] * mv_speed;
    }
    else if (key == RGHT_K)
    {
        mv_speed = moveSpeed ;
        d_[X] += d->plane[X] * mv_speed;
        d_[Y] += d->plane[Y] * mv_speed;
    }
    else
        return (0);
    d->pos[X] += d_[X];
	d->pos[Y] += d_[Y];
    raycast(d);
    return (0);
}

int	ft_exit(void)
{
	exit (EXIT_SUCCESS);
	return (0);
}

int main(int ac, char **av)
{
    t_cub   	data;
   t_parsing	parsing;
	int 		index;
	int 		jndex;

    data = (t_cub){0};
	index = -1;
	jndex = -1;
	if (parsing_directions_colors(&parsing, av, ac)
		|| skip_newlines(&parsing))
		return (1);
	parse_map(&parsing, 0);
	parse_map_assign(&parsing, 0);
	if (check_map(&parsing, 0, 0))
		return (1);
	replace_spc_wall(&parsing);
	if (search_for_player(&parsing, 0, 0, 0))
		return (1);
	close(parsing.fd);
	data.worldMap = (int **)malloc(sizeof(int *) * parsing.count_lines + 1);
	while (++index < parsing.count_lines)
		data.worldMap[index] = (int *)malloc(sizeof(int) * parsing.biggest_lines + 1);
	index = -1;
   while (++index < parsing.count_lines)
   {
	   jndex = -1;
	   while (++jndex < parsing.biggest_lines)
	   {
		   if (parsing.map[index][jndex] == '0')
				data.worldMap[index][jndex] = 0;
	   		else if (parsing.map[index][jndex] == '1')
				data.worldMap[index][jndex] = 1;
			else
			{
				data.pos[X] = index;
				data.pos[Y] = jndex;
				data.worldMap[index][jndex]= 0;
				if (parsing.map[index][jndex] == 'E' || parsing.map[index][jndex] == 'W')
                {
                    data.dir[X] = 0;
		            data.dir[Y] = (-(parsing.map[index][jndex] == 'W') || 1);
		            data.plane[X] = 0.66 * (-(parsing.map[index][jndex] == 'W') || 1);
		            data.plane[Y] = 0;
                
	            }
                else if (parsing.map[index][jndex] == 'S' || parsing.map[index][jndex] == 'N')
                {
		            data.dir[X] = (-(parsing.map[index][jndex] == 'S') || 1);
                    data.dir[Y] = 0;
                    data.plane[X] = 0;
		            data.plane[Y] = -0.66 * (-(parsing.map[index][jndex] == 'S') || 1);
                }
			}	
	   }
   }
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, screenWidth, screenHeight, "cub3D");
    raycast(&data);
    mlx_hook(data.win_ptr, 2, 0, key_handle, &data);
    mlx_hook(data.win_ptr, 17, 2, &ft_exit, &data);
    mlx_loop(data.mlx_ptr);
	free_parsing(&parsing);
    return (0);
}
