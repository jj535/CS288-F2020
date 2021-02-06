/******************************************************************************
 CS288 HW7 three search strategies: depth, breadth, and intelligent
 command example: command 16 numbers and search strategy

 fifteen 1 2 3 4 5 6 7 8 9 10 11 12 13 14 0 15 {dfs|bfs|astar}
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BF 4			/* Branching factor of the search tree */
#define N 4
#define NxN 16
#define DFS 1                   /* depth first search */
#define BFS 2                   /* breadth first search */
#define BEST 3                  /* best first search */
#define BB 4                    /* branch and bound */
#define ASTAR 5                 /* A* search */
#define UNKNOWN 9		/* unknown search strategy */

#define MAX_PATH 1000

#define DN 0			/* for finding path */
#define RT 1
#define UP 2
#define LT 3
#define UK 9

#define FVAL 0			/* f=g+h, keep it simple for now */
#define GVAL 1
#define HVAL 2
#define PATH 3			/* array index, how it got to this state */

#define TRUE 1
#define FALSE 0

int level,strategy;

int nodes_same(),str_compare(),count(),find_h(), abs();
void swap(),exit_proc(),print_a_node(),print_nodes();
int toggle_dir(), solvable();
void find_path(),print_path(),find_parent();
int path[MAX_PATH],path_buf[MAX_PATH];
void prep_dir_to_str(),dir_to_str();
char *dir_to_sdir[4],strategy_s[10]; /* four directions */

struct node {
  int board[N+1][N];
  struct node *next;
};

struct node *start,*goal;
struct node *initialize(),*expand(),*merge(),*filter(),*move(),*prepend(),*append();
struct node *insert_node(),*check_list(),*goal_found();

int main(int argc,char **argv) {
  int iter,cnt=0,total=1,ocnt=0,ccnt=0;
  int perm;		/* perm=odd=no solution, perm=even=solvable */
  struct node *cp,*open,*closed,*succ,*tp;
  
  open=closed=succ=NULL;
  start=initialize(argc,argv);	/* init initial and goal states */
  perm=solvable(start);		/* check if solvable permutation */
  if (perm & 1) return 1;

  open=start; 
  iter=0;

  while (open) {
    printf("%d: open=%d + clsd=%d = total=%d\n",iter,ocnt,ccnt,ocnt+ccnt);
    ocnt=count(open);
    ccnt=count(closed);
    cp=open; open=open->next; cp->next=NULL; /* get the first node from open */
    succ = expand(cp);			     /* Find new successors */
   // print_nodes(succ, "succ without filter");
    succ = filter(succ,open);		     /* New succ list */
    succ = filter(succ,closed);		     /* New succ list */
   // print_nodes(succ, "succ after filter");
    cnt=count(succ);
    total=total+cnt;
    if (succ) open=merge(succ,open,strategy); /* New open list */
  //  print_nodes(open, "open");
    closed=append(cp,closed);		      /* New closed */
 //   print_nodes(open, "open");
 //   print_nodes(closed, "closed");
 //   print_a_node(cp);
    if ((cp=goal_found(succ,goal))) break;
    iter++;
  }
  printf("%s strategy: %d iterations %d nodes\n",strategy_s,iter+1,total);
  find_path(cp,open,closed);
  return 0;
} /* end of main */

int toggle_dir(int dir){
  int opp_dir;
  // return opp direction
  if (dir%2==1) {
	  opp_dir=4-dir;
  }
  else {
	  if (dir==0) {
	  	 opp_dir=2;
	  }
	  else {
		 opp_dir=0;
	  }	
  }
  return opp_dir;
}

void find_path(struct node *cp,struct node *opnp,struct node *cldp){
  int i,j,dir,opp;
  char *sdir,*opp_sdir;
  int cnt=0,p;
  struct node *tp, *travel;
  //start from the very last node that matches the goal state because
  //that has the direction info
  //toggle the direction, get the parent
  //look for that parent in closed
  //repeat until you find the initial state

  tp=malloc(sizeof(struct node));
  travel=malloc(sizeof(struct node));
  tp=cp;
//  printf("DIR: %d\n", tp->board[4][3]);
 // print_a_node(start);
  while (!nodes_same(tp, start)) {
	 // print_a_node(tp);
	  dir=tp->board[4][3];
	 // printf("cnt :  %d\n", cnt);

	  for (i=0;i<N;i++) {
		  for(j=0;j<N;j++) {
			  if (tp->board[i][j]==0){
				  break;
			  }
		  }
		  if (j!=4) break;
	  }
	  
	  if (dir==0) {
		 opp=2;
		 tp=move(tp,i,j,i-1,j,2);
	  }
	  else if (dir==1) {
		 opp=3;
		 tp=move(tp,i,j,i,j-1,3);
	  }
	  else if (dir==2) {
		 opp=0;
		 tp=move(tp,i,j,i+1,j,0);
	  }
	  else {
		 opp=1;
		 tp=move(tp,i,j,i,j+1,1);
	  } 

	 // print_a_node(tp);
	  
//	  printf("opp DIR before\n");
//	  printf("OPP: %d\n", opp);
	 
	  path[cnt]=opp;
	  cnt++;

	  
	  travel=cldp;
	  while(travel !=NULL) {
		  if (nodes_same(travel, tp)==TRUE) {
			tp->board[4][3]=travel->board[4][3]; 
			break;
		  }
		  
		  travel=travel->next;
	  }
//	  print_a_node(tp);
  }

  char strdir[5][4] = {
	  "DN",
	  "RT",
	  "UP",
	  "LT"
  };
  printf("entering print_path: n=%d\n",cnt);
  for(i=cnt-1;i>=0;i--) {
	  printf("%s ", strdir[toggle_dir(path[i])]);
  }
  printf("\n");
  printf("exiting print_path\n");
  
}

