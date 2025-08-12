/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:31:42 by mdivan            #+#    #+#             */
/*   Updated: 2025/08/12 16:31:45 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philosopher_main_loop(t_philo *philo)
{
	while (!is_simulation_end(philo->data))
	{
		take_forks(philo);
		if (philo->data->philo_count == 1)
			break ;
		eat(philo);
		if (philo->data->must_eat_count != -1)
		{
			pthread_mutex_lock(&philo->meal_mutex);
			if (philo->meals_eaten >= philo->data->must_eat_count)
			{
				pthread_mutex_unlock(&philo->meal_mutex);
				break ;
			}
			pthread_mutex_unlock(&philo->meal_mutex);
		}
		sleep_and_think(philo);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count % 2 == 1)
	{
		if (philo->id % 2 == 0)
			usleep(philo->data->time_to_eat * 1000 / 2);
	}
	else
	{
		if (philo->id % 2 == 0)
			usleep(500);
	}
	philosopher_main_loop(philo);
	return (NULL);
}

int	handle_single_philosopher(t_table *table)
{
	printf("0 1 has taken a fork\n");
	ft_usleep(table->data->time_to_die);
	printf("%d 1 died\n", table->data->time_to_die);
	return (SUCCESS);
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data->philo_count)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philosopher_routine,
				&table->philos[i]) != 0)
			return (ERROR);
		usleep(50);
		i++;
	}
	return (SUCCESS);
}

int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data->philo_count)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	return (SUCCESS);
}
