/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:09 by drafe             #+#    #+#             */
/*   Updated: 2020/01/21 21:44:29 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** **************************************************************************
**	static int door_total(t_player *pl)
**	Function to init array of doors
** **************************************************************************
*/

static void	door_init(t_player *pl, int	*sec_arr)
{
	int	i;

	i = -1;
	while(++i < pl->door_all)
	{
		pl->doors[i].s_nb = sec_arr[i];
		pl->doors[i].dir = 0.1;
		pl->doors[i].max_d = 20;
		pl->doors[i].min_d = 0;
		pl->doors[i].opened = 0;
	}
}

/*
** **************************************************************************
**	static void door_total(t_player *pl)
**	Function to countdown doors and malloc them
**	pl->sectors[pl->door.nb].ceil = pl->sectors[pl->door.nb].ceil
** **************************************************************************
*/

static void	door_total(t_player *pl)
{	
	int	i;
	int	sec_arr[MAX_DOORS];
	int	*ptr;

	pl->door_all = 0;
	i = -1;
	while(++i < pl->sectors_nb)
	{
		if ((pl->sectors[i].ceil == 0) && (pl->sectors[i].floor == 0))
		{
			sec_arr[pl->door_all] = i;
			if (pl->door_all++ >= MAX_DOORS)
			{
				ft_putstr_fd("Too much doors", 2);
				exit(EXIT_FAILURE);
			}
		}
	}
	ptr = sec_arr;
	if (pl->door_all > 0)
		if (!(pl->doors = (t_door *)malloc(sizeof(t_door) * pl->door_all)))
			exit(EXIT_FAILURE);
	door_init(pl, ptr);
}

/*
** **************************************************************************
**	void door_button(t_player *pl, t_subevents *se)
**	Function to start lift door when button pressed
** **************************************************************************
*/

void		door_button(t_player *pl, t_subevents *se)
{
	int		d_nb;
	int		d_sec_nb;
	int		i;

	i = -1;
	d_nb = -1;
	if (pl->door_all == -1)
		door_total(pl);
	else if (pl->door_all < 1)
		return ;
	d_sec_nb = door_exist(pl);
	while (++i < pl->door_all)
		if (pl->doors[i].s_nb == d_sec_nb)
			d_nb = i;
	if ((d_nb == -1) || (pl->doors[d_nb].opened == 1))
		return ;
	pl->door_nb = d_nb;
	if ((pl->sectors[d_sec_nb].ceil) <= pl->doors[d_nb].max_d)
		se->wsad[4] = 1;
	else
		se->wsad[4] = 0;
}

/*
** **************************************************************************
**	void door(t_player *pl)
**	Function to door open process
** **************************************************************************
*/

void		door(t_player *pl, t_subevents *se)
{
	int		d_nb;
	int		d_sec_nb;

	
	d_nb = pl->door_nb;
	d_sec_nb = 0;
	if ((pl->door_all < 1) || (d_nb > pl->door_all))
		return ;
	//door_exist(pl);
	d_sec_nb = pl->doors[d_nb].s_nb;
	if (((pl->sectors[d_sec_nb].ceil + pl->doors[d_nb].dir) \
	<= pl->doors[d_nb].max_d) && (se->wsad[4] == 1))
		pl->sectors[d_sec_nb].ceil += pl->doors[d_nb].dir;
	pl->doors[d_nb].opened = 1;
	//d_sec_nb = se->wsad[4] == 1;
}
