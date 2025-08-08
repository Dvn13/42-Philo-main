/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by user             #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_table *table, int i)
{
	long	current_time;
	long	time_since_meal;

	pthread_mutex_lock(&table->philos[i].last_meal_mutex);
	current_time = get_current_time();
	time_since_meal = current_time - table->philos[i].last_meal_time;
	if (time_since_meal >= table->data->time_to_die)
	{
		pthread_mutex_unlock(&table->philos[i].last_meal_mutex);
		pthread_mutex_lock(&table->data->dead_mutex);
		table->data->simulation_end = 1;
		pthread_mutex_unlock(&table->data->dead_mutex);
		pthread_mutex_lock(&table->data->print_mutex);
		printf("%ld %d died\n", current_time - table->data->start_time,
			table->philos[i].id);
		pthread_mutex_unlock(&table->data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->philos[i].last_meal_mutex);
	return (0);
}

int	check_all_ate_enough(t_table *table)
{
	int	i;
	int	finished_eating;

	if (table->data->must_eat_count == -1)
		return (0);
	finished_eating = 0;
	i = 0;
	while (i < table->data->philo_count)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (table->philos[i].meals_eaten >= table->data->must_eat_count)
			finished_eating++;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		i++;
	}
	if (finished_eating == table->data->philo_count)
	{
		pthread_mutex_lock(&table->data->dead_mutex);
		table->data->simulation_end = 1;
		pthread_mutex_unlock(&table->data->dead_mutex);
		return (1);
	}
	return (0);
}

static int	run_monitoring(t_table *table)
{
	int	i;

	while (1)
	{
		if (check_all_ate_enough(table))
			break ;
		i = 0;
		while (i < table->data->philo_count)
		{
			if (check_philosopher_death(table, i))
				return (1);
			i++;
		}
		usleep(100);
	}
	return (0);
}

int	start_simulation(t_table *table)
{
	if (table->data->philo_count == 1)
		return (handle_single_philosopher(table));
	if (create_threads(table) == ERROR)
		return (ERROR);
	if (run_monitoring(table))
		return (join_threads(table));
	return (join_threads(table));
}
