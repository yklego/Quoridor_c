#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define max_bound 5

int p[max_bound][max_bound]; //玩家的位置
int wi[max_bound][max_bound-1]; //表示擺縱方向的wall
int wj[max_bound-1][max_bound]; //表示擺橫方向的wall
char buff[max_bound*2+1][max_bound*3+1];
int Now=1;
int count;
int Exiting;
int numwall[2];
#define MAXSTACK 100
int stack[MAXSTACK][2];
int Deway[MAXSTACK][2];
int top=-1;
int dex=0;

//------Stack part------

int isEmpty(){
	return(top==-1)?1:0;
}

int pop(){
	if(isEmpty()){
		return -1;
	}
	else{
		top--;
		return 0;			
	}
}

int push(int arr[2]){
	if(top>=MAXSTACK){
		return -1;
	}
	else{
		top++;
		stack[top][0]=arr[0];
		stack[top][1]=arr[1];
	}
	return 0;
}

int InitialTheStack(){
	memset(stack,0,sizeof stack);
	top=-1;
	return 0;
}

int InitialDeway(){
	memset(Deway,0,sizeof Deway);
	dex=0;
	return 0;
}

int inStack(int i,int j){
	for (int k=0;k<MAXSTACK;k++){
		if(stack[k][0]==i && stack[k][1]==j){
			return 1;
		}
	}
	return 0;
}

int inDeway(int i, int j){
	for (int k=0;k<MAXSTACK;k++){
		if(Deway[k][0]==i && Deway[k][1]==j){
			return 1;
		}
	}
	return 0;
}
//-------------------

int if_win(int i,int j){
	if(Now==1 && i>0 && i<max_bound){
		return(j==4)?1:0;
	}
	if(Now==2 && i>0 && i<max_bound){
		return(j==0)?1:0;
	}
	return -1;
}

int welcome(){
	char start[1];
	printf("        ================================================================================\n");
	printf("       / AAAAAAAA    AA    AA  AAAAAA  AAAAAAAAA  AAAAAA   AAAAAA    AAAAAA  AAAAAAAAA /\n");
	printf("      / AA    AA    AA    AA    AA    AA     AA    AA     A     A   A    A  AA     AA /\n");
	printf("     / AA    AA    AA    AA    AA    AA    AA     AA     A     A   A    A  AA    AA  /\n");
	printf("    / AA    AA    AA    AA    AA    AA  AAA      AA     A      A  A    A  AA  AAA   /\n");
	printf("   / AA  AAAA    AA    AA    AA    AAAAAA       AA     A      A  A    A  AAAAAA    /\n");
	printf("  / AA   AAA    AA    AA    AA    AA   AA      AA     A     A   A    A  AA   AA   /\n");
	printf(" / AA    AAA   AA    AA    AA    AA    AA     AA     A     A   A    A  AA    AA  /\n");
	printf("/ AAAAAAAAAA   AAAAAA   AAAAAA  AA     AA  AAAAAA   AAAAAA    AAAAAA  AA     AA /\n");
	printf("===========AA===================================================================\n\n\n");
	printf("                          ================================\n");
	printf("                         /      Start The Game: Any Key  /\n");
	printf("                        /      Exit The Game:  0        /\n");
    printf("                        ================================\n");
    scanf(" %s",start);
    if(start[0]=='0'){
    	exit(1);
    }
    return 0;
}

int Exit(){
	char i;
	while(1){
		if(Exiting){
			exit(1);
		}
		else{
			printf("Continue？(y/n)\n");
			scanf(" %c",&i);
			if(i=='n'){
				Exiting=1;
			}
			else if(i=='y'){
				break;
			}
			else{
				printf("invalid input. Please try again\n");
			}
		}
	}
	return 0;
}

