// Hello Salma put this in the int main before while(1)
    signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sigint);
// this is the function for crtl+C
    void ft_sigint(int num)
{
	static int i;
	if (i == 0)
        printf("~$\n~$");
	else 
        printf("~$^C\n~$ ");
}