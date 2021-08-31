/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 19:04:05 by marmota           #+#    #+#             */
/*   Updated: 2021/08/30 17:42:40 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

/*	
	kill(pid, signal)
	Recieve server PID 
	If PID is not recieved EXIT
	PID is converted to an integer and sent with SIGUSR1

	send_signaal() will convert a ASCII character code to binary and then send
	SIGUSR1 for "1" and SIGUSR2 for "2" for the 8 bits of the character

	The character will then be converted to a character again by the server program.
*/	
void send_signal(char *message, int pid)
{
	int i;
	int shift;
	int nline;
	shift = -1;
	i = 0;
	nline=0;

	while (1)
	{
		shift = -1;
		if(!message[i])
		{
			nline = 1;
			message[i]='\n';
		}
		while(++shift < 8)
		{
			if (message[i] & (0x80 >> shift))
			{
				//write(1,"1",1);
				if(kill(pid, SIGUSR1) == -1)
					exit(1);
			}
			else
			{
				//write(1,"0",1);
				if(kill(pid, SIGUSR2) == -1)
					exit(1);
			}
			usleep(30);
		}
			if(nline)
				break;
		i++;
	}
}

int main(int argc, char *argv[])
{
	int pid;

	// 1st arg = program name; 2nd arg = PID; 3rd arg = Char;
	// ./bin/client 4111 a -> a[97]
	if (argc != 3)
	{
		printf("client: no arguments\n");
		exit(EXIT_FAILURE);
	}
	pid = atoi(argv[1]);
	send_signal(argv[2], pid);
	return (0);
}

/* Binary conversions */


