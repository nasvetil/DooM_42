/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_gui_draw_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:33:46 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/23 19:09:54 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	T	|	top
**	B	|	bottom
**	L	|	left
**	R	|	right
*/

#define GUI_MAP_GRID_LIMIT_TL	0x1
#define GUI_MAP_GRID_LIMIT_TR	0x2
#define GUI_MAP_GRID_LIMIT_BL	0x3
#define GUI_MAP_GRID_LIMIT_BR	0x4

void	ft_gui_draw_map_grid_limit_sector(t_wolf3d *w, t_gui_rect rect, \
	t_vector3 v, int type)
{
	t_gui_coord	pos;

	pos = ft_gui_map_vertex_to_coord(w, rect, v);
	if (type == GUI_MAP_GRID_LIMIT_TL || type == GUI_MAP_GRID_LIMIT_TR)
		ft_gui_fill_area(w, (t_gui_coord){rect.v1.x, rect.v1.y, 0}, \
			(t_gui_coord){rect.v2.x, (pos.y > rect.v2.y ? rect.v2.y : pos.y), 0}, 0x222222);
	else
		ft_gui_fill_area(w, (t_gui_coord){rect.v1.x, (pos.y < rect.v1.y ? rect.v1.y : pos.y), 0}, \
			(t_gui_coord){rect.v2.x, rect.v2.y, 0}, 0x222222);
	if (type == GUI_MAP_GRID_LIMIT_TL || type == GUI_MAP_GRID_LIMIT_BL)
		ft_gui_fill_area(w, (t_gui_coord){rect.v1.x, rect.v1.y, 0}, \
				(t_gui_coord){(pos.x > rect.v2.x ? rect.v2.x : pos.x), rect.v2.y, 0}, 0x222222);
	else
		ft_gui_fill_area(w, (t_gui_coord){(pos.x < rect.v1.x ? rect.v1.x : pos.x), rect.v1.y, 0}, \
			(t_gui_coord){rect.v2.x, rect.v2.y, 0}, 0x222222);
}

/*
**	void ft_gui_draw_map(t_wolf3d *w, t_list *list)
**	
**	Function that draw limit line for map grid.
*/
void	ft_gui_draw_map_grid_limit_line(t_wolf3d *w, t_gui_rect rect, t_vector3 v, int scale)
{
	t_gui_coord	pos;

	pos = ft_gui_map_vertex_to_coord(w, rect, v);
	if (pos.y >= rect.v1.y && pos.y <= rect.v2.y)
		ft_fdf_wu_color(
			&(t_vector3){rect.v1.x, pos.y, 0, 0}, \
			&(t_vector3){rect.v2.x, pos.y, 0, 0}, \
			w, 0x888888 \
		);
	if (pos.x >= rect.v1.x && pos.x <= rect.v2.x)
		ft_fdf_wu_color(
			&(t_vector3){pos.x, rect.v1.y, 0, 0}, \
			&(t_vector3){pos.x, rect.v2.y, 0, 0}, \
			w, 0x888888 \
		);
}

/*
**	void ft_gui_draw_map(t_wolf3d *w, t_list *list)
**	
**	Function that draw map grid.
*/
void	ft_gui_draw_map_grid(t_wolf3d *w, t_gui_rect rect, int scale)
{
	t_gui_coord	pos;

	pos = ft_gui_map_vertex_to_coord(w, rect, \
		(t_vector3){floor(w->gui_map.v.x), floor(w->gui_map.v.y), 0, 0});
	while (pos.y < rect.v2.y && pos.y < WIN_HEIGHT)
	{
		ft_fdf_wu_color(
			&(t_vector3){rect.v1.x, pos.y, 0, 0}, \
			&(t_vector3){rect.v2.x, pos.y, 0, 0}, \
			w, 0x333333 \
		);
		pos.y += w->gui_map.grid_scale;
	}
	while (pos.x < rect.v2.x && pos.x < WIN_WIDTH)
	{
		ft_fdf_wu_color(
			&(t_vector3){pos.x, rect.v1.y, 0, 0}, \
			&(t_vector3){pos.x, rect.v2.y, 0, 0}, \
			w, 0x333333 \
		);
		pos.x += w->gui_map.grid_scale;
	}
}

