#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "bstree.h"

BSTree NewBSTree()
{
	// Novo prazno stablo
	BSTree out = (BSTree)calloc(1, sizeof(Node));
	return out;
}

void AddNode(BSTree *bst, char *word)
{
	// Rekurzivno se tra�i mjesto za novi �vor u stablu. Ako rije� postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokaziva�.

	if ((*bst) -> word == NULL){
		(*bst) -> word = (char*)malloc(sizeof(char) * strlen(word));
		strcpy((*bst) -> word, word);
		return;
	}

	int res = strcmp((*bst) -> word, word);

	//puts((*bst) -> word);

	if (res == 0){
		return;
	}

	if (res > 0){
		if ((*bst) -> left == NULL){
			(*bst) -> left = NewBSTree();
		}
		AddNode(&((*bst) -> left), word);
	}

	if (res < 0){
		if ((*bst) -> right == NULL){
			(*bst) -> right = NewBSTree();
		}
		AddNode(&((*bst) -> right), word);
	}

}

int BSTHeight(BSTree bst)
{
	// Rekurzivno se prolazi cijelo stablo da bi se prona�la najdu�a grana (visina stabla).
	
	if (bst == NULL){
		return 0;
	}

	int lh = BSTHeight(bst -> left);
	int rh = BSTHeight(bst -> right);

	return lh > rh ? lh + 1 : rh + 1;
}

void PrintBSTree(BSTree bst)
{
	// Ispisuje rije�i u stablu na ekran po abecednom redu.
	// In-order �etnja po stablu (lijevo dijete, �vor, desno dijete)

	if (bst -> left != NULL){
		PrintBSTree(bst -> left);
	}

	printf("%s ", bst -> word);

	if (bst -> right != NULL){
		PrintBSTree(bst -> right);
	}

}

void SaveBSTree(BSTree bst, FILE *fd)
{
	// Snima rije� po rije� iz stabla u tekstualnu datoteku. Rije�i su odvojene razmakom.
	// Pre-order �etnja po stablu (ttenutni �vor pa djeca)

	if (bst == NULL){
		return;
	}

	fwrite(bst -> word, sizeof(char), strlen(bst -> word), fd);
	fputc(' ', fd);

	SaveBSTree(bst -> left, fd);
	SaveBSTree(bst -> right, fd);

}

void DeleteBSTree(BSTree bst)
{
	// Bri�e stablo (string word i sam �vor) iz memorije.
	// Post-order �etnja po stablu (prvo djeca pa trenutni �vor)

	if (bst == NULL){
		return;
	}

	DeleteBSTree(bst -> left);
	DeleteBSTree(bst -> right);

	free(bst);

}

int readWord(FILE *fd, char *buffer)
{
	int c;
	
	do {
		c = fgetc(fd);				
		if(c == EOF)
			return 0;
	} while(!isalpha(c));

	do {
		*buffer = tolower(c);
		buffer++;
		c = fgetc(fd);
		if(c == 146)
			c = '\'';
	} while(isalpha(c) || c == '\'');

	*buffer = '\0';
	return 1;
}

BSTree LoadBSTree(FILE *fd)
{
	// U�itava rije� po rije� iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rije� duplicirati sa strdup().

	BSTree out = NewBSTree();
	char buf[512];

	while(readWord(fd, buf)){
		AddNode(&out, buf);
	}
	
	return out;
}


// char* biggest(BSTree bst, char* word){
// 	char* out = word;

// 	if(bst->left == NULL && bst->right == NULL) return bst->word;

// 	char* tmp;
// 	if(strlen(tmp = bst->word) > strlen(out)) out = tmp;
// 	if(strlen(tmp = bst->word) > strlen(out)) out = tmp;
// 	if(bst->left != NULL && strlen(tmp = biggest(bst->left)) > strlen(out)) out = tmp;
// 	if(bst->right != NULL && strlen(tmp = biggest(bst->right)) > strlen(out)) out = tmp;

// 	return out;
// }

int biggest(BSTree bst){
	int out = 0;

	if(bst->left == NULL && bst->right == NULL) return strlen(bst->word);

	int tmp;
	if(tmp = strlen(bst->word) > out) out = tmp;
	if(bst->left != NULL && ((tmp = biggest(bst->left)) > out)) out = tmp;
	if(bst->right != NULL && ((tmp = biggest(bst->right)) > out)) out = tmp;

	return out;
}