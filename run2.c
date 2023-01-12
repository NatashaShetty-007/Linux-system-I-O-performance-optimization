#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

// XORs the values in a buffer and returns the result
unsigned int xoring_function(unsigned int *buffer, int size) 
{
    unsigned int xor_result = buffer[0];
    for (int i = 1; i < size; i++) 
    {
        xor_result ^= buffer[i]; //xoring the stored buffer value of reading the file
    }
    return xor_result;
}

// XORs the values in a buffer and returns the result
unsigned int xor_buffer(long long block_count, int block_size, char *file_name) 
{
    int size = block_size/4;
    unsigned int buffer_x[size];
    unsigned int xor_result = 0;
    long long bc = block_count;

    // Open the file for reading
    FILE* file2 = fopen(file_name, "rb"); //using file pointer
    // Check if the file was successfully opened
    if (file2 == NULL)
    {
        fprintf(stderr, "Error: Failed to open file for reading.\n"); //file opening error printing statement
        return 1;
    }
    int r;
    int count = 0;

    while ((count < bc) && (r=fread(buffer_x, block_size, 1, file2)) > 0) 
    {
        xor_result ^= xoring_function(buffer_x, size);
        count++;
    }
    // Close the file
    fclose(file2);
    printf("XOR value : %08x\n", xor_result); //printing the xor value
}


// Reads a file and calculates the XOR of the blocks in the file
void read_function(int block_size, char *file_name) 
{
    // Open the file for reading
    FILE* file = fopen(file_name, "rb"); //using file pointer

    // Check if the file was successfully opened
    if (file == NULL)
    {
        fprintf(stderr, "Error: Failed to open file for reading.\n");  //file opening error printing statement
    }

    // Set the file pointer to the end of the file to get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate a buffer to store the file data
    char* buffer = (char*)malloc(block_size);
    if (buffer == NULL) {
        perror("Error allocating buffer"); //printing error get when allocating buffer from reading file
        fclose(file); 
    }

    // Read the file in blocks and measure the time it takes
    long duration = 0;
    long long block_count = 0; //Taking long long here as it has a 
    
    // Start the timer
    clock_t start_time = clock();
    while (duration < 5 * CLOCKS_PER_SEC || duration > 15 * CLOCKS_PER_SEC) 
    {    
        // Read a block of data from the file
        size_t bytes_read = fread(buffer, 1, block_size, file);
        if (bytes_read < block_size) 
        {
            // If we reached the end of the file, break out of the loop
            if (feof(file)) 
            {
                break;
            }
            // Otherwise, there was an error reading the file
            perror("Error reading file");
            fclose(file); //closing the file
            free(buffer); //free the memory allocated to store the read file buffer
        }
        // Stop the timer and update the elapsed time
        duration = (clock() - start_time) / CLOCKS_PER_SEC; //
        block_count++;
    }

    // Close the file
    fclose(file);

    // Free the buffer
    free(buffer);

    // Calculate the total file size and performance in bytes/sec
    long long total_size = block_count * block_size;
    double performance = (double)((( total_size / duration) / 1024) / 1024);

    xor_buffer(block_count, block_size, file_name);

    // Print all the results which we get 
    printf("Block count: %lld\n", block_count);
    printf("Total size: %lld bytes\n", total_size);
    printf("Performance: %f MiB/sec\n", performance);
}   


int main(int argc, char *argv[]) 
{
    // Check if the number of arguments is correct
    if (argc != 3) 
    {
        fprintf(stderr, "Usage: %s <filename> <block_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char * file_name = argv[1]; // file name
    int block_size = atoi(argv[2]);  // block size
    //int block_count; // block count

    // Check if the block size is positive
    if (block_size <= 0)
    {
        fprintf(stderr, "Error: Invalid given block size\n", block_size); //block size invalid error printing
        return 1;
    }

    printf("Block size: %d\n", block_size);
    read_function(block_size, file_name);
    return EXIT_SUCCESS;
}