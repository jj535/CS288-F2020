/******************************************************************************
  READ AND FOLLOW THE INSTRUCTIONS.
  Answers that do not follow the instructions will be penalized.


  Problem 2 (State space search, 30 points) Complete the C program below for solving the 15-Puzzle problem. Follow the instructions below. 

  SUBMIT A COMPLETE PROGRAM IN PLAIN TEXT THAT COMPILES, not just the missing part.

  WE WILL COMPILE AND EXECUTE YOUR PROGRAM WITH SAMPLE INITIAL STATES.

  Do not change the global variables and those declared in main()
  Change of these variables will result in zero credit.

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BF 4			/* Branching factor of the search tree */
#define N 4
#define NxN 16

#define DFS 1                   /* depth first search */
#define BFS 2                   /* breadth first search */
#define BEST 3                  /* best first search */
#define BB 4                    /* branch and bound */
#define ASTAR 5                 /* A* search */
#define UNKNOWN 9		/* unknown search strategy */

#define MAX_PATH 100

#define DN 0
#define RT 1
#define UP 2
#define LT 3
#define UK 9

#define F 0
#define G 1
#define H 2
#define P 3

#define TRUE 1
#define FALSE 0

int bb;	  /* strategy in number, see the definition above */
char *aa;	  /* strategy string */

int expand_a_node(),nodes_same(),count(),find_h(),goal_found();
int strcmp();
void print_a_node(),print_nodes();

struct node { int rr[N+1][N];  struct node *next; };

struct node *ss;	/* initial state */
struct node *tt;	/* goal state */

struct node *initialize(),*expand(),*merge(),*merge_using_value(),*filter(),*move(),*append();


int main(int argc,char **argv) {
  int yy = 0;		/* number of iterations */
  int zz = 1;		/* number of nodes generated */

  struct node *uu=NULL;	/* current open */
  struct node *oo=NULL;	/* open */
  struct node *pp=NULL;	/* closed */
  struct node *qq=NULL;	/* successors */

  oo = initialize(argc,argv);

  while (oo) {
    uu=oo; oo=oo->next;
    uu->next=NULL;
    qq=expand(uu);
    qq=filter(qq,oo);
    qq=filter(qq,pp);

    zz=zz+count(qq);
    if (qq) oo=merge(qq,oo,bb);
    uu->next=pp; pp=uu;
    
    if (goal_found(qq,tt)) break;
    yy++;
  }

  printf("%s strategy, %d iterations, %d nodes\n",aa,yy,zz);
  return 0;
} /* end of main */

struct node *expand(struct node *cp) {

  /*
    SUBMIT A COMPLETE PROGRAM IN PLAIN TEXT THAT COMPILES, not just the missing part.

    WE WILL COMPILE AND EXECUTE YOUR PROGRAM WITH MULTIPLE CASES.

    Complete the function.
    Do not change the global variables and those declared in main()
    Change of these variables will result in zero credit.
  */
  int i,j,k,cnt,row,col;
  struct node *succ,*tp;
  succ=NULL;
  for (i=0;i<N;i++) {
         for(j=0;j<N;j++) {
                if (cp->rr[i][j]==0){
                       break;
                }
         }
         if (j<4) break;
  }
  row=i;
  col=j;
  tp=malloc(sizeof(struct node));
  if (row!=3) {
          tp=move(cp,i,j,i+1,j,0);
          succ=append(tp, succ);
  }
  if (col!=3) {
          tp=move(cp,i,j,i,j+1,1);
          succ=append(tp, succ);
  }
  if (row!=0) {
          tp=move(cp,i,j,i-1,j,2);
          succ=append(tp, succ);
  }
  if (col!=0) {
          tp=move(cp,i,j,i,j-1,3);
          succ=append(tp, succ);
  }

  return succ;

}


struct node *move(struct node *cp,int a,int b,int x,int y,int dir) {
  struct node *newp;
  int i,j,g,h,tmp;
  // malloc
  // copy from cp
  // swap two vals
  // compute f,g,h
  // insert the direction that resulted in this node, used for printing path
  newp=malloc(sizeof(struct node));

  for (i=0;i<N;i++) {
          for (j=0;j<N;j++) {
                  newp->rr[i][j]=cp->rr[i][j];
          }
  }

  tmp=newp->rr[a][b];
  newp->rr[a][b]=newp->rr[x][y];
  newp->rr[x][y]=tmp;

  g=cp->rr[4][1];
  g++;
  h=find_h(newp->rr,tt->rr);
  newp->rr[4][0]=g+h;
  newp->rr[4][1]=g;
  newp->rr[4][2]=h;
  newp->rr[4][3]=dir;

  return newp;

}





struct node *filter(struct node *qq,struct node *hp){ 

  /*
    SUBMIT A COMPLETE PROGRAM IN PLAIN TEXT THAT COMPILES, not just the missing part.

    WE WILL COMPILE AND EXECUTE YOUR PROGRAM WITH MULTIPLE CASES.

    Complete the function.
    Do not change the global variables and those declared in main()
    Change of these variables will result in zero credit.
  */


   struct node *lsp,*rsp;   
   struct node *cp;         