void	ft_gui_draw_point(t_wolf3d *w, t_gui_coord c, int color)
{
	int	v_d;

	v_d = w->gui_map.grid_scale / 8;
	if (v_d < 2)
		v_d = 2;
	ft_gui_fill_area(w, (t_gui_coord){c.x - v_d, c.y - v_d, 0}, \
		(t_gui_coord){c.x + v_d, c.y + v_d, 0}, color);
}

int		ft_gui_draw_map_vertex(t_wolf3d *w, t_gui_coord c, int status, int mode)
{
	int	color;

	if (status == 1 && mode != GUI_MD_ME)
	{
		color = GUI_CL_STANDART;
		if (mode == GUI_MD_ME_SET_SECTOR)
			color = GUI_CL_SECTOR;
		if (mode == GUI_MD_ME_SET_PLAYER)
			color = GUI_CL_PLAYER;
		if (mode == GUI_MD_ME_SET_SPRITE)
			color = GUI_CL_SPRITE;
		if (mode == GUI_MD_ME_SET_ENEMY)
			color = GUI_CL_ENEMY;
		ft_gui_draw_point(w, c, color);
	}
	return (0);
}

// function that draw line
int		ft_gui_draw_map_vertex_line(t_wolf3d *w, t_gui_coord c1)
{
	t_sector	*s;
	t_gui_coord	c2;

	if (w->gui.mode == GUI_MD_ME_SET_SECTOR && w->sector)
	{
		s = w->sector->content;
		if (s->status == 0 && s->vertex_count > 0 && ft_new_editor_map_check_area(w))
		{
			c2 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *s->vertex[s->vertex_count - 1]);
			ft_fdf_wu_color(&(t_vector3){c1.x, c1.y, 0, 0}, &(t_vector3){c2.x, c2.y, 0, 0}, w, 0x888888);
		}
	}
	return (0);
}

void	ft_draw_sector_walls(t_wolf3d *w, t_sector *s)
{
	int				i;
	t_gui_coord		c1;
	t_gui_coord		c2;
	int				vtx1_n; // vertex number
	int				vtx2_n;

	i = 0;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % s->vertex_count;
		if (vtx2_n == 0 && s->status == 0)
			break ;

		// Get line coordinates  
		c1 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *s->vertex[vtx1_n]);
		c2 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *s->vertex[vtx2_n]);

		ft_fdf_wu_color(&(t_vector3){c1.x, c1.y, 0, 0}, &(t_vector3){c2.x, c2.y, 0, 0}, w, s->color);

		i++;
	}
}

void	ft_draw_area_hatch(t_wolf3d *w, t_gui_rect rect, int color)
{
	t_gui_coord	v;
	t_gui_coord	c;
	t_vector3	vec;

	vec = (t_vector3){1, 0, 0, 0};
	vec = ft_transform_vertex(vec, ft_rz_matrix((t_matrix_4x4){1, 0, 0, 0}, -M_PI_4));

	v.y = rect.v1.y >= 0 ? rect.v1.y : 0;
	while (v.y + w->gui_map.grid_scale <= rect.v2.y && v.y < WIN_HEIGHT)
	{
		v.x = rect.v1.x >= 0 ? rect.v1.x : 0;
		while (v.x + w->gui_map.grid_scale <= rect.v2.x && v.x < WIN_WIDTH)
		{
			c.x = v.x + w->gui_map.grid_scale;
			c.y = v.y + w->gui_map.grid_scale;
			ft_fdf_wu_rect_color(w, (t_gui_rect){v, c, 0, 0}, rect, color);
			v.x += w->gui_map.grid_scale;
		}
		v.y += w->gui_map.grid_scale;
	}
}

t_gui_rect	ft_sector_get_rect(t_wolf3d *w, t_sector *s)
{
	t_vector3	v1;
	t_vector3	v2;
	t_gui_rect	rect;
	int			i;

	if (s->vertex_count == 0)
		return ((t_gui_rect){0, 0, 0, 0});
	rect = (t_gui_rect){0, 0, 0, 0};
	v1 = *s->vertex[0];
	v2 = *s->vertex[0];
	i = 1;
	while (i < s->vertex_count)
	{
		(s->vertex[i]->x < v1.x) ? v1.x = s->vertex[i]->x : 0;
		(s->vertex[i]->x > v2.x) ? v2.x = s->vertex[i]->x : 0;
		(s->vertex[i]->y < v1.y) ? v1.y = s->vertex[i]->y : 0;
		(s->vertex[i]->y > v2.y) ? v2.y = s->vertex[i]->y : 0;
		i++;
	}
	rect.v1 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, v1);
	rect.v2 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, v2);
	rect.w = v2.x - v1.x;
	rect.h = v2.y - v2.x;
	return (rect);
}

