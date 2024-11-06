#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void sortArray(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <space-separated integers>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int *arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    // Sort the array
    sortArray(arr, n);

    // Fork to create a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        free(arr);
        return 1;
    } else if (pid == 0) {
        // Child process
        char *args[n + 1];
        for (int i = 0; i < n; i++) {
            args[i] = malloc(12); // Allocate space for each number as string
            sprintf(args[i], "%d", arr[i]); // Convert int to string
        }
        args[n] = NULL; // Last argument must be NULL

        // Execute child program
        execve("./child", args, NULL);
        
        // If execve fails
        perror("execve failed");
        for (int i = 0; i < n; i++) {
            free(args[i]);
        }
        free(arr);
        exit(1);
    } else {
        // Parent process
        wait(NULL); // Wait for child process to finish
    }

    free(arr);
    return 0;
}

