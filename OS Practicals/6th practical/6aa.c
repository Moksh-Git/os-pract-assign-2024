#include <stdio.h>

#define MAX_FRAMES 3  // Minimum frame size as specified

// Function to check if a page is in memory
int isPageInMemory(int page, int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page) {
            return 1;  // Page found in memory
        }
    }
    return 0;  // Page not found
}

// Function to implement FCFS Page Replacement
void fcfsPageReplacement(int pages[], int pageCount) {
    int frames[MAX_FRAMES];
    int frameIndex = 0;  // To track the oldest frame position
    int pageFaults = 0;

    // Initialize frames to -1 (indicating empty)
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    // Process each page in the page request sequence
    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        printf("Page requested: %d\n", page);

        // Check if the page is already in memory
        if (!isPageInMemory(page, frames, MAX_FRAMES)) {
            // Page fault occurs since page is not in memory
            pageFaults++;
            printf("Page fault occurred.\n");

            // Replace the oldest page with the new page (FCFS)
            frames[frameIndex] = page;
            frameIndex = (frameIndex + 1) % MAX_FRAMES;  // Move to next frame in a circular manner
        } else {
            printf("Page is already in memory. No page fault.\n");
        }

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

    printf("\nFirst-Come, First-Served (FCFS) Page Replacement Algorithm\n");
    fcfsPageReplacement(pages, pageCount);

    return 0;
}

