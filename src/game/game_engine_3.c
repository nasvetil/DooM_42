/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:26:45 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/24 18:27:01 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	ft_game_ceil_floor_move(t_new_player *pl)
{
	if (pl->flag_move_neighbors == 1)
	{
		if (pl->sect->ceil - pl->sect->floor < 20.0)
			pl->sect->ceil += 0.02;
	}
	if (pl->flag_move_neighbors == -1)
	{
		if (pl->sect->ceil - pl->sect->floor > 8.0)
			pl->sect->ceil -= 0.02;
	}
}
