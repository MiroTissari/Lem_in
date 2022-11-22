/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_calculations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:46:31 by mtissari          #+#    #+#             */
/*   Updated: 2022/11/22 15:47:27 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	calculate_paths(t_option *option)
{
	int	counter;

	counter = 1;
	while (option->next)
		option = option->next;
	while (option->previous)
	{
		option = option->previous;
		counter++;
	}
	return (counter);
}

int	calculate_diff(t_option *option)
{
	int			diff;
	t_option	*temp;

	temp = option->previous;
	diff = option->edges - temp->edges;
	// free (temp); // Not sure if it's a leak or not.. //
	return (diff);
}

int	calculate_paths_used(t_data *data, t_option *option)
{
	int	diff1;
	int	diff2;
	int	nb_of_paths;

	nb_of_paths = calculate_paths(option);
	if (option->next)
	{
		while (option->next)
			option = option->next;
		while (1)
		{
			diff2 = calculate_diff(option);
			option = option->previous;
			diff1 = calculate_diff(option);
			if (diff2 == 0)
				diff2 = -2;
			if (data->nb_ants >= (diff1 + 3) + (diff2 + 2))
				break ; // Not sure yet if this works for all possibilities.
			nb_of_paths--;
		}
	}
	return (nb_of_paths);
}

/*
	The "data->nb_ants >= (diff1 + 3) + (diff2 + 2)" works on 3 paths, but 
	not sure if it works with more. We'll see later on.///
*/

int	calculate_turns(t_data *data, t_option *option) // irrelevant for now!!!
{
	int	paths; // NOT YET sure if this is even needed!!

	paths = calculate_paths(option);
	// Need to see if we can find a pattern for the nb of ants in the paths
	// This function is going to be a big one for us:
	// It's gonna calculate the turns, so it's gonna solve how many ants
	// go to which path, and calculate from there.
}