int InitialTheGame(){
	memset(p,0,sizeof p);
	memset(wi,0,sizeof wi);
	memset(wj,0,sizeof wj);
	p[3][0]=1;
	p[1][4]=2;
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

int winthegame(){
	if(Now==1){						//Determined the condtion that player 1 win the game
		if(find_pos(Now,2)==4){
			return 1;
		}
		else{
			return 0;
		}
	}
	if(Now==2){
		if(find_pos(Now,2)==0){		//for player 2
			return 2;
		}
		else{
			return 0;
		}
	}
	return 0;
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
	else if (i%2==0 && wj[i/2-1][(j-2)/4]==1 && (j-2)%4==0 && i/2-1<=max_bound-2 && (j-2)/4<=max_bound-1 && i>0 && i<max_bound*2){     //print橫向的wall
		printf("Ξ");
	}
	else if (i%2==0){							//print棋格
		printf("-");
	}
	else if (i%2==1 && wi[(i-1)/2][j/4-1]==1 && (i-1)%2==0 && j%4==0 && (i-1)/2<=max_bound-1 && j/4-1<=max_bound-2 && j>0 && j<max_bound*4){		//print縱向的wall
		printf("Ξ");
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
		
		if(u2==i && abs(j-v1)==1 && u2-u1>0 && (wj[u2][v2]==1 || u2==max_bound-1)){  //往下 落地點遭牆阻擋的情況	*** 如果又遭阻擋
			if(j-v1==-1 && wi[i][j]==1){  //left going
				return 0;
			}
			if(j-v1==1 && wi[u2][v2]==1){ 	//right going
				return 0;
			}		
			return 1;
		}

		if(u2==i && abs(j-v1)==1 && u2-u1<0 && (wj[u2-1][v2]==1 || u2==0)){	//往上 落地點遭阻擋的情況
			if(j-v1==-1 && wi[i][j]==1){  //left going
				return 0;
			}
			if(j-v1==1 && wi[u2][v2]==1){ 	//right going
				return 0;
			}
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
		
		if(v2==j && abs(i-u1)==1 && v2-v1>0 && (wi[u2][v2]==1|| v2==max_bound-1)){  //往右 落地點遭牆阻擋的情況  *** 如果又遭阻擋
			if(i-u1==-1 && wj[i][j]==1){  //up going
				return 0;
			}
			if(i-u1==1 && wj[u2][v2]==1){ 	//down going
				return 0;
			}
			return 1;
		}

		if(v2==j && abs(i-u1)==1 && v2-v1<0 && (wi[u2][v2-1]==1 || v2==0)){	//往左 落地點遭阻擋的情況
			if(i-u1==-1 && wj[i][j]==1){  //up going
				return 0;
			}
			if(i-u1==1 && wj[u2][v2]==1){ 	//down going
				return 0;
			}
			return 1;
		}	
	
	}
	
	if(abs(i-u1)>1 || abs(j-v1)>1 || (abs(i-u1)==1 && abs(j-v1)==1 )){        //----只供十字形的移動方式
		
		return 0;
	}
	
	
	if( (abs(i-u1)==1 && abs(j-v1)==0) || (abs(j-v1)==1 && abs(i-u1)==0)){        //----只供十字形的移動方式(double check)

		if(i-u1>0){ 						//i方向移動,向下
			if(wj[u1][v1]==1){					//中間有牆無法通行
				return 0;
			}
		}
		if(i-u1<0){
			if(wj[i][j]==1){				//i方向移動,向上
				return 0;						//中間有牆無法通行
			}
		}
		if(j-v1>0){
			if(wi[u1][v1]==1){				//j方向移動,向右
				return 0;						//中間有牆無法通行
			}
		}
		if(j-v1<0){
			if(wi[i][j]==1){				//j方向移動,向左
				return 0;						//中間有牆無法通行
			}
		}

			return 1;
	}

	printf("%d %d %d %d\n",u1,v1,u2,v2);
	printf("%d %d\n", i,j);
	

	return -1; 			//---return to print the error message (debug)
}

int isPath(int iorj, int i, int j){
	int posarr[2];
	int u1, v1;
	int initi,initj;

	if(iorj==1){
		if(wi[i][j]!=1 && wi[i+1][j]!=1){
			wi[i][j]=1;
			wi[i+1][j]=1;
		}
		else{
			printf("#1\n");
			return -1;			//for debug
		}
	}

	if(iorj==2){
		if(wj[i][j]==0 && wj[i][j+1]==0){
			wj[i][j]=1;
			wj[i][j+1]=1;
		}
		else{
			printf("#2\n");
			return -1;			//for debug
		}
		
	}
	
	u1=find_pos(flip(Now),1);			//判斷對手的位置
	v1=find_pos(flip(Now),2);
	initi=u1;
	initj=v1;



	posarr[0]=u1;
	posarr[1]=v1;
	push(posarr);
	printf("stack:(%d,%d)\n",stack[top][0],stack[top][1]);

	if(Now==1){
		Now=flip(Now);
		while(!isEmpty()){

			if(step_allowed(u1,v1-1) && !inStack(u1,v1-1) && !inDeway(u1,v1-1)){
				p[u1][v1]=0;
				v1--;
				posarr[0]=u1;
				posarr[1]=v1;
				push(posarr);
				p[u1][v1]=Now;
				printf("left stack:(%d,%d)\n",stack[top][0],stack[top][1]);
			}
			else if(step_allowed(u1+1,v1) && !inStack(u1+1,v1) && !inDeway(u1+1,v1)){
				p[u1][v1]=0;
				u1++;
				posarr[0]=u1;
				posarr[1]=v1;
				push(posarr);
				p[u1][v1]=Now;
					printf("down stack:(%d,%d)\n",stack[top][0],stack[top][1]);

			}
			else if(step_allowed(u1-1,v1) && !inStack(u1-1,v1) && !inDeway(u1-1,v1)){
				p[u1][v1]=0;
				u1--;
				posarr[0]=u1;
				posarr[1]=v1;
				push(posarr);
				p[u1][v1]=Now;
					printf("up stack:(%d,%d)\n",stack[top][0],stack[top][1]);

			}
			else if(step_allowed(u1,v1+1) && !inStack(u1,v1+1) && !inDeway(u1,v1+1)){
				p[u1][v1]=0;
				v1++;
				posarr[0]=u1;
				posarr[1]=v1;
				push(posarr);
				p[u1][v1]=Now;
					printf("right stack:(%d,%d)\n",stack[top][0],stack[top][1]);

			}
			
			else{
				p[u1][v1]=0;
				Deway[dex][0]=u1;
				Deway[dex][1]=v1;
				dex++;
				pop();
				u1=stack[top][0];
				v1=stack[top][1];
				p[stack[top][0]][stack[top][1]]=Now;
				printf("u1,v1=%d,%d\n",u1,v1);
				printf("pop stack:(%d,%d)\n",stack[top][0],stack[top][1]);
				printf("step_allowed:%d %d %d %d\n",step_allowed(u1,v1+1),step_allowed(u1+1,v1),step_allowed(u1-1,v1),step_allowed(u1,v1-1));


			}
			if(if_win(u1,v1)==1){		//判定可以走到終點

				if(iorj==1){			//先把還原預先放進去的
					wi[i][j]=0;
					wi[i+1][j]=0;
				}
				if(iorj==2){
					wj[i][j]=0;
					wj[i][j+1]=0;
				}
				printf("win!\n");
				p[find_pos(Now,1)][find_pos(Now,2)]=0;
				p[initi][initj]=Now;
				InitialTheStack();
				InitialDeway();
				Now=flip(Now);
				return 1;
			}
		}

		InitialTheStack();
		InitialDeway();
		p[find_pos(Now,1)][find_pos(Now,2)]=0;
		p[initi][initj]=Now;

		if(iorj==1){				//就算沒有找到路還是要還原預先放進去的	
			wi[i][j]=0;
			wi[i+1][j]=0;
		}
		if(iorj==2){
			wj[i][j]=0;
			wj[i][j+1]=0;
		}
		Now=flip(Now);
		return 0;
	}

	
	if(Now==2){
		Now=flip(Now);
		while(!isEmpty()){

			if(step_allowed(u1,v1+1) && !inStack(u1,v1+1) && !inDeway(u1,v1+1)){
				p[u1][v1]=0;
				v1++;
				posarr[0]=u1;
				posarr[1]=v1;
				push(posarr);
				p[u1][v1]=Now;
				printf("right stack:(%d,%d)\n",stack[top][0],stack[top][1]);
			}
			else if(step_allowed(u1+1,v1) && !inStack(u1+1,v1) && !inDeway(u1+1,v1)){
				p[u1][v1]=0;
				u1++;
				posarr[0]=u1;
				posarr[1]=v1;
				push(posarr);
				p[u1][v1]=Now;
				printf("down stack:(%d,%d)\n",stack[top][0],stack[top][1]);
			}
			else if(step_allowed(u1-1,v1) && !inStack(u1-1,v1) && !inDeway(u1-1,v1) ){
				p[u1][v1]=0;
				u1--;
				posarr[0]=u1;
				posarr[1]=v1;
				push(posarr);
				p[u1][v1]=Now;
				printf("up stack:(%d,%d)\n",stack[top][0],stack[top][1]);
			}
			else if(step_allowed(u1,v1-1) && !inStack(u1,v1-1) && !inDeway(u1,v1-1)){
				p[u1][v1]=0;
				v1--;
				posarr[0]=u1;
				posarr[1]=v1;
				push(posarr);
				p[u1][v1]=Now;
				printf("left stack:(%d,%d)\n",stack[top][0],stack[top][1]);
			}
			else{
				p[u1][v1]=0;				//pop的事前準備工作
				Deway[dex][0]=u1;
				Deway[dex][1]=v1;
				dex++;
				pop();
				u1=stack[top][0];
				v1=stack[top][1];
				p[stack[top][0]][stack[top][1]]=Now;
				printf("u1,v1=%d,%d",u1,v1);
				printf("step_allowed:%d %d %d %d\n",step_allowed(u1,v1+1),step_allowed(u1+1,v1),step_allowed(u1-1,v1),step_allowed(u1,v1-1));
				printf("pop stack:(%d,%d)\n",stack[top][0],stack[top][1]);
			}

			if(if_win(u1,v1)==1){
				if(iorj==1){			//還原預先放進去的
					wi[i][j]=0;
					wi[i+1][j]=0;
				}
				if(iorj==2){
					wj[i][j]=0;
					wj[i][j+1]=0;
				}
				p[find_pos(Now,1)][find_pos(Now,2)]=0;
				p[initi][initj]=Now;
				InitialTheStack();
				InitialDeway();
				Now=flip(Now);

				return 1;
			}
		}


		if(iorj==1){				//還原預先放進去的	
			wi[i][j]=0;
			wi[i+1][j]=0;
		}
		if(iorj==2){
			wj[i][j]=0;
			wj[i][j+1]=0;
		}
		InitialTheStack();
		InitialDeway();
		p[find_pos(Now,1)][find_pos(Now,2)]=0;
		p[initi][initj]=Now;
		Now=flip(Now);

		return 0;
	}


	return -1;
 	
}

int wall_allowed(int iorj, int i, int j){			//assume that the wall been placed by the index (i,j)(i+1,j)for wi 
	int cnt=0;
	int c;
	if(iorj==1){		//---要判斷的是縱向的wi
		if(i>max_bound-2 || j>max_bound-2 || i<0 || j<0){	//不允許超出邊界
			return 0;
		}
		if(wi[i][j]==1 || wi[i+1][j+1]==1){	 				//不允許重疊放置
			return 0;
		}
		
		for (c=0;c<max_bound;c++){
			if(wi[cnt][j]==1){
				cnt+=1;
			}
		}
		
		if(cnt>3){
			return 0;
		}
	}

	if(iorj==2){		//--要判斷的是橫向的wj
		
		if(i>max_bound-2 || j>max_bound-2 || i<0 || j<0){	//不允許超出邊界
			return 0;
		}

		if(wj[i][j]==1){	//不允許重複放置
			return 0;
		}
	}

	if(isPath(iorj,i,j)==1){
		return 1;
	}
	else if(isPath(iorj,i,j)==-1){
		printf("isPath has bug\n");
	}
	else if(isPath(iorj,i,j)==0){
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

			printf("Please enter the index to indicate where to move:(letter-number)\n");
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
				break;
			}
			else{
				cnt=0;
				if(step_allowed(i,j)==0){
					printf("invalid step!\n");
				}
				else if(step_allowed(i,j)==-1){
					printf("system error\n");
				}
				else{
					printf("wrong input!\n");
				}
			}

		}

		if(p[i][j]==1 && cnt==2){
			break;
		}
		
	}
	return 0;
}

