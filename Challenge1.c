#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define INIT_POS 50 //The dial starts on 50
#define MAX_VALUE = 99;

struct node{
    int value;
    struct node* next;
    struct node* previous;
};
int code_line_reader(int FP){
    printf("Tagala\n");
    //While we don't hit a \n we will keep reading
    char buffer[1025];
    buffer[1024] = '\0';
    int size_read = 0;
    int return_value = 0;
    while(read(FP,&buffer[size_read],1) && buffer[size_read] != '\n'){
        size_read++;
        printf("%c\n",buffer[size_read]);
    }
    buffer[size_read+1] = '\0';
    
    int to_atoi_helper = 0;
    if(buffer[0] == 'L'){
        printf("Move left\n");
        //We move to the left
        while(buffer[to_atoi_helper] != '\0'){
            buffer[to_atoi_helper] = buffer[to_atoi_helper+1];
            to_atoi_helper++;
        }
        return_value = -atoi(buffer);
    }else if(buffer[0] == 'R'){
        printf("Move right\n");
        //We move to the right
        //buffer[0] = '\0';
        while(buffer[to_atoi_helper] != '\0'){
            buffer[to_atoi_helper] = buffer[to_atoi_helper+1];
            to_atoi_helper++;
        }
        return_value = atoi(buffer);
    }else{
        return 100;
    }
    printf("Return_value -> %d\n", return_value);
    return return_value;
}



struct node* create_vault_node(struct node* prev_node,int vaultKnobValue){

    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->previous = prev_node;
    new_node->value = vaultKnobValue;

    return new_node;
}

struct node* generate_vault_nodes(struct node* vault_head){

    struct node* head = vault_head;
    struct node* temp_head = head;
    struct node* temp;

    //Will return the head at 50
    for(int i = 0; i < 100; i++){
        if(i == 0){
            head->value = i;
        }else{
            temp = (struct node*)malloc(sizeof(struct node));
            temp->value = i;
            temp->previous = temp_head;
            temp_head->next = temp;
            temp_head = temp;
        }
    }
    temp_head->next = head;
    head->previous = temp_head;

    return head;
}


int main(int argc, char* argv[]){

    struct node* Vault_Node = (struct node*)malloc(sizeof(struct node));
    int rotation_value;
    int pass_counter = 0;

    if(argc<2){
        perror("Missing input file\n");
        exit(-1);
    }

    printf("%s\n",argv[1]);

    generate_vault_nodes(Vault_Node);

    int input_file_fp = open(argv[1], O_RDONLY, 0666);

    if(input_file_fp == -1){
        perror("Couldn't open file\n");
        return -1;
    }

    while(Vault_Node->value != 50){
        Vault_Node = Vault_Node->next;
    }

    //printf("Vault_Node value = %d\n",Vault_Node->value);

    while((rotation_value = code_line_reader(input_file_fp)) != 100){
        if(rotation_value < 0){
            for(int move_left = 0; move_left != rotation_value; move_left--){
                Vault_Node = Vault_Node->previous;
                if(Vault_Node->value == 0 && move_left-1 != rotation_value){
                    pass_counter++;
                }
            }   
        }else{
            for(int move_right = 0; move_right != rotation_value; move_right++){
                Vault_Node = Vault_Node->next;
                if(Vault_Node->value == 0 && move_right+1 != rotation_value){
                    pass_counter++;
                }
            }
        }
        
        if(Vault_Node->value == 0){
            pass_counter++;
        }

        printf(("Current_Value -> %d\n"),Vault_Node->value);
    }

    close(input_file_fp);

    printf("Password is: %d\n", pass_counter);

    return 0;
}