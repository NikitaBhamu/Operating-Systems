#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100
#define MAX2 100 // max number you will be reading from file

bool is_empty(char** queue, int size){
    //int size = strlen(queue);
    for(int i=0; i<size; i++){
        if(strcmp(queue[i],"X") == 0){
            return false;
        }
    }
   // printf("Hiii nikita\n");
    return true;
}

bool is_present(char** queue, char* ch, int size){
  // int size = strlen(queue);
   for(int i=0; i<size; i++){
       if(strcmp(queue[i],ch) == 0){
           return true;
       }
   }
   return false;
}

int increase_ptr(int p, int page_frames){
    if(p+1 == page_frames){
        return 0;
    }
    return p+1;
}
int first_empty_place(char** frame, int size){
    for(int i=0; i<size; i++){
        if(strcmp(frame[i],"X")==0){
           return i;
        }
    }
    return -1;
}

int least_frequent_index(int* frequency, int size){
    int min = frequency[0];
    int min_index = 0;
    for(int i=0; i<size; i++){
        if(frequency[i]<min){
            min = frequency[i];
            min_index = i;
        }
    }
    return min_index;
}
      
int index_at_which_it_is_present(char** frame, int size, char* ch){
    for(int i=0; i<size; i++){
        if(strcmp(frame[i],ch)==0){
            return i;
        }
    }
    return -1;
}
           
int least_recent_index(int* call_time, int size){
    int min = call_time[0];
    int min_index = 0;
    for(int i=0; i<size; i++){
        if(call_time[i]<min){
            min = call_time[i];
            min_index = i;
        }
    }
    return min_index;
}
           

int no_second_chance_place(int* call_time, int size, int pointer){
    int local_ptr = pointer;
    int n = 0;
    while( n<size ){
        if(call_time[local_ptr] == 0){
            return local_ptr;
        }
        else{
            call_time[local_ptr] = 0;
            local_ptr = increase_ptr(local_ptr,size);
        }
        n++;
    }
    return pointer;
}


           
int no_N_chance_place( int chance, int* call_time, int size, int pointer){
    int local_ptr = pointer;
    int n = 0;
    while( n< (chance-1)*size ){
        if(call_time[local_ptr] == 0){
            return local_ptr;
        }
        else{
            call_time[local_ptr]--;
            local_ptr = increase_ptr(local_ptr,size);
        }
        n++;
    }
    return pointer;
}


bool is_integer(char ch){
  if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9'){
     return true;
  }
  return false;
}