int write_wall(){
	char in1[2];
	char in2[2];
	char temp1[10];
	char temp2[10];
	int iorj;
	int i,j=0;
	int cnt=0;
	while(1){

		while(1){
			printf("Please enter the index to indicate where the wall should be put BETWEEN:\n(AB,de,12,23 are acceptable. please type IN ORDER!)\n");
			scanf(" %s", temp1);
			if(strlen(temp1)!=2){
				printf("wrong input!\n");
			}
			else{
				in1[0]=temp1[0];
				in1[1]=temp1[1];
				break;
			}
		}
		
		if( (in1[0]=='A' && in1[1]=='B') || (in1[0]=='a' && in1[1]=='b')){
			iorj=2;
			i=0;
			cnt++;
		}


		if( (in1[0]=='B' && in1[1]=='C') || (in1[0]=='b' && in1[1]=='c')){
			iorj=2;
			i=1;
			cnt++;
		}


		if( (in1[0]=='C' && in1[1]=='D') || (in1[0]=='c' && in1[1]=='d')){
			iorj=2;
			i=2;
			cnt++;
		}

		if( (in1[0]=='D' && in1[1]=='E') || (in1[0]=='d' && in1[1]=='e')){
			iorj=2;
			i=3;
			cnt++;
		}

		if( in1[0]=='1' && in1[1]=='2'){
			iorj=1;
			j=0;
			cnt++;
		}


		if( in1[0]=='2' && in1[1]=='3'){
			iorj=1;
			j=1;
			cnt++;
		}


		if( in1[0]=='3' && in1[1]=='4'){
			iorj=1;
			j=2;
			cnt++;
		}

		if( in1[0]=='4' && in1[1]=='5'){
			iorj=1;
			j=3;
			cnt++;
		}


		if(cnt==1){
			while(1){
				printf("Please enter the index to indicate where the wall should be put ALONG:\n(please type IN ORDER!)\n");
				scanf(" %s", temp2);
				if(strlen(temp2)!=2){
					printf("wrong input!\n");
				}
				else{
					in2[0]=temp2[0];
					in2[1]=temp2[1];
					break;
				}

			}

			if( ((in2[0]=='A' && in1[1]=='B') || (in2[0]=='a' && in2[1]=='b') ) && iorj==1 ){		//double check
				i=0;
				cnt++;
			}


			if( ((in2[0]=='B' && in2[1]=='C') || (in2[0]=='b' && in2[1]=='c'))&& iorj==1){
				i=1;
				cnt++;
			}


			if( ((in2[0]=='C' && in2[1]=='D') || (in2[0]=='c' && in2[1]=='d'))&& iorj==1){
				i=2;
				cnt++;
			}

			if( ((in2[0]=='D' && in2[1]=='E') || (in2[0]=='d' && in2[1]=='e'))&& iorj==1){
				i=3;
				cnt++;
			}

			if( in2[0]=='1' && in2[1]=='2' &&iorj==2){
				j=0;
				cnt++;
			}


			if( in2[0]=='2' && in2[1]=='3'&& iorj==2){
				j=1;
				cnt++;
			}


			if( in2[0]=='3' && in2[1]=='4' && iorj==2){
				j=2;
				cnt++;
			}

			if( in2[0]=='4' && in2[1]=='5'&& iorj==2){
				j=3;
				cnt++;
			}
		}

		if(cnt==2 && wall_allowed(iorj,i,j)==1 ){
			if(iorj==1){
				wi[i][j]=1;
				wi[i+1][j]=1;
				numwall[Now-1]+=1;
				cnt=0;
				break;
			}
			if(iorj==2){
				wj[i][j]=1;
				wj[i][j+1]=1;
				numwall[Now-1]+=1;
				cnt=0;
				break;
			}
		}

		else if(cnt==2 && wall_allowed(iorj,i,j)==-1){
			cnt=0;
			printf("system error(wall_allowed)\n");
		}
		else{
			cnt=0;
			printf("invalid input\n");
		}


	}
	
	return 0;
}



int input(){
	char In;
	printf("********************************* +-------------------+\n");
	printf("| PLACE THE WALL     ---press p | I  PLAYER%d's trun   I\n",Now);
	printf("| MOVE THE PIECE        press m | I  WALL remain:%d    I\n",2-numwall[Now-1]);
	printf("********************************* +-------------------+\n");
	while(1){
		printf("your command:");
		scanf(" %c",&In);
		if(In=='m'){
			write_piece();
			break;
		}
		if(In=='p'){
			if(numwall[Now-1]<2){
				write_wall();
				break;
			}
			else if(numwall[Now-1]>=2){
				printf("No wall can be put!");
			}
		}
		else{
			printf("command error please enter again\n");
		}
	}
	return 0;
}

int main (void){
	welcome();
	while(1){
		InitialTheGame();
		InitialDeway();
		InitialTheStack();
		while(1){
			Display();
			input();
			if(winthegame()){
				printf("\n");
				printf("**************************\n");
				printf("*       GAME OVER        *\n");
				printf("*      PLAYER %d WIN!     *\n",Now);
				printf("**************************\n");
				printf("\n");
				break;
			}
			Now=flip(Now);
		}
		Exit();
	}
	return 0;
}