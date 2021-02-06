#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256
#define MAX_FIELDS 5 /* 5 fields: views,user,upload_time,duration,title */

struct clip *build_a_lst();
struct clip *append();
int find_length();
void print_lst();
void split_line();

struct clip {
  int views;
  char *user;
  char *upload_time;
  char *duration;
  char *title;
  struct clip *next;
} *head;

int main(int argc, char **argv) {
  int n;
  head = build_a_lst(*(argv+1));
  /*
   *Here I assumed that the csv file provided is well organized
   *CSV file should have all commas replaced by MY_COMMAS
   *Have all five fields, and only five fields 
   *No extra stuff
   *as the purpose of this assignment, I focused on making structure in C
   *than taking care of outputs that deals with non-regular case. 
   * */
  n = find_length(head);
  printf("%d clips\n",n);
  print_lst(head);		/* prints the table */
  return 0;
}

int find_length(struct clip *hp) {
	int count =0;
	struct clip *cp=hp;

	while (cp->next != NULL) {
		count++;
		cp=cp->next;
	}
	return count;
}

struct clip *build_a_lst(char *fn) {
  FILE *fp;
  struct clip *hp;
  char *fields[MAX_FIELDS];
  char line[LINE_LENGTH];
  int cnt=0;
  hp=NULL;

  // open fn
  // while no more lines
  // read a line
  // split the line into five substrings/int and store them in a struct
  // append - add the struct at the end of the list
  // return the head pointer holding the list
  fp = fopen(fn, "r");

  // here we assume fn is not null 
  // for the sake of this assignment

  while ( fgets (line, LINE_LENGTH, fp) != NULL ) {
	  // printf("%s", line);
	  split_line(fields, line);
	  hp=append(hp,fields);
  }
  fclose(fp);
  return hp;
}

/* fields will have five values stored upon return */
void split_line(char **fields,char *line) {
  int i=0;
  char *token, *delim;
  delim = ",\n";
  /* 
     call strtok(line, delim);
     repeat until strtok returns NULL using strtok(NULL, delim);
     use the routine we wrote in class.
  */
  //printf("%s\n", line);
  //Title
  token = strtok( line, delim );
  //printf("Token: %s\n", token);
  *(fields+4) = token;
//  printf("fields: %s\n", *(fields+4));
  //user
  token = strtok( NULL, delim);  
  //printf("Token: %s\n", token);
  *(fields+1)= token;
//  printf("fields: %s\n", *(fields+1));
  //upload time
  token = strtok( NULL, delim);
  *(fields+2) = token;
//  printf("fields: %s\n", *(fields+2));
  //duration
  token  = strtok( NULL, delim);
  *(fields+3) = token;
 // printf("fields: %s\n", *(fields+3));
  //views
  token = strtok( NULL, delim);
  *fields= token;
//  printf("fields: %s\n", *(fields));
}

/* set five values into a clip, insert a clip at the of the list */
struct clip *append(struct clip *hp,char **five) {
  struct clip *cp,*tp;

  /* 
     malloc tp
     views need to be converted to int using atoi(*five). 
     no malloc needed for int views, provided you converted views to int
     malloc for four fields using malloc(strlen(five[.]))
     strcpy four strings to tp fields
     insert tp at the end of the list pointed by hp
     check if it's the first time or not
     use cp to traverse the list
  */

//  printf("%d\n", atoi(*five));

  tp = malloc(sizeof (struct clip));
   
  tp->views = atoi(*five);
  
//  printf("tp->views: %d\n", tp->views);

  (five)++;
  tp->user = malloc(strlen(*five));
  strcpy( tp->user, *five);
//  printf("tp->users: %s\n", tp->user);

  (five)++;
  tp->upload_time = malloc(strlen(*five));
  strcpy( tp->upload_time, *five);
//  printf("tp->upload_time: %s\n", tp->upload_time);



  (five)++;
  tp->duration = malloc(strlen(*five));
  strcpy( tp->duration, *five);
//  printf("tp->duration: %s\n", tp->duration);



  (five)++;
  tp->title = malloc(strlen(*five)); 
  strcpy( tp->title, *five);
//  printf("tp->title: %s\n", tp->title);


//  tp->next=NULL;

  if (hp == NULL ) {
	  hp=tp;
//	  printf("cp==NULL\n");
  } 
  else {
          cp=hp;
	  while (cp->next != NULL ) {
	    cp=cp->next;
	  }
	  cp->next=tp;
//	  printf("added\n");
  }

//  printf("---------------------------\n");
  return hp;
}

void print_lst(struct clip *cp) {
  /* 
     use a while loop and the statement below to print the list
     printf("%d,%s,%s,%s,%s\n",cp->views,cp->user,cp->id,cp->title,cp->time);
  */
	while (cp->next != NULL) {
               printf("%d,%s,%s,%s,%s\n",cp->views,cp->user,cp->duration,cp->title,cp->upload_time);
	       cp=cp->next;
	}
}

/* End of file */
