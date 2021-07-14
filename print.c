#include "phil.h"

void	wrapped_print(t_opt *opt, t_llint ttime, int pid, char *str)
{
	pthread_mutex_lock(opt->print_m);
	if (opt->alive)
		printf("%lld %d %s\n", ttime - opt->sim_start, pid, str);
	pthread_mutex_unlock(opt->print_m);
}
