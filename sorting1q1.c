#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<string.h>

#define MAX 100000

void swap(int*a,int*b){
int temp=*a;
*a=*b;
*b=temp;
}
void selectionSort(int arr[],int n){
int i,j,min;
for(i=0;i<n;i++){
min=i;
for(j=i+1;j<n;j++)
if(arr[j]<arr[min])
min=j;
swap(&arr[i],&arr[min]);
}
}

//insrtion sort
void insertionSort(int arr[],int n){
int i,key,j;
for(i=1;i<n;i++){
key=arr[i];
j=i-1;

while(j>=0&&arr[j]>key)
arr[j+1]=arr[j--];
arr[j+1]=key;
}
}

//heap sort
void heapify(int arr[],int n,int i){
int largest=i,left=2*i+1,right=2*i+2;

if(left<n&&arr[left]<arr[largest])
largest=left;

if(right<n&&arr[right]<arr[largest])
largest=right;

if(largest!=i){
swap(&arr[i],&arr[largest]);
heapify(arr,n,largest);
}
}
void heapSort(int arr[],int n){
for(int i=n/2-1;i>=0;i--)
heapify(arr,n,i);

for(int i=n-1;i>=0;i--){
swap(&arr[0],&arr[i]);
heapify(arr,i,0);
}
}

//radix sort
int getMax(int arr[],int n){
int max=arr[0];
for(int i=1;i<n;i++)
if(arr[i]>max)max=arr[i];
return max;
}
void countSort(int arr[],int n,int exp){
int output[n];
int count[10]={0};

 for(int i=0;i<n;i++)
 count[(arr[i]/exp)%10]++;
 for(int i=1;i<10;i++)
 count[i]+=count[i-1];
 
 for(int i=n-1;i>=0;i--){
 output[count[(arr[i]/exp)%10]-1]=arr[i];
 count[(arr[i]/exp)%10]--;
 }
 for(int i=0;i<n;i++)
 arr[i]=output[i];
 }
 void radixSort(int arr[],int n) {
 int max=getMax(arr,n);
 for(int exp=1;max/exp>0;exp*=10)
 countSort(arr,n,exp);
 }
 void generateRandomArray(int arr[],int n){
 for(int i=0;i<n;i++)
 arr[i]=rand()%100000;
 }
 //measure time
 void measureTime(void(*sortFunc)(int*,int),int arr[],int n,const char*name){
 int*copy=(int*)malloc(n*sizeof(int));
 memcpy(copy,arr,n*sizeof(int));
 
 clock_t start=clock();
 sortFunc(copy,n);
 clock_t end=clock();
 
 double time_taken=((double)(end-start))/CLOCKS_PER_SEC;
 printf("%s Sort took %f seconds for n=%d\n",name,time_taken,n);
 free(copy);
 }
 
 int main(){
 int n_values[]={1000,5000,10000,20000};
 int num_cases=sizeof(n_values)/sizeof(n_values[0]);
 
 for(int k=0;k<=num_cases;k++){
 int n=n_values[k];
 int*arr=(int*)malloc(n*sizeof(int));
 
 generateRandomArray(arr,n);
 printf("\n-----for n%d-----\n",n);
 
 measureTime(selectionSort,arr,n,"Selection");
 measureTime(insertionSort,arr,n,"Insertion");
 measureTime(heapSort,arr,n,"Heap");
 measureTime(radixSort,arr,n,"Radix");
 
 free(arr);
 }
 return 0;}
