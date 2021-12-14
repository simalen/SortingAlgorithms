#define _CRT_SECURE_NO_WARNINGS
#include "SortingAlgorithms.h"
#include "Statistics.h"
#include "Array.h"
#include <assert.h>
#include <string.h>

int isImplemented(SortingAlgorithm algorithm)
{
	switch (algorithm)
	{
//        case BUBBLE_SORT:
//        case INSERTION_SORT:
//        case SELECTION_SORT:
//        case QUICK_SORT:
        case MERGE_SORT:
            return 1;
        default:
            return 0;
	}
}

/*Antalet byten i en och samma algoritm kan vara olika beroende p� implementationen. Ibland ligger datat redan p� r�tt plats och d� kan man v�lja att testa det och inte g�ra ett byte (vilket ger extra j�mf�relse) eller s� kan man �nd� g�ra ett byte (med sig sj�lv). F�ljer man de algoritmer som vi g�tt igenom p� f�rel�sningarna exakt s� g�r man en swap �ven p� ett element som ligger p� r�tt plats
 
    N�r du analyserar det data som genereras (result.txt) s� beh�ver du ha detta i �tanke */

/******************************************************************************************/
/* Era algoritmer har: */

void printTheArrayPls(ElementType* arrayToSort, unsigned int size) {
    printf_s("\nArray: [");
    for(int i = 0; i < size; i++) {
        printf_s(" %d ", arrayToSort[i]);
    }
    printf_s("]\n");
}

static void bubbleSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
    printf_s("#=== BUBBLE SORT ===#\n");
    printTheArrayPls(arrayToSort, size);

    int occurrence;
    do {
        occurrence = 0;
        for(int index = 0; lessThan(index+1, size, statistics); index++) {
            unsigned int T;
            if(greaterThan(arrayToSort[index], arrayToSort[index+1], statistics)) {
                swapElements(&arrayToSort[index+1], &arrayToSort[index], statistics);
                occurrence++;
            }
        }
    }while(!equalTo(occurrence, 0, statistics));

    printTheArrayPls(arrayToSort, size);
    printf_s("\n#=== END OF BUBBLE SORT ===#\n");
}

static void insertionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{

}

static void selectionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
    printf_s("#=== SELECTION SORT ===#\n");
    printTheArrayPls(arrayToSort, size);

    int v = 0, indexOfSmallest;
    for(int maxIndex = 0; lessThan(v, size, statistics); maxIndex++) {
        indexOfSmallest = v;
        for(int index = v; lessThan(index, size, statistics); index++)
            if(lessThan(arrayToSort[index], arrayToSort[indexOfSmallest], statistics))
                indexOfSmallest = index;
        swapElements(&arrayToSort[v], &arrayToSort[indexOfSmallest], statistics);
        v++;
    }

    printTheArrayPls(arrayToSort, size);
    printf_s("\n#=== END OF SELECTION SORT ===#\n");
}

void merge(ElementType* arrayToSort, int start, int mid, int end, Statistics* statistics) {
    ElementType* tempArray = malloc(sizeof(ElementType)*(end-start));
    int i = 0, i1 = start, i2 = mid+1;

    while(i1 <= mid && i2 <= end) {
        if(arrayToSort[i1] < arrayToSort[i2]) {
            tempArray[i++] = arrayToSort[i1++];
        }
        else if(arrayToSort[i1] >= arrayToSort[i2]) {
            tempArray[i++] = arrayToSort[i2++];
        }
    }

    if(i1 <= mid) {
        while(i1 <= mid) {
            tempArray[i++] = arrayToSort[i1++];
        }
    }
    else if(i2 <= end) {
        while(i2 <= end) {
            tempArray[i++] = arrayToSort[i2++];
        }
    }
    for(int j = start; j <= end; j++) {
        arrayToSort[j] = tempArray[j-start];
    }
    free(tempArray);
}

void split(ElementType* arrayToSort, int start, int end, Statistics* statistics) {
    if(start == end) return;
    int mid = (start+end)/2;
    split(arrayToSort, start, mid, statistics);
    split(arrayToSort, mid+1, end, statistics);
    merge(arrayToSort, start, mid, end, statistics);
}

