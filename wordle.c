/* wordle.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ResultGreen	1
#define ResultYellow	2
#define ResultRed	4


typedef char Result;

Result *cw(char*, char*);
Result cc(char, int, char*);
bool isin(char, char*);
void Example_print_result(Result*);
int main(int,char**);

bool isin(char c, char* w){
	int i, size;
	size = strlen(w);

	for(i=0; i<size; i++){
		if(w[i]==c){
			return true;
		}
	}
	return false;
}

Result cc(char guess, int idx, char* word){
	char correct;
	correct = word[idx];

	if(guess==correct){
		return ResultGreen;
	}else if(isin(guess, word)){
		return ResultYellow;
	}
	return ResultRed;
}

Result *cw(char* guess, char* word){
	static Result res[5];
	int i;

	for(i=0; i<5; i++){
		res[i] = cc(guess[i], i, word);
	}
	return res;
}

void Example_print_result(Result *res){
	int i;
	for(i=0; i<5; i++){
		switch(res[i]){
			case ResultGreen:
				printf("%s\n", "Green");
				break;
			case ResultYellow:
				printf("%s\n", "Yellow");
				break;
			case ResultRed:
				printf("%s\n", "Red");
				break;
			default:
				printf("Invalid color: %d\n", res[i]);
		}
	}
	return;
}

int main(int argc, char *argv[]){
	char *correct, *guess;
	Result *res;

	if(argc < 3){
		fprintf(stderr, "USAGE: %s CORRECTWORD GUESSWORD\n\n", argv[0]);
		return -1;
	}

	correct = argv[1];
	guess = argv[2];

	res = cw(guess, correct);
	Example_print_result(res);
	
	printf("Wordle game\n");
	return 0;
}



















