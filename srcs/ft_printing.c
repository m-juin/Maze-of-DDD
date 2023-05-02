/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 08:30:27 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/02 13:50:23 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"

void	ft_print_x_lines(mlx_image_t *img, t_bresenham *bre, mlx_texture_t *text)
{
	int	i;

	i = 0;
	while (i <= bre->dx)
	{
		if (bre->pos1.x > -1 && bre->pos1.x < WIDTH && bre->pos1.y > -1 && bre->pos1.y < WIDTH)
			mlx_put_pixel(img, bre->pos1.x, bre->pos1.y, get_rgba(255, 0, 0, 255));
		i++;
		bre->ex = bre->ex - bre->dy;
		if (bre->ex < 0)
		{
			bre->pos1.y = bre->pos1.y + bre->yincr;
			bre->ex = bre->ex + bre->dx;
		}
		bre->pos1.x = bre->pos1.x + bre->xincr;
	}
}

void	ft_print_y_lines(mlx_image_t *img, t_bresenham *bre, mlx_texture_t *text, int texture_x)
{
	t_fvector	pos;
	int	i;
	float	step;

	i = 0;
	step = 256 / (bre->pos2.y - bre->pos1.y) * 4;
	pos.y = 0;
	while (i <= bre->dy)
	{
		if (bre->pos1.x > -1 && bre->pos1.x < HEIGHT && bre->pos1.y > -1 && bre->pos1.y < HEIGHT)
		{
			mlx_put_pixel(img, bre->pos1.x, bre->pos1.y, get_rgba(text->pixels[(int)pos.y * text->width + texture_x],text->pixels[(int)pos.y * text->width + texture_x + 1],text->pixels[(int)pos.y * text->width + texture_x + 2],text->pixels[(int)pos.y * text->width + texture_x + 3]));
		}
		i++;
		bre->ey = bre->ey - bre->dx;
		if (bre->ey < 0)
		{
			bre->pos1.x = bre->pos1.y + bre->xincr;
			bre->ey = bre->ey + bre->dy;
		}
		bre->pos1.y = bre->pos1.y + bre->yincr;
	 	pos.y += step;
	}
}

/*void	ft_print_lines(mlx_image_t *img, t_player *player)
{
	t_bresenham *bre;

	bre = malloc(sizeof(t_bresenham) * 1);
	bre->y1 = player->py;
	bre->y2 = player->pdy;
	bre->x1 = player->px;
	bre->x2 = player->pdx;
	bre->ey = abs(bre->y2 - bre->y1);
	bre->ex = abs(bre->x2 - bre->x1);
	bre->dx = bre->ex * 2;
	bre->dy = bre->ey * 2;
	bre->dx = bre->ex;
	bre->dy = bre->ey;
	bre->xincr = 1;
	bre->yincr = 1;
	if (bre->x1 > bre->x2)
		bre->xincr = -1;
	if (bre->y1 > bre->y2)
		bre->yincr = -1;
	if (bre->dx > bre->dy)
		ft_print_x_lines(img, bre, player->color);
	else
		ft_print_y_lines(img, bre, player->color);
	free(bre);
}*/

mlx_texture_t	*ft_get_texture(t_data *data, t_fvector ray_pos, int *text_x)
{
	if (ray_pos.x < data->player->pos.x)
		ray_pos.x += 1;
	if (ray_pos.y < data->player->pos.y)
		ray_pos.y += 1;
	printf("X = %i	Y = %i\n", (int)ray_pos.x, (int)ray_pos.y);
	if ((int)ray_pos.x % 64 == 0)
	{
		*text_x = ((int)ray_pos.y % 64 * 4);
		if (ray_pos.x < data->player->pos.x)
		{
			*text_x	= 256 - *text_x;
			return (data->east);
		}
		return (data->west);
	}
	*text_x = ((int)ray_pos.x % 64 * 4);
	if (ray_pos.y >= data->player->pos.y)
		return (data->north);
	*text_x	= 256 - *text_x;
	return (data->south);
}

void	ft_print_lines_v3(t_data *data, t_fvector start,t_fvector end, mlx_texture_t *text, int text_pos)
{
	t_bresenham		*bre;

	bre = malloc(sizeof(t_bresenham) * 1);
	bre->pos1.x = start.x;
	bre->pos1.y = start.y;
	bre->pos2.x = end.x;
	bre->pos2.y = end.y;
	bre->ey = abs(bre->pos2.y - bre->pos1.y);
	bre->ex = abs(bre->pos2.x - bre->pos1.x);
	bre->dx = bre->ex * 2;
	bre->dy = bre->ey * 2;
	bre->dx = bre->ex;
	bre->dy = bre->ey;
	bre->xincr = 1;
	bre->yincr = 1;
	if (bre->pos1.x > bre->pos2.x)
		bre->xincr = -1;
	if (bre->pos1.y > bre->pos2.y)
		bre->yincr = -1;
	if (bre->dx > bre->dy)
		ft_print_x_lines(data->img_3d, bre, text);
	else
		ft_print_y_lines(data->img_3d, bre, text, text_pos);
	free(bre);
}

/*void	ft_print_lines_v2(mlx_image_t *img, t_player *player, int rx, int ry)
{
	t_bresenham *bre;

	bre = malloc(sizeof(t_bresenham) * 1);
	bre->y1 = player->py;
	bre->y2 = ry;
	bre->x1 = player->px;
	bre->x2 = rx;
	bre->ey = abs(bre->y2 - bre->y1);
	bre->ex = abs(bre->x2 - bre->x1);
	bre->dx = bre->ex * 2;
	bre->dy = bre->ey * 2;
	bre->dx = bre->ex;
	bre->dy = bre->ey;
	bre->xincr = 1;
	bre->yincr = 1;
	if (bre->x1 > bre->x2)
		bre->xincr = -1;
	if (bre->y1 > bre->y2)
		bre->yincr = -1;
	if (bre->dx > bre->dy)
		ft_print_x_lines(img, bre, player->color);
	else
		ft_print_y_lines(img, bre, player->color);
	free(bre);
}*/
