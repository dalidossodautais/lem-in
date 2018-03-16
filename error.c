/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 18:33:50 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/08/16 18:33:51 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_error_next(const char cases)
{
	if (cases == ABSENT_START_AND_END)
		write(1, "Il n'y a ni sortie, ni entrée.\n", 32);
	else if (cases == ABSENT_START)
		write(1, "Il n'y a pas d'entrée.\n", 24);
	else if (cases == ABSENT_END)
		write(1, "Il n'y a pas de sortie.\n", 24);
	else if (cases == START_BAD_FOLLOW)
		write(1, "L'entrée n'est pas suivi d'une salle correctement "
			"initialisée.\n", 65);
	else if (cases == END_BAD_FOLLOW)
		write(1, "La sortie n'est pas suivi d'une salle correctement "
			"initialisée.\n", 65);
	else if (cases == ABSENT_PATH)
		write(1, "Il n'y a aucun chemin menant à la sortie.\n", 43);
	else if (cases == BAD_LINE)
		write(1, "Cette ligne ne correspond à aucun format.\n", 43);
}

int			ft_error(const char cases)
{
	if (cases == FAIL_ALLOC)
		write(1, "Il y a eu une erreur dans l'allocation de mémoire.\n", 52);
	else if (cases == FLAG_BAD_INIT)
		write(1, "Il y a eu une erreur dans l'entrée des flags.\n", 47);
	else if (cases == FLAG_UNKNOWN)
		write(1, "Il y a un flag qui n'existe pas.\n", 33);
	else if (cases == FAIL_READ)
		write(1, "Il y a eu une erreur dans la lecture du fichier.\n", 49);
	else if (cases == EMPTY_FILE)
		write(1, "Le fichier est vide.\n", 21);
	else if (cases == NBR_ANTS_BAD_INIT)
		write(1, "Il y a eu une erreur dans l'entrée du nombre de fourmi.\n",
			57);
	else if (cases == NBR_ANTS_NULL_NEG)
		write(1, "Le nombre de fourmi est négatif.\n", 34);
	else if (cases == EXISTING_NAME)
		write(1, "Deux salles ont un nom identique.\n", 34);
	else if (cases == EXISTING_XY)
		write(1, "Deux salles ont les mêmes coordonnées.\n", 41);
	else if (cases == EXISTING_START)
		write(1, "Il y a plusieurs entrées.\n", 27);
	if (cases == EXISTING_END)
		write(1, "Il y a plusieurs sorties.\n", 26);
	ft_error_next(cases);
	return (0);
}
