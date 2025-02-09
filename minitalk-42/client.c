#include "minitalk.h"

void send_character(pid_t server_pid, char character) 
{
	int	i;

	i = 0;
   while (i < 8) 
	{
        if (character & (1 << (7 - i)))
            kill(server_pid, SIGUSR1);
		  else 
            kill(server_pid, SIGUSR2);
        usleep(400);
		  i++;
   }
}

void send_message(pid_t server_pid, const char *message) {
    while (*message) 
	 {
        send_character(server_pid, *message);
        message++;
    }
}

void confirmation_handler(int sig) {
    if (sig == SIGUSR1)
        printf("Le serveur a confirmé la réception du message.\n");
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <PID du serveur> <message>\n", argv[0]);
        exit(1);
    }
    pid_t server_pid = atoi(argv[1]);
    const char *message = argv[2];
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = confirmation_handler;
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Erreur avec sigaction pour SIGUSR1");
        exit(1);
    }
    send_message(server_pid, message);
    printf("Message envoyé : %s\n", message);
    pause();
    return 0;
}

