#include <stdio.h>

#define MAXLINE 1000
#define NUMPOINTERS 100

int getln(char s[], int lim);
void parse(char input[], int size);

int main()
{
	char line[MAXLINE];
	int size;
	while(1) {
		size = getln(line, MAXLINE);
		parse(line, size);
	}
}

int getln(char s[], int lim)
{
	int c, i;
	
	for (i = 0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}


void parse(char input[], int size)
{
	static char ptrs[NUMPOINTERS]; // Brainfuck uses 8-bit memory cells 
	static int i = 0;
	static int loopnums[10];
	int j, loopindex;
	int loopdepth = 0;
	
	for (j = 0; j < size; ++j) {
		switch (input[j])
		{
			case '>':
				++i;
				break;
			
			case '<':
				--i;
				break;
			
			case '+':
				++ptrs[i];
				break;
			
			case '-':
				--ptrs[i];
				break;
			
			case '.':
				putchar(ptrs[i]);
				break;
			
			case ',':
				ptrs[i] = getchar();
				break;
			
			case '[':
				loopindex = i;
				++j;
				int k = 0;
				char loop[100];
				while (input[j] != ']' || loopdepth) {
					loop[k] = input[j];
					switch (input[j]) {
						case '[':
							++loopdepth;
							break;
							
						case ']':
							--loopdepth;
							break;
					}
					++k;
					++j;
				}
				
				while (ptrs[loopindex]) {
					parse(loop, k);
				}
			
				break;
		}
	}
}
