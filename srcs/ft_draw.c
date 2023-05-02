/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:18:30 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/02 13:09:16 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(mlx_image_t *img, int beginX, int beginY, int endX, int endY, int color)
{
	double	deltaX;
	double	deltaY;
	int		pixels;
	double	pixelX;
	double	pixelY;

	deltaX = endX - beginX;
	deltaY = endY - beginY ;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while (pixels)
	{
		mlx_put_pixel(img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		if (pixelX < 0 || pixelY < 0 || pixelX > img->width || pixelY > img->height)
			return ;
		--pixels;
	}
}

void	ft_draw_3D_2(t_data *data, t_fvector start, t_fvector end, mlx_texture_t *text, int text_pos)
{
	int	j;

	j = 0;


	while (j < 8)
	{
		end.x += 1;
		start.x += 1;
		ft_print_lines_v3(data, start, end, text, text_pos);
		j++;
	}
}

/*void	ft_draw_3D(mlx_image_t *img, float ax, float ay, float bx, float by, int color)
{
	int	j;

	j = 0;	
	while (j < 8)
	{
		ft_print_lines_v3(img, ax + j, ay, bx + j, by, color);
		j++;
	}
}*/

void	ft_draw_case(mlx_image_t *img, t_ivector pos, int color)
{
	t_ivector	pos2;

	pos2.y = 0;
	while (pos2.y < CSIZE)
	{
		pos2.x = 0;
		while (pos2.x < CSIZE)
		{
			mlx_put_pixel(img, ((pos.x * CSIZE) + pos2.x), ((pos.y * CSIZE) + pos2.y), color);
			pos2.x++;
		}
		pos2.y++;
	}
}

mlx_image_t	*ft_draw_map(t_data *data)
{
	t_ivector			pos;
	mlx_image_t			*map;

	map = fill_image(get_rgba(255, 255, 255, 255), 8 * CSIZE, 8 * CSIZE, data->mlx);
	pos.y = 0;
	while (data->map[pos.y] != NULL)
	{
		pos.x = 0;
		while (data->map[pos.y][pos.x] != '\0')
		{
			if (data->map[pos.y][pos.x] == '1')
				ft_draw_case(map, pos, get_rgba(255, 0, 0, 255));
			else
				ft_draw_case(map, pos, get_rgba(1, 1, 1, 255));
			pos.x++;
		}
		pos.y++;
	}
	return (map);
}
