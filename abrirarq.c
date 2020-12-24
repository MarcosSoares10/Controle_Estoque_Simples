#include<stdio.h>
FILE *fp;
void abrirarq(){
	fp = fopen("save.db", "r+b");
	if(fp== NULL)
		fp = fopen("save.db", "w+b"); 
}
