/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_solver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:13:06 by mtissari          #+#    #+#             */
/*   Updated: 2022/11/22 16:05:11 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_option	*make_t_option(t_data *data, t_path *cur_path)
{
	t_option	*new_option;

	new_option = (t_option *)malloc(sizeof(t_option));
	if (!new_option)
		error_exit(data);
	new_option->next = NULL;
	new_option->previous = NULL;
	new_option->path = cur_path;
	new_option->turns = 0;
	return (new_option);
}

t_option	*find_all_disjoint_paths(t_data *data, t_room **room)
{
	t_path		*cur_path;
	t_option	*all_paths;

	all_paths = NULL;
	while (1)
	{
		cur_path = bfs(data, room);
		if (cur_path == NULL)
			break ;
		if (all_paths == NULL)
			all_paths = make_t_option(data, cur_path);
		else
		{
			all_paths->next = make_t_option(data, cur_path);
			all_paths->next->previous = all_paths;
			all_paths = all_paths->next;
		}
		make_residual_path(all_paths, room);
		free (cur_path);
	}
	if (all_paths == NULL)
		(error_exit1("no paths found\n", data));
	while (all_paths->previous != NULL)
		all_paths = all_paths->previous;
	return (all_paths);
}

t_option	*solver(t_data *data)
{
	t_option	*orig_option;
	t_option	*next_added;
	t_room		**room;

	room = make_room_array(data);
	orig_option = find_all_disjoint_paths(data, room);
	if (calculate_paths(orig_option) > calculate_paths_used(data, orig_option)
		|| calculate_paths(orig_option) <= data->nb_ants)
		return (orig_option);
	next_added = vertex_disjoint(data, room, orig_option);
	while (calculate_paths(orig_option) < calculate_paths_used(data, next_added))
	{
		free_option(orig_option);
		orig_option = next_added;
		//free_option(next_added);
		next_added = vertex_disjoint(data, room, orig_option);
	}
	free_option(next_added);
	// all freeing are uncertain still!
	return (orig_option);
}

/*
	solver takes care of everything that happens between parsing and printing.
	
	The first if is to check if there's just one ant - in which case we don't
	need to do all the algorithms.
	The second if is a similiar check - it checks whether we have already found
	more paths than we even need.
*/