static void mergeSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics) {
    printf_s("#=== MERGE SORT ===#\n");
    printTheArrayPls(arrayToSort, size);

    split(arrayToSort, 0, size, statistics);

    printTheArrayPls(arrayToSort, size);
    printf_s("\n#=== END OF MERGE SORT ===#\n");
}

static void quickSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
}

/******************************************************************************************/


char* getAlgorithmName(SortingAlgorithm algorithm)
{
	/* Ar inte strangen vi allokerar lokal for funktionen?
	   Nej, inte i detta fall. Strangkonstanter ar ett speciallfall i C */
	switch (algorithm)
	{
        case BUBBLE_SORT:	 return "  Bubble sort ";
        case SELECTION_SORT: return "Selection sort";
        case INSERTION_SORT: return "Insertion sort";
        case MERGE_SORT:	 return "  Merge sort  ";
        case QUICK_SORT:	 return "  Quick sort  ";
        default: assert(0 && "Ogiltig algoritm!"); return "";
	}
}

// Sorterar 'arrayToSort' med 'algorithmToUse'. Statistik for antal byten och jamforelser hamnar i *statistics
static void sortArray(ElementType* arrayToSort, unsigned int size, SortingAlgorithm algorithmToUse, Statistics* statistics)
{
	if(statistics != NULL)
		resetStatistics(statistics);

	switch (algorithmToUse)
	{
	case BUBBLE_SORT:	 bubbleSort(arrayToSort, size, statistics); break;
	case SELECTION_SORT: selectionSort(arrayToSort, size, statistics); break;
	case INSERTION_SORT: insertionSort(arrayToSort, size, statistics); break;
	case MERGE_SORT:	 mergeSort(arrayToSort, size, statistics); break;
	case QUICK_SORT:	 quickSort(arrayToSort, size, statistics); break;
	default:
		assert(0 && "Ogiltig algoritm!");
	}
}

// Forbereder arrayer for sortering genom att allokera minne for dem, samt intialisera dem
static void prepareArrays(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], const unsigned int sizes[])
{
	assert(isImplemented(algorithm));

	int i;
	int totalArraySize;

	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		totalArraySize = sizeof(ElementType)*sizes[i];
		sortingArray[i].arrayToSort = malloc(totalArraySize);
		memcpy(sortingArray[i].arrayToSort, arrays[i], totalArraySize);

		sortingArray[i].algorithm = algorithm;
		sortingArray[i].arraySize = sizes[i];
		resetStatistics(&sortingArray[i].statistics);
	}
}

// Sorterar arrayerna
static void sortArrays(SortingArray toBeSorted[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		SortingArray* current = &toBeSorted[i];
		sortArray(current->arrayToSort, current->arraySize, current->algorithm, &current->statistics);
	
		if (!isSorted(current->arrayToSort, current->arraySize))
		{
			printf("Fel! Algoritmen %s har inte sorterat korrekt!\n", getAlgorithmName(current->algorithm));
			printf("Resultatet �r: \n");
			printArray(current->arrayToSort, current->arraySize, stdout);
			assert(0); // Aktiveras alltid
		}
	}
}

void printResult(SortingArray sortedArrays[], FILE* file)
{
	assert(file != NULL);

	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		fprintf(file, "%4d element: ", sortedArrays[i].arraySize);
		printStatistics(&sortedArrays[i].statistics, file);
		fprintf(file, "\n");
	}
	fprintf(file, "\n");
}

void sortAndPrint(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], unsigned int sizes[], FILE* file)
{
	assert(file != NULL);

	prepareArrays(sortingArray, algorithm, arrays, sizes);
	sortArrays(sortingArray);
	printResult(sortingArray, file);
}

void freeArray(SortingArray sortingArray[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		if (sortingArray[i].arrayToSort != NULL)
			free(sortingArray[i].arrayToSort);
		sortingArray[i].arrayToSort = NULL;
		sortingArray[i].arraySize = 0;
		resetStatistics(&sortingArray[i].statistics);
	}
}
