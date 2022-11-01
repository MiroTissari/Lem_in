/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:17:36 by ajones            #+#    #+#             */
/*   Updated: 2022/11/01 16:14:41 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define GNL_FAIL	"File input error\n"  // These are examples
# define ANT_ERROR	"Not a valid number of ants\n"
# define MAP_ERROR	"Not a valid map\n"
# define DATA_FAIL "ERROR, malloc of data failed!\n"
# define VERIFY_FAIL "ERROR, malloc of verify failed!\n"

# define OFF		0
# define ON			1
# define COMMENT	11
# define START		12
# define END		13
# define NOT_READ	0

# include "../libft/libft.h"

typedef struct s_data
{
	int			nb_ants;
	int			nb_rooms;
	t_room		*source;
	t_room		*sink;
}				t_data;

typedef struct s_verify
{
	int			valid_map;
	int			ants;
	int			nb_of_starts;
	int			nb_of_ends;
	int8_t		start;
	int8_t		end;
	int8_t		all_rooms_read;
}				t_verify;

typedef struct s_room
{
	char			*name;
	char			*edges;
	int8_t			start;
	int8_t			end;
	struct s_room	*next;
}					t_room;

typedef struct s_path
{
	int				present;
	struct s_path	*previous;
}					t_pat;

typedef struct s_queue
{
	t_room			*next_room;
	t_room			*cold_rooms;
	char			*room_queue;
}					t_queue;

/*
	Functions that parse input
*/

void	read_input(t_data *data);
void	get_ant_info(char *line, t_verify *verify);
void	read_room_and_link_info(char *line, t_verify *verify, t_data *data);
t_room	*get_room_info(char *line, t_verify *verify, t_data *data, t_room *room);
int		get_link_info(char *line, t_verify *verify, t_data *data);
int		comment_start_end(char *line, t_verify *verify);
int		check_if_line_is_digits(char *line);

/*
	Initialize structs
*/

void	init_data(t_data *data);
void	init_verify(t_verify *verify);

/*
	Error management
*/

void	error_exit(char *error_str, t_verify *verify);
void	error_handling(char *error_str);

/*
	Freeing functions
*/

void	free_verify(t_verify *verify);

#endif