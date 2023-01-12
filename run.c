#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

// XORs the values in a buffer and returns the result
unsigned int xor_buffer(unsigned int *buffer, int size) 
{
	unsigned int xor_result = 0;
	for (int i = 0; i < size; i++) 
	{
		xor_result ^= buffer[i]; //xoring the stored buffer value of reading the file
	}
	return xor_result;
}

// Reads a file and calculates the XOR of the blocks in the file
void read_function(int block_size, int block_count, char *file_name) 
{
	int size = block_size/4;
	unsigned int buffer_x[size];
	unsigned int xor_result = 0;
	// Open the file for reading
	FILE* file = fopen(file_name, "rb"); //using file pointer
	// Check if the file was successfully opened
	if (file == NULL)
	{
	    fprintf(stderr, "Error: Failed to open file for reading.\n"); //file opening error printing statement
	    return;
	}
	int r;
	int count = 0;

	// Measure the time it takes to read the file
	clock_t start = clock();
	while ((count < block_count) && (r=fread(buffer_x, block_size, 1, file)) > 0) 
	{
		xor_result ^= xor_buffer(buffer_x, size);
		count++;
	}
	// Close the file
	fclose(file);
	// Measure the time it took to read the file
	clock_t end = clock();
	double duration = (double)(end - start) / CLOCKS_PER_SEC; //calculating the duration
	// Calculate the read speed in MB/s
	double read_speed = ((double) block_size * block_count) / duration;  //calculating the read_speed
	printf("Performance - read speed: %f bytes/sec\n", read_speed); //printing the performance of the reading function
	printf("XOR value : %08x\n", xor_result); //printing the xor value
}	


// Writes a file with the specified number of blocks of a specified size
void write_function(int block_size, int block_count, char *file_name) 
{
	// Create a buffer to hold the data to write to the file
	char* buffer = (char*) malloc(block_size);
	// Fill the buffer with random data
	srand((unsigned)time(NULL));
	memset(buffer, rand(), block_size);
	// Open the file for writing
	FILE* file = fopen(file_name, "wb");
	// Check if the file was successfully opened
	if (file == NULL)
	{
    	fprintf(stderr, "Error: Failed to open file for writing.\n"); //file opening error
    	return;
	}
	// Measure the time it takes to write the file
	clock_t start = clock();
	// Write the data to the file the specified number of times
	for (int i = 0; i < block_count; i++)
	{
    	fwrite(buffer, block_size, 1, file);
	}
	// Close the file
	fclose(file);
	// Measure the time it took to write the file
	clock_t end = clock();
	double duration = (double)(end - start) / CLOCKS_PER_SEC; //calculating the duration
	// Calculate the write speed in MB/s
	double write_speed = ((double) block_size * block_count) / duration; //calculating the write_speed
	printf("Write speed: %f bytes/sec\n", write_speed); //printing the performance of the reading function
}


int main(int argc, char *argv[]) 
{
	char * file_name; // file name
	int block_size; // block size
	int block_count; // block count
	if (argc != 5) 
	{
		fprintf(stderr, "Usage: %s <filename> [-r|-w] <block_size> <block_count>\n", argv[0]);
		return EXIT_FAILURE;
	}

	file_name = argv[1];
	block_size = atoi(argv[3]);
	block_count = atoi(argv[4]);

	if (argv[2][1] == '\0') 
	{
		fprintf(stderr, "Error: Invalid read/write flag provided. Must be -r or -w.\n");
    		return EXIT_FAILURE;
	} 
	else if (argv[2][1] != 'r' && argv[2][1] != 'w') 
	{
		fprintf(stderr, "Error: invalid input\n");
	} 
	else if (argv[2][1] == 'r') 
	{
		read_function(block_size, block_count, file_name);
	} 
	else if (argv[2][1] == 'w') 
	{
		write_function(block_size, block_count, file_name);
	}
	return EXIT_SUCCESS;
}
