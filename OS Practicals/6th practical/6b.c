#include <stdio.h>

#define MAX_FRAMES 3  // Minimum frame size as specified

// Function to check if a page is in memory and return its index
int findPageInMemory(int page, int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page) {
            return i;  // Return index of the page if found
        }
    }
    return -1;  // Return -1 if page is not found
}

// Function to find the Least Recently Used page's index
int findLRU(int usage[], int frameCount) {
    int min = usage[0], lruIndex = 0;
    for (int i = 1; i < frameCount; i++) {
        if (usage[i] < min) {
            min = usage[i];
            lruIndex = i;
        }
    }
    return lruIndex;
}

// Function to implement LRU Page Replacement
void lruPageReplacement(int pages[], int pageCount) {
    int frames[MAX_FRAMES];
    int usage[MAX_FRAMES];  // To keep track of usage times
    int pageFaults = 0;
    int time = 0;  // Simulates time for LRU tracking

    // Initialize frames and usage times to -1
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
        usage[i] = -1;
    }

    // Process each page in the page request sequence
    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        printf("Page requested: %d\n", page);

        // Check if the page is already in memory
        int pageIndex = findPageInMemory(page, frames, MAX_FRAMES);

        if (pageIndex == -1) {  // Page fault
            pageFaults++;
            printf("Page fault occurred.\n");

            // Find the LRU page's index if frames are full
            int lruIndex = findLRU(usage, MAX_FRAMES);
            frames[lruIndex] = page;     // Replace the LRU page
            usage[lruIndex] = time;      // Update usage time for new page
        } else {
            printf("Page is already in memory. No page fault.\n");
            usage[pageIndex] = time;  // Update usage time for accessed page
        }

        time++;  // Increment time after each page request

        // Print current state of frames
        printf("Current Frames: ");
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n\n");
    }

    printf("Total page faults: %d\n", pageFaults);
}

int main() {
    int pageCount;

    printf("Enter the number of pages in the sequence: ");
    scanf("%d", &pageCount);

    int pages[pageCount];  // Array to store page sequence

    printf("Enter the page sequence:\n");
    for (int i = 0; i < pageCount; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }

    printf("\nLeast Recently Used (LRU) Page Replacement Algorithm\n");
    lruPageReplacement(pages, pageCount);

    return 0;
}

