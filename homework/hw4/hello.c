#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void memory_map ( int argc, char **argv) ; 


int main (int argc, char *argv[]) {
memory_map(argc, argv);
return 0;

}

void memory_map(int argc, char **argv) {


	printf("0x000000000000 |------------------------------------|\n");

	printf("               |------------------------------------|\n");
	printf("               |------------------------------------|\n");
	printf("               |---------+--------+--------+--------|\n");

	printf("%p |    00   |   00   |   00   |    %X   | argc\n",&argc, argc);
	printf("               |---------+--------+--------+--------|\n");
	printf("%p |           %p           | argv\n", &argv, argv);


	printf("               |------------------------------------|\n");
	printf("               |------------------------------------|\n");
	printf("               |------------------------------------|\n");

	int i=0;
	while(*argv) {
		printf("%p |           %p           | argv+%X\n",argv,*argv, i); 
		printf("               |------------------------------------|\n");
		argv++;
		i++;



	}

	printf("               |------------------------------------|\n");
	printf("               |------------------------------------|\n");
	printf("               |---------+--------+--------+--------|\n");

	argv-=argc;

	int cnt=0;
	
	char *tmp=*argv;
	while (*argv) {
		while (**argv) {
			if (cnt%4==0) {
				printf("%p | ",tmp );
				tmp+=4;
			}
			printf("%X (%c)  |", **argv, **argv);
			(*argv)++;
			cnt++;
			if(!(**argv)) {
				if(cnt%4==0) {
					printf("\n");
					printf("               |---------+--------+--------+--------|\n");
					printf("%p | ", tmp);
					tmp+=4;
				}
				printf("00 (\\0) |");
				cnt++;
			}
			if (cnt%4==0) {
				printf("\n");		
				printf("               |---------+--------+--------+--------|\n");
			}
		}		

		argv++;
		i++;
	}
	for (i=0;i<4-(cnt%4);i++) {
		printf("        |");

	}
	printf("\n");

	printf("               |---------+--------+--------+--------|\n");
	printf("               |------------------------------------|\n");
	printf("               |------------------------------------|\n");

	printf("0xffffffffffff |------------------------------------|\n");
}
