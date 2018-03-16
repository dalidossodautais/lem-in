/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 11:45:35 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/08/22 11:45:37 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_check_rooms(t_lst *rooms, const unsigned int flags)
{
	int		place;

	place = NOTHING_FIND;
	while (rooms)
	{
		place += rooms->room->place;
		rooms = rooms->next;
	}
	if (place == NOTHING_FIND)
		return (flags & FLAG_ERROR ? ft_error(ABSENT_START_AND_END) : 0);
	if (place == START_FIND)
		return (flags & FLAG_ERROR ? ft_error(ABSENT_START) : 0);
	if (place == END_FIND)
		return (flags & FLAG_ERROR ? ft_error(ABSENT_START) : 0);
	return (1);
}

static void	ft_find_my_path(t_lst **tlst)
{
	t_lst	*tlinks;

	tlinks = (*tlst)->room->links;
	*tlst = NULL;
	while (tlinks)
	{
		if (tlinks->room->place && tlinks->room->place != START &&
			(!*tlst || tlinks->room->place < (*tlst)->room->place))
			*tlst = tlinks;
		tlinks = tlinks->next;
	}
}

void		ft_print_paths_next(t_lst *rooms, const int ants)
{
	t_lst	*tlst;
	int		a;
	int		b;
	int		c;

	a = 0;
	while (a++ < ants + rooms->room->place)
	{
		b = -1;
		c = 0;
		tlst = rooms;
		while (++b <= rooms->room->place)
		{
			if (b <= rooms->room->place && b < a && a - b - 1 < ants)
			{
				c = (c ? write(1, " ", 1) : 1);
				write(1, "L", 1);
				ft_putnbr(a - b);
				write(1, "-", 1);
				write(1, tlst->room->name, tlst->room->sizename);
			}
			ft_find_my_path(&tlst);
		}
		write(1, "\n", 1);
	}
}

void		ft_print_paths(t_lst *rooms, const int ants)
{
	int		a;

	if (rooms->room->place == START_AND_END)
		return ;
	ft_find_my_path(&rooms);
	if (rooms->room->place == END)
	{
		a = 0;
		while (a++ < ants)
		{
			write(1, "L", 1);
			ft_putnbr(a);
			write(1, "-", 1);
			write(1, rooms->room->name, rooms->room->sizename);
			write(1, "\n", 1);
		}
	}
	else
		ft_print_paths_next(rooms, ants);
}
