/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobozier <lobozier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:14:57 by lobozier          #+#    #+#             */
/*   Updated: 2023/05/10 12:38:38 by lobozier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	deg_to_rad(int angle)
{
    return (angle * DR);
}

float	dist(t_fvector a, t_fvector b, float angle)
{
    return (cos(deg_to_rad(angle)) * (b.x - a.x) - \
            sin(deg_to_rad(angle)) * (b.y - a.y));
}

int	fix_ang(int angle)
{
    if (angle > 358)
        angle -= 359;
    if (angle < -1)
        angle += 359;
    return (angle);
}

void	ft_draw_minimap(t_data *data)
{
	int	r = 0;
	int	doffset;
	t_ivector map;
	float	ray_angle;
	float	aTan;
	float	nTan;
	t_fvector	ray_pos;
	t_fvector	ray_offset;
	t_fvector H;
	float distH;
	float distV;
	float distT;
	t_fvector V;
	float LineH;
	float LineO;
	float Camera_angle;

	//ft_clean_img(data->img_ray);
	//ft_clean_img(data->img_3d);
	ray_angle = fix_ang(data->player->facing_dir + 30);
	H.x = data->player->pos.x;	
	H.y = data->player->pos.y;
	V.x = data->player->pos.x;
	V.y = data->player->pos.y;
	while (r < 60)
	{
		distV = INFINITY;
		doffset = 0;
		nTan = tan(deg_to_rad(ray_angle));
		if (cos(deg_to_rad(ray_angle)) > 0.001)
		{
			ray_pos.x = (((int)data->player->pos.x >> 6) << 6) + 64;
			ray_pos.y = (data->player->pos.x - ray_pos.x) * nTan + data->player->pos.y;
			ray_offset.x = 64;
			ray_offset.y = -ray_offset.x * nTan;
		}
		else if (cos(deg_to_rad(ray_angle)) < -0.001)
		{
			ray_pos.x = (((int)data->player->pos.x >> 6) << 6) - 0.0001;
			ray_pos.y = (data->player->pos.x - ray_pos.x) * nTan + data->player->pos.y;
			ray_offset.x = -64;
			ray_offset.y = -ray_offset.x * nTan;
		}
		else
		{
			ray_pos.x = data->player->pos.x;
			ray_pos.y = data->player->pos.y;
			doffset = 8;
		}
		while (doffset < 8)
		{
			map.x = (int)(ray_pos.x) >> 6;
			map.y = (int)(ray_pos.y) >> 6;
			if (map.x > -1 && map.x < 8 && map.y > -1 && map.y < 8 && data->map[map.y][map.x] == '1')
			{
				V.x = ray_pos.x;
				V.y = ray_pos.y;
				distV = dist(data->player->pos, ray_pos, ray_angle);
				doffset = 8;
			}
			else
			{
				ray_pos.x += ray_offset.x;
				ray_pos.y += ray_offset.y;
				doffset += 1;
			}
		}
		distH = INFINITY;
		doffset = 0;
		aTan = 1.0f / nTan;
		if (sin(deg_to_rad(ray_angle)) > 0.001)
		{
			ray_pos.y = (((int)data->player->pos.y >> 6) << 6) - 0.0001;
			ray_pos.x = (data->player->pos.y - ray_pos.y) * aTan + data->player->pos.x;
			ray_offset.y = -64;
			ray_offset.x = -ray_offset.y * aTan;
		}
		else if (sin(deg_to_rad(ray_angle)) < -0.001)
		{
			ray_pos.y = (((int)data->player->pos.y >> 6) << 6) + 64;
			ray_pos.x = (data->player->pos.y - ray_pos.y) * aTan + data->player->pos.x;
			ray_offset.y = 64;
			ray_offset.x = -ray_offset.y * aTan;
		}
		else 
		{
			ray_pos.x = data->player->pos.x;
			ray_pos.y = data->player->pos.y;
			doffset = 8;
		}
		while (doffset < 8)
		{
			map.x = (int)(ray_pos.x) >> 6;
			map.y = (int)(ray_pos.y) >> 6;
			if (map.x > -1 && map.x < 8 && map.y > -1 && map.y < 8 && data->map[map.y][map.x] == '1')
			{
				H.x = ray_pos.x;
				H.y = ray_pos.y;
				distH = dist(data->player->pos, ray_pos, ray_angle);
				doffset = 8;
			}
			else
			{
				ray_pos.x += ray_offset.x;
				ray_pos.y += ray_offset.y;
				doffset += 1;
			}
		}
		if (distV < distH)
		{
			ray_pos.x = V.x;
			ray_pos.y = V.y;
			distT = distV;
		}
		else
		{
			ray_pos.x = H.x;
			ray_pos.y = H.y;
			distT = distH;
		}
		ft_print_lines_v3(data->img_ray, data->player->pos.x + 4, data->player->pos.y + 4, ray_pos.x, ray_pos.y);
		r++;
		ray_angle = fix_ang(ray_angle - 1);
	}
}