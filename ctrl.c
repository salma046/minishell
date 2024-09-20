// Hello Salma put this in the int main before while(1)
signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sigint);
// this is the function for crtl+C
void ft_sigint(int num)
{
	static int i;
	if (i == 0)
		write(1, "~$\n~$", 6);
	else 
		write(1, "~$^C \n~$", 8);
}