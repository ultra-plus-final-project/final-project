#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long MurmurOAAT32(char* key) {
    unsigned long h = 3323198485ul;
    for (; *key; ++key) {
        h ^= *key;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h % TABLE_SIZE;
}

Hashtable* newHashtable() {
    Hashtable* new = (Hashtable*)malloc(sizeof(Hashtable));
    new->length = 0;  // length of a empty table is 0
    new->table = (Element**)malloc(sizeof(Element*) * TABLE_SIZE);
    // let every element of table be "NULL"
    memset(new->table, 0, sizeof(Element*) * TABLE_SIZE);
    return new;
}

void HashtableSet(Hashtable* hashtable, char* key, int value) {
    unsigned long index = MurmurOAAT32(key);

    // check whetyher the key is exist
    Element* position = hashtable->table[index];
    while (position != NULL) {
        if (!strcmp(position->key, key)) {       ////strcmp: 若兩字串相同 則return 0(bool : false), 前方加'!'為negation, false -> true
            break;
        } else {
            position = position->next;
        }
    }

    if (position == NULL) {  // the key is not exist
        Element* new = (Element*)malloc(sizeof(Element));
        char* string = (char*)malloc(strlen(key) + 1);
        new->key = strncpy(string, key, strlen(key) + 1);
        new->value = value;
        new->next = hashtable->table[index];  // insert new data to the first
        hashtable->table[index] = new;
        hashtable->length += 1;
    } else {  // the key has already exist
        position->value = value;
    }
    return;
}

int HashtableGet(Hashtable* hashtable, char* key) {
    int value = -9999;
    unsigned long index = MurmurOAAT32(key);

    // check whetyher the key is exist
    Element* position = hashtable->table[index];
    while (position != NULL) {
        if (!strcmp(position->key, key)) {  // if find the position of the key
            break;
        } else {
            position = position->next;
        }
    }

    if (position != NULL) {
        value = position->value;
        return value;
    } else {
        return value;
    }
}

void HashtableDelete(Hashtable* hashtable, char* key) {
    unsigned long index = MurmurOAAT32(key);

    // check whetyher the key is exist
    Element* prev = NULL;
    // Element* prev = hashtable->table[index];
    Element* position = hashtable->table[index];
    while (position != NULL) {
        if (!strcmp(position->key, key)) {
            break;
        } else {
            prev = position;
            position = position->next;
        }
    }

    if (position != NULL) {
        if (prev == NULL) {
            hashtable->table[index] = position->next;
        } else {
            prev->next = position->next;
        }
        free(position->key);
        free(position);
        hashtable->length -= 1;
        return;
    } else {
        return;
    }
}

void HashtableClear(Hashtable* hashtable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Element* toDelete = hashtable->table[i];
        Element* toDeleteNext = NULL;
        while (toDelete != NULL) {
            toDeleteNext = toDelete->next;
            free(toDelete->key);
            free(toDelete);
            toDelete = toDeleteNext;
        }
        hashtable->table[i] = NULL;
    }
    hashtable->length = 0;
}

ItemArray HashtableGetItems(Hashtable* hashtable) {
    ItemArray array;
    array.items = (Item*)malloc(sizeof(Item) * hashtable->length);
    array.length = hashtable->length;
    int temp = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Element* toAdd = hashtable->table[i];
        while (toAdd != NULL) {
            char* string = (char*)malloc(strlen(toAdd->key) + 1);
            // printf("||||||||||%s\n", toAdd->key);
            array.items[temp].key =
                strncpy(string, toAdd->key, strlen(toAdd->key) + 1);
            array.items[temp].value = toAdd->value;
            toAdd = toAdd->next;
            temp++;
        }
    }
    return array;
}

Hashtable* mergeHashtable(Hashtable* ht1, Hashtable* ht2) {
    Hashtable* new = newHashtable();
    ItemArray ht1_element = HashtableGetItems(ht1);  // get the items of ht1
    for (int i = 0; i < ht1->length; i++) {
        HashtableSet(
            new, ht1_element.items[i].key,
            ht1_element.items->value);  // add new element to the new hashtable
    }
    ItemArray ht2_element = HashtableGetItems(ht2);
    for (int i = 0; i < ht2->length; i++) {
        HashtableSet(
            new, ht2_element.items[i].key,
            ht1_element.items->value);  // add new element to the new hashtable
    }
    return new;
}