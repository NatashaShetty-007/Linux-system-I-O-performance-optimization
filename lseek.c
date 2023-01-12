#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

double now() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

void performance(int blockSize, int blockCount, double duration) {
    unsigned int file = (blockCount / 1000000) * blockSize;
    printf("File size: %d MB\n", file);
    printf("Performance: %f MiB/s ", file/duration);
}

void file_read(int blockSize, int blockCount, char *fileName) {
    int fd = open(fileName, O_RDONLY); //open the image file
    if(fd == -1) {
        printf("File error: %s -- could not be opened\n", fileName);
        return;
    }
    else {
        int r;
        int count = 0;
        while (count < blockCount) {
            lseek(fd, 0, SEEK_SET);
            count++;
        }
        
        
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    char * fileName; //file name
    int blockSize = 1;
    int blockCount = 1000000;
    double start, end;
    if (argc != 2) {
        printf("Invalid inputs");
        return 0;
    }

    fileName = argv[1];
    
    do{
        start = now();
        file_read(blockSize, blockCount, fileName);
        end = now();
        performance(blockSize, blockCount, end - start);
        printf("Read Time: %f seconds\n", end - start);
        blockCount *= 2;
    }while((end-start)<16);
    
    return 0;
}
