#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>

#define MAX 2000000

void seq(int []);
void par(int []);

void main(int argc,char *argv[])
{
	int arr[MAX];
	int i;

	for(i=0;i<MAX;i++)
		arr[i]=i;

	if(atoi(argv[1])==1)
		seq(arr);
	else if(atoi(argv[1])==0)
		par(arr);
	else{
		perror("wrong command\n");
		exit(1);
	}
}

void seq(int arr[])
{
	int i,num=0;
	long long sum=0;
	struct timeval start_time,end_time;
	gettimeofday(&start_time,NULL);

	for(i=0;i<MAX;i++){
		if(arr[i]%2==0)
			num++;
	}
	printf("total even numbers are :%d\n",num);

	num=0;
	for(i=0;i<MAX;i++){
		if(arr[i]%2==1)
			num++;
	}
	printf("total odd numbers are :%d\n",num);

	for(i=0;i<MAX;i++){
		if(arr[i]%2==0)
			sum+=arr[i];
	}
	printf("sum of even numbers is :%lld\n",sum);

	sum=0;
	for(i=0;i<MAX;i++){
		if(arr[i]%2==1)
			sum+=arr[i];
	}
	printf("sum of odd numbers is :%lld\n",sum);

	gettimeofday(&end_time,NULL);
	double operating_time= (double)(end_time.tv_sec)+(double)(end_time.tv_usec)/1000000.0-(double)(start_time.tv_sec)-(double)(start_time.tv_usec)/1000000.0;

	printf("Elapsed: %f seconds\n",(double)operating_time);
}

void par(int arr[])
{
	int i;
	int pid;
	void parent(int[]),child1(int[]),child2(int []),child3(int []);
	struct timeval start_time,end_time;
	gettimeofday(&start_time,NULL);

	printf("parent pid is %d\n",pid=getpid());
	pid=fork();
	if(pid==0)
		child1(arr);
	pid=fork();
	if(pid==0)
		child2(arr);
	pid=fork();
	if(pid==0)
		child3(arr);
	parent(arr);

	gettimeofday(&end_time,NULL);
	double operating_time=(double)(end_time.tv_sec)+(double)(end_time.tv_usec)/1000000.0-(double)(start_time.tv_sec)-(double)(start_time.tv_usec)/1000000.0;

	printf("Elapsed: %f seconds\n",(double)operating_time);
}

void parent(int arr[])
{
	int i,eNum=0;

	for(i=0;i<MAX;i++){
		if(arr[i]%2==0)
			eNum++;
	}
	printf("pid of parent is %d, the total even numbers are %d\n",getpid(),eNum);
	
	while(wait(0)!=-1);
}

void child1(int arr[])
{
	int i,oNum=0;

	for(i=0;i<MAX;i++){
		if(arr[i]%2==1)
			oNum++;
	}
	printf("pid of 1st child is %d, the total odd numbers are %d\n",getpid(),oNum);

	exit(17);
}

void child2(int arr[])
{
	int i;
	long long eSum=0;

	for(i=0;i<MAX;i++){
		if(arr[i]%2==0)
			eSum+=arr[i];
	}
	printf("pid of 2nd child is %d, sum of even numbers is %lld\n",getpid(),eSum);
	exit(17);
}

void child3(int arr[])
{
	int i;
	long long oSum=0;

	for(i=0;i<MAX;i++){
		if(arr[i]%2==1)
			oSum+=arr[i];
	}
	printf("pid of 3rd child is %d, sum of odd numbers is %lld\n",getpid(),oSum);
	exit(17);
}

