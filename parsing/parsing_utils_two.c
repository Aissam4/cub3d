/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:16:45 by atouhami          #+#    #+#             */
/*   Updated: 2022/03/06 19:31:58 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_file_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.' && str[i + 1] && str[i + 2] && str[i + 3]
			&& str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b'
			&& !str[i + 4])
			return (0);
		i++;
	}
	return (-1);
}

int	skip_spaces(char *tmpline)
{
	int	i;

	i = 2;
	while (tmpline[i] == ' ')
		i++;
	return (i);
}

int	assign_floor(t_parsing *parsing, int i)
{
	parsing->floor_red = ft_atoi(&parsing->tmpline[1]);
	while (parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	if (parsing->tmpline[i])
		i++;
	parsing->floor_green = ft_atoi(parsing->tmpline + i);
	while (parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	if (parsing->tmpline[i])
		i++;
	parsing->floor_blue = ft_atoi(parsing->tmpline + i);
	if (parsing->floor_red > 255 || parsing->floor_green > 255
		|| parsing->floor_blue > 255 || parsing->floor_red < 0
		|| parsing->floor_green < 0 || parsing->floor_blue < 0)
		return (free_parsing(parsing), printf("Error : Map Error : 0x4\n"), 1);
	parsing->color_floor = (parsing->floor_red << 16)
		+ (parsing->floor_green << 8) + parsing->floor_blue;
	parsing->counter += 1;
	return (0);
}

int	assign_ceiling(t_parsing *parsing, int i)
{
	parsing->ceiling_red = ft_atoi(&parsing->tmpline[1]);
	while (parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	if (parsing->tmpline[i])
		i++;
	parsing->ceiling_green = ft_atoi(parsing->tmpline + i);
	while (parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	if (parsing->tmpline[i])
		i++;
	parsing->ceiling_blue = ft_atoi(parsing->tmpline + i);
	if (parsing->ceiling_red > 255 || parsing->ceiling_green > 255
		|| parsing->ceiling_blue > 255 || parsing->ceiling_red < 0
		|| parsing->ceiling_green < 0 || parsing->ceiling_blue < 0)
		return (free_parsing(parsing), printf("Error : Map Error : 0x4\n"), 1);
	parsing->color_ceiling = (parsing->floor_red << 16)
		+ (parsing->floor_green << 8) + parsing->floor_blue;
	parsing->counter += 1;
	return (0);
}

void	assign_vars_two(t_parsing *parsing)
{
	int	i;

	if (parsing->tmpline[0] == 'N' && parsing->tmpline[1]
		== 'O' && parsing->tmpline[2] == ' ')
	{
		i = skip_spaces(parsing->tmpline);
		parsing->no = ft_strdup(parsing->tmpline + i);
		parsing->counter += 1;
	}	
	if (parsing->tmpline[0] == 'S' && parsing->tmpline[1]
		== 'O' && parsing->tmpline[2] == ' ')
	{
		i = skip_spaces(parsing->tmpline);
		parsing->so = ft_strdup(parsing->tmpline + i);
		parsing->counter += 1;
	}
	if (parsing->tmpline[0] == 'W' && parsing->tmpline[1]
		== 'E' && parsing->tmpline[2] == ' ')
	{
		i = skip_spaces(parsing->tmpline);
		parsing->we = ft_strdup(parsing->tmpline + i);
		parsing->counter += 1;
	}
}
