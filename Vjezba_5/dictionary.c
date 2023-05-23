#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Dictionary create(){
    Dictionary out = (Word*)malloc(sizeof(Word));
    out->word = (char*)""; //add string break char and make c++ compiler not complain
    return out;
}

void add(Dictionary dict, char *str){
    if(dict->count == 0){ //first word case
        dict->word = (char*)malloc(sizeof(char) * strlen(str));
        strcpy(dict->word, str);
        dict->count++;
        return;
    }

    int strRes;

    while((strRes = strcmp(dict->word, str)) < 0 && dict->next != NULL){
        dict = dict->next;
    }

    if(strRes == 0){
        dict->count++;
        return;
    }

    Dictionary tmp = (Dictionary)malloc(sizeof(Word));
    tmp->count = dict->count;
    tmp->word = dict->word;
    tmp->next = dict->next;
    dict->next = tmp;

    dict->count = 1;
    dict->word = (char*)malloc(sizeof(char) * strlen(str));
    strcpy(dict->word, str);

}

void print(Dictionary dict){
    while(dict){
        printf("%d %s\n", dict->count, dict->word);
        dict = dict->next;
    }
}

void destroy(Dictionary dict){
    if(dict->next) destroy(dict->next);
    free(dict->word);
    free(dict);
}

int filter(Word *w){
    int a = w->count > 5;
    int b = w->count < 10;
    int c = strlen(w->word) > 3;
    return a && b && c;
}

Dictionary filterDictionary(Word* indict, int (*filter)(Word *w)){
    while(!(*filter)(indict)){
        Word* tmp = indict;
        indict = indict->next;
        free(tmp->word);
        free(tmp);
    }

    Word* dict = indict;

    while(dict != NULL && dict -> next != NULL){
        if(!(*filter)(dict->next)){
            Word* tmp = dict->next;
            dict->next = dict->next->next;
            free(tmp->word);
            free(tmp);
        }else{
            dict = dict->next;
        }
    }
    return indict;
}