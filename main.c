#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_array(int* arr, int n) {
    //extra memory - accessory array
    int* ascending_numbers = (int*)malloc(n * sizeof(int));
    /*first, I generate random values*/
    for (int i = 0; i < n; i++) {
        ascending_numbers[i] = rand() % 10000 + 1;
    }
    /*Now, I sort the accessory array with a naive bubblesort*/
    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ascending_numbers[i] > ascending_numbers[j]) {
                /*SWAP*/
                int temp = ascending_numbers[j];
                ascending_numbers[j] = ascending_numbers[i];
                ascending_numbers[i] = temp;
            }
        }
    }
    /*Now that I have a sorted size n accessory array I copy past the values to arr*/
    for (int i = 0; i < n; i++) {
        arr[i] = ascending_numbers[i];
    }
    /*Now that the values has been copied, I free the accessory array*/
    free(ascending_numbers); 
}
int arrayIsValid(int arr[],int M, int n){
    int numOfZeros = 0;
    int positiveOrdered = 1;//assume true
    for (int i = 0; i < n-1; i++) {
        if (arr[i] > arr[i + 1]) {
            positiveOrdered = 0;
            break;
        }
    }
    int zerosFlag = 1;
    for (int i = n; i < M; i++) {
        if (arr[i] != 0) {
            zerosFlag = 0;
            break;
        }
        numOfZeros++;
    }
    return positiveOrdered * zerosFlag *(1-(n-numOfZeros));
}
void printArray(int arr[], int M) {
    for (int i = 0; i < M; i++) {
        if (i % 100 == 0) {
            printf("\n\n");
        }
        printf("%d ", arr[i]);
    }
}
int f1(int arr[],int M,int x,int* n1) {
    (*n1) = 0;
    int val;
    for (int i = 0; i < M; i++) {
        //Technically, each and every time we enter the loop, it is a comparison,
        //so I counted that too.
        (*n1)++;//for the for condition
        val = arr[i];
        (*n1)++;//for the if bellow
        /*THIS line here assures time-complexity O(n), since
        the first zero appearing siginifes that we reached the number n*/
        if (val == 0) {
            return -1;
        }
        (*n1)++;//for the if bellow
        if (val == x) {
            return i;
        }
    }
}
int f2(int arr[], int M, int x, int* n2) {
    int start_index = 0;//1 in psuedo-code
    int end_index = M - 1;//M in psuedo-code
    int mid_index;
    (*n2)=1;//for the initial comparision of the while loop. the cmp happens anyway.
    while (start_index <= end_index) {
        mid_index = (int)((start_index + end_index) / 2);//0.5 will disappear, since mid_index is int.
        /*COND3: if it is a match, returns the index.
        this prevents further checks.*/

        (*n2)++;//for the condition bellow
        if (arr[mid_index] == x) {
            return mid_index;
        }

        /*if we reached the zeros it means we are to the right of where the number may be found
        int the sorted array, if it does appear in the array.
        Same if we reached an index where all the values are bigger than x.
        Thus, we need next iteration to go to the left half.*/

        (*n2)++;//for the condition bellow
        if(arr[mid_index]==0 || arr[mid_index] > x) {
            end_index = mid_index - 1;
        }
        /* like in regular binary search, if at the index mid_index the value is
        smaller, it means all the numbers left of it as well will be smaller, thus we need to go
        to the right half.*/
        (*n2)++;//for the condition bellow
        if (arr[mid_index]!=0 && arr[mid_index] < x) {
            start_index = mid_index + 1;
        }
        (*n2)++;//for the next cmp that happens in the while
    }
    /* if COND3 would have been met even 1 time, it means
    that the number was found, thus the return instruction
    would have prevented us from reaching here.
    Since that didn't happen, we can deduce that the number x is NOT in the array*/
    return -1;
}

int checkIfOneNeighbourIsTheSame(int arr[], int i,int n) {
    int flag = 0;
    if (i < 0) {
        return flag;
    }
    if (i > 0 && arr[i - 1] == arr[i]) {
        flag = 1;
    }
    if (i < n - 1 && arr[i + 1] == arr[i]) {
        flag = 1;
    }
    return flag;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    int validCount = 0;
    int num_arrays = 200;
    int timesFound = 0;
    int input_array[1000];
    int totalCmp1 = 0;
    int totalCmp2 = 0;
    for (int j = 0; j < num_arrays; j++) {
        int n = rand() % 101 + 150;
        generate_random_array(input_array, n);
        for (int i = n; i < 1000; i++) {
            input_array[i] = 0;
        }
        if (!arrayIsValid(input_array,1000,n)) {
            printf("\nARRAY NOT VALID\n");
            return -1;
        }
        
        int randomNum = rand() % 10000 + 1;
        int numOfComparisons1 = 0;
        int numOfComparisons2 =0;
        int numOfComparisons3 =0;
        int res1 = f1(input_array, 1000, randomNum,&numOfComparisons1);
        int res2 = f2(input_array, 1000, randomNum,&numOfComparisons2);
        totalCmp1 += numOfComparisons1;
        totalCmp2 += numOfComparisons2;
        printf("\nnumOfComparisons1 = %d,totalCmp1 = %d, n= %d", numOfComparisons1, totalCmp1,n);
        printf("\nnumOfComparisons2 = %d,totalCmp1 = %d, n= %d\n", numOfComparisons2, totalCmp2,n);
        if (res1 != res2) {
            printf("res1 is %d, while res2 is %d", res1, res2);
            if(res1>=0){
                if (checkIfOneNeighbourIsTheSame(input_array, res1, n)) {
                    printf("\n res1 neighbour is the same");
                }
                else {
                    printf("\n res1no duplicates. what does thie mean?");
                }
            }
            if (res2 >= 0) {
                if (checkIfOneNeighbourIsTheSame(input_array, res2, n)) {
                    printf("\n res2 neighbour is the same");
                }
                else {
                    printf("\n res2 no duplicates. what does thie mean?");
                }
            }
        }
        //int randomCell = rand() % n;

        ////MBF stands for Must Be Found, since I asked to search for a value that must be in the array
        //int MBF1 = f1(input_array, 1000, input_array[randomCell]);
        //int MBF2 = f2(input_array, 1000, input_array[randomCell]);
        //if(MBF1!=MBF2){
        //    printf("\nMBF1 = %d and MBF2 = %d", MBF1, MBF2);
        //    if(checkIfOneNeighbourIsTheSame(input_array,MBF1,n)){
        //        printf("\nDuplicates. cehcked with MBF1. should be the same for 2.");
        //        if (checkIfOneNeighbourIsTheSame(input_array, MBF2, n)) {
        //            printf("\nDuplicates. cehcked in 2");
        //        }
        //    }
        //    else {
        //        printf("ERROR");
        //    }
        //}
    }
    //printf("validCOunt = %d", validCount);
    printf("\n\n150<=n<=250");
    float avg1 = totalCmp1 / 200;
    printf("\n\nSearch1:%f", avg1);
    float avg2 = totalCmp2 / 200;
    printf("\n\nSearch2: %f", avg2);
    return 0;
}
