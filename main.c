#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define max_bound 5

int p[max_bound][max_bound]; //玩家的位置
int wi[max_bound][max_bound]; //表示擺縱方向的wall
int wj[max_bound][max_bound]; //表示擺橫方向的wall
char buff[max_bound*2+1][max_bound*3+1];//输出缓冲器//当前光标位置
int Now=1;//当前走子的玩家，1代表黑，2代表白
int count;//回合数
int Exiting;//1为当场上无子并按ESC时询问是否退出程序的状态，2为非此状态

int Exit(){
	char i;
	while(1){
		if(Exiting){
			exit(1);
		}
		else{
			printf("確定要退出遊戲？(y/n)\n");
			scanf(" %c",&i);
			if(i=='y'){
				Exiting=1;
			}
			else if(i=='n'){
				break;
			}
			else{
				printf("輸入錯誤，請再試一次");
			}
		}
	}
	return 0;
}

int Initial(){
	memset(p,0,sizeof p);
	memset(wi,0,sizeof wi);
	memset(wj,0,sizeof wj);
	p[2][0]=1;
	p[2][4]=2;
	return 0;
}



int find_pos(int who, int wch){
	int i,j;
	for (i=0; i<max_bound; i++){
		for (j=0; j<max_bound; j++){
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

int flip(int i){
	return (i==1)?2:1;
}

int getstyle(int i,int j){

	if(p[(i-1)/2][(j-2)/4]==1 && (i-1)%2==0 && (j-2)%4==0 ){ 			//print玩家1位置
		printf("1");
	}
	else if(p[(i-1)/2][(j-2)/4]==2 && (i-1)%2==0 && (j-2)%4==0){
		printf("2");
	}
	else if (i%2==0 && j%4==0 ){			    //print棋目
		printf("+");
	}
	else if (i%2==0 && wj[i/2-1][(j-2)/4]){     //print橫向的wall
		printf("B");
	}
	else if (i%2==0){							//print棋格
		printf("-");
	}
	else if (i%2==1 && wi[(i-1)/2][j/4-1]){		//print縱向的wall
		printf("B");
	}
	else if (i%2==1 && j%4==0){					//print棋格
		printf("|");
	}				
	else if (i%2==1){								//print格子內的空隙
		printf(" ");
	}
	return 0;
}

int Display(){
	int i=0;
	int j=0;
	int c;
	
	for(c=1;c<=max_bound;c++){  //print out the index (12345)
		printf("  %d ",c);
		if(c==max_bound){
			printf("\n");
		}
	}

	while(i<=max_bound*2){
		while(j<=max_bound*4){
			getstyle(i,j);
			j++;
		}
		if(i==1){				//print out the index (abcde)
			printf(" A");
		}
		if(i==3){
			printf(" B");
		}
		if(i==5){
			printf(" C");
		}
		if(i==7){
			printf(" D");
		}
		if(i==9){
			printf(" E");
		}
		printf("\n");
		j=0;
		i++;
	}
	return 0;
}

int step_allowed(int i,int j){
	int u1,v1,u2,v2;	//the previous step (u,v) -> (i,j)
	int m=0;
	int n=0;
	
	if(i<0||j<0||i>max_bound-1||j>max_bound-1){		//----step that is out-of-bound is not allowed
		return 0;
	}



	if(Now==1){
		u1=find_pos(1,1);	//現在是誰的turn來判斷
		u2=find_pos(2,1);
		v1=find_pos(1,2);
		v2=find_pos(2,2);
	}
	
	if(Now==2){				//relative player 1 & player 2
		u1=find_pos(2,1);		
		u2=find_pos(1,1);
		v1=find_pos(2,2);
		v2=find_pos(1,2);
	}
	printf("%d %d %d %d\n",u1,v1,u2,v2);

	if((i==u2 && j==v2 )|| (i==u1 && j==v1 )){					//-----不可重疊(neither opponent nor self)
		return 0;
	}

	if(abs(u1-u2)==1 && v1==v2){							//----跳過對手的棋子(同行)
		if(i==u1+2*(u2-u1) && j==v1){								//直接越過的情況
			if(u2-u1>0 && wj[u1][v1]==0 && wj[u2][v2]==0){				//往下跳且沒有牆
				return 1;	
			}
			if(u2-u1<0 && wj[i][j]==0 && wj[u2][v2]==0){				//往上跳且沒有牆
				return 1;
			}
		}
		
		if(u2==i && abs(j-v1)==1 && u2-u1>0 && (wj[u2][v2]==1|| u2==4)){  //往下 落地點遭牆阻擋的情況
			return 1;
		}

		if(u2==i && abs(j-v1)==1 && u2-u1<0 && (wj[u2-1][v2]==1 || u2==0)){	//往上 落地點遭阻擋的情況
			return 1;
		}
	}

	if(abs(v1-v2)==1 && u1==u2){						//-----跳過對手的棋子(同列)
		if(j==v1+2*(v2-v1) && u1==i){							//直接越過的情況
			if(v2-v1>0 && wi[u1][v1]==0 && wi[u2][v2]==0){			//往右跳且沒有牆
				return 1;
			}
			if(v2-v1<0 && wi[i][j]==0 && wi[u2][v2]==0){			//往左跳且沒有牆
				return 1;
			}
		}
		
		if(v2==j && abs(i-u1)==1 && v2-v1>0 && (wi[u2][v2]==1|| v2==4)){  //往右 落地點遭牆阻擋的情況
			return 1;
		}

		if(v2==j && abs(i-u1)==1 && v2-v1<0 && (wi[u2][v2-1]==1 || v2==0)){	//往左 落地點遭阻擋的情況
			return 1;
		}	
	
	}
	
	if(abs(i-u1)>1 || abs(j-v1)>1 || (abs(i-u1)==1 && abs(j-v1)==1 )){        //----只供十字形的移動方式
		
		return 0;
	}
	
	

	if(abs(i-u1)<=1 && abs(j-v1)<=1){        //----只供十字形的移動方式
		
		return 1;
	}

	if( (wi[i][j]==1 || wi[u1][v1]==1) || (wj[i][j]==1 || wj[u1][v1]==1) ){
		return 0;
	}

	return -1;
}

int write_piece(){
	char in[2];
	char temp[10];
	int i;
	int j;
	int cnt=0;
	
	while(1){

		while(1){		//check the length is proper or not

		printf("Please enter the index to indicate where to move:\n");
		scanf(" %s", temp);
		if(strlen(temp)!=2){
			printf("wrong input!\n");
		}
		else{
			in[0]=temp[0];
			in[1]=temp[1];
			break;
		}
	}
	
		if(strlen(temp)==2){		//check the elements are proper or not
		
			if(in[0]=='A'||in[0]=='a'){
				i=0;
				cnt++;
			}
			if(in[0]=='B'||in[0]=='b'){
				i=1;
				cnt++;
			}
			if(in[0]=='C'||in[0]=='c'){
				i=2;
				cnt++;
			}
			if(in[0]=='D'||in[0]=='d'){
				i=3;
				cnt++;
			}
			if(in[0]=='E'||in[0]=='e'){
				i=4;
				cnt++;
			}
			if(in[1]=='1'){
				j=0;
				cnt++;
			}
			if(in[1]=='2'){
				j=1;
				cnt++;
			}
			if(in[1]=='3'){
				j=2;
				cnt++;
			}
			if(in[1]=='4'){
				j=3;
				cnt++;
			}
			if(in[1]=='5'){
				j=4;
				cnt++;
			}
			if(cnt==2 && step_allowed(i,j)==1){				//check whether the move follows the rules
				p[find_pos(Now,1)][find_pos(Now,2)]=0;		//if fullfill all condition update the position
				p[i][j]=Now;
				Now=flip(Now);
				break;
			}
			else{
				cnt=0;
				printf("wrong input!\n");
			}

		}
		if(p[i][j]==1 && cnt==2){
			break;
		}
		
	}
	return 0;
}



int input(){
	char In;
	printf("                                  player %d's turn\n",Now);
	printf("*********************************\n");
	printf("| PLACE THE WALL     ---press p |\n");
	printf("| MOVE THE PIECE        press m |\n");
	printf("*********************************\n");
	while(1){
		scanf(" %c",&In);
		if(In=='m'){
			write_piece();
			break;
		}
		if(In=='p'){
		//	write_wall();
			break;
		}
		else{
			printf("command error please enter again");
		}
	}
	return 0;
}

int main (void){
	Initial();
	while(1){
		Display();
		input();
	}
	return 0;
}