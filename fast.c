#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <aio.h>
#include <sys/mman.h>
#include <pthread.h>

#define BLOCK_SIZE 512 // 8KB block size
#define MAX_THREADS 1


typedef struct {
    int fd;
    int blockSize;
    unsigned int *buf;
    unsigned int offset;
    unsigned int xor;
} ThreadParameters;

unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

void *childThread(void *args) {
    ThreadParameters *temp = (ThreadParameters *)args;
    temp->xor = 0;
    int r;
    while ((r=pread(temp->fd, temp->buf, temp->blockSize, temp->offset)) > 0) {
        temp->xor ^= xorbuf(temp->buf, temp->blockSize / 4);
        temp->offset += temp->blockSize;
    }
    pthread_exit (NULL);
}

unsigned int threadRead(int blockSize, int blockCount, char *fileName, int threadNum, ThreadParameters *args) {
    int size = blockSize / 4;
    unsigned int xor = 0;
    int fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        printf("File error: %s -- could not be opened\n", fileName);
        return 1;
    }
    else {
        pthread_t child[threadNum];
        long offset = 0;
        for (int i = 0; i < threadNum; i++) {
            args[i].fd = fd;
            args[i].blockSize = blockSize;
            args[i].buf = (unsigned int *)malloc(blockSize);
            args[i].offset = offset;
            pthread_create(&child[i], NULL, childThread, (void *)&args[i]);
            offset += blockSize * blockCount / threadNum;
        }
        for (int i = 0; i < threadNum; i++) {
            pthread_join(child[i], NULL);
            xor ^= args[i].xor;
        }
    }
    
    close(fd);
    return xor;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./fast <file_to_read>\n");
        return 1;
    }
    char *fileName = argv[1];
    ThreadParameters args[MAX_THREADS];
    // To Clear the disk caches
    system("sudo sh -c \"/usr/bin/echo 3 > /proc/sys/vm/drop_caches\"");
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    unsigned int xor = threadRead(BLOCK_SIZE, -1, fileName, MAX_THREADS, args);
    clock_gettime(CLOCK_MONOTONIC, &end);
    unsigned long elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    unsigned long bytesProcessed = lseek(args[0].fd, 0, SEEK_END);
    unsigned long performance = (((bytesProcessed / elapsedTime) / 1024 ) / 1024);
    printf("%08x\n", xor);
    //printf("Elapsed time: %lu seconds\n", elapsedTime);
    //printf("Bytes processed: %lu\n", bytesProcessed);
    //printf("Performance: %lu bytes/second\n", performance);
    return 0;
}