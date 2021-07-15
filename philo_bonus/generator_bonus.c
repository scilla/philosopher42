/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:25:47 by scilla            #+#    #+#             */
/*   Updated: 2021/07/15 17:25:48 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil_bonus.h"

void	gen_sem(t_opt *opt)
{
	char	*sem_name;

	sem_name = ft_strdup("phil");
	sem_unlink(sem_name);
	opt->sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, opt->p_count);
	free(sem_name);
	sem_name = ft_strdup("salive");
	sem_unlink(sem_name);
	opt->alive = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 0);
	free(sem_name);
}

void	wrong_args(t_opt *opt)
{
	free(opt);
	printf("wrong args\n");
	exit(0);
}

t_opt	*gen_opt(int argc, char **argv)
{
	t_opt	*opt;

	opt = malloc(sizeof(t_opt));
	if (argc < 5 || argc > 6)
		wrong_args(opt);
	opt->p_count = ft_atoi(argv[1]);
	opt->time_die = ft_atoi(argv[2]);
	opt->time_eat = ft_atoi(argv[3]);
	opt->time_sleep = ft_atoi(argv[4]);
	opt->eat_count = -1;
	if (argc == 6)
		opt->eat_count = ft_atoi(argv[5]);
	if (!opt->p_count || !opt->time_die || !opt->time_eat || !opt->time_sleep
		|| !opt->eat_count)
		wrong_args(opt);
	opt->sim_start = mtime();
	opt->phils = malloc(sizeof(t_phil *) * opt->p_count);
	opt->pids = malloc(sizeof(int) * opt->p_count);
	gen_sem(opt);
	return (opt);
}

t_phil	*gen_phil(t_opt *opt, int i)
{
	t_phil	*phil;

	phil = malloc(sizeof(t_phil));
	phil->stage = 0;
	phil->eat_count = 0;
	phil->stage_time = 0;
	phil->checking = 0;
	phil->has_forks = 0;
	phil->last_eat = mtime();
	phil->opt = opt;
	phil->pid = i + 1;
	return (phil);
}
