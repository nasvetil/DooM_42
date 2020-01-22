/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_desctuct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:21:05 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/22 18:32:05 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_editor_desctuct_objects(t_wolf3d *w)
{
	ft_lstdel(&w->sprite, ft_bzero);
	ft_lstdel(&w->enemy, ft_bzero);
}

void	ft_editor_desctuct_vertexes(t_vector3 **vrtx, int count)
{
	int	i;
	
	i = 0;
	while (i < count)
		free(vrtx[i++]);
	free(vrtx);
}

void	ft_editor_desctuct_sectors(t_wolf3d *w)
{
	t_list		*list;
	t_list		*ptr;
	t_sector	*s;
	
	list = w->sector;
	while (list)
	{
		ptr = list->next;
		s = list->content;

		free(s->neighbors);
		ft_editor_desctuct_vertexes(s->vertex, s->vertex_count);
		free(list);

		list = ptr;
	}
}

void	ft_editor_desctuct(t_wolf3d *w)
{
	ft_gui_desctuct(w->gui.dom);
	ft_gui_desctuct_fonts(w->gui.fonts);
	ft_editor_desctuct_sectors(w);
	ft_editor_desctuct_objects(w);
	ft_clean_sdl(w);
	// sleep(15);
}