int main(int argc, char* argv[]){
    char* data = argv[1];
    char* algo = argv[2];
    FILE* fp;
    fp = fopen(data,"r");

    char (*ref_str)[MAX];   // changed from array of pointers to pointer of array
    ref_str = (char (*)[])malloc(sizeof(char)*MAX2*MAX); // allot memory else you get segmentation fault as you will be writing to null
    char ch;
    char str[15];
    int ptr = 0;
    int ref_ptr = 0;
    int misses;
    int hits;
        
    int p=0;
    while((ch = fgetc(fp)) != EOF){
       p++;
       if(is_integer(ch)){
          str[ptr] = ch;
          ptr++;
       }
       else{
          if(ptr != 0){
             for(int i=0; i<ptr; i++){
                ref_str[ref_ptr][i] = str[i];
             }
             ref_str[ref_ptr][ptr] = '\0';
             ref_ptr += 1;
             ptr = 0;
          }
       }
    }
    int num_pages = atoi(ref_str[0]);
    int page_frames = atoi(ref_str[1]);
    int size = ref_ptr - 2;
    char (*ref_string)[MAX];
    ref_string = (char (*)[])malloc(sizeof(char)*size*MAX);
    for(int i=0; i<size; i++){
        for(int j=0; j<MAX; j++){
            if(ref_str[i+2][j] == '\0'){
                ref_string[i][j] = ref_str[i+2][j];
                break;
            }
            else{
                ref_string[i][j] = ref_str[i+2][j];
            }
        }
    }
  
    if(strcmp(algo,"FF") == 0){ //First In First Out
        
        int size_ref_str = size;
        char* queue[page_frames];
            for(int i=0; i<page_frames; i++){
                queue[i] = "X";
            }

        misses = 0;
        hits = 0;
        char* ch;
        int first_in = -1;
        int empty_pos = -1;
        int niks =0;
        int itr = 0;
            
        for(int i=0; i<size_ref_str; i++){
            ch = ref_string[i];
            
            if(itr == 0){
                queue[0] = ch;
                first_in = 0;
                if(first_in+1 == page_frames){
                    empty_pos = first_in;
                }
                else{
                    empty_pos = first_in+1;
                }
                misses += 1;
                itr = 1;
            }
            else{
                if(!is_present(queue,ch,page_frames)){
                    niks += 1;
                    if(first_in == empty_pos){
                        queue[empty_pos] = ch;
                        first_in = increase_ptr(first_in,page_frames);
                        empty_pos = increase_ptr(empty_pos,page_frames);
                    }
                    else{
                        queue[empty_pos] = ch;
                        empty_pos = increase_ptr(empty_pos,page_frames);
                    }
                    misses += 1;
                }
                else{
                    hits += 1;
                }
            }
        }
        printf("In FIFO strategy ->\nThe number of misses are : %d\nThe number of hits are : %d\n",misses,hits);
        printf("\n");
    }
    else if(strcmp(algo,"LF") == 0){ //Least Frequently Used
        
        int size_ref_str = size;
        char* frame[page_frames];
        int frequency[page_frames];
        for(int i=0; i<page_frames; i++){
            frame[i] = "X";
            frequency[i] = 0;
        }
        
        misses = 0;
        hits = 0;
        char* ch;
        int present_index;
        int empty_place;
        int least_freq_place;
        for(int i=0; i<size_ref_str; i++){
           ch = ref_string[i];
            //printf("%s : ",ch);
           present_index = index_at_which_it_is_present(frame,page_frames,ch);
           if(present_index != -1){
               frequency[present_index]++;
               hits++;
               //printf("This is a hit\n");
           }
           else{
             empty_place = first_empty_place(frame,page_frames);
             if(empty_place != -1){
                 frame[empty_place] = ch;
                 frequency[empty_place] = 1;
             }
             else{
                 least_freq_place = least_frequent_index(frequency,page_frames);
                 frame[least_freq_place] = ch;
                 frequency[least_freq_place] = 1;
             }
             misses += 1;
               //printf("This is a miss\n");
           }
        }
        printf("In LFU strategy ->\nThe number of misses are : %d\nThe number of hits are : %d\n",misses,hits);
        printf("\n");
        
    }
    else if(strcmp(algo,"LR") == 0){ //Least Recently Used
        
        int size_ref_str = size;
        char* frame[page_frames];
        int call_time[page_frames];
        for(int i=0; i<page_frames; i++){
            frame[i] = "X";
            call_time[i] = -1;
        }
        misses = 0;
        hits = 0;
        char* ch;
        int present_index;
        int empty_place;
        int least_rec_place;
        for(int i=0; i<size_ref_str; i++){
           ch = ref_string[i];
           present_index = index_at_which_it_is_present(frame,page_frames,ch);
           if(present_index != -1){
              call_time[present_index] = i;
              hits++;
           }
           else{
              empty_place = first_empty_place(frame,page_frames);
              if(empty_place != -1){
                 frame[empty_place] = ch;
                 call_time[empty_place] = i;
              }
              else{
                 least_rec_place = least_recent_index(call_time,page_frames);
                 frame[least_rec_place] = ch;
                 call_time[least_rec_place] = i;
              }
               misses += 1;
           }
        }
        printf("In LRU strategy ->\nThe number of misses are : %d\nThe number of hits are : %d\n",misses,hits);
        printf("\n");
        
    }
    else if(strcmp(algo,"CL") == 0){ //Clock
        
        int size_ref_str = size;
        
        char* frame[page_frames];
        int second_chance[page_frames];
        for(int i=0; i<page_frames; i++){
            frame[i] = "X";
            second_chance[i] = 0;
        }
        misses = 0;
        hits = 0;
        char* ch;
        int pointer = 0;
        int present_index;
        int empty_place;
        int place_with_no_second_chance;
                
        for(int i=0; i<size_ref_str; i++){
            ch = ref_string[i];
            present_index = index_at_which_it_is_present(frame,page_frames,ch);
            if(present_index != -1){
               second_chance[present_index] = 1;
               hits++;
            }
            else{
               empty_place = first_empty_place(frame,page_frames);
               if(empty_place != -1){
                  frame[empty_place] = ch;
                  second_chance[empty_place] = 0;
                  pointer = increase_ptr(pointer,page_frames);
               }
               else{
                  place_with_no_second_chance = no_second_chance_place(second_chance, page_frames, pointer);
                  frame[place_with_no_second_chance] = ch;
                  second_chance[place_with_no_second_chance] = 0;
                  pointer = increase_ptr(place_with_no_second_chance,page_frames);
               }
               misses += 1;
            }
        }
        printf("In Clock(Second chance) algorithm strategy ->\nThe number of misses are : %d\nThe number of hits are : %d\n",misses,hits);
        printf("\n");
        
    }
    
    else if(strcmp(algo,"SC") == 0){ //N Chance
        int chance;
        printf("Please enter the N of N-Chance : ");
        scanf("%d",&chance);
        int size_ref_str = size;
        
        char* frame[page_frames];
        int N_chance[page_frames];
        for(int i=0; i<page_frames; i++){
            frame[i] = "X";
            N_chance[i] = 0;
        }
        misses = 0;
        hits = 0;
        char* ch;
        int pointer = 0;
        int present_index;
        int empty_place;
        int place_with_no_chance;
                       
        for(int i=0; i<size_ref_str; i++){
            ch = ref_string[i];
            present_index = index_at_which_it_is_present(frame,page_frames,ch);
            if(present_index != -1){
                if(N_chance[present_index] < chance-1){
                    N_chance[present_index]++;
                }
                else{
                    N_chance[present_index] = chance-1;
                }
                hits++;
            }
            else{
                empty_place = first_empty_place(frame,page_frames);
                if(empty_place != -1){
                    frame[empty_place] = ch;
                    N_chance[empty_place] = 0;
                    pointer = increase_ptr(pointer,page_frames);
                }
                else{
                    place_with_no_chance = no_N_chance_place(chance, N_chance, page_frames, pointer);
                    frame[place_with_no_chance] = ch;
                    N_chance[place_with_no_chance] = 0;
                    pointer = increase_ptr(place_with_no_chance,page_frames);
                }
                misses += 1;
            }
        }
        printf("In N-Chance(N=%d) algorithm strategy ->\nThe number of misses are : %d\nThe number of hits are : %d\n",chance,misses,hits);
        printf("\n");
        
    }
    
    else{
        printf("There is no such policy implemented which you want to test.\n");
        printf("\n");
    }
    
        
    return 0;
}
