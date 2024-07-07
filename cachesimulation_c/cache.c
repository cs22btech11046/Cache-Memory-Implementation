#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <stdbool.h>
#define LIMIT 8
#define MAXLIMIT 5000


int cache_size,block_size,ass,time;
char rep_pol[LIMIT],wrt_pol[LIMIT];
int hits,misses;
int hit_check;

struct set{
int tag;
int valid;
int time;
};

void cachesearch(struct set (*cache)[ass], int tag, int set_index,char mode,char rep_pol[LIMIT],char wrt_pol[LIMIT]);
int find_li(struct set (*cache)[ass], int set_index);
int find_fi(struct set (*cache)[ass], int set_index);
int Random(int assoc);


int main(){
hits=0;
misses=0;

FILE *file = fopen("cache.config", "r");
if (file == NULL) {
return 1;
    }
    

if (fscanf(file, "%d\n%d\n%d\n%s\n%s\n",&cache_size,&block_size,&ass,rep_pol,wrt_pol) == EOF) {
     
   }
    
    fclose(file);
    
int numsets ;
int offset ;
int set_offset ;

if(ass == 0){
numsets =1;
set_offset =0;
}
else{
 numsets = (cache_size )/ (ass * block_size);
 offset = log(block_size)/log(2);
 set_offset = log(numsets)/log(2);
}

struct set (*cache)[ass] = malloc(numsets * sizeof(struct set[ass]));
    if (cache == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < numsets; i++) {
        for (int j = 0; j < ass; j++) {
            cache[i][j].tag = 0;
            cache[i][j].valid = 0;
            cache[i][j].time = 0;
        }
    }
    



    FILE *file1 = fopen("cache.access", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    unsigned int line;
    char mode; 
    
for(int i=0;i<MAXLIMIT; i++){
    while (fscanf(file1, "%c: 0x%x", &mode,&line) == 2) {
        //printf("%c: 0x%d \n", mode, line);
        
        int set_index = ((line >> offset) % numsets);
        int tag = line >> (set_offset + offset);
        hit_check =0;
        cachesearch(cache,tag,set_index,mode,rep_pol,wrt_pol);
       if(hit_check == 1){
       printf(" Address: 0x%08X, Set: 0x%02X, Hit, Tag: 0x%06X \n",line,set_index,tag);
       }
       else{
       printf(" Address: 0x%08X, Set: 0x%02X, Miss, Tag: 0x%06X \n",line,set_index,tag);
       }
       
    }
    }
    fclose(file1);
	free(cache);
 // printf("total hits: %d\n",hits); 
  //printf("total misses: %d\n",misses);     
    

    return 0;

}

void cachesearch(struct set (*cache)[ass], int tag, int set_index,char mode,char rep_pol[LIMIT],char wrt_pol[LIMIT]){
bool check;
check =false;
if (mode == 'R') {
    // Process read operation
    for (int i = 0; i < ass; i++) {
        if (cache[set_index][i].tag == tag && cache[set_index][i].valid ==1) {
            check = true;
            // Cache hit
            hits++;
            cache[set_index][i].time ++;
            hit_check =1;
            break;
        } else if (cache[set_index][i].valid ==0) {
            misses++;
            cache[set_index][i].tag = tag;
            cache[set_index][i].valid = 1;
            cache[set_index][i].time++;
            check = true;
            break;
        }
    }
    if(check == false){
    	if(strcmp(rep_pol, "LRU") == 0){
    		int lrui = find_li(cache,set_index);
    		misses++;
    		cache[set_index][lrui].tag = tag;
    		cache[set_index][lrui].valid = 1;
    		cache[set_index][lrui].time++;
    	}
    	else if(strcmp(rep_pol, "FIFO") == 0){
    		int fifo = find_fi(cache,set_index);
    		misses++;
    		cache[set_index][fifo].tag = tag;
    		cache[set_index][fifo].valid = 1;
    		cache[set_index][fifo].time++;
    	
    	}
    	else if (strcmp(rep_pol, "RANDOM") == 0) {
    		// RANDOM replacement policy
    		int random = Random(ass);
    		misses++;
    		cache[set_index][random].tag = tag;
    		cache[set_index][random].valid = 1;
    		cache[set_index][random].time++;
	}
    }
  }
  
else {
  if(strcmp(wrt_pol, "WB")==0){
    for (int i = 0; i < ass; i++) {
        if (cache[set_index][i].tag == tag && cache[set_index][i].valid ==1) {
            check = true;
            // Cache hit
            hits++;
            cache[set_index][i].time ++;
            hit_check =1;
            break;
        } else if (cache[set_index][i].valid ==0) {
            misses++;
            cache[set_index][i].tag = tag;
            cache[set_index][i].valid = 1;
            cache[set_index][i].time++;
            check = true;
            break;
        }
    }
    if(check == false){
    	if(strcmp(rep_pol, "LRU") == 0){
    		int lrui = find_li(cache,set_index);
    		misses++;
    		cache[set_index][lrui].tag = tag;
    		cache[set_index][lrui].valid = 1;
    		cache[set_index][lrui].time++;
    	}
    	else if(strcmp(rep_pol, "FIFO") == 0){
    		int fifo = find_fi(cache,set_index);
    		misses++;
    		cache[set_index][fifo].tag = tag;
    		cache[set_index][fifo].valid = 1;
    		cache[set_index][fifo].time++;
    	
    	}
    	else if (strcmp(rep_pol, "RANDOM") == 0) {
    		// RANDOM replacement policy
    		
    		int random = Random(ass);
    		misses++;
    		cache[set_index][random].tag = tag;
    		cache[set_index][random].valid = 1;
    		cache[set_index][random].time++;
	}
    }
   } 
    if(strcmp(wrt_pol, "WT")==0){
    for (int i = 0; i < ass; i++) {
        if (cache[set_index][i].tag == tag && cache[set_index][i].valid ==1) {
            check = true;
            // Cache hit
            hits++;
            cache[set_index][i].time ++;
            hit_check =1;
            break;
        } else if (cache[set_index][i].valid ==0) {
            misses++;
            
            check = true;
            break;
        }
    }
    if(check == false){
    	misses++;
    }
   } 
  }
}

int find_li(struct set (*cache)[ass], int set_index) {
    int min = cache[set_index][0].time;
    int lrui = 0;

    for (int i = 1; i < ass; i++) {
        if (cache[set_index][i].time < min) {
            min = cache[set_index][i].time;
            lrui = i;
        }
    }

    return lrui;
}
int find_fi(struct set (*cache)[ass], int set_index) {
    int max = cache[set_index][0].time;
    int fifo_index = 0;

    for (int i = 1; i < ass; i++) {
        if (cache[set_index][i].time > max) {
            max = cache[set_index][i].time;
            fifo_index = i;
        }
    }

    return fifo_index;
}

int Random(int assoc) {
if(assoc == 0){
    		return 0;
    		}
    return rand() % assoc;
}
