/* HW6 read cafefully and follow all the instructions/comments
   this program compiles and runs as is although it's not doing much.
   DO NOT CHANGE THE SEED. Changing seed gives a different sequence of
   numbers but we want the same numbers for comparison purposes.

   FLOATING point radix sort requires some substantial changes to this code
   float n, lst[N],tmp[N];	
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define OK 1
#define NOK 0
#define NELM 100000		/* default 100 elements */
//#define N 1048576		/* 2^30 or 1 meg elements  */
//#define N 2097152
//#define N 4194304
//#define N 8388608
//#define N 16777216
//#define N 33554432
#define N 107374182

void selection_sort();
void swap();

void merge_sort();
void msort_recursive();

void int_radix_sort();
void float_radix_sort();
void swap();
void self_check();
void init_flst();
void print_flst();
void self_f_check();

int rand(void);
void srand();
int rand_r();
void init_lst();
void print_lst();

struct timeval gettimeofday();

int n, lst[N], buf[N];

//only need this for float_radix_sort
//I will note that this program ran perfectly in one of my laptop while it gave a compiler error for the other 
//I included a screenshot as a proof 
float flst[N], fbuf[N];


int main(int argc,char **argv) {

  long int del_sec,del_msec;
  struct timeval tv_s,tv_e;

  if (argc>1) n = atoi(argv[1]);
  else n = NELM;
  
  /*
  sorting_choice 
  0: selection sort
  1: merge_sort
  2: int_radix_sort
  3: float_radix_sort
  default: float_radix_sort
  */
  
  int sorting_choice;
  if (argc==3) {
  	sorting_choice=atoi(argv[2]);
  }
  else {
  	sorting_choice=3;
  }
  
  if (sorting_choice==0) {
  	printf("n=%d\n",n);
	printf("Selection Sort\n");
	init_lst(lst,n);
  	
  	gettimeofday(&tv_s, NULL); 
  	selection_sort(lst,n);
  	gettimeofday(&tv_e, NULL);
  	
  //	printf("%d %d\n", tv_e, tv_s);
  	if (n<=100) 
	     print_lst(lst,n);
        self_check(lst,n);
  	
  }
  else if (sorting_choice==1) {
  	printf("n=%d\n",n);
	printf("Merge Sort\n");
	init_lst(lst,n);
  	
  	gettimeofday(&tv_s, NULL); 
  	merge_sort(lst, buf,n);
  	gettimeofday(&tv_e, NULL);
  	
  //	printf("%d %d\n", tv_e, tv_s);
  	if (n<=100) 
	  print_lst(lst,n);
    self_check(lst,n);
  	
  }
  else if (sorting_choice==2) {
  	printf("n=%d\n",n);
	printf("Radix Sort with unsigned int\n");
	init_lst(lst,n);
  	
  	
  	gettimeofday(&tv_s, NULL); 
  	int_radix_sort(lst, buf , n , 8);
  	gettimeofday(&tv_e, NULL); 
  	
  //	printf("%d %d\n", tv_e, tv_s);
  	if (n<=100) 
	  print_lst(lst,n);
    self_check(lst,n);
  }
  else if (sorting_choice==3) {
  	printf("n=%d\n",n);
	printf("Radix Sort with unsigned float\n");
	init_flst(flst,n);

  	gettimeofday(&tv_s, NULL);
  	float_radix_sort(flst, fbuf , n, 8);
  	gettimeofday(&tv_e, NULL);
  	
//	printf("%d %d\n", tv_e, tv_s);
  	if (n<=100) 
	    print_flst(flst,n);
        self_f_check(flst,n);
  }
  




  return 0;
}

void selection_sort(int lst[],int n){
  // fill here
  int i,j, min;
  for (i=0; i<n-1;i++) {
  	min=i;
  	for (j=i;j<n;j++) {
  		if (lst[min]>lst[j]) {
  			min=j;
		}
	}
  	swap(&lst[min], &lst[i]);
  }
}


void swap (int *a, int *b) {
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
	
	
}

void merge_sort(int lst[], int buf[], int n){
  msort_recursive(lst, buf, 0, n-1);
}

//use recursion
void msort_recursive(int lst[], int buf[], int left, int right){
  // fill here
  
  int middle;
  middle = (left+right) / 2;
  //printf("MIDDLE : %d\n", middle);
  if (left<right) {
  	msort_recursive(lst, buf, left, middle);
  	msort_recursive(lst, buf, middle+1, right);
  	//merge
  	int i,j,k, b;
  	i=left;
  	j=middle+1;
  	k=left;
  	b=left;
  	
  	while (i<=middle && j<=right) {
	  if (lst[i] <= lst[j])	{
	  	buf[b++]=lst[i++];
	  }
	  else {
	  	buf[b++]=lst[j++];
	  }
	}
	
  	while (i<=middle) {
  		buf[b++]=lst[i++];
	}
	
  	while (j<=right) {
  		buf[b++]=lst[j++];
	}
	
	//copying all elemnet to lst
	i=right-left+1;
	for (j=0;j<i;j++) {
		lst[k+j]=buf[k+j];
	}
	
  }
}

