#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (struct event_content*)(0xFFFFFFFFFFFFUL)

struct event_content{
    char *name; //name of event
    int start_time; //unit: hour
    int end_time; //unit: hour
    int remainder; //0: the moment,
                   //1: one hour ago
                   //-1: no remainder
    //maybe add notes function...
    //struct event_content *next; //point to next node
};

struct event_content *hash_table[TABLE_SIZE];

unsigned int hash(char *name){
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for(int i = 0; i < length; i++){
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table(){
    for(int i = 0; i < TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
}

void print_table(){
    printf("Start\n");
    for(int i = 0; i < TABLE_SIZE; i++){
        if(hash_table[i] == NULL){
            printf("\t%d\t---\n", i);
        }else if(hash_table[i] == DELETED_NODE){
            printf("\t%d\t---<deleted>\n", i);
        }else{
            printf("\t%d\t%s\n", i, hash_table[i] -> name);
        }
    }
    printf("End\n");
}

bool hash_table_insert(struct event_content *p){
    if(p == NULL){
        return false;
    }
    int index = hash(p -> name);
    for(int i = 0; i < TABLE_SIZE; i++){
        int try = (i + index) % TABLE_SIZE;
        if(hash_table[try] == NULL || hash_table[try] == DELETED_NODE){
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

struct event_content *hash_table_lookup(char *name){
    int index = hash(name);
    //printf("index: %d\n", index);
    for(int i = 0; i < TABLE_SIZE; i++){
        int try = (i + index) % TABLE_SIZE;
        if(hash_table[try] == NULL){
            return false;
        }
        if(hash_table[try] == DELETED_NODE){
            continue;
        }
        if(strncmp(hash_table[try] -> name, name, TABLE_SIZE) == 0){
            return hash_table[try];
        }
    }
    return NULL;
}

struct event_content *hash_table_delete(char *name){
    int index = hash(name);
    //printf("index: %d\n", index);
    for(int i = 0; i < TABLE_SIZE; i++){
        int try = (i + index) % TABLE_SIZE;
        if(hash_table[try] == NULL){
            return NULL;
        }
        if(hash_table[try] == DELETED_NODE){
            continue;
        }
        if(strncmp(hash_table[try] -> name, name, TABLE_SIZE) == 0){
            struct event_content *tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }
    return NULL;
}

int main(){
    init_hash_table();

    struct event_content aaa = {.name = "aaa"};
    struct event_content bbb = {.name = "bbb"};
    struct event_content ccc = {.name = "ccc"};
    struct event_content ddd = {.name = "ddd"};
    struct event_content eee = {.name = "eee"};
    struct event_content fff = {.name = "fff"};
    struct event_content ggg = {.name = "ggg"};
    struct event_content hhh = {.name = "hhh"};
    struct event_content iii = {.name = "iii"};

    hash_table_insert(&aaa);
    hash_table_insert(&bbb);
    hash_table_insert(&ccc);
    hash_table_insert(&ddd);
    hash_table_insert(&eee);
    hash_table_insert(&fff);
    hash_table_insert(&ggg);
    hash_table_insert(&hhh);
    hash_table_insert(&iii);

    print_table();

    hash_table_delete("aaa");
    struct event_content *tmp = hash_table_lookup("aaa");

    if(tmp == false){
        printf("Not found!\n");
    }else if(tmp == NULL){
        printf("deleted %s\n", tmp -> name);
    }else{
        printf("found %s\n", tmp -> name);
    }

    print_table();



    /*
    printf("111 -> %u\n", hash("111"));
    printf("222 -> %u\n", hash("222"));
    printf("333 -> %u\n", hash("333"));
    printf("444 -> %u\n", hash("444"));
    */
}