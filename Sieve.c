//
// Created by henri on 7/19/2025.
//

#include "Sieve.h"

#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <time.h>

#include "buffer.h"


void sieve(ULL upperLimit,int bufferSize) { // Given that sqrt(upperLimit) can be stored as an int! (upperLimit <= 4,611,685,193,793,671,168 ) lol --4.611 sextillion....
    clock_t start = clock();
    int chunkSize = (int)sqrt((double)upperLimit);
    //open file to overwrite:
    FILE* t = fopen("chunk.bin","wb");
    if (!t) exit(-1);
    fclose(t);
    //Create the static buffer
    Buffer buffer;
    initBuffer(&buffer,bufferSize);

    printf("Calculations start now, %.4f MB of RAM will be needed ( %.2f MB for buffer )\n", 2* (chunkSize / (8.0 * 1024 * 1024)),((float)(bufferSize*sizeof(uint64_t)))/(8*1024*1024)); //2*, bc. workingChunk(dynamic)+ basechunk ( static)
    //prepare by calculating base chunk:
    Chunk baseChunk;
    initChunk(&baseChunk,0,chunkSize);
    calcBaseChunk(&baseChunk);
    writeChunkToBuffer(&buffer,&baseChunk);

    //now sieving using base chunk
    Chunk workingChunk;
    for (ULL currentStart= chunkSize; currentStart < upperLimit; currentStart+=chunkSize) {

        initChunk(&workingChunk,currentStart,currentStart+chunkSize);
        calcChunk(&baseChunk,&workingChunk);

        writeChunkToBuffer(&buffer,&workingChunk);

        //working chunk can now be cleared, because it's been written to the buffer by now
        free(workingChunk.chunkSet);
    }
    //free all allocated memory
    flushBufferToFile(&buffer);
    freeBuffer(&buffer);
    free(baseChunk.chunkSet);
    //time consume output->
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time: %.6f seconds\n", time_spent);
}

//for debugging file-writing:
void printFromFile() {
    FILE *file = fopen("chunk.bin", "rb");

    uint64_t number;
    size_t count = 0;

    while (fread(&number, sizeof(uint64_t), 1, file) == 1) {
        printf("Number %zu: %llu\n", count++, number);
    }

    fclose(file);
}