//fix the bucket size to 256. run 4 passes where each pass processes 8 bits
//use lst and tmp only. do not use any more memory of size n.
void int_radix_sort(int lst[], int buf[], int n, int group) {
  int i,j,mask,buckets;
  int flag,*src,*dst;
  flag=1;
  
  buckets=256;
  int cnt[buckets], map[buckets];
  mask=buckets-1;
  for (i=0; i<32; i=i+group) {
    // set src/dst to lst/buf depending on iter number
    // fill here with what's discussed in class
    // ...
    
	    for (j=0;j<buckets;j++) {
	  	
		  	cnt[j]=0;
	    }
	    
	    
	    //odd-th iteration
	    if (flag==1) {
	    	flag=0;
	    	for (j=0;j<n;j++) {
	    		cnt[(lst[j]>>i)&mask]++;
			}
	        map[0]=0;
			for (j=1;j<buckets;j++) {
				map[j]=map[j-1]+cnt[j-1];
			}  	
	    	for (j=0;j<n;j++) {
	    		buf[map[(lst[j]>>i)&mask]++]=lst[j];
			}
	    	
	    //	printf("odd iter\n");
	    //	print_lst(buf, n);
		}
		//even-th iteration
		else {
			flag=1;
			
			for (j=0;j<n;j++) {
	    		cnt[(buf[j]>>i)&mask]++;
	    		
			}
	        
	        map[0]=0;
			for (j=1;j<buckets;j++) {
				map[j]=map[j-1]+cnt[j-1];
			}  	
	    	
	    	for (j=0;j<n;j++) {
	    		lst[map[(buf[j]>>i)&mask]++]=buf[j];
			}
			
	    //	printf("even iter\n");
		//	print_lst(lst, n);
		}
	}
}

void float_radix_sort(int flst[],int fbuf[], int n, int group) {
  int i,j,mask,buckets;
  int flag;
  flag=1;
  
  buckets=256;
  int cnt[buckets], map[buckets];
  mask=buckets-1;
  
 //  print_flst(flst, n);

  for (i=0; i<32; i=i+group) {
	    for (j=0;j<buckets;j++) {
		  	cnt[j]=0;
	    }
	    if (flag==1) {
	    	flag=0;
	    	for (j=0;j<n;j++) {
	    		cnt[((unsigned int)flst[j]>>i)&mask]++;
		}
	        map[0]=0;
		for (j=1;j<buckets;j++) {
			map[j]=map[j-1]+cnt[j-1];
		}  	    	
	    	for (j=0;j<n;j++) {
	    		fbuf[map[((unsigned int)flst[j]>>i)&mask]++]=flst[j];
		}    	
//		print_flst(fbuf,n);
    	    }
	    else {
		  flag=1;
	  	  for (j=0;j<n;j++) {
	  		  cnt[((unsigned int)fbuf[j]>>i)&mask]++;
  		  }
		  map[0]=0;
	  	  for (j=1;j<buckets;j++) {
  			  map[j]=map[j-1]+cnt[j-1];
		  }  	
  		  for (j=0;j<n;j++) {
  			  flst[map[((unsigned int)fbuf[j]>>i)&mask]++]=fbuf[j];
		  }			
//		  print_flst(flst,n);
	    }
  }
}


void print_lst(int *l,int n){
  int i;
  for (i=0; i<n; i++) {
    printf("%d ",l[i]);
  }
  printf("\n");
}

void init_lst(int *l,int n){
  int i;
  int seed = time(0) % 100;	/* seconds since 1/1/1970 */
  printf ("seed=%d\n", seed);
  srand(1234);			/* SEED */
  for (i=0; i<n; i++) {
    l[i] = rand();
  }
}


void init_flst(float *l, int n) {
    int i;
    int seed = time(0) % 100;	/* seconds since 1/1/1970 */
    printf ("seed=%d\n", seed);
    srand(1234);			/* SEED */
    for (i=0; i<n; i++) {
        l[i] = (float) rand()/RAND_MAX;

    }
}


void print_flst(float *l, int n) {
  int i;
  for (i=0; i<n; i++) {
    printf("%f ",l[i]);
  }
  printf("\n");
}

void self_f_check(float *lst, int n) {
  int i,flag=OK;
  float *lstp;

  lstp = lst;
  for (i=0;i<n-1;i++)
     if (lstp[i] > lstp[i+1]) { flag = NOK; break; }

  if (flag == OK) printf("sorted\n");
  else printf("NOT sorted at %d\n",i);
	
}


void self_check(int *lst,int n) {
  int i,flag=OK,*lstp;

  lstp = lst;
  for (i=0;i<n-1;i++)
     if (lstp[i] > lstp[i+1]) { flag = NOK; break; }

  if (flag == OK) printf("sorted\n");
  else printf("NOT sorted at %d\n",i);
}

/* End of file */
