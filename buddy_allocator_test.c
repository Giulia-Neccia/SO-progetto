#include "buddy_allocator.h"
#include <stdio.h>

#define BUFFER_SIZE 256
#define BUDDY_LEVELS 3
#define MEMORY_SIZE 256
#define MIN_BUCKET_SIZE (MEMORY_SIZE>>(BUDDY_LEVELS))

char buffer[BUFFER_SIZE]; // 100 Kb buffer to handle memory should be enough
char memory[MEMORY_SIZE];

BuddyAllocator alloc;
int main(int argc, char** argv) {
  printf("init... ");
  BuddyAllocator_init(&alloc, BUDDY_LEVELS,
                      buffer,
                      BUFFER_SIZE,
                      memory,
                      MEMORY_SIZE,
                      MIN_BUCKET_SIZE);
  printf("DONE\n");

  void* p1=BuddyAllocator_malloc(&alloc, 27);
  void* p2=BuddyAllocator_malloc(&alloc, 27);
  void* p3=BuddyAllocator_malloc(&alloc, 54);
//   BuddyAllocator_free(&alloc, p1);
//   BuddyAllocator_free(&alloc, p2);
//   BuddyAllocator_free(&alloc, p3);
printf ("%p %p %p", p1,p2,p3);
return 0; 
}
