/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 19:28:51 by marmota           #+#    #+#             */
/*   Updated: 2021/08/30 20:34:09 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void handler_sig(int signum)
{
	static char c = 0xFF;
	static int bits = 0;
	//static char a[20];
	//static int index =0;

	if (signum == SIGUSR1)
	{
		//write(1,"1", 1);
		c |= 128 >> bits;
	}
	else if (signum == SIGUSR2)
	{
			//write(1,"0", 1);
		c ^= 128 >> bits;
	}
	bits++;
	if (bits == 8)
	{
		//write(1," -> ", 4);
		write(1, &c, 1);
		//write(1,"\n", 1);
		bits = 0;
		//a[index++]=c;
		c = 0xFF;
	}
	//if (index == 19)
	//write(1,a,20);
}

/*	Server recieves a signal from client */
//void handler_sigusr1(int signum)
//{
//	
//	(void)signum;
//	write(1, "1", 2);
//
//}
//
//void handler_sigusr2(int signum)
//{
//	(void)signum;
//	write(1, "0", 2);
//}

int main(void)
{
	pid_t	pid;

	pid = getpid();
	printf("PID: %d\n", pid);
	signal(SIGUSR1, handler_sig);
	signal(SIGUSR2, handler_sig);
	while(1)
		pause();
}

/*	
	Resources:
	step-by-step: https://github.com/mlanca-c/Minitalk/wiki/
	Other tutorial: https://bingu.tistory.com/m/4?category=902575

	pid_t: included with <sys/types.h>
	Get the process ID of the calling process.

	signal(2) - Linux manual page
	https://www.gnu.org/software/libc/manual/html_node/Basic-Signal_Handling.html

	signal() sets the disposition of the signal *signum* to *handler*, 
	which is either SIG_ING(ignored), SIG_DFL(default), or the address 
	of a programmer-defined function (a "signal handler").

	sighandler_t signal(int signum, sighandler_t action)
	The signal function provides a simple interface for establishing an action for a particular signal. 

	<signum.h> 
	#define	SIGUSR1		10

	https://www.gnu.org/software/libc/manual/html_node/Miscelaneous-Signals.html

	The SIGUSR1 and SIGUSR2 signals are set aside for you to use any way you 
	want. They're useful for simple interprocess communication. If you write a 
	signal handler for them in the program that recieves the signal. 

!!! using printf() inside you handler function may not work ("user defined signal 1 ./bin/cliente xxxx a")

*/