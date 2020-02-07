/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_sector_vertex.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 13:45:10 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/05 15:49:19 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void ft_editor_sector_set_vertex(t_wolf3d *w, t_sector *sector, \
**			t_vector3 v, int pos)
**
**	Function that add new vertex for sector.
**
**	Parameters:
**	t_wolf3d *w			| pointer to data-struct [NOT USE!]
**	t_sector *sector	| pointer to sector
**	t_vector3 v			| vertex
**	int pos				| vertex number (position)
** **************************************************************************
*/

void	ft_editor_sector_set_vertex(t_wolf3d *w, t_sector *sector, \
			t_vector3 v, int pos)
{
	t_vector3	**vertex;
	t_vector3	*p;
	int			i;
	int			j;

	vertex = ft_my_malloc(sizeof(void*) * sector->vertex_count + 1); // тут течёт
	i = 0;
	j = 0;
	while (i < sector->vertex_count + 1)
	{
		if (i == pos)
		{
			p = ft_my_malloc(sizeof(t_vector3)); // и тут течёт
			ft_bzero(p, sizeof(t_vector3));
			*p = v;
			vertex[i] = p;
		}
		else
		{
			vertex[i] = sector->vertex[j];
			j++;
		}
		i++;
	}

	free(sector->vertex);
	sector->vertex = vertex;
	sector->vertex_count++;
}

/*
** **************************************************************************
**	void ft_editor_sector_del_last_vertex(t_wolf3d *w, t_sector *sector)
**
**	Function that delete last vertex.
**
**	Parameters:
**	t_wolf3d *w			| pointer to data-struct [NOT USE!]
**	t_sector *sector	| pointer to sector
** **************************************************************************
*/

void	ft_editor_sector_del_last_vertex(t_wolf3d *w, t_sector *sector)
{
	t_vector3	**vertex;
	int			i;

	vertex = ft_my_malloc(sizeof(void*) * (sector->vertex_count - 1));
	i = 0;
	while (i < sector->vertex_count - 1)
	{
		vertex[i] = sector->vertex[i];
		i++;
	}
	free(sector->vertex[i]);
	free(sector->vertex);
	sector->vertex = vertex;
	sector->vertex_count--;
	if (sector->status == 1)
	{
		sector->status = 0;
		w->sector_status = 1;
	}
}

/*
** **************************************************************************
**	[DEPRECATED]
**	
**	void ft_editor_delete_last_vertex(t_wolf3d *w)
**
**	Function that delete last vertex.
**
**	Parameters:
**	t_wolf3d *w			| pointer to data-struct
** **************************************************************************
*/

void		ft_editor_delete_last_vertex(t_wolf3d *w)
{
	t_sector	*sector;

	if (w->sector == NULL)
		return ;
	sector = w->sector->content;
	if (sector == NULL)
		return ;
	if (sector->status == 1)
	{
		sector->status = 0;
		w->sector_status = 1;
	}
	else
	{
		ft_editor_sector_del_last_vertex(w, sector);
	}
	if (sector->vertex_count == 0)
	{
		w->sector_count--;
	 	w->sector = w->sector->next;
		w->sector_status = 0;
	}
	else
	{
		sector->status = 0;
		w->sector_status = 1;
	}
}