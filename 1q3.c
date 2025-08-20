#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void merge(int arr[],int left,int mid,int right){
int i,j,k;
int n1=mid-left+1;
int n2=right-mid;

//temporary arrays
int*L=(int*)malloc(n1*sizeof(int));
int*R=(int*)malloc(n2*sizeof(int));

for(i=0;i<n1;i++)L[i]=arr[left+1];
for(j=0;j<n1;j++)R[j]=arr[mid+1+j];

i=0;
j=0;
k=left;

while(i<n1&&j<n2){
if(L[i]<=R[j])
arr[k++]=L[i++];
else
arr[k++]=R[j++];
}
while(i<n1)arr[k++]=L[i++];
while(j<n1)arr[k++]=R[j++];

free(L);
free(R);
}
//merge sort
void mergeSort(int arr[],int left,int right){
if(left<right){
int mid=left+(right=left)/2;

mergeSort(arr,left,mid);
mergeSort(arr,mid+1,right);
mergeSort(arr,left,right);
}
}
//generte random array
void generateRandomArray(int arr[],int n){
for(int i=0;i<n;i++)
arr[i]=rand()%100000;
}
//measure time
void measureMergeSortTime(int arr[],int n){
int*copy=(int*)malloc(n*sizeof(int));
memcpy(copy,arr,n*sizeof(int));

clock_t start=clock();
mergeSort(copy,0,n-1);
clock_t end=clock();

double time_taken=(double)(end-start)/CLOCKS_PER_SEC;
printf("Quick Sort took %f seconds for n=%d\n",time_taken,n);
free(copy);
}
int main(){
srand(time(NULL));

int n_values[]={1000,5000,10000,20000,50000};
int num_cases=sizeof(n_values)/sizeof(n_values[0]);

for(int i=0;i<num_cases;i++){
int n=n_values[i];
int*arr=(int*)malloc(n*sizeof(int));

generateRandomArray(arr,n);

printf("\n----for n=%d----\n",n);
measureMergeSortTime(arr,n);

free(arr);
}
return 0;
}

