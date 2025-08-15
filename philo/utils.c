/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:31:32 by mdivan            #+#    #+#             */
/*   Updated: 2025/08/15 14:02:52 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

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
		if (ft_strcmp(status, "died") == 0)
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