void	ft_draw_door(t_wolf3d *w, t_sector *s)
{
	if (s->status == SECTOR_STATUS_READY || \
		s->status == SECTOR_STATUS_PRESET ||
		s->status == SECTOR_STATUS_SET)
	{
		s->color = GUI_CL_DOOR; // каждый раз-
		ft_draw_sector_walls(w, s);
	}
	if (s->status == SECTOR_STATUS_PRESET ||
		s->status == SECTOR_STATUS_SET)
		ft_draw_area_hatch(w, ft_sector_get_rect(w, s), s->color);

	
	// if ()
}

/*
	void ft_editor_map_draw_walls(t_wolf3d *w, t_sector *ptr_sector)

	Draw walls on the map.
*/
void		ft_gui_draw_map_sector_walls(t_wolf3d *w, t_sector *s)
{
	int				i;
	t_gui_coord		c1;
	t_gui_coord		c2;
	int				vtx1_n; // vertex number
	int				vtx2_n;

	i = 0;
	if (s->status == 0)
		s->color = 0x7b68ee;
	else
		s->color = 0xf8f32b;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = i + 1;
		if (vtx2_n == s->vertex_count)
		{
			if (s->status == 1)
				vtx2_n = 0;
			else
				break ;
		}

		// Get line coordinates  
		c1 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *s->vertex[vtx1_n]);
		c2 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *s->vertex[vtx2_n]);

		ft_fdf_wu_color(&(t_vector3){c1.x, c1.y, 0, 0}, &(t_vector3){c2.x, c2.y, 0, 0}, w, s->color);

		i++;
	}

	i = 0;
	while (i < s->vertex_count)
	{
		c1 = ft_gui_map_vertex_to_coord(w, (t_gui_rect){0, 0, 0, 0}, *s->vertex[i]);
		ft_gui_draw_point(w, c1, s->color);
		i++;
	}
}

void	ft_gui_draw_map_sector(t_wolf3d *w, t_list *list)
{
	t_sector	*s;
	if (list)
	{
		ft_gui_draw_map_sector(w, list->next);
		s = list->content;
		if (s->type == SECTOR_TYPE_SECTOR)
			ft_gui_draw_map_sector_walls(w, s);
		// else if (s->type == SECTOR_TYPE_DOOR)
			// ft_draw_door(w, s);
	}
}

void	ft_gui_draw_map_door(t_wolf3d *w, t_list *list)
{
	t_sector	*s;
	if (list)
	{
		ft_gui_draw_map_door(w, list->next);
		s = list->content;
		if (s->type == SECTOR_TYPE_DOOR)
			ft_draw_door(w, s);
	}
}

// sector->status = SECTOR_STATUS_NOTHING;

/*
**	void ft_gui_draw_map(t_wolf3d *w, t_list *list)
**	
**	Function that draw map.
*/
void	ft_gui_draw_map(t_wolf3d *w, t_list *list)
{
	t_gui_elem	*elem;

	elem = list->content;
	ft_gui_draw_map_grid_limit_sector(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, w->gui_map.r1, GUI_MAP_GRID_LIMIT_TL);
	ft_gui_draw_map_grid_limit_sector(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, w->gui_map.r2, GUI_MAP_GRID_LIMIT_BR);
	ft_gui_draw_map_grid(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, w->gui_map.grid_scale);
	ft_gui_draw_map_grid_limit_line(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, w->gui_map.r1, w->gui_map.grid_scale);
	ft_gui_draw_map_grid_limit_line(w, (t_gui_rect){elem->v1, elem->v2, elem->w, \
		elem->h}, w->gui_map.r2, w->gui_map.grid_scale);
	w->gui_map.check_vertex = ft_gui_draw_map_vertex(w, w->gui.mouse_pos, \
		w->gui_map.check_vertex, w->gui.mode);
	ft_gui_draw_map_vertex_line(w, w->gui.mouse_pos);
	ft_gui_draw_map_door(w, w->sector);
	ft_gui_draw_map_sector(w, w->sector);
	ft_gui_draw_player(w);
	ft_gui_draw_sprites(w);
	ft_gui_draw_enemies(w);
}