#include "minitalk.h"

static void	action(int sig, siginfo_t *info, void *context)
{
}



// struct sigaction {
   //  void (*sa_handler)(int);  // Pointeur vers la fonction de gestion du signal
   //  sigset_t sa_mask;         // Bloque d'autres signaux pendant le traitement
   //  int sa_flags;             // Options supplémentaires
   // };
int   main(int ac, char **av)
{
   struct sigaction sa;

   sa.sa_handler = handle_signal;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = 0; 
   if (ac != 1)
   {
		write(2, "Usage: ./server\n", 16);
      exit(1);
   }
   printf("Server PID : %d\n",getpid());

   sigaction(SIGUSR1, &sa, NULL);
   sigaction(SIGUSR2, &sa, NULL);

   while (1)
      pause();
   return (0);
}