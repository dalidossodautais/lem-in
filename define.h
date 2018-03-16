/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 17:30:21 by ddosso-d          #+#    #+#             */
/*   Updated: 2017/08/17 17:30:22 by ddosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_DEFINE_H
# define LEM_IN_DEFINE_H
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define STR_INT_MIN "-2147483648"

# define NOTHING_FIND 0
# define START_FIND -1
# define END_FIND -2
# define EVERYTHING_FIND -3

# define RANDOM_ROOM 0
# define START -1
# define END -2
# define START_AND_END -3

# define BUFF_SIZE 4096

# define FLAG_ERROR 1

# define FAIL_ALLOC 0
# define FLAG_BAD_INIT 1
# define FLAG_UNKNOWN 2
# define FAIL_READ 3
# define EMPTY_FILE 4
# define NBR_ANTS_BAD_INIT 5
# define NBR_ANTS_NULL_NEG 6
# define EXISTING_NAME 7
# define EXISTING_XY 8
# define EXISTING_START 9
# define EXISTING_END 10
# define ABSENT_START_AND_END 11
# define ABSENT_START 12
# define ABSENT_END 13
# define START_BAD_FOLLOW 14
# define END_BAD_FOLLOW 15
# define ABSENT_PATH 16
# define IMPOSSIBLE_LINK 17
# define ROOM_TO_ROOM 18
# define EXISTING_LINK 19
# define BAD_LINE 20

#endif
