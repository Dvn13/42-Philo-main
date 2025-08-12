/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:32:45 by mdivan            #+#    #+#             */
/*   Updated: 2025/08/12 16:32:47 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (ERROR);
	}
	if (parse_arguments(argc, argv, &data) == ERROR)
		return (ERROR);
	table.data = &data;
	if (init_table(&table) == ERROR)
		return (ERROR);
	if (start_simulation(&table) == ERROR)
	{
		cleanup_table(&table);
		return (ERROR);
	}
	cleanup_table(&table);
	return (SUCCESS);
}
