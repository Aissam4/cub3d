#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 600
#define screenHeight 600

# define moveSpeed  0.5
# define rotSpeed   0.3

# define ESC_K  53
# define UP_K   13
# define DOWN_K 1
# define LFT_K  0
# define RGHT_K 2
# define R_LFT  123
# define R_RGHT 124

# define SKY    0x87CEEB
# define GRASS  0x567D46

# define X  0
# define Y  1
#define BUFFER_SIZE 1

typedef struct s_parsing
{
	int fd;
	int index;
	int counter;
	char *tmpline;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	int floor_red;
	int floor_green;
	int floor_blue;
	int color_floor;
	int ceiling_red;
	int ceiling_green;
	int ceiling_blue;
	int color_ceiling;
	char **argv;
	char *first_line;
	char **map;
	size_t count_lines;
	size_t biggest_lines;
	size_t skip_lines;
}	t_parsing;

typedef struct cub3D
{
    double  pos[2];
    double  dir[2];
    double  plane[2];
    void    *mlx_ptr;
    void    *win_ptr;
    int     worldMap[mapWidth][mapHeight];
}   t_cub;

typedef struct rayCast
{
    double  camera_x;
    double  delta_dist[2];
    double  side_dist[2];
    double  ray_dir[2];
    int     step[2];
    int     map[2];
    int     side;
    int     hit;
    double  perp_wall_dist;
    int     line_height;
    int     draw_start;
    int     draw_end;
    int     color;
}   t_render;


void    raycast(t_cub *data);
char	*get_next_line(int fd);
char	*ft_strdup(char *str);
size_t	ft_strlen(const char *s);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
int search_for_player(t_parsing *parsing);
void replace_spc_wall(t_parsing *parsing);
void parse_map_assign(t_parsing *parsing);
int check_map(t_parsing *parsing);
int check_first_indexes(t_parsing *parsing);
int check_fist_last_line(t_parsing *parsing);
void parse_map(t_parsing *parsing);
int skip_newlines(t_parsing *parsing);
int skip_directions(t_parsing *parsing, char *argv[], int argc);
int parsing_directions_colors(t_parsing *parsing, char *argv[], int argc);
void init_parsing(t_parsing *parsing, char *argv[]);
int assign_vars(t_parsing *parsing);
int assign_ceiling(t_parsing *parsing, int i);
int assign_floor(t_parsing *parsing, int i);
int skip_spaces(char *tmpline);
int check_file_name(char *str);
int	ft_atoi(const char *str);
void free_parsing(t_parsing *parsing);
void replace_nl_with_null(char *str);
void	*ft_memset(void *s, int c, size_t n);
#endif
