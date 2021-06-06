#include <assert.h>
#include <math.h> // for floor and log2
#include <stdio.h>
#include <stdlib.h>

#include "buddy_allocator.h"

void BuddyAllocator_initvoid(BuddyAllocator* allocator,
                         int num_levels,                         
                         char* memory, //memoria allocator
                         int memory_size, 
                         char* memory_bitmap, //memoria bitmap
                         int memory_bitmap_size,                                                 
                         int min_bucket_size){

  // we need room also for level 0
  allocator->num_levels = num_levels;
  allocator->memory = memory;
  allocator->memory_size  = memory_size;
 // controllo se la dimensione è grande almeno per la bitmap
  assert(min_bucket_size>8);
  allocator->min_bucket_size=min_bucket_size;

  assert(num_levels<MAX_LEVELS);

  //generazione numero di bit per la bit_map, ogni bit è un buddy di minbucket size
  int num_bits = (1<<(num_levels+1)) - 1;
  //se non ci sono abbastanza byte per tutti i bit che devo conservare errore
  assert(BitMap_getBytes(num_bits)<=memory_bitmap_size);

  printf("BUDDY INITIALIZING\n");
  printf("\tmanaged memory: %d bytes\n", memory_size);
  printf("\tlevels: %d\n", num_levels);  
  printf("\tmin bucket size:%d\n", min_bucket_size);  
  printf("\tbits_bitmap: %d\n", num_bits);
  printf("\tbitmap memory %d bytes usati di %d bytes forniti \n",BitMap_getBytes(num_bits), memory_bitmap_size);

  BitMap_init(&allocator->bitmap, num_bits, memory_bitmap);
  print_bitmap(&allocator->bitmap);
};


void *BuddyAllocator_malloc(BuddyAllocator *alloc, int size) {
  BitMap bitmap = allocator->bitmap;
  size = size+ sizeof(int); //sizeof(int) byte vengono usati per salvare l'indice della bitmap
  assert(allocator->memory_size  > size);
  //con questo mi calcolo il livello al quale si troverà il blocco da allocare

  int actual_level=check_level(allocator,size,allocator->min_bucket_size,allocator->num_levels);
  printf("Provo ad allocare il nuovo blocco di size %d al livello %d\n", size,actual_level);
  // la dimensione del blocco sarà la totale /2*num_level
  int size_start= (allocator->memory_size)>>actual_level;
  printf("level=%d size_start=%d tot_memory=%d\n\n",actual_level,size_start,allocator->memory_size);

  //scandire da first_idx del livello 
  int idx=-1;
  for(int i=firstIdx(actual_level); i<firstIdx(actual_level+1)-1; i++){
    if(!BitMap_bit(&bitmap,i)){ //se non è occupato
      idx=i; //lo occuperò e salvo l'indice
      break;
    }
  }
  assert("non ci sono livelli liberi a sufficienza" && idx!=-1);
  set_parent(&bitmap, idx , 1);
  set_child(&bitmap, idx ,1);
  printf("l'indice è %d\n",idx);
  print_bitmap(&bitmap);
  char* start_memory=allocator->memory+startIdx(idx)*size_start;
  *((int*)start_memory)=idx; //ritorno il ptr+ 4 e salvo nei primi 4 byte il valore dell'indice
   return (void*)(start_memory + 4);
}
// releases allocated memory
void BuddyAllocator_free(BuddyAllocator *alloc, void *mem) {

}
