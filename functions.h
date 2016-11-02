#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int flag = 0;
char ip[1024];

void copy(int x) {
	flag = x;
}

void resetflag(){
	flag = 0;
}

/* functions for head command */

//if user mentions only number of lines and don't mention filename, this funtion reads standard input
void inputlines(int n){
	int i = 0;

	while(i < n){
		scanf("%s", ip );
		printf("%s", ip);
		printf("\n");
		i++;
	}
}

//if user mentions only number of bytes and don't mention filename, this function invokes
void inputbytes(int n){
	int i = 0;
	char ch;	

	while(i < n){
		ch = getchar();
		i++;
		printf("%c", ch);
	}
}

//prints first 'opt' number of lines from file
int nline(char *file, char *opt) {

	FILE *fp;
	int cnt = 0;
	size_t len = 0;
	char *line;

	fp = fopen(file, "r");

	if(fp == NULL){
		printf("\nCan't open %s file !!!\n", file);
		return -1;
	}

	while(getline(&line, &len, fp) != -1){
		cnt++;
		if(cnt > atoi(opt))
			break;

		printf("%s", line);
	}

	fclose(fp);
	return 0;
}

//prints first 'x' bytes from file
int nbyte(char *file, int x) {

	FILE *fp;
	int i = 0;
	char ch;

	fp = fopen(file, "r");
	if(fp == NULL){
		printf("\nCan't open %s file !!!\n", file);
		return -1;
	}

	while(i < x) {
		fread(&ch, 1, 1, fp);
		printf("%c", ch);
		i++;
	}

	fclose(fp);
	return 0;
}

//write or append first 'no' lines from sourcefile src to targetfile target
int copyline(char *src, char *no, char *target) {
	FILE *fp1, *fp2;
	char  ch;
	int i = 0;

	fp1 = fopen(src, "r");

	if(fp1 == NULL){
		printf("\nCan't open %s file !!!\n", src);
		return -1;
	}

	if(flag == 1)
		fp2 = fopen(target, "a");
	else 
		fp2 = fopen(target, "w");

	if(fp2 == NULL){
		printf("\nCan't open %s file !!!\n", target);
		return -1;
	}

	while(i < atoi(no)) {
		fread(&ch, 1, 1, fp1);
		if(ch == '\n')
			i = i + 1;
		fwrite(&ch, 1, 1, fp2);
	}

	resetflag();
	fclose(fp1);
	fclose(fp2);

}

//copy first 'no' bytes from sourcefile src to the targetfile target
int copybyte(char *src, char *no, char *target) {
	FILE *fp1, *fp2;
	char  ch;
	int i = 0;

	fp1 = fopen(src, "r");

	if(fp1 == NULL){
		printf("\nCan't open %s file !!!\n", src);
		return -1;
	}

	if(flag == 2)
		fp2 = fopen(target, "w");
	else 
		fp2 = fopen(target, "a");

	if(fp2 == NULL){
		printf("\nCan't open %s file !!!\n", target);
		return -1;
	}

	while(i < atoi(no)) {
		i++;
		fread(&ch, 1, 1, fp1);
		fwrite(&ch, 1, 1, fp2);
	}

	fclose(fp1);
	fclose(fp2);

}

//implement -z option, print all file
int printfile(char *file){
	FILE *fp;
	char ch;

	fp = fopen(file, "r");

	if(fp == NULL){
		printf("\nCan't open %s file !!!\n", file);
		return -1;
	}

	do{
               ch = fgetc(fp);
               if(ch != EOF)
                       putchar(ch);
        }while(ch != EOF);
	
	fclose(fp);
}

//if user do not mention filename, this function invokes
void input(){

	while(1){
		scanf("%s", ip);
		if(flag != 1){
			printf("%s", ip);
			printf("\n");
		}
	}

	resetflag();
}

