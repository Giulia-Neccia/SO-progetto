#include <assert.h>
#include <math.h> // for floor and log2
#include <stdio.h>
#include <stdlib.h>

#include "buddy_allocator.h"

void BuddyAllocator_init(BuddyAllocator *alloc, 
                        int num_levels, 
                        char *buffer,
                        int buffer_size, 
                        char *memory, 
                        int min_bucket_size) {
  // we need room also for level 0
  alloc->num_levels = num_levels;
  alloc->memory = memory;
  alloc->min_bucket_size = min_bucket_size;
  assert(num_levels < MAX_LEVELS);
  // we need enough memory to handle internal structures
  assert(buffer_size >= BuddyAllocator_calcSize(num_levels));

 

  printf("BUDDY INITIALIZING\n");
  printf("\tlevels: %d -- list-items: %d", num_levels, list_items);
  printf("\tmax list entries %d bytes\n", list_alloc_size);
  printf("\tbucket size:%d\n", min_bucket_size);
  printf("\tmanaged memory %d bytes\n", (1 << num_levels) * min_bucket_size);

};


void *BuddyAllocator_malloc(BuddyAllocator *alloc, int size) {
  
}
// releases allocated memory
void BuddyAllocator_free(BuddyAllocator *alloc, void *mem) {
}
