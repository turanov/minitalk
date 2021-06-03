#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
static void	solv(int n, int fd)
{
	int	k;

	k = 1;
	if (n < 0)
		k = -1;
	if (n <= 9 && n >= -9)
	{
		ft_putchar_fd(n * k + 48, fd);
		return ;
	}
	solv(n / 10, fd);
	ft_putchar_fd((n % 10) * k + 48, fd);
}
int ft_pow(int x, int n)
{
	int ans = x;
	while (--n)
		ans *= x;
	return ans;
}
void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
		solv(n, fd);
}

void solve(int id)
{
	static short counter = 0;
	static char c = 0;
	static short count = 128;
	
	if (SIGUSR1 == id)
	{
		c += count;
		count >>= 1;
		counter++;
	}
	else if (SIGUSR2 == id){
		count >>= 1;
		counter++;
	}
	if (counter == 8)
	{
		counter = 0;
		write(1, &c, 1);
		count = 128;
		c = 0;
	}
	

}
int main()
{
	int check;
	
	check = 1;
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (check)
	{
		signal(SIGUSR1, solve);
		signal(SIGUSR2, solve);
	}
}
