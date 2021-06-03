#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

size_t	ft_strlen (const char *str)
{
	size_t	i;

	i = 0;
	while (*str++ != '\0')
		i++;
	return (i);
}
int	ft_isdigit(int ch)
{
	if (ch >= 48 && ch <= 57)
		return (1);
	return (0);
}
static int	ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (1);
	if (c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

static int	getint(const char *str, int i, int minus)
{
	int	ans;

	ans = 0;
	if (ft_isdigit(str[i]) == 1)
		ans = str[i++] - 48;
	while (ft_isdigit(str[i]) == 1)
	{
		ans *= 10;
		ans += str[i] - 48;
		i++;
	}
	if (minus == 1)
		ans *= -1;
	return (ans);
}

int	ft_atoi(const char *str)
{
	int	minus;
	int	i;

	i = 0;
	minus = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = 1;
		i++;
	}
	while (str[i] == '0')
		i++;
	if (ft_isdigit(str[i]) == 0)
		return (0);
	return (getint(str, i, minus));
}

void ft_get_char(int pid, char c)
{
	int counter = 128;
	while (counter)
	{
		if (counter & c){
			if (kill(pid, SIGUSR1) == -1)
				ft_putstr_fd("we", 1);
		}
		else{
			if (kill(pid, SIGUSR2) == -1)
				ft_putstr_fd("we", 1);
		}
		counter >>= 1;
		usleep(100);
	}
}

int main(int argc, char **argv)
{
	int pid;
	
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid > 2)
		{
			int i = 0;
			while (argv[2][i])
			{
				ft_get_char(pid, argv[2][i]);
				i++;
			}
			ft_get_char(pid, '\n');
		}
		else{
			ft_putstr_fd(RED"./client not found server :(\n", 2);
			return (1);
		}
		
	}
	else {		
		ft_putstr_fd(RED"./client [pid] [message]\n", 2);
		return (1);
	}
	return (0);
	
}
