/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdivan <mdivan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:31:51 by mdivan            #+#    #+#             */
/*   Updated: 2025/08/12 16:31:54 by mdivan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR 1

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				simulation_end;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	last_meal_mutex;
	t_data			*data;
}					t_philo;

typedef struct s_table
{
	t_data			*data;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}					t_table;

int					parse_arguments(int argc, char **argv, t_data *data);
int					ft_atoi(char *str);
int					is_valid_number(char *str);

long				get_current_time(void);
void				ft_usleep(int microseconds);
void				print_status(t_philo *philo, char *status);
int					is_simulation_end(t_data *data);

int					init_data(t_data *data);
int					init_table(t_table *table);
int					init_philosopher_mutexes(t_table *table, int i);
int					init_philosophers(t_table *table);
void				assign_forks(t_table *table);

int					start_simulation(t_table *table);
void				*philosopher_routine(void *arg);

int					check_philosopher_death(t_table *table, int i);
int					check_all_ate_enough(t_table *table);

void				take_forks(t_philo *philo);
void				eat(t_philo *philo);
void				sleep_and_think(t_philo *philo);

void				cleanup_table(t_table *table);
void				cleanup_philosopher_mutexes(t_table *table, int count);
void				destroy_mutexes(t_table *table);
int					handle_single_philosopher(t_table *table);
int					create_threads(t_table *table);
int					join_threads(t_table *table);

#endif