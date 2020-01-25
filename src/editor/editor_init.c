/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:07:54 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/25 19:20:41 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_editor_add_new_txtr(t_wolf3d *w, char *path)
{
	t_txtr	txtr;
	t_list	*new_list;

	txtr.id = w->txtr_count + 1;
	// txtr.color = color;
	txtr.surf = IMG_Load(path);
    txtr.surf = SDL_ConvertSurfaceFormat(txtr.surf, SDL_PIXELFORMAT_ARGB8888, 0);
	txtr.color = *(int*)txtr.surf->pixels;
	new_list = ft_lstnew(&txtr, sizeof(txtr));
	if (w->txtr == NULL)
		w->txtr = new_list;
	else
		ft_lstadd(&w->txtr, new_list);
	w->txtr_count++;
}

void		ft_editor_init_txtr_list(t_wolf3d *w)
{
	ft_editor_add_new_txtr(w, "Textures/wall1.png");
	ft_editor_add_new_txtr(w, "Textures/wood.png");
	ft_editor_add_new_txtr(w, "Textures/wall2.png");
	ft_editor_add_new_txtr(w, "Textures/wall1.png");
	ft_editor_add_new_txtr(w, "Textures/wood.png");
	ft_editor_add_new_txtr(w, "Textures/wall2.png");
}



/*
**	void ft_editor_init(t_wolf3d *w)
**
**	Function that init. some values...
*/
void		ft_editor_init(t_wolf3d *w)
{
	// w->redraw = ft_editor_redraw;
	// w->sector_status = 0;
	// w->mouse_pos = (t_vector3){0, 0, 0, 0};
	// w->status = 1;
	w->sector_count = 0;
	w->sector = NULL;

	w->txtr = NULL;
	w->txtr_count = 0;
	
	ft_editor_init_txtr_list(w);

	w->gui_map.r1 = (t_vector3){0, 0, 0, 0};
	w->gui_map.r2 = (t_vector3){54, 33, 0, 0};
	// w->txtr_opt_type = 1;
	// w->act_s = NULL;
}