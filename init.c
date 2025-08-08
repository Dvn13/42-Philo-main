/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by user             #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	data->simulation_end = 0;
	data->start_time = get_current_time();
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->data->philo_count);
	if (!table->forks)
		return (ERROR);
	i = 0;
	while (i < table->data->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&table->forks[i]);
			}
			free(table->forks);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

static int	init_philosophers(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->data->philo_count);
	if (!table->philos)
		return (ERROR);
	i = 0;
	while (i < table->data->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = table->data->start_time;
		table->philos[i].data = table->data;
		if (pthread_mutex_init(&table->philos[i].meal_mutex, NULL) != 0)
			return (ERROR);
		if (pthread_mutex_init(&table->philos[i].last_meal_mutex, NULL) != 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void	assign_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data->philo_count)
	{
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1)
			% table->data->philo_count];
		i++;
	}
}

int	init_table(t_table *table)
{
	if (init_data(table->data) == ERROR)
		return (ERROR);
	if (init_forks(table) == ERROR)
	{
		pthread_mutex_destroy(&table->data->print_mutex);
		pthread_mutex_destroy(&table->data->dead_mutex);
		return (ERROR);
	}
	if (init_philosophers(table) == ERROR)
	{
		cleanup_table(table);
		return (ERROR);
	}
	assign_forks(table);
	return (SUCCESS);
}