// Expand: generate successors of the current node
struct node *expand(struct node *cp) {
  int i,j,k,cnt,row=0,col;
  struct node *succ,*tp;
  succ=NULL;
  /* check where 0 is. find indices i,j */
  for (i=0;i<N;i++) {
	 for(j=0;j<N;j++) {
		if (cp->board[i][j]==0){
		       break;
		}
	 }
	 if (j!=4) break;
  }	 
  row=i;
  col=j;
  /* DOWN */
  tp=malloc(sizeof(struct node));
  if (row!=3) {
	  tp=move(cp,i,j,i+1,j,0);
	  succ=append(tp, succ);
  }
  /* RIGHT */
  if (col!=3) {
	  tp=move(cp,i,j,i,j+1,1);
	  succ=append(tp, succ);
  }
  /* UP */
  if (row!=0) {
	  tp=move(cp,i,j,i-1,j,2);
	  succ=append(tp, succ);
  }
  /* LEFT */
  if (col!=0) {
	  tp=move(cp,i,j,i,j-1,3);
	  succ=append(tp, succ);
  }
  
  return succ;
}

/* attach at the end */
struct node *append(struct node *tp,struct node *sp) {
  struct node *cp;
  cp=sp;
  if (sp==NULL) {
	  return tp;
  }
  if (tp==NULL) {
	  return sp;
  }
  
  while (cp->next) {
	  cp=cp->next;
  }
  cp->next=tp;

  return sp;
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
		  newp->board[i][j]=cp->board[i][j];
	  }
  }

  tmp=newp->board[a][b];
  newp->board[a][b]=newp->board[x][y];
  newp->board[x][y]=tmp;
  
  g=cp->board[4][1];
  g++;
  h=find_h(newp->board,goal->board);
  newp->board[4][0]=g+h;
  newp->board[4][1]=g;
  newp->board[4][2]=h;
  newp->board[4][3]=dir; 

  return newp;

}

struct node *goal_found(struct node *cp,struct node *gp){
  int flg=FALSE;
  // check if succ list has goal
  // if found, return that for finding path else return NULL
  struct node *tp;
  tp=cp;
  while(tp) {
	  flg=nodes_same(tp,gp);
	  if (flg) {
		  break;
	  }
	  tp=tp->next;
  }

  //will return NULL if it's not found
  return tp;
}

int count(struct node *cp) {
  int cnt=0;
  //return the number of nodes on the list
  struct node *tp;
  tp=cp;
  while (tp) {
	  tp=tp->next;
	  cnt++;
  }
  return cnt;
}

struct node *merge(struct node *succ,struct node *open,int flg) {
  struct node *csucc,*copen;

  if (flg==DFS) {	/* attach in the front: succ -> ... -> open */
	  open=append(open, succ);
  }else if (flg==BFS) {	  /* attach at the end: open -> ... -> succ */
	  open=append(succ, open);
  }
  else{			/* A* search: sort on f=g+h value */
	  if(succ->next == NULL){
	      	  open = insert_node(succ, open);
	  }
	  else{
		  while(succ){
			  copen = succ;
		  	  succ = succ->next;
		  	  open = insert_node(copen,open);
		  }
	  }
  }
  return open;
}


struct node *insert_node(struct node *succ,struct node *open) {
  if (open == NULL || open->board[N][0] >= succ->board[4][0]){
    succ->next = open;
    return succ;
  }

  struct node *copen;
  copen=malloc(sizeof(struct node));
  copen = open;
  while(copen->next != NULL && copen->next->board[N][0] < succ->board[4][0])
    {
      copen = copen->next;
  }
  succ->next = copen->next;
  copen->next = succ;
  return open;
}





