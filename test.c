#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int p[5][5];
int ch(){
	p[1][1]=1;
	p[1][2]=2;
	return 0;
}


int find_pos(int who, int wch){
	
	int i,j;
	for (i=0; i<5; i++){
		for (j=0; j<5; j++){
			if(p[i][j]==who){
				if(wch==1){
					return i;
				}
				else if(wch==2){
					return j;
				}
			}
		}
	}
	return -1;
	
}


int main(void){
	int u;
	ch();
	u=find_pos(2,2);
	printf("%d",u);
	return 0;
	
}