/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 13:32:44 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/04/01 13:32:45 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "define.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_file
{
	char	*txt;
	int		index;
	int		size;
}				t_file;

typedef struct	s_room
{
	char			*name;
	int				sizename;
	int				x;
	int				y;
	int				place;
	struct s_lst	*links;
}				t_room;

typedef struct	s_lst
{
	struct s_room	*room;
	struct s_lst	*next;
}				t_lst;

int				ft_read_flags(unsigned *flags, const int ac, const char **av);
int				ft_read_file(t_file *file, const unsigned flags);
int				ft_read_nbr_ants(t_file *file, int *ants,
	const unsigned flags);
int				ft_read_rooms(t_file *file, t_lst **rooms,
					const unsigned int flags);
int				ft_check_rooms(t_lst *rooms, const unsigned flags);
int				ft_read_links(t_file *file, t_lst **rooms,
	const unsigned flags);
int				ft_find_paths(t_lst **rooms, const unsigned flags);
int				ft_first_start_and_end(t_lst **rooms);
void			ft_first_start(t_lst **rooms);
void			ft_first_end(t_lst **rooms);
void			ft_print_paths(t_lst *rooms, const int ants);
void			ft_free_rooms(t_lst *rooms);
void			ft_putnbr(int n);
int				ft_strnequ(char *s1, char *s2, short size);
int				ft_atoi(t_file *file, int *a, int *t);
void			ft_print_room(const t_room room);
int				ft_error(const char cases);

#endif
