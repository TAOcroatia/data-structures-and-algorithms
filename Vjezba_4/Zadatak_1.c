#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BIGRAND ((rand() % 32768) * (rand() % 32768))
#define MULTIPLIER 5000

void arrPrint(int arrOrg[], int arrSize){
    int* arr = arrOrg;

    printf("[ ");
    for (int i = 0; i < arrSize; i++){
        int tmp = arr[i];
        printf("%d", tmp);
        if (i < arrSize - 1){
            printf(", ");
        }
    }
    printf(" ]\n");
}

int cmpInt(const void* a, const void* b){
	return *(int*)a - *(int*)b;
}

void shuffle(int* niz, int n) {
	for (int i = 0; i < n - 1; i++) {
		int j = i + BIGRAND % (n - i);
		int tmp = niz[i];
		niz[i] = niz[j];
		niz[j] = tmp;
	}
}

int* generate(int n) {
	int* niz = (int*)malloc(sizeof(int) * n);
    if(niz == NULL){
        printf("ERROR");
        exit (1);
    }
	niz[0] = 1 + BIGRAND % 3;
	for (int i = 1; i < n; i++)
		niz[i] = niz[i-1] + BIGRAND % 3 + 1;
	shuffle(niz, n);
	return niz;
}

void presjek(int* arr1, int* arr2, int arrSize){
	int startTime = clock();
	//start

	int arrCount = 0;
	int* arr3 = (int*)malloc(sizeof(int) * arrSize);

	for(int i = 0; i < arrSize; i++){
		for(int j = 0; j < arrSize; j++){
			if(arr1[i] == arr2[j]){
				arrCount++;
				break;
			}
		}
	}
	
	//end
	int stopTime = clock();

	double finalTime = (double)(stopTime - startTime) / CLOCKS_PER_SEC;
	printf("presjek: size=%d out=%d time=%f\n\n", arrSize, arrCount, finalTime);
}

void presjek_jedan_sortiran(int* arr1, int* arr2, int arrSize){
	int startTime = clock();
	//start

	int arrCount = 0;

	qsort(arr2, arrSize, sizeof(int), cmpInt);

	for(int i = 0; i < arrSize; i++){
		arrCount += !!bsearch(arr1 + i, arr2, arrSize, sizeof(int), cmpInt);
	}

	//end

	// arrPrint(arr1, arrSize);
	// arrPrint(arr2, arrSize);

	int stopTime = clock();

	double finalTime = (double)(stopTime - startTime) / CLOCKS_PER_SEC;
	printf("presjek_jedan_sortiran: size=%d out=%d time=%f\n\n", arrSize, arrCount, finalTime);
}

void presjek_oba_sortirana(int* arr1, int* arr2, int arrSize){
	int startTime = clock();
	//start

	int arrCount = 0;

	qsort(arr1, arrSize, sizeof(int), cmpInt);
	qsort(arr2, arrSize, sizeof(int), cmpInt);

	for(int i = 0, j = 0; i < arrSize || j < arrSize; i++, j++){
		if(arr1[i] == arr2[j]){
			arrCount++;
		}else if(arr1[i] > arr2[j]){
			i--;
		}else{
			j--;
		}
	}

	//end
	int stopTime = clock();

	double finalTime = (double)(stopTime - startTime) / CLOCKS_PER_SEC;
	printf("presjek_oba_sortirana: size=%d out=%d time=%f\n\n", arrSize, arrCount, finalTime);
}

void presjek_po_indeksima(int* arr1, int* arr2, int arrSize){
	int startTime = clock();

	//start
	
	int arrCount = 0;
	int biggestNum = arr1[0];

	for(int i = 0; i < arrSize; i++){
		if(arr1[i] > biggestNum) biggestNum = arr1[i];
		if(arr2[i] > biggestNum) biggestNum = arr2[i];
	}

	char* arr1Mask = (char*)calloc(biggestNum + 1, sizeof(char));
	char* arr2Mask = (char*)calloc(biggestNum + 1, sizeof(char));

	for(int i = 0; i < arrSize; i++){
		arr1Mask[arr1[i]] = 1;
		arr2Mask[arr2[i]] = 1;
	}

	for(int i = 0; i <= biggestNum; i++){
		if(arr1Mask[i] == 1 && arr2Mask[i] == 1) arrCount++;
	}

	free(arr1Mask);
	free(arr2Mask);

	//end
	int stopTime = clock();

	double finalTime = (double)(stopTime - startTime) / CLOCKS_PER_SEC;
	printf("presjek_po_indeksima: size=%d out=%d time=%f\n\n", arrSize, arrCount, finalTime);
}

int main() {
	srand(time(NULL));

	for(int i = 1 * MULTIPLIER; i <= 30 * MULTIPLIER; i += 3 * MULTIPLIER){
		int* niz1 = generate(i);
		int* niz2 = generate(i);

		presjek(niz1, niz2, i);

		presjek_jedan_sortiran(niz1, niz2, i);

		presjek_oba_sortirana(niz1, niz2, i);

		presjek_po_indeksima(niz1, niz2, i);

		free(niz1);
		free(niz2);
	}

    return 0;
}