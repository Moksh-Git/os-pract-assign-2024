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

// Function to find the optimal page to replace
int findOptimal(int frames[], int frameCount, int pages[], int pageCount, int currentIndex) {
    int farthest = currentIndex;
    int indexToReplace = -1;

    for (int i = 0; i < frameCount; i++) {
        int j;
        // Find the next occurrence of frames[i]
        for (j = currentIndex + 1; j < pageCount; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {  // Update farthest if this page is used later
                    farthest = j;
                    indexToReplace = i;
                }
                break;
            }
        }
        // If frames[i] is never referenced in the future, return this page
        if (j == pageCount) {
            return i;
        }
    }

    // If all frames are referenced, replace the one that is used the farthest in the future
    return (indexToReplace == -1) ? 0 : indexToReplace;
}

// Function to implement Optimal Page Replacement
void optimalPageReplacement(int pages[], int pageCount) {
    int frames[MAX_FRAMES];
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
        int pageIndex = findPageInMemory(page, frames, MAX_FRAMES);

        if (pageIndex == -1) {  // Page fault
            pageFaults++;
            printf("Page fault occurred.\n");

            // If there is an empty frame, place the page there
            int emptyIndex = findPageInMemory(-1, frames, MAX_FRAMES);
            if (emptyIndex != -1) {
                frames[emptyIndex] = page;
            } else {
                // No empty frames, find the optimal page to replace
                int optimalIndex = findOptimal(frames, MAX_FRAMES, pages, pageCount, i);
                frames[optimalIndex] = page;
            }
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

    printf("\nOptimal Page Replacement Algorithm\n");
    optimalPageReplacement(pages, pageCount);

    return 0;
}

