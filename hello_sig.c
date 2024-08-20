#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handle_int_sig(int signum, siginfo_t *info, void *context) {
    printf("Caught signal %d\n", signum);
    exit(1);
}

int main() {
    struct sigaction sig;

    sig.sa_sigaction = handle_int_sig;
    sig.sa_flags = SA_SIGINFO;

    if (sigaction(SIGINT, &sig, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    while (1) {
        // Program runs indefinitely until SIGINT (Ctrl + C) is caught
    }

    return 0;
}

