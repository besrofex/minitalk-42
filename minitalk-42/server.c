#include "minitalk.h"

volatile sig_atomic_t current_char = 0;  // Variable pour suivre la position du caractère actuel
char received_string[1024]; // Tableau pour stocker la chaîne reçue

void handler(int sig, siginfo_t *info, void *ucontext) {
    static int bit_position = 0;
    static unsigned char character = 0;

    if (sig == SIGUSR1)
        character |= (1 << (7 - bit_position));
    bit_position++;
    if (bit_position == 8) 
	 {
        received_string[current_char++] = character;
        character = 0;
        bit_position = 0;
        if (current_char >= sizeof(received_string) - 1) 
		  {
            received_string[current_char] = '\0';
            printf("Message reçu : %s\n", received_string);
            current_char = 0;
            // kill(info->si_pid, SIGUSR1);
        }
    }
}

int main() 
{
    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Erreur avec sigaction SIGUSR1");
        exit(1);
    }
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Erreur avec sigaction SIGUSR2");
        exit(1);
    }
    printf("PID : %d\n", getpid());
    while (1) {
        pause();
    }
    return 0;
}


