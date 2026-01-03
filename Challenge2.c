#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int is_valid_sequence(char* id_to_check, int sequence_pos, int string_size){
    //To do
    return 0;
}

//If the string of an window of size x has an null char before the runner manages to reach the end of the window the sequence can't be checked
/*int contains_eos(char* checkedString,int window_size){
    if(strlen(checkedString) < window_size){

    }
    int runner = 0;
    while(runner < window_size){
        if(checkedString[runner] == '\0'){
            return 1;
        }
        runner++;
    }
    return 0;
}*/

int check_invalid_id(char* id_to_check){

    int sequence_size = strlen(id_to_check); //If we have an sequence to which the size isn't 0 when mod is done to the total size it is discarded we know that we can only
    int is_even = sequence_size%2;
    int stop_at = sequence_size/2;
    //printf("stop_at value ->%d\n",stop_at);
    int sequence_checker = 0;
    int window_size = 1;
    int window_overflow = 0;
    int is_invalid = 0;
    if(is_even != 0){
        stop_at++;
    }
    int check_for_new_sequence = 0;

    while(window_size != sequence_size){ // 824824824
        char* first_window = (char*)malloc(window_size);
        char* second_window = (char*)malloc(sequence_size);
        
        strncpy(first_window,id_to_check,window_size);

        if(is_even != 0){
            strncpy(second_window,id_to_check+window_size,window_size);
        }else{
            strncpy(second_window,id_to_check+window_size,window_size);
        }
        if(strlen(first_window) == strlen(second_window) && (sequence_size%window_size == 0)){
            if(strcmp(first_window,second_window) == 0){
                //We have an sequence that is equal
                while(window_overflow != 1 && is_invalid != -1){
                    sequence_checker++;
                    if(strcmp(first_window,second_window)==0){
                        is_invalid = 1;
                        //printf("Invalid -> first_windows -> %s | second_window->%s\n",first_window,second_window);
                    }else{
                        is_invalid = -1;
                    }
                    strncpy(second_window,id_to_check+(sequence_checker*window_size),window_size);
                    if(strlen(second_window) < window_size){
                        window_overflow = 1;
                    }
                }
            }
        }
        
        if(is_invalid == 1){
            //printf("Window_size -> %d, sequence_checker -> %d,first_window ->%s second_window -> %s\n",window_size,sequence_checker,first_window, second_window);
            return -1;
        }

        is_invalid = 0;
        sequence_checker = 0;
        window_overflow = 0;
        
        window_size++;
    }

    return 1;
    //We should probably keep going in the id_to_check until we get and reptition of the sequence, check if the size is good and then 

    //Basicamente temos de ver quando um padrão acontece e se este é sempre igual para a formulação do número



    /*char *buffer = (char*)malloc(sizeof(char)*strlen(id_to_check));
    //sprintf(buffer,"%lld", id_to_check);
    
    int buffer_size = strlen(id_to_check);
    //printf("%d\n",buffer_size);
    if(buffer_size % 2 != 0){
        return 1;
    }else{
        buffer_size = buffer_size/2;
    }
    char buffer_half1[buffer_size+1];
    char buffer_half2[buffer_size+1];
    buffer_half1[buffer_size] = '\0';
    buffer_half2[buffer_size] = '\0';

    memmove(buffer_half1,id_to_check,buffer_size);
    memmove(buffer_half2,id_to_check+buffer_size,buffer_size);*/

    /*if(strcmp(buffer_half1,buffer_half2) == 0){
        //printf("Equal %lld\n",id_to_check);
        return -1;
    }
    return 1;*/
}

long long read_line_check_line(int file_fp){
    
    char buffer[1024];
    ssize_t read_size = 0;
    ssize_t hifen_pos = 0;
    ssize_t reached_EOF = 1;
    long long value_invalid_id = 0;

    while(reached_EOF != 0){

        //printf("EOF->%ld\n",reached_EOF);
        
        while(((reached_EOF = read(file_fp,&buffer[read_size],1)) != 0) && buffer[read_size] != ','){
            if(buffer[read_size] == '-'){
                hifen_pos = read_size;
            }
            read_size++;
        }
        buffer[read_size] = '\0';
        buffer[read_size+1] = '\0';

        char *init_value = (char*)malloc(hifen_pos+2);
        init_value[hifen_pos+1] = '\0';
        int second_part_size = read_size-hifen_pos;
        char *end_value = (char*)malloc(second_part_size+2);
        end_value[second_part_size+1] = '\0';
        memmove(init_value,buffer,hifen_pos);
        memmove(end_value,buffer+hifen_pos+1,second_part_size);
        
        printf("start->%s\n",init_value);
        printf("end->%s\n",end_value);

        //long long init_value_int = strtoll(init_value, NULL,10);
        long long end_value_int = strtoll(end_value, NULL,10);
        long long runner_int = strtoll(init_value, NULL,10);
        
        char* runner = (char*)malloc(sizeof(long long));


        while(runner_int != end_value_int+1){
            sprintf(runner,"%lld",runner_int);
            if(check_invalid_id(runner) != 1){
                printf("invalid id -> %lld\n",runner_int);
                value_invalid_id += runner_int;
                //printf("new_value->%lld\n",value_invalid_id);
            }
            runner_int++;
        }
        /*printf("%lld\n",init_value_int);
        printf("%lld\n",end_value_int);
        printf("%lld\n",runner);*/
        memset(buffer,'\0',1024);
        free(init_value);
        free(end_value);
        //free(runner);
        read_size = 0;
    }

    return value_invalid_id;
}

int main(int argc, char* argv[]){

    if(argc < 2){
        perror("Missing input file\n");
    }

    int file_fp = open(argv[1],O_RDONLY,0666);

    if(file_fp == -1){
        perror("Couldn't open file\n");
        return -1;
    }

    printf("%lld\n",read_line_check_line(file_fp));
}