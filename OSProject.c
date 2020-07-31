#include <stdio.h>
#include<stdlib.h>

int getPlaceInPointer(int index,int *BlockSize)
{
     int givIndex=0;
    int i=0;
    while(i<index)
    {
        givIndex=givIndex+BlockSize[i];
        i=i+1;
    }
    if(givIndex!=0)
    {
            givIndex=givIndex+1;
    }
    return givIndex;
}
void  deallocationForFixed(int * UsedBlocks,int  * allocation,int processNo,int n,int m,int *pointer,int *blockSize)
{
    if(processNo <0 || processNo >=n)
        printf("No such process to be deallocated\n");
    int blockNo=allocation[processNo];
        allocation[processNo]=-1;
        UsedBlocks[blockNo]=0;
        int index = getPlaceInPointer(blockNo,blockSize);
        int length=blockSize[blockNo];
        int i=index;
        int j=0;
        while(j<length)
        {
            pointer[i]=-1;
            i=i+1;
            j=j+1;
        }
    
}
void memoryMap(int * pointer,int * blockSize,int length,int * processSize)
{
    int i=0;
    int j=0;
    printf("BLOCK SIZE\t\tPROCESS SIZE\t\t\tPROCESS NO\n");
    while(i<length)
    {
        if(pointer[i] != -1)
        {
            printf("%d\t\t\t\t%d\t\t\t\t%d\n",blockSize[j],processSize[pointer[i]],pointer[i]);
        }
        else
        {
            printf("%d\t\t\t\tNot allocated\t\t\tNot Allocated\n",blockSize[j]);
        }
        i=i+blockSize[j]+1;
        j=j+1;
    }
    printf("\n");
}
int firstFitForFixedPartition(int * blockSize,int  processSize ,int index,int m ,int n,int * allocation,int * UsedBlocks)
{
        int j=0;
        while(j<m)
        {
            if(blockSize[j]>= processSize && UsedBlocks[j]==0 && allocation[index]==-1)
            {
                //allocate the process
                allocation[index]=j;
                UsedBlocks[j]=1;
                return j;
            }
            j=j+1;
        }
    return -1;
}
int worstFitForFixedPartition(int * blockSize,int  processSize ,int index,int m ,int n,int * allocation,int * UsedBlocks)
{
    int max=0;
    int in =-1;
    int i=0;
    while(i<m)
       {
           if(blockSize[i] > max && blockSize[i] >= processSize && UsedBlocks[i]==0 && allocation[index]==-1)
           {
               max=blockSize[i];
               in=i;
           }
           i=i+1;
       }
       if(in !=-1)
       {
           allocation[index]=in;
           UsedBlocks[in]=1;
           return in;
       }
       return -1;
}
int bestFitForFixedPartition(int * blockSize,int  processSize ,int index,int m ,int n,int * allocation,int * UsedBlocks)
{
    int min=10000;
    int in=-1;
    int i=0;
    while(i<m)
    {
        if(blockSize[i] < min && blockSize[i] >= processSize && UsedBlocks[i]==0 && allocation[index]==-1)
        {
            min=blockSize[i];
            in=i;
        }
        i=i+1;
    }
    if(in !=-1)
    {
        allocation[index]=in;
        UsedBlocks[in]=1;
        return in;
    }
    
    return -1;
}
void allocationFixed(int index,int *pointer,int length,int g)
{
    int i=index;
    int j=0;
    while(j<length)
    {
        pointer[i]=g;
        i=i+1;
        j=j+1;
    }
}
int main()
{
    int n;
    int m;
    scanf("%d",&n);
    scanf("%d",&m);
    int * processSize=(int *)malloc(sizeof(int)* n);
    int i=0;
    while(i<n)
    {
        int temp;
        scanf("%d",&temp);
        processSize[i]=temp;
        i=i+1;
    }
    int * BlockSize=(int *)malloc(sizeof(int)*m);
    int j=0;
    while(j<m)
    {
        int temp;
        scanf("%d",&temp);
        BlockSize[j]=temp;
        j=j+1;
    }
    int count=0;
    int k=0;
    while(k<m)
    {
        count = count + BlockSize[k];
        k=k+1;
    }
    int * pointer=(int * )malloc(sizeof(int)*(count));
    int r1=0;
    while(r1<count)
    {
        pointer[r1]=-1;
        r1=r1+1;
    }
    int *allocation =(int *)malloc(sizeof(int)* n);
    int *UsedBlocks=(int * )malloc(sizeof(int)* m);
    int r=0;
    while(r<m)
    {
        UsedBlocks[r]=0;
        r=r+1;
    }
    k=0;
    while(k<n)
    {
        allocation[k]=-1;
        k=k+1;
    }
    int g=0;
    while(g<n)
    {
        int index=firstFitForFixedPartition(BlockSize, processSize[g],g, m, n,allocation,UsedBlocks);
        if(index==-1)
        {
            g=g+1;
            continue;
        }
        int givIndex=getPlaceInPointer(index,BlockSize);
        allocationFixed(givIndex,pointer,BlockSize[index],g);
        g=g+1;
    }
    
    memoryMap(pointer, BlockSize,count,processSize);
    //worstFitForFixedPartition(BlockSize, processSize, m, n,allocation,UsedBlocks);
    //bestFitForFixedPartition(BlockSize, processSize, m, n,allocation,UsedBlocks);
     deallocationForFixed(UsedBlocks, allocation, 0, 3, 3,pointer,BlockSize);
     memoryMap(pointer, BlockSize,count,processSize);
   // memoryMap( processSize, BlockSize, n, allocation);
}

