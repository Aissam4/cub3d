/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:23:43 by abarchil          #+#    #+#             */
/*   Updated: 2022/03/09 14:24:34 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
static void compute_ray_dir(t_cub *d, t_render *r, int x)
{
    r->camera_x = 2.0 * x / screenWidth - 1.0;
    r->ray_dir[X] = d->dir[X] + d->plane[X] * r->camera_x;
    r->ray_dir[Y] = d->dir[Y] + d->plane[Y] * r->camera_x;
}

static void compute_delta_dist(t_cub *d, t_render *r)
{
    r->map[X] = (int)d->pos[X];
    r->map[Y] = (int)d->pos[Y];
    r->delta_dist[X] = fabs(1 / r->ray_dir[X]);
	r->side_dist[X] = 0.0;
	r->side_dist[Y] = 0.0;
    if (r->ray_dir[X] == 0)
        r->delta_dist[X] = 1e30;
    r->delta_dist[Y] = fabs(1 / r->ray_dir[Y]);
    if (r->ray_dir[Y] == 0)
        r->delta_dist[Y] = 1e30;
	r->perp_wall_dist = 0.0;
	r->step[X] = 0.0;
	r->step[Y] = 0.0;
}

static void compute_step_dist(t_cub *d, t_render *r)
{
    if (r->ray_dir[X] < 0)
    {
        r->step[X] = -1;
        r->side_dist[X] = (d->pos[X] - r->map[X]) * r->delta_dist[X];
    }
    else
    {
        r->step[X] = 1;
        r->side_dist[X] = (r->map[X] + 1.0 - d->pos[X]) * r->delta_dist[X];
    }
    if (r->ray_dir[Y] < 0)
    {
        r->step[Y] = -1;
        r->side_dist[Y] = (d->pos[Y] - r->map[Y]) * r->delta_dist[Y];
    }
    else
    {
        r->step[Y] = 1;
        r->side_dist[Y] = (r->map[Y] + 1.0 - d->pos[Y]) * r->delta_dist[Y];
    }
}

static void dda(t_cub *d, t_render *r)
{
    r->hit = 0;
    while (!r->hit)
    {
        if (r->side_dist[X] < r->side_dist[Y])
        {
            r->side_dist[X] += r->delta_dist[X];
            r->map[X] += r->step[X];
            r->side = X;
        }
        else
        {
            r->side_dist[Y] += r->delta_dist[Y];
            r->map[Y] += r->step[Y];
            r->side = Y;
        }
        if (d->worldMap[r->map[X]][r->map[Y]] > 0)
			r->hit = 1;
    }
}

static void compute_perp_wall_dist(t_render *r)
{
    if (r->side == X)
        r->perp_wall_dist = r->side_dist[X] - r->delta_dist[X];
    else
        r->perp_wall_dist = r->side_dist[Y] - r->delta_dist[Y];

}

static void compute_line_height(t_render *r)
{
    r->line_height = screenHeight / r->perp_wall_dist;
    r->draw_start = -r->line_height / 2.0 + screenHeight / 2.0;
    if (r->draw_start < 0)
        r->draw_start = 0;
    r->draw_end = r->line_height / 2.0 + screenHeight / 2.0;
    if (r->draw_end >= screenHeight)
        r->draw_end = screenHeight - 1;
}

static void find_wall_color(t_cub *d, t_render *r)
{
    if (d->worldMap[r->map[X]][r->map[Y]] == 1)
        r->color = 0xFF0000;
    else if (d->worldMap[r->map[X]][r->map[Y]] == 2)
        r->color = 0x00FF00;
    else if (d->worldMap[r->map[X]][r->map[Y]] == 3)
        r->color = 0x0000FF;
    else if (d->worldMap[r->map[X]][r->map[Y]] == 4)
        r->color = 0xFFFFFF;
    else
        r->color = 0xFFFF00;
    if (r->side == X)
        r->color /= 2;
}

static void draw_ver_line(t_cub *d, t_render *r, int x)
{
    int y;

    y = 0;
    while (y < r->draw_start)
        mlx_pixel_put(d->mlx_ptr, d->win_ptr, x, y++, SKY);
    while (y < r->draw_end)
        mlx_pixel_put(d->mlx_ptr, d->win_ptr, x, y++, r->color);
    while (y < screenHeight)
        mlx_pixel_put(d->mlx_ptr, d->win_ptr, x, y++, GRASS);
}

void    raycast(t_cub *data)
{
    int 		x;
    t_render    render;

    x = -1;
    render  = (t_render){0};
    while (++x < screenWidth)
    {
        compute_ray_dir(data, &render, x);
        compute_delta_dist(data, &render);
        compute_step_dist(data, &render);
        dda(data, &render);
        compute_perp_wall_dist(&render);
        compute_line_height(&render);
        find_wall_color(data, &render);
        draw_ver_line(data, &render, x);
    }
}
