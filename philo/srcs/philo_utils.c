/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:22:47 by jmaizel           #+#    #+#             */
/*   Updated: 2025/03/18 15:11:19 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
je vais associer chacun de mes arguments a la valeur associer dans ma strcture.
je return 0 si le parsing reussi 1 dans le cas contraire. je lui donne mes
condiscion de parsing aussi.
*/
static int	parse_args(t_data *data, int ac, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meals_required = -1;
	if (ac == 6)
	{
		data->meals_required = ft_atoi(av[5]);
		if (data->meals_required < 0)
			return (ft_printf("error: invalid arguments\n"), 1);
	}
	data->simulation_end = 0;
	if (data->num_philo < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
		return (ft_printf("error: invalid arguments\n"), 1);
	return (0);
}

/*
dans cette fonction, je vais alouer de la memoire pour les mutex et
pour les structures des phiilosophes.

et apres j alloue un mutex pour chaque fourchette.
une mutex pour l affichage
et un mutex pour la fin de simulation (end_mutex)
*/
static int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->forks || !data->philos)
		return (ft_printf("Error: Memory allocation failed\n"), 1);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->end_mutex, NULL);
	return (0);
}

/*
cette fonction configure chaque philosophe avec les donnees besoin,
elle attribue aussi les fourchette dans une logique circulaire
*/
static void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].is_dead = 0;
		data->philos[i].index_left_fork = i;
		data->philos[i].index_right_fork = (i + 1) % data->num_philo;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		i++;
	}
}

int	init_data(t_data *data, int ac, char **av)
{
	if (parse_args(data, ac, av))
		return (1);
	if (init_mutex(data))
		return (1);
	init_philosophers(data);
	return (0);
}
