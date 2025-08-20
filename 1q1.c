#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    int n;

    printf("Enter number of child ");
    scanf("%d", &n);

    for (int i=0; i<n; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process:
            for (int j=0;j<100000000; j++);
            exit(0); 
        }
    }

    // Parent process waits for all children
    struct rusage usage;
    for (int i=0; i<n; i++) {
        wait(NULL);
    }

    getrusage(RUSAGE_CHILDREN, &usage);
        
    printf("User time   = %ld.%06ld sec\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("System time = %ld.%06ld sec\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);

    return 0;
}

