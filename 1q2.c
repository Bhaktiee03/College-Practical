#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void swap(int*a,int*b)
{
int temp=*a;
*a=*b;
*b=temp;
}
int partition(int arr[],int low,int high){
int pivot=arr[high];
int i=low-1;

for(int j=low;j<high;j++){
if (arr[j]<pivot){
i++;
swap(&arr[i],&arr[j]);
}
}
swap(&arr[i+1],&arr[high]);
return i+1;
}
//quick sort
void quickSort(int arr[],int low,int high){
if(low<high){
int pi=partition(arr,low,high);

quickSort(arr,low,pi-1);
quickSort(arr,pi+1,high);
}
}

void generateRandomArray(int arr[],int n){
for(int i=0;i<n;i++)
arr[i]=rand()%100000;

void measureQuickSortTime(int arr[],int n){
int*copy=(int*)malloc(n*sizeof(int));
memcpy(copy,arr,n*sizeof(int));

clock_t start=clock();
quickSort(copy,0,n-1);
clock_t end=clock();

double time_taken=(double)(end-start)/CLOCKS_PER_SEC;
printf("Quick Sort took %f seconds for n=%d\n",time_taken,n);
free(copy);
}

int main(){
srand(time(0));

int n_values[]={1000,5000,10000,20000,50000};
int num_cases=sizeof(n_values)/sizeof(n_values[0]);

for(int i=0;i<num_cases;i++){
int n=n_values[i];
int*arr=(int*)malloc(n*sizeof(int));
generateRandomArray(arr,n);

printf("\n----for n=%d----\n",n);
measureQuickSortTime(arr,n);

free(arr);
}
return 0;
}

