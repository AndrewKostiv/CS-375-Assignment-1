#include <stdio.h>
#include <stdlib.h>

int findNumLines(FILE *fp);

FILE *srcFP, *destFP;
int numLines, *data;

void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);
int binarySearch(int n, const int S[], int x);

// ========================

// Main

// ========================

int main(int argc, char *argv[])
{
    int i;
    char str[100];
    int *b1_input = (int *)malloc(numLines * sizeof(int));
    int *b2_input = (int *)malloc(numLines * sizeof(int));
    int *b1_size = 0;
    int *b2_size = 0;

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
    data = (int *)malloc(numLines * sizeof(int));

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

    parseData(data, b1_input, b1_size, b2_input, b2_size);

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

void parseData(int *data, int *b1_input, int *b1_size, int *b2_input, int *b2_size)
{
    int i;
    for (i = 0; i < numLines; i++)
    {
        if (data[i] == "//Part B.2")
        {
            b1_size = i;
            break;
        }
        b1_input[i] = data[i];
    }

    for (int j = 0; i < numLines; i++, j++)
    {
        b2_input[j] = data[i];
    }

}