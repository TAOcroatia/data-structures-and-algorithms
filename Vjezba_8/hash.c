#include "hash.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define HCONST 3567892

HashTable *NewTable(int size)
{
	// kreira novu hash tablicu (alocira samu strukturu i niz pokaziva�a)

	HashTable* out = (HashTable*)calloc(1, sizeof(HashTable));
	out->table = (Bin**)calloc(size, sizeof(Bin*));
	out->size = size;

	return out;
}

unsigned int hash(char *word)
{
	// od kljuca generira hash kod
	unsigned int key = 0;
	while(*word != '\0')
	{
		key = key*HCONST + *word;
		word++;
	}
	return key;
}

void Insert(HashTable *ht, char *word)
{
	// dodaje novu rijec u listu na odgovarajucem pretincu

	unsigned int pos = hash(word) % ht -> size;

	Bin* outBin = (Bin*)calloc(1, sizeof(Bin));
	outBin->word = (char*)malloc(sizeof(char) * strlen(word) + 1);
	strcpy(word, outBin->word);

	outBin->next = ht->table[pos];
	ht->table[pos] = outBin;

	ht->load++;
}

int Get(HashTable *ht, char *word)
{
	// vraca 0 ili 1 ovisno o tome da li rijec postoji u tablici

	unsigned int pos = hash(word) % ht -> size;
	Bin* myBin = ht->table[pos];

	while (myBin != NULL){
		if (strcmp(word, myBin->word) == 0){
			return 1;
		}
		myBin = myBin->next;
	}

	return 0;
}

void DeleteTable(HashTable *ht)
{
	// brise cijelu hash tablicu (liste na svim pretincima (rijec i element liste), pretince ...)

	for (int i = 0; i < ht->size; i++){
		Bin* myBin = ht->table[i];

		while (myBin != NULL){
			Bin* nextBin = myBin->next;
			free(myBin->word);
			free(myBin);
			myBin = nextBin;
		}
	}

	free(ht);
}