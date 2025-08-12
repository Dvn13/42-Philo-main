/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by user             #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_table *table)
{
	int	i;

	if (table->philos)
	{
		i = 0;
		while (i < table->data->philo_count)
		{
			pthread_mutex_destroy(&table->philos[i].meal_mutex);
			pthread_mutex_destroy(&table->philos[i].last_meal_mutex);
			i++;
		}
	}
	if (table->forks)
	{
		i = 0;
		while (i < table->data->philo_count)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
		table->forks = NULL;
	}
	pthread_mutex_destroy(&table->data->print_mutex);
	pthread_mutex_destroy(&table->data->dead_mutex);
}

void	cleanup_table(t_table *table)
{
	destroy_mutexes(table);
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}

void	cleanup_philosopher_mutexes(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		pthread_mutex_destroy(&table->philos[i].last_meal_mutex);
		i++;
	}
	free(table->philos);
	table->philos = NULL;
}
