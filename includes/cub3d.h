/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:19:29 by niespana          #+#    #+#             */
/*   Updated: 2023/06/12 10:19:31 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include "../mlx/mlx.h"
# include <stdlib.h>
# include "../libft/libft.h"

# define WIN_WIDTH 1280
# define WIN_WIDTH_2 640
# define WIN_HEIGHT 720
# define WIN_HEIGHT_2 360
# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define W 13
# define A 2
# define S 1
# define D 0
# define PI2 6.28

typedef enum e_path
{
	EA,
	SO,
	WE,
	NO
}t_path;

typedef struct s_img {
	void	*ptr;
	char	*offset;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

/* need to change texture and texture offset to chained list 
 * to allow for multiple elements to be visible when behind each other
 */
typedef struct s_ray {
	double	distance;
	double	angle;
	double	x0;
	double	y0;
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	dx_inv;
	double	dy_inv;
	double	texture_offset;
	t_img	*texture;
}	t_ray;

typedef struct s_player
{
	double	angle;
	double	x;
	double	y;
}	t_player;

typedef struct s_asset{
	char	id;
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	t_img	d;
}	t_asset;

typedef enum e_color
{
	CEILING,
	FLOOR
}t_color;

enum e_shape
{
	CROSS,
	DOT,
	CIRCLE
};

typedef struct s_cursor
{
	int				hover;
	t_img			img;
	enum e_shape	shape;
	int				hover_x;
	int				hover_y;
}t_cursor;

typedef struct s_game
{
	t_player	*player;
	t_asset		*asset;
	t_img		frame;
	t_img		minimap;
	t_cursor	cursor;
	t_img		gun_effect[7];
	t_img		gun;
	t_img		gun_sprite;
	int			pos[3][2];
	int			dimension[2];
	int			sprite_frame;
	int			firing;
	void		*mlx_ptr;
	void		*win_ptr;
	char		**file;
	char		**map;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor_color;
	int			ceiling_color;
	int			up;
	int			down;
	int			left;
	int			right;
	int			key_a;
	int			key_d;
	int			mouse[2];
	int			mouse_lock;
	int			hide_minimap;
	int			should_cast;
	int			color_type;
	int			color_change;
	int			map_allocated;
	int			fired;
	int			current_ray;
}t_game;

//utils.c
int				safe_free(void	*mem_allocated);
int				ft_strcmp(const char *s1, const char *s2);
void			free_array(char	**arr);

//terminate.c
void			terminate(t_game *game, char *msg);

//game_loop.h
void			game_loop(t_game *game);
int				destroy(t_game *game);
int				key_hook(int keycode, t_game *game);
int				loop_hook(t_game *game);

//parsing.c
char			**get_file_array(char *s);
char			*get_path(char **file, t_path path);
int				get_color(char **file, t_color color);
double			get_init_angle(t_game *game);
int				set_player_position(t_game *game, int i, int j);
int				closed_map(char **map);
void			fill_map_blanks(t_game *game, char **map);
void			add_doors(t_game *game, int i, int j);
char			*str_in_str(char *s1, char *s2, int n);
int				arr_size(char **arr);
//raycasting.c
void			cast_ray(t_ray *ray, t_game *game);
void			ray_copy(t_ray *src, t_ray *dest);

//intersect.c
int				intersect_so(t_ray *ray, t_ray *ray_tmp, \
t_game *game, char tile);
int				intersect_no(t_ray *ray, t_ray *ray_tmp, \
t_game *game, char tile);
int				intersect_ea(t_ray *ray, t_ray *ray_tmp, \
t_game *game, char tile);
int				intersect_we(t_ray *ray, t_ray *ray_tmp, \
t_game *game, char tile);

//render.c
void			*build_frame(t_ray *ray, t_game *game);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
unsigned int	get_texture_color(t_img *img, int x, int y);
//syntax.c

int				valid_format(char *s);
int				is_invalid_name(char *s);
int				empty_line(char *s);
int				valid_map_line(char *s);

//minimap.c
char			**get_map(char **file);
void			minimap(t_game *game);
int				trgb(int t, int r, int g, int b);
int				is_charset(char c, char *set, int i);

//game_loop_utils
int				handle_mouse(t_game *game);
int				is_wall(char **map, double y, double x);
void			raycast(t_game *game);
int				input_management(t_game *game, double d_x, double d_y);
int				change_color(t_game *game);

//minimap2.c
void			print_player(t_img *minimap, double i, double j, int color);
void			print_player_fov(t_img *minimap, t_game *game, int color);
void			print_outer_circle(t_img *img, int pos, \
int inner_radius, int color);
void			print_element(t_img *minimap, t_game *game, int i, int j);

//cursor.c
void			init_cursor(t_game *game);
void			print_cursor(t_game *game, int i, int j);
void			print_sprite(t_img *img, int pos[2], int \
dimension[2], t_img *sprite);
void			init_sprite(t_game *game);

//interact.c
void			shoot(t_game *game);

//init.c
void			init_game2(t_game *game);
void			init_game(t_game *game, char *path);
void			init_mlx(t_game *game);
void			init_asset_2(t_game *game);
void			init_asset(t_game *game);
#endif
