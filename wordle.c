/* wordle.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ResultGreen	1
#define ResultYellow	2
#define ResultRed	4
#define max		1379

typedef char Result;

struct s_words {
	char **arr;
	int n;
};

typedef struct s_words Words;

Result *cw(char*, char*);
Result cc(char, int, char*);
bool isin(char, char*);
void Example_print_result(Result*);
int main(int,char**);
Words readfile(char*);

/*
 * Read wordlist file into 2D array
*/
Words readfile(char *filename){
	char buf[8];
	int i, size;
	FILE *fd;
	
	// Dynamic memory allocation
	static char ret[max][5];
	

	fd = fopen(filename, "r");
	if(!fd){
		perror("fopen");
		Words words = {
			.arr = (char **)0,
			.n = 0
		};
		return words;
	}
	
	// Clean out buffer
	i = 0;
	memset(buf, 0, 8);
	while(fgets(buf, 7, fd)){
		size = strlen(buf);
		
		if(size < 1){
			memset(buf, 0, 8);
			continue;
		}
		// Example: speed\n\0
		// We need to remove \n
		// strlen() => 6
		size--; // Decrement to exclude \n
		buf[size] = 0;
		if(size != 5){
			memset(buf,0,8);
			continue;
		}
		
		ret[i][0] = buf[0];
		ret[i][1] = buf[1];
		ret[i][2] = buf[2];
		ret[i][3] = buf[3];
		ret[i][4] = buf[4];
		
		memset(buf, 0, 8);
		i++;

		if(max <= i){
			break;
		}
	}
	fclose(fd);
	Words words = {
		.arr = (char **)&ret,
		.n = i
	};
	
	return words;
}

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
	int i, size;
	size = strlen(word);
	static Result res[5];

	for(i=0; i<size; i++){
		res[i] = cc(guess[i], i, word);
	}
	return res;
}

void Example_print_result(Result *res){
	int i, size;
	size = strlen(res);
	for(i=0; i<size; i++){
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



















