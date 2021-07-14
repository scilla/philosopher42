#include "phil_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n && (str1[i] != 0 || str2[i] != 0))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

void	wrapped_print(t_opt *opt, t_llint ttime, int pid, char *str)
{
	sem_wait(opt->print_m);
	printf("%lld %d %s\n", ttime - opt->sim_start, pid, str);
	if (ft_strncmp(str, "died", 4))
		sem_post(opt->print_m);
}
