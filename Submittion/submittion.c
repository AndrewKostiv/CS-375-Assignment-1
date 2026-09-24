// This program reads an input file of numbers.
// The input file has on number per line.
// The program prints out the squares of the input file numbers
// to the output file.
// The output file has on number per line.

#include <stdio.h>
#include <stdlib.h>

long long findNumLines(FILE *fp);

FILE *srcFP, *destFP;
long long numLines, *data;

// ========================

// Merge Sort

// ========================

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

// ========================

// Binary Search

// ========================

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
// ========================

// Main

// ========================

int main(int argc, char *argv[])
{

    int i;
    char str[100];

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

    numLines = findNumLines(srcFP);

    data = (long long *)malloc(numLines * sizeof(long long));

    for (i = 0; i < numLines; i++)
    {
        fgets(str, 100, srcFP);
        sscanf(str, "%lld", &(data[i]));
    }
    if ((destFP = fopen(argv[2], "w")) == NULL)
    {
        perror("Error opening output file");
        exit(0);
    }

    writeDestFile(destFP);

    fclose(srcFP);
    fclose(destFP);
}

int writeDestFile(FILE *fp)
{
    long long i;
    for (i = 0; i < numLines; i++)
        fprintf(fp, "%d\n", data[i] * data[i]);
}

// returns file size as number of lines in the file
long long findNumLines(FILE *fp)
{

    long long numLines = 0;
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