   lsp=qq;
   rsp=qq;
   cp=hp;
   while(rsp) {
           cp=hp;
           while(cp&&!nodes_same(cp, rsp)) {
                   cp=cp->next;
           }
           if (cp==NULL) {
                   lsp=rsp;
                   rsp=rsp->next;
           }
        
	   else {
                   if (lsp==rsp) {
                           qq=lsp=rsp=rsp->next;
                   }
                   else {
                           lsp->next=rsp->next;
                           rsp=rsp->next;
                   }
           }
   }

   return qq;

}

/* qq points to successor list
   oo points to open list
   bb refers to strategy in number, see the definition above
 */
struct node *merge(struct node *qq,struct node *oo, int bb) {
	struct node *cccc;
  switch (bb) {
  case DFS: oo = append(oo,qq); break;
  case BFS: oo = append(qq,oo); break;
  default: 
	    if (qq->next == NULL) {
	           oo = merge_using_value(qq,oo,F);	   
	   }
	   else {

		   while (qq) {
		   cccc=qq;
		   qq=qq->next;
		   oo = merge_using_value(qq,oo,F);
		}
	   }
  }
  return oo;
}

struct node *merge_using_value(struct node *qq,struct node *oo,int fgh) {

  /*
    SUBMIT A COMPLETE PROGRAM IN PLAIN TEXT THAT COMPILES, not just the missing part.

    WE WILL COMPILE AND EXECUTE YOUR PROGRAM WITH MULTIPLE CASES.

    Complete the function.
    Do not change the global variables and those declared in main()
    Change of these variables will result in zero credit.
  */


  if (oo == NULL || oo->rr[N][fgh] >= qq->rr[4][fgh]){
    qq->next = oo;
    return qq;
  }

  struct node *coo;
  coo=malloc(sizeof(struct node));
  coo = oo;
  while(coo->next != NULL && coo->next->rr[N][fgh] < qq->rr[4][fgh])
    {
      coo = coo->next;
  }
  qq->next = coo->next;
  coo->next = qq;
  return oo;

}

int goal_found(struct node *cp, struct node *gp){
  while(cp){
    if (nodes_same(cp, gp)) return TRUE;
    cp = cp->next;
  }
  return FALSE;
}

int count(struct node *qq) {
  int cnt=0;
   while (qq) {
      cnt++;
      qq=qq->next;
   }
   return cnt;
}


struct node *append(struct node *ap, struct node *bp) {
  struct node *cp;
  if (bp == NULL) bp = ap;
  else{
    cp = bp;
    while (cp->next) cp = cp->next;
    cp->next = ap;
  }
  return bp;
}

int find_h(int current[N+1][N],int goalp[N+1][N]) {
  int h=0,i,j,k,l;

  for (i=0;i<N;i++) 
    for (j=0;j<N;j++) {
      for (k=0;k<N;k++) {
	for (l=0;l<N;l++) if (current[i][j] == goalp[k][l]) break;
	if (l < N) break;
      }
      h = h + abs(i-k) + abs(j-l);
    }

  return h;
}

int nodes_same(struct node *a,struct node *b) {
   int i,j;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++)
         if (a->rr[i][j] != b->rr[i][j]) return FALSE;

   return TRUE;
}

struct node *initialize(int argc, char **argv){
  int i,j,k,npe,n,idx,gidx;
   struct node *tp;

   tp=(struct node *) malloc(sizeof(struct node));
   idx = 1;
   for (j=0;j<N;j++)
     for (k=0;k<N;k++) tp->rr[j][k]=atoi(argv[idx++]);
   for (k=0;k<N;k++) tp->rr[N][k]=0;	/* set f,g,h of initial state to 0 */
   tp->next=NULL;
   ss=tp;

   aa = argv[idx];

   if (strcmp(aa, "dfs") == 0) bb = DFS;
   else if (strcmp(aa, "bfs") == 0) bb = BFS;
   else if (strcmp(aa, "best") == 0) bb = BEST;
   else if (strcmp(aa, "bb") == 0) bb = BB;
   else if (strcmp(aa, "astar") == 0) bb = ASTAR;
   else bb = UNKNOWN;
   
   tp=(struct node *) malloc(sizeof(struct node));
   gidx = 1;
   for (j=0;j<N;j++)
     for (k=0;k<N;k++) tp->rr[j][k] = gidx++;
   tp->rr[N-1][N-1] = 0;		/* empty tile=0 */
   for (k=0;k<N;k++) tp->rr[N][k]=0;	/* set f,g,h of goal state to 0 */
   tp->next=NULL;
   tt=tp;			/* Local PEs need this */
   //   print_nodes(ss,"initial_state");
   //   printf("str_strategy=%s strategy=%d\n", aa,bb);

  return ss;
}

void print_a_node(struct node *np) {
  int i,j;
  for (i=0;i<N+1;i++) {
    for (j=0;j<N;j++) printf("%2d ",np->rr[i][j]);
    printf("\n");
  }
  printf("\n");
}

void print_nodes(struct node *cp,char name[20]) {
  printf("%s:\n",name);
  while (cp) {
    print_a_node(cp);
    cp=cp->next;
  }
}

/*****************************************************************************
 End of file
*****************************************************************************/
