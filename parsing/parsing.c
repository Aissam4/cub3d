/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:09:42 by abarchil          #+#    #+#             */
/*   Updated: 2022/03/05 21:12:57 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3D.h"
void	*ft_memset(void *s, int c, size_t n)
{
	int		i;
	char	*psource;

	i = 0;
	psource = (char *)s;
	while (n)
	{
		psource[i] = (unsigned char)c;
		i++;
		n--;
	}
	return (s);
}

void replace_nl_with_null(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}

void free_parsing(t_parsing *parsing)
{
	int i;

	free(parsing->EA);
	free(parsing->NO);
	free(parsing->WE);
	free(parsing->SO);
	free(parsing->tmpline);
	free(parsing->first_line);
	i = 0;
	while(parsing->map && parsing->map[i])
	{
		free(parsing->map[i]);
		parsing->map[i] = NULL;
		i++;
	}
	free(parsing->map);
	parsing->NO = NULL;
	parsing->SO = NULL;
	parsing->EA = NULL;
	parsing->WE = NULL;
	parsing->tmpline = NULL;
	parsing->map = NULL;
	parsing->first_line = NULL;
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	count;

	i = 0;
	sign = 1;
	count = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		count = count * 10 + str[i] - 48;
		i++;
	}
	return (count * sign);
}


char	*ft_strdup(char *source)
{
	int		i;
	char	*dst;

	i = 0;
	while (source[i])
		i++;
	dst = malloc(i * sizeof(char) + 1);
	if (dst == NULL)
		return (printf("Error : Failed allocation\n"), exit(1), NULL);
	i = 0;
	while (source[i])
	{
		dst[i] = source[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}


int check_file_name(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '.' && str[i + 1] && str[i + 2] && str[i + 3] 
			&& str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b'
			&& !str[i + 4])
			return 0;
		i++;
	}
	return -1;
}

int skip_spaces(char *tmpline)
{
	int i;

	i = 2;
	while(tmpline[i] == ' ')
		i++;
	return i;
}

int assign_floor(t_parsing *parsing, int i)
{
	parsing->floor_red = ft_atoi(&parsing->tmpline[1]);
	while(parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	i++;
	parsing->floor_green = ft_atoi(parsing->tmpline + i);
	while(parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	i++;
	parsing->floor_blue = ft_atoi(parsing->tmpline + i);
	if (parsing->floor_red > 255 || parsing->floor_green > 255
	 || parsing->floor_blue > 255 || parsing->floor_red < 0 
	 || parsing->floor_green < 0 || parsing->floor_blue < 0)
		return(free_parsing(parsing),printf("Error : Map Error : 0x4\n"), 1);
	parsing->color_floor = (parsing->floor_red << 16) + 
	(parsing->floor_green << 8) + parsing->floor_blue;
	parsing->counter += 1;
	return 0;
}

int assign_ceiling(t_parsing *parsing, int i)
{
	parsing->ceiling_red = ft_atoi(&parsing->tmpline[1]);
	while(parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	i++;
	parsing->ceiling_green = ft_atoi(parsing->tmpline + i);
	while(parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	i++;
	parsing->ceiling_blue = ft_atoi(parsing->tmpline + i);
	if (parsing->ceiling_red > 255 || parsing->ceiling_green > 255 
	|| parsing->ceiling_blue > 255 || parsing->ceiling_red < 0 
	|| parsing->ceiling_green < 0 || parsing->ceiling_blue < 0)
		return(free_parsing(parsing) ,printf("Error : Map Error : 0x4\n"), 1);
	parsing->color_ceiling = (parsing->floor_red << 16) + 
	(parsing->floor_green << 8) + parsing->floor_blue;
	parsing->counter += 1;
	return 0;
}

int assign_vars(t_parsing *parsing)
{
	int i;

	if (parsing->tmpline[0] == 'N' && parsing->tmpline[1] == 
	'O' && parsing->tmpline[2] == ' ')
	{
		i = skip_spaces(parsing->tmpline);
		parsing->NO = ft_strdup(parsing->tmpline + i);
		parsing->counter += 1;
	}	
	if (parsing->tmpline[0] == 'S' && parsing->tmpline[1] ==
	 'O' && parsing->tmpline[2] == ' ')
	{
		i = skip_spaces(parsing->tmpline);
		parsing->SO = ft_strdup(parsing->tmpline + i);
		parsing->counter += 1;
	}
	if (parsing->tmpline[0] == 'W' && parsing->tmpline[1] == 
	'E' && parsing->tmpline[2] == ' ')
	{
		i = skip_spaces(parsing->tmpline);
		parsing->WE = ft_strdup(parsing->tmpline + i);
		parsing->counter += 1;
	}
	if (parsing->tmpline[0] == 'E' && parsing->tmpline[1] ==
	 'A' && parsing->tmpline[2] == ' ')
	{
		i = skip_spaces(parsing->tmpline);
		parsing->EA = ft_strdup(parsing->tmpline + i);
		parsing->counter += 1;
	}
	if (parsing->tmpline && parsing->tmpline[0] == 'F' && parsing->tmpline[1] == ' ')
		if(assign_floor(parsing, 2))
			return 1;
	if (parsing->tmpline && parsing->tmpline[0] == 'C' && parsing->tmpline[1] == ' ')
		if(assign_ceiling(parsing, 2))
			return 1;
	return 0;
}

void init_parsing(t_parsing *parsing, char *argv[])
{
	parsing->index = 0;
	parsing->counter = 0;
	parsing->skip_lines = 0;
	parsing->biggest_lines = 0;
	parsing->count_lines = 0;
	parsing->argv = argv;
	parsing->NO = NULL;
	parsing->SO = NULL;
	parsing->EA = NULL;
	parsing->WE = NULL;
	parsing->fd = open(argv[1], O_RDONLY);
	parsing->map = NULL;
	parsing->first_line = NULL;
}

int parsing_directions_colors(t_parsing *parsing, char *argv[], int argc)
{
	if (argc != 2 || check_file_name(argv[1]) == -1)
		return(printf("Error : Invalid arguments : 0x0\n"), 1);
	init_parsing(parsing, argv);
	if (parsing->fd == -1)
		return(printf("Error : Invalid File : 0x1\n"), 1);
	while(parsing->index != 6)
	{
		parsing->tmpline = get_next_line(parsing->fd);
		if (!(parsing->tmpline))
			return(free_parsing(parsing), printf("Error:Map Error: 0x2\n"), 1);
		parsing->skip_lines += 1;	
		if (parsing->tmpline[0] == '\n')
			{
				free(parsing->tmpline);
				parsing->tmpline = NULL;
				continue;
			}
		if (assign_vars(parsing))
			return 1;
		free(parsing->tmpline);
		parsing->tmpline = NULL;
		parsing->index += 1;
	}
	if (parsing->index != parsing->counter || !parsing->SO
	|| !parsing->WE|| !parsing->NO || !parsing->EA)
		return(free_parsing(parsing), printf("Error : Map Error : 0x3\n"), 1);
	return 0;
}

int skip_directions(t_parsing *parsing, char *argv[], int argc)
{
	if (argc != 2 || check_file_name(argv[1]) == -1)
		return(printf("Error : Invalid arguments : 0x0\n"), 1);
	if (parsing->fd == -1)
		return(printf("Error : Invalid File : 0x1\n"), 1);
	parsing->index = 0;
	while(parsing->index != 6)
	{
		printf("%s", parsing->tmpline);
		parsing->tmpline = get_next_line(parsing->fd);
		if (!(parsing->tmpline))
			return(free_parsing(parsing), printf("Error:Map Error: 0x2\n"), 1);
		if (parsing->tmpline[0] == '\n')
			{
				free(parsing->tmpline);
				parsing->tmpline = NULL;
				continue;
			}
		parsing->index += 1;
		free(parsing->tmpline);
		parsing->tmpline = NULL;
	}
	return 0;
}

int skip_newlines(t_parsing *parsing)
{
	while(1)
	{
		parsing->tmpline = get_next_line(parsing->fd);
		if (!parsing->tmpline)
			return(free_parsing(parsing), printf("Error:Map Error: 0x7\n"), 1);
		parsing->skip_lines += 1;	
		if (parsing->tmpline[0] == '\n')
			{
				free(parsing->tmpline);
				parsing->tmpline = NULL;
				continue;
			}
		else
			break;
	}
	parsing->first_line = ft_strdup(parsing->tmpline);
	free(parsing->tmpline);
	parsing->tmpline = NULL;
	return 0;
}

void parse_map(t_parsing *parsing)
{
	size_t i;

	i = 0;
	parsing->count_lines += 1;
	parsing->biggest_lines = ft_strlen(parsing->first_line);
	while(1)
	{
		parsing->tmpline = get_next_line(parsing->fd);
		if (parsing->tmpline)
		{	
			replace_nl_with_null(parsing->tmpline);
			if (ft_strlen(parsing->tmpline) > parsing->biggest_lines)
				parsing->biggest_lines = ft_strlen(parsing->tmpline);
			parsing->count_lines += 1;
			free(parsing->tmpline);
			parsing->tmpline = 0;
			continue ;
		}
		break;
	}
	parsing->map = malloc(sizeof(char *) * (parsing->count_lines + 1));
	if (!parsing->map)
		return (free_parsing(parsing), printf("Error : Failed allocation\n"), exit(1));
	while(i < parsing->count_lines + 1)
		parsing->map[i++] = NULL;
}

int check_fist_last_line(t_parsing *parsing)
{
	int j;

	j = 0;
	while(parsing->map[0][j])
		{
			if (parsing->map[0][j] != '1' && parsing->map[0][j] != ' ')
				return 1;
			j++;
		}
	j = 0;
	while(parsing->map[parsing->count_lines - 1][j])
		{
			if (parsing->map[parsing->count_lines - 1][j] != '1'
			 && parsing->map[parsing->count_lines - 1][j] != ' ')
				return 1;
			j++;
		}
	return 0;
}

int check_first_indexes(t_parsing *parsing)
{
	int j;

	j = 0;
	while(parsing->map[j] && parsing->map[j][0])
		{
			if (parsing->map[j][0] != '1' && parsing->map[j][0] != ' ')
				return 1;
			j++;
		}
	return 0;
}


int check_map(t_parsing *parsing)
{
	int i;
	int j;

	i = 0;
	if (check_fist_last_line(parsing) || check_first_indexes(parsing))
		return(free_parsing(parsing), printf("Error:Map Error: 0x8\n"), 1);
	while(parsing->map[i])
	{
		j = 0;
		while(parsing->map[i][j])
		{
			if (parsing->map[i][j] == ' ' &&
			(
			(i > 0 && parsing->map[i - 1][j] != '1' &&  parsing->map[i - 1][j] != ' ') || 
			(j > 0 && parsing->map[i][j - 1] != '1' &&  parsing->map[i][j - 1] != ' ') ||
			(i < (int)parsing->count_lines - 1 && parsing->map[i + 1][j] != '1' &&  parsing->map[i + 1][j] != ' ') || 
			(j < (int)parsing->biggest_lines  - 1 && parsing->map[i][j + 1] != '1' &&  parsing->map[i][j + 1] != ' ')
			))
				return(free_parsing(parsing), printf("Error:Map Error: 0x9\n"), 1);
			
			j++;
		}
		i++;
	}
	return 0;
}

void parse_map_assign(t_parsing *parsing)
{

	size_t i;

	i = 0;
	close(parsing->fd);
	parsing->fd = open(parsing->argv[1], O_RDONLY);
	while (i < parsing->skip_lines - 1)
	{
		parsing->tmpline = get_next_line(parsing->fd);
		free(parsing->tmpline);
		parsing->tmpline = NULL;
		i++;
	}
	i = 0;
	while(i < parsing->count_lines)
	{
		parsing->tmpline = get_next_line(parsing->fd);
		if (parsing->tmpline)
		{	
			parsing->map[i] = malloc(sizeof(char) * parsing->biggest_lines +1);
			if (!parsing->map[i])
				return (free_parsing(parsing), printf("Error : Failed allocation\n"), exit(1));
			if (parsing->tmpline[0] == '\n')
				return(free_parsing(parsing), printf("Error:Map Error: 0x11\n"), exit(1));
			parsing->map[i][parsing->biggest_lines] = '\0';
			ft_memset(parsing->map[i], ' ', parsing->biggest_lines);
			replace_nl_with_null(parsing->tmpline);
			ft_memmove(parsing->map[i], parsing->tmpline, ft_strlen(parsing->tmpline));
			i++;
			free(parsing->tmpline);
			parsing->tmpline = NULL;
			continue ;
		}
		break;
	}
}

void replace_spc_wall(t_parsing *parsing)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(parsing->map[i])
	{
		j = 0;
		while(parsing->map[i][j])
		{
			if (parsing->map[i][j] == ' ')
				parsing->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int search_for_player(t_parsing *parsing)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	j = 0;
	while(parsing->map[i])
	{
		j = 0;
		while(parsing->map[i][j])
		{
			if (parsing->map[i][j] != '1' && parsing->map[i][j] != '0' && parsing->map[i][j] != 'N' 
			&& parsing->map[i][j] != 'S' && parsing->map[i][j] != 'E' && parsing->map[i][j] != 'W')
				return(free_parsing(parsing), printf("Error:Map Error: 0x10\n"), 1);
			else if (parsing->map[i][j] == 'N'  || parsing->map[i][j] == 'S' 
			|| parsing->map[i][j] == 'E' || parsing->map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return(free_parsing(parsing), printf("Error:Map Error: 0x10\n"), 1);
	return 0;
}
