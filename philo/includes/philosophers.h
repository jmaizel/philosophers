/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:22:45 by jmaizel           #+#    #+#             */
/*   Updated: 2025/03/18 14:59:15 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;

	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	end_mutex;
	int				simulation_end;

	struct s_philo	*philos;
}					t_data;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				meals_eaten;
	pthread_t		thread;
	int				index_left_fork;
	int				index_right_fork;
	pthread_mutex_t	meal_mutex;
	struct s_data	*data;
	int				is_dead;
}					t_philo;

int					init_data(t_data *data, int ac, char **av);
int					start_threads(t_data *data);
void				clean_data(t_data *data);
void				print_data(t_data *data);

void				*philo_routine(void *arg);
void				*monitor_death(void *arg);
void				print_state(t_philo *philo, char *state);
void				*handle_single_philo(t_philo *philo);

long long			get_time(void);

#endif