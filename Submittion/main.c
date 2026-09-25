#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findNumLines(FILE *fp);

FILE *srcFP, *destFP;
int numLines, *data;

void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);
int binarySearch(int n, const int S[], int x);
void parseData(int *data, int *b1_input, int *b1_size, int *b2_input, int *b2_size);
int writeDestFile(FILE *fp);

// ========================

// Main

// ========================

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: progname <input_file> <output_file>");
        exit(0);
    }
    if ((srcFP = fopen(argv[1], "r")) == NULL)
    {
        perror("Error opening input file");
        exit(0);
    }

    char str[100];
    numLines = findNumLines(srcFP);
    int *b1_input = (int *)malloc(numLines * sizeof(int));
    int *b2_input = (int *)malloc(numLines * sizeof(int));
    int b1_size = 0;
    int b2_size = 0;
    // parce input string into 2 arrays
    int is_b1 = 1;
    while (fgets(str, 100, srcFP))
    {
        if (strstr(str, "//Part B.2") == 0)
            is_b1 = 0;
        if (is_b1)
        {
            b1_input[b1_size] = str;
            b1_size++;
        }
        else
        {
            b2_input[b2_size] = str;
            b2_size;
        }
    }

    // write to output
    if ((destFP = fopen(argv[2], "w")) == NULL)
    {
        perror("Error opening output file");
        exit(0);
    }

    writeDestFile(destFP);

    fclose(srcFP);
    fclose(destFP);
}

// ========================

// Utility functions

// ========================

int writeDestFile(FILE *fp)
{
    int i;
    for (i = 0; i < numLines; i++)
        fprintf(fp, "%d\n", data[i] * data[i]);
}

// returns file size as number of lines in the file
int findNumLines(FILE *fp)
{

    int numLines = 0;
    char str[100];

    while (!feof(fp))
    {
        fgets(str, 100, fp);
        numLines++;
    }

    numLines--; // the above increments count even when EOF reached

    if (fseek(fp, 0L, SEEK_SET) == EOF)
    {
        perror("Error while seeking to begining of file");
        exit(0);
    }

    return numLines;
}

void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int leftArr[n1], rightArr[n2];
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
            arr[k] = leftArr[i++];
        else
            arr[k] = rightArr[j++];
        k++;
    }
    while (i < n1)
        arr[k++] = leftArr[i++];
    while (j < n2)
        arr[k++] = rightArr[j++];
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int binarySearch(int n, const int S[], int x)
{
    int low = 0;
    int high = n - 1;
    int mid;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (x == S[mid])
            return mid;
        else if (x < S[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int b1(int *arr[], int n, int *ans_arr[])
{
    // sort the list
    // loop though each element twice to get all pairs
    // for each pair binary search to find if theier is a number equal to the difference of the pairs
    // put the formatted answer into ans_arr
    // return the arr at the end of the loop
    int ans_arr_size = 0;
    mergeSort(arr, 0, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j || (arr[i] - arr[j]) < 0)
                continue;
            ans_arr[ans_arr_size] = binarySearch(n, arr, arr[i] - arr[j]);
            ans_arr_size++;
        }
    }
}

int b2(int *arr[], int n, int x, int *ans_arr[])
{
    // sort the list
    // loop though each element
    // for each element binary search to find the difference between that element and the given int
    // put the formatted answer into ans_arr
    // return the arr at the end of the loop
    mergeSort(arr, 0, n);
    int ans_arr_size = 0;
    for (int i = 0; i < n; i++)
    {
        ans_arr[ans_arr_size] = binarySearch(n, arr, arr[i] - x);
        ans_arr_size++;
    }
}