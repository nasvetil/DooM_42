/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 19:02:58 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/28 14:54:36 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_thread.h"
# include "SDL2/SDL_ttf.h"

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <libft.h>

# include "const.h"

# include "algebra.h"
# include "file.h"

# include "general_struct.h"
# include "gui_struct.h"
# include "func_struct.h"
# include "editor_struct.h"

# include "new/wolf3d.h"

# include "func_func.h"
# include "gui_func.h"
# include "editor_func.h"
# include "math_func.h"

void	ft_main_gui_init_win(t_list *head);
void	ft_main_gui_init(t_wolf3d *w);
void	ft_game_redraw(void *d, t_list *dom);
void	ft_game_gui_init_hud(t_list *head);

void	ft_gui_mousebuttonup_win_menu_btngame(\
			void *data, \
			SDL_Event e, \
			t_list *dom, int type);
void	ft_gui_mousebuttonup_win_menu_btneditor(\
			void *data, \
			SDL_Event e, \
			t_list *dom, int type);
void	ft_gui_mousebuttonup_win_menu_btnexit(\
			void *data, \
			SDL_Event e, \
			t_list *dom, int type);
void	ft_gui_mousebuttonup_win_editor_menu_btnmenu(\
			void *data, SDL_Event e, t_list *dom, int type);

void	ft_main_events(t_wolf3d *w);

#endif