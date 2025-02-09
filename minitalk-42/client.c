#include "minitalk.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void send_character(pid_t server_pid, char character)
{
    for (int i = 0; i < 8; i++) {
        if (character & (1 << (7 - i))) {
            kill(server_pid, SIGUSR1);  // Envoie SIGUSR1 pour bit 1
        } else {
            kill(server_pid, SIGUSR2);  // Envoie SIGUSR2 pour bit 0
        }
        usleep(100);  // Pause entre les signaux, ajuster la vitesse si nécessaire
    }
}

void send_message(pid_t server_pid, const char *message)
{
    while (*message) {
        send_character(server_pid, *message);  // Envoi de chaque caractère
        message++;
    }
    send_character(server_pid, '\0');  // Envoi d'un caractère NULL pour signaler la fin du message
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <PID du serveur> <message>\n", argv[0]);
        exit(1);
    }

    pid_t server_pid = atoi(argv[1]);
    const char *message = argv[2];

    // Envoi du message au serveur
    send_message(server_pid, message);
   //  printf("Message envoyé : %s\n", message);

    return 0;
}