int find_h(int current[N+1][N],int goalp[N+1][N]) {
  int h=0,i,j,k,l,done;

  for (i=0;i<N;i++) {
	  for (j=0;j<N;j++) {
		  if (current[i][j]==0) {
			  h+=abs(3-i)+abs(3-j);
		  }
		  else {
		 	  k=(current[i][j]-1)/4;
			  l=(current[i][j]-1)%4;	  
			  h+=abs(k-i)+abs(l-j);
		  }
	  }
  }
  return h;
}

/* a=b=x[N][N] */
int nodes_same(struct node *xp,struct node *yp) {
  int i,j,flg=TRUE;
  for (i=0;i<N;i++) {
	  for (j=0;j<N;j++) {
		  if (xp->board[i][j] != yp->board[i][j]) {
			  return FALSE;
		  }
	  }
  }
  return flg;
}

/******************************************************************************
  Check succ against open and closed. Remove those succ nodes that are in open or closed.
******************************************************************************/
struct node *filter(struct node *succ,struct node *hp){ 
   struct node *lsp,*rsp;	/* lsp=left succ p, rsp=right succ p */
   struct node *cp;		/* temp ptr */
   //...

   lsp=succ;
   rsp=succ;
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
	   //duplicate found
	   else {
		   if (lsp==rsp) {
			   succ=lsp=rsp=rsp->next;
		   }
		   else {
			   lsp->next=rsp->next;
			   rsp=rsp->next;
		   }
	   }
   }

   	return succ;
}

void print_nodes(struct node *cp,char name[20]) {
  int i;
  printf("%s:\n",name);
  while (cp) { print_a_node(cp); cp=cp->next; }
}

void print_a_node(struct node *np) {
  int i,j;
  if (np==NULL) {
	  printf("NULL\n");
  }
  else {
  for (i=0;i<N+1;i++) {
    for (j=0;j<N;j++) printf("%2d ",np->board[i][j]);
    printf("\n");
  }
  printf("\n");
  }
}

//cnt=odd -> no solution, cnt=even=solvable
int solvable(struct node *cp) {
  int i,j,k=0,lst[NxN],cnt=0;
  //flatten the board in to flat lst and work with that
  for (i=0;i<N;i++) {
	  for (j=0;j<N;j++) {

		  if (cp->board[i][j]==0) {
			  k=i;
		  }
		  lst[cnt++]=cp->board[i][j];
	  }
  }
  cnt=0;
  for (i=0;i<NxN-1;i++) {
	  for (j=i+1;j<NxN;j++) {
		  if (lst[j] && lst[i] && lst[i] > lst[j]) {
			  cnt++;
		  }
	  }
  }
  return k%2? cnt: cnt+1;	/* return the number we discussed in class today 3/31/2015*/
}

/* fif 0 1 2 4 5 6 3 8 9 10 7 12 13 14 11 15 astar */
struct node *initialize(int argc, char **argv){
  int i,j,k,npe,n,idx,gidx,inv;
   struct node *tp;

   tp=(struct node *) malloc(sizeof(struct node));
   idx = 1;
   for (j=0;j<N;j++)
     for (k=0;k<N;k++) tp->board[j][k]=atoi(argv[idx++]);
   for (k=0;k<N;k++) tp->board[N][k]=0;	/* set f,g,h of initial state to 0 */
   tp->next=NULL;
   start=tp;

   printf("init state: \n");
   print_a_node(start);

   tp=(struct node *) malloc(sizeof(struct node));
   gidx = 1;
   for (j=0;j<N;j++)
     for (k=0;k<N;k++) tp->board[j][k] = gidx++;
   tp->board[N-1][N-1] = 0;		/* empty tile=0 */
   for (k=0;k<N;k++) tp->board[N][k]=0;	/* set f,g,h of goal state to 0 */
   tp->next=NULL;
   goal=tp;

   printf("goal state: \n");
   print_a_node(goal);

   strcpy(strategy_s,argv[idx]);
   if (strcmp(strategy_s,"dfs")==0) strategy=DFS;
   else if (strcmp(strategy_s,"bfs")==0) strategy = BFS;
   else if (strcmp(strategy_s,"best")==0) strategy=BEST;
   else if (strcmp(strategy_s,"bb")==0) strategy=BB;
   else if (strcmp(strategy_s,"astar")==0) strategy=ASTAR;
   else strategy=UNKNOWN;
   printf("strategy=%s\n",strategy_s);

   return start;
}

void exit_proc(char *msg){
   printf("Error: %s\n",msg);
   exit(1);
}

/*****************************************************************************
 End of file: fif.c. Fifteen Puzzle, Sequential A* 1 processor version.
*****************************************************************************/
