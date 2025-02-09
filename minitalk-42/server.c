#include "minitalk.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static char current_char = 0;
static int bit_count = 0;
static int message_received = 0;

void signal_handler(int sig)
{
    if (sig == SIGUSR1)
        current_char |= (1 << (7 - bit_count)); // Si SIGUSR1, on met à 1 le bit correspondant.
    // SIGUSR2 ne fait rien, donc on n'a pas besoin d'assigner un bit.

    bit_count++;

    // Si on a reçu 8 bits, on a un caractère complet.
    if (bit_count == 8) {
        if (current_char == '\0') {  // Si c'est un caractère NULL, on termine le message
            message_received = 1;
            printf("\n");
        } else {
            printf("%c", current_char);  // Affichage du caractère reçu
        }
        current_char = 0;  // Réinitialiser pour le prochain caractère
        bit_count = 0;     // Réinitialiser le compteur de bits
    }
}

int main()
{
    struct sigaction sa;

    // Affichage du PID du serveur
    printf("Serveur lancé avec le PID : %d\n", getpid());

    // Configuration du gestionnaire de signaux pour SIGUSR1 et SIGUSR2
    sa.sa_flags = 0;
    sa.sa_handler = signal_handler;
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Erreur avec sigaction");
        exit(1);
    }

    // Le serveur peut recevoir plusieurs messages
    while (1) {
        // Attente que tous les signaux pour un message aient été reçus
        while (!message_received) {
            pause();  // Bloque l'exécution et attend les signaux
        }

        // Réinitialisation pour le prochain message
        message_received = 0;
    }

    return 0;
}




