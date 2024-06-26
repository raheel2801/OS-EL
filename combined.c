#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#define FRAME_SIZE 3 // Size of the page frame

typedef struct
{
    int page;
    int referenced;
} PageEntry;

// FIFO Page Replacement Algorithm
int fifoPageFaults(int pages[], int n,int FRAME_SIZE)
{
    PageEntry frame[FRAME_SIZE];
    int i, j, k, pos = 0;
    int page_faults = 0;

    // Initialize frame
    for (i = 0; i < FRAME_SIZE; i++)
    {
        frame[i].page = -1;
        frame[i].referenced = 0;
    }

    for (i = 0; i < n; i++)
    {
        // Check if page is already in frame
        for (j = 0; j < FRAME_SIZE; j++)
        {
            if (frame[j].page == pages[i])
                break;
        }

        // If page is not in frame, replace the oldest page
        if (j == FRAME_SIZE)
        {
            frame[pos].page = pages[i];
            page_faults++;

            pos = (pos + 1) % FRAME_SIZE;
        }

        // Print current frame
        printf("FIFO Frame: ");
        for (k = 0; k < FRAME_SIZE; k++)
        {
            if (frame[k].page == -1)
                printf(" - ");
            else
                printf("%2d ", frame[k].page);
        }
        printf("\n");
    }

    return page_faults;
}

// Clock (Second Chance) Page Replacement Algorithm
int clockPageFaults(int pages[], int n,int FRAME_SIZE)
{
    PageEntry frame[FRAME_SIZE];
    int i, j, k, pos = 0;
    int page_faults = 0;

    // Initialize frame
    for (i = 0; i < FRAME_SIZE; i++)
    {
        frame[i].page = -1;
        frame[i].referenced = 0;
    }

    for (i = 0; i < n; i++)
    {
        // Check if page is already in frame
        for (j = 0; j < FRAME_SIZE; j++)
        {
            if (frame[j].page == pages[i])
            {
                frame[j].referenced = 1;
                break;
            }
        }

        // If page is not in frame, replace the oldest unreferenced page
        if (j == FRAME_SIZE)
        {
            while (frame[pos].referenced == 1)
            {
                frame[pos].referenced = 0;
                pos = (pos + 1) % FRAME_SIZE;
            }

            frame[pos].page = pages[i];
            frame[pos].referenced = 0;
            page_faults++;

            pos = (pos + 1) % FRAME_SIZE;
        }

        // Print current frame
        printf("Clock Frame: ");
        for (k = 0; k < FRAME_SIZE; k++)
        {
            if (frame[k].page == -1)
                printf(" - ");
            else
                printf("%2d ", frame[k].page);
        }
        printf("\n");
    }

    return page_faults;
}

int main()
{
    //int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}; // Reference string
    int num;
    printf("Enter the number of pages\n");
    scanf("%d",&num);
    int pages[num];
    printf("Enter the reference string\n");
    for(int i=0;i<num;i++) scanf("%d",&pages[i]);
    int n = sizeof(pages) / sizeof(pages[0]);

    printf("Reference String: ");
    for (int i = 0; i < n; i++)
        printf("%d ", pages[i]);
    printf("\n\n");

    clock_t start, end;
    double cpu_time_used;
    int FRAME_SIZE;
    printf("Enter the size of the page frame\n");
    scanf("%d",&FRAME_SIZE);
    start = clock();
    int fifo_faults = fifoPageFaults(pages, n,FRAME_SIZE);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nFIFO Page Faults: %d\n", fifo_faults);
    printf("FIFO Execution Time: %f seconds\n\n", cpu_time_used);

    start = clock();
    int clock_faults = clockPageFaults(pages, n,FRAME_SIZE);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nClock Page Faults: %d\n", clock_faults);
    printf("Clock Execution Time: %f seconds\n\n", cpu_time_used);

    return 0;
}
