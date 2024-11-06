#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function to find the index of the closest request
int findClosestRequest(int head, int requests[], int visited[], int num_requests) {
    int min_distance = abs(head - requests[0]);
    int index = -1;
    
    for (int i = 0; i < num_requests; i++) {
        int distance = abs(head - requests[i]);
        if (!visited[i] && distance < min_distance) {
            min_distance = distance;
            index = i;
        }
    }
    return index;
}

// Function to implement SSTF Disk Scheduling
void sstfDiskScheduling(int requests[], int num_requests, int head) {
    int visited[MAX_REQUESTS] = {0};  // Array to mark processed requests
    int total_seek_time = 0;

    printf("Order of servicing requests: ");
    
    for (int i = 0; i < num_requests; i++) {
        int closest_index = findClosestRequest(head, requests, visited, num_requests);
        if (closest_index == -1) {
            break;
        }

        // Calculate seek time to the next request
        int seek_time = abs(head - requests[closest_index]);
        total_seek_time += seek_time;
        
        printf("%d ", requests[closest_index]);
        
        // Update head position and mark this request as visited
        head = requests[closest_index];
        visited[closest_index] = 1;
    }
    
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int num_requests, head;
    int requests[MAX_REQUESTS];

    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);

    printf("Enter the positions of each disk request:\n");
    for (int i = 0; i < num_requests; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("\nShortest Seek Time First (SSTF) Disk Scheduling Algorithm\n");
    sstfDiskScheduling(requests, num_requests, head);

    return 0;
}

