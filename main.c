/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 13:32:57 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/04/01 13:32:57 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(const int ac, const char **av)
{
	t_file			file;
	t_lst			*rooms;
	int				ants;
	unsigned int	flags;

	flags = 0;
	file.txt = NULL;
	file.size = 0;
	ants = 0;
	rooms = NULL;
	ft_read_flags(&flags, ac, av);
	if (ft_read_file(&file, flags) && ft_read_nbr_ants(&file, &ants, flags) &&
		ft_read_rooms(&file, &rooms, flags))
		if (ft_read_links(&file, &rooms, flags) && file.index < file.size)
			flags & FLAG_ERROR ? ft_error(BAD_LINE) : 0;
	if (rooms && ft_check_rooms(rooms, flags) && ft_find_paths(&rooms, flags))
		ft_print_paths(rooms, ants);
	else
		write(1, "ERROR\n", 6);
	free(file.txt);
	ft_free_rooms(rooms);
	return (0);
}
