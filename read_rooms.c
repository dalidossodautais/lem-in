/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 13:12:55 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/08/15 13:12:58 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ft_fill_room(t_file *file, t_room *room, int a,
	const unsigned int flags)
{
	int	b;

	b = a;
	while (file->index + a < file->size && file->txt[file->index + a] != ' ' &&
		file->txt[file->index + a] != '-' && file->txt[file->index + a] != '\n')
		++a;
	if (!a || file->index + a == file->size || file->txt[file->index + a] == '-'
		|| file->txt[file->index + a] == '\n')
		return (0);
	if (!(room->name = (char *)malloc(sizeof(char) * a - b)))
		return (flags & FLAG_ERROR ? ft_error(FAIL_ALLOC) : 0);
	room->sizename = 0;
	while (room->sizename < a - b)
		room->name[room->sizename++] =
			file->txt[file->index + b + room->sizename];
	if (file->index + a == file->size || file->txt[file->index + a] == '-' ||
		file->txt[file->index + a++] == '\n' || !ft_atoi(file, &a, &room->x) ||
		file->index + a == file->size || file->txt[file->index + a] == '-' ||
		file->txt[file->index + a++] == '\n' || !ft_atoi(file, &a, &room->y) ||
		file->index + a == file->size || file->txt[file->index + a] == ' ' ||
		file->txt[file->index + a++] == '-')
		return (0);
	write(1, file->txt + file->index, b);
	file->index += a;
	return (1);
}

static int	ft_next_room_second(t_file *file, t_room *room, int a,
	const unsigned int flags)
{
	while (file->index + a < file->size && file->txt[file->index + a] == '#' &&
		!(file->index + a + 8 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##start\n", 8)) &&
		!(file->index + a + 6 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##end\n", 6)))
		while (file->index + ++a < file->size &&
			file->txt[file->index + a - 1] != '\n')
			;
	if ((file->index + a + 8 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##start\n", 8) &&
		room->place + START == START_AND_END) ||
		(file->index + a + 6 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##end\n", 6) &&
		room->place + END == START_AND_END))
		room->place = START_AND_END;
	while (file->index + a < file->size && file->txt[file->index + a] == '#')
		while (file->index + ++a < file->size &&
			file->txt[file->index + a - 1] != '\n')
			;
	return (ft_fill_room(file, room, a, flags));
}

static int	ft_next_room_first(t_file *file, t_room *room,
	const unsigned int flags)
{
	int	a;

	room->name = NULL;
	room->links = NULL;
	a = 0;
	while (file->index + a < file->size && file->txt[file->index + a] == '#' &&
		!(file->index + a + 8 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##start\n", 8)) &&
		!(file->index + a + 6 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##end\n", 6)))
		while (file->index + ++a < file->size &&
			file->txt[file->index + a - 1] != '\n')
			;
	room->place = 0;
	if (file->index + a + 8 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##start\n", 8) && (a += 8))
		room->place = START;
	else if (file->index + a + 6 < file->size &&
		ft_strnequ(file->txt + file->index + a, "##end\n", 6) && (a += 6))
		room->place = END;
	return (ft_next_room_second(file, room, a, flags));
}

static int	ft_first_case(const t_room room, t_lst *rooms, const unsigned flags)
{
	while (rooms)
	{
		if (rooms->room->sizename == room.sizename &&
			ft_strnequ(rooms->room->name, room.name, room.sizename))
			return (flags & FLAG_ERROR ? ft_error(EXISTING_NAME) : 0);
		if (rooms->room->x == room.x && rooms->room->y == room.y)
			return (flags & FLAG_ERROR ? ft_error(EXISTING_XY) : 0);
		if ((room.place == START || room.place == START_AND_END) &&
			(rooms->room->place == START ||
			rooms->room->place == START_AND_END))
			return (flags & FLAG_ERROR ? ft_error(EXISTING_START) : 0);
		if ((room.place == END || room.place == START_AND_END) &&
			(rooms->room->place == END || rooms->room->place == START_AND_END))
			return (flags & FLAG_ERROR ? ft_error(EXISTING_END) : 0);
		rooms = rooms->next;
	}
	write(1, room.name, room.sizename);
	write(1, " ", 1);
	ft_putnbr(room.x);
	write(1, " ", 1);
	ft_putnbr(room.y);
	write(1, "\n", 1);
	return (1);
}

int			ft_read_rooms(t_file *file, t_lst **rooms, const unsigned int flags)
{
	t_lst	*tlst;
	t_room	troom;

	while (ft_next_room_first(file, &troom, flags))
	{
		if (!ft_first_case(troom, *rooms, flags))
		{
			free(troom.name);
			return (0);
		}
		tlst = (t_lst *)malloc(sizeof(t_lst));
		tlst->room = (t_room *)malloc(sizeof(t_room));
		tlst->room->name = troom.name;
		tlst->room->sizename = troom.sizename;
		tlst->room->x = troom.x;
		tlst->room->y = troom.y;
		tlst->room->place = troom.place;
		tlst->room->links = NULL;
		tlst->next = *rooms;
		*rooms = tlst;
	}
	free(troom.name);
	return (1);
}
