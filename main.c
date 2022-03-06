#include "cub3D.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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
    t_cub   data;

    data = (t_cub){0};
    t_parsing parsing;

	if (parsing_directions_colors(&parsing, av, ac) || skip_newlines(&parsing))
		return (1);
	parse_map(&parsing);
	parse_map_assign(&parsing);
	if (check_map(&parsing))
		return 1;
	replace_spc_wall(&parsing);
	if (search_for_player(&parsing))
		return 1;
	close(parsing.fd);
	free_parsing(&parsing);
    // BETA
    for (int i = 0; i < mapHeight; i++)
        for (int j = 0; j < mapWidth; j++)
            data.worldMap[i][j] = worldMap[i][j];
    data.pos[X] = 22;
    data.pos[Y] = 12;
    data.dir[X] = -1;
    data.dir[Y] = 0;
    data.plane[X] = 0;
    data.plane[Y] = 0.66;
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, screenWidth, screenHeight, "cub3D");
    raycast(&data);
    mlx_hook(data.win_ptr, 2, 0, key_handle, &data);
    mlx_hook(data.win_ptr, 17, 2, &ft_exit, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}
