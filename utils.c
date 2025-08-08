/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by user             #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by user            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int microseconds)
{
	long	start;
	long	current;

	start = get_current_time();
	while (1)
	{
		current = get_current_time();
		if ((current - start) >= microseconds)
			break ;
		usleep(500);
	}
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_simulation_end(philo->data))
	{
		timestamp = get_current_time() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
		if (strcmp(status, "died") == 0)
		{
			pthread_mutex_lock(&philo->data->dead_mutex);
			philo->data->simulation_end = 1;
			pthread_mutex_unlock(&philo->data->dead_mutex);
		}
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	is_simulation_end(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->dead_mutex);
	result = data->simulation_end;
	pthread_mutex_unlock(&data->dead_mutex);
	return (result);
}
