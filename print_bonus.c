#include "phil_bonus.h"

void	wrapped_print(t_opt *opt, t_llint ttime, int pid, char *str)
{
	sem_wait(opt->print_m);
	if (opt->alive)
		printf("%lld %d %s\n", ttime - opt->sim_start, pid, str);
	sem_post(opt->print_m);
}
