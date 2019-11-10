#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<time.h>
#include<direct.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define WIDE 1024 //窗口宽度
#define HIGH 768 //窗口高度
#define LINE1 (int)((350.0/480)*HIGH) //小鸟飞行区域和控制区纵坐标界限
#define LINE2 (int)((250.0/640)*WIDE) //控制区和信息显示区横坐标界限

bool welcome();
struct bird *creat_bird(struct bird *head,int y);
void display(struct bird *head,IMAGE *img1,IMAGE *img2,IMAGE *img3,IMAGE *img4,IMAGE *img1_b,IMAGE *img2_b,IMAGE *img3_b,IMAGE *img4_b,
			 IMAGE *select,IMAGE *select_b,IMAGE *n1,IMAGE *n2,IMAGE *n3,IMAGE *n4,IMAGE *n5,IMAGE *n6,IMAGE *n7,IMAGE *n8,IMAGE *n9,
			 IMAGE *plus,IMAGE *minus,IMAGE *multiply,IMAGE *devide);
struct bird *deleteBird(struct bird *head);
void move(struct bird *head);
int position(struct bird *head);
int randomNum();
int randomType();
int randomAnswerPosition();
int randomAnswerAddValue();
int judge(struct bird *head,int choiceAnswer);
void fileWrite(struct bird *head,char user[],int score);
struct bird *fileRead(struct bird *head,char user[],int *score,bool temp,IMAGE *wallPaper);
void show(char user[],IMAGE *wallPaper);
void scoreList(char user[],int score);
/*小鸟结构体*/
struct bird{
	bool flag; //选中标记
	int birdtype;  //小鸟图片类型
	int num1;  //第一个运算数字
	int num2;  //第二个运算数字
	int type;  //符号标记
	int answer;  //正确答案
	int answerArray[4];  //选项数组
	int x;  //x坐标
	int y;  //y坐标
	struct bird *next;//链表下一个节点地址
};
/*高分榜结构体*/
struct list{
	char username[10];//用户名
	int score;//分数
};

void main(){

	IMAGE img1,img2,img3,img4,img1_b,img2_b,img3_b,img4_b,select,select_b,n1,n2,n3,n4,n5,n6,n7,n8,n9,plus,minus,multiply,devide;
	loadimage(&img1,"image\\blackbird.jpg");
	loadimage(&img1_b,"image\\blackbird_b.jpg");
	loadimage(&img2,"image\\yellowbird.jpg");
	loadimage(&img2_b,"image\\yellowbird_b.jpg");
	loadimage(&img3,"image\\redbird.jpg");
	loadimage(&img3_b,"image\\redbird_b.jpg");
	loadimage(&img4,"image\\bluebird.jpg");
	loadimage(&img4_b,"image\\bluebird_b.jpg");
	loadimage(&select,"image\\select.jpg");
	loadimage(&select_b,"image\\select_b.jpg");
	loadimage(&n1,"image\\1.jpg");
	loadimage(&n2,"image\\2.jpg");
	loadimage(&n3,"image\\3.jpg");
	loadimage(&n4,"image\\4.jpg");
	loadimage(&n5,"image\\5.jpg");
	loadimage(&n6,"image\\6.jpg");
	loadimage(&n7,"image\\7.jpg");
	loadimage(&n8,"image\\8.jpg");
	loadimage(&n9,"image\\9.jpg");
	loadimage(&plus,"image\\plus.jpg");
	loadimage(&minus,"image\\minus.jpg");
	loadimage(&multiply,"image\\multiply.jpg");
	loadimage(&devide,"image\\devide.jpg");

	_mkdir("save");  //建立save文件夹
	struct bird *head=NULL,*p=NULL,*p1=NULL;
	int score=0,i,choice=0;
	bool mode=true;
	int sec=0;
	char seconds[3];

	char user[10],s[10];
	char str0[5]=".txt";
	char str[20]="save\\";
	
	mciSendString("open BGM\\AngryBird.mp3 alias AngryBird",NULL,0,NULL);//播放音乐
	mciSendString("play AngryBird repeat",NULL,0,NULL);//循环播放
	
	mode=welcome();

	do{
		InputBox(user,10,"输入用户名:");
	}while(user[0]=='\0');//检查是否有效输入

	for(i=0;user[i]!='\0';i++){
		if(user[i]==' ')
			user[i]='_';  //空格替换为下划线
	}
	IMAGE wallPaper;
	if(mode)
		loadimage(&wallPaper,"image\\wallpaper_speed.jpg",WIDE,HIGH);
	else
		loadimage(&wallPaper,"image\\wallpaper.jpg",WIDE,HIGH);
	if(!mode){
		strcat(str,user);
		strcat(str,str0);  //拼接路径字符串
		FILE *fp=fopen(str,"r");  //检查是否有存档
		if(fp!=NULL){   //有存档则读取
			head=fileRead(head,str,&score,false,&wallPaper);
			fclose(fp);
		}
	}
	MOUSEMSG m;

	setbkmode(TRANSPARENT);
	settextstyle(20,0,"华文新魏");
	srand(time(NULL));  //获取随机数种子
	
	time_t t=time(NULL)+30;

	

	while(true){
		while(MouseHit()){
			m=GetMouseMsg();
			switch(m.uMsg){
			case WM_MOUSEMOVE:
				if(m.x>=22.0/640*WIDE && m.x<=88.0/640*WIDE && m.y>=385.0/480*HIGH && m.y<=409.0/480*HIGH)
					choice=1;
				else if(m.x>=22.0/640*WIDE && m.x<=88.0/640*WIDE && m.y>=416.0/480*HIGH && m.y<=440.0/480*HIGH)
					choice=2;
				else if(m.x>=92.0/640*WIDE && m.x<=158.0/640*WIDE && m.y>=416.0/480*HIGH && m.y<=440.0/480*HIGH)
					choice=3;
				else if(m.x>=162.0/640*WIDE && m.x<=228.0/640*WIDE && m.y>=385.0/480*HIGH && m.y<=409.0/480*HIGH){
					if(mode){
						break;
					}
					choice=4;
				}
				else if(m.x>=162.0/640*WIDE && m.x<=228.0/640*WIDE && m.y>=416.0/480*HIGH && m.y<=440.0/480*HIGH){
					if(mode){
						break;
					}
					choice=5;
				}
				else if(m.x>=405.0/640*WIDE && m.x<=445.0/640*WIDE && m.y>=390.0/480*HIGH && m.y<=435.0/480*HIGH)
					choice=6;
				else if(m.x>=460.0/640*WIDE && m.x<=505.0/640*WIDE && m.y>=390.0/480*HIGH && m.y<=435.0/480*HIGH)
					choice=7;
				else if(m.x>=520.0/640*WIDE && m.x<=565.0/640*WIDE && m.y>=390.0/480*HIGH && m.y<=435.0/480*HIGH)
					choice=8;
				else if(m.x>=580.0/640*WIDE && m.x<=625.0/640*WIDE && m.y>=390.0/480*HIGH && m.y<=435.0/480*HIGH)
					choice=9;
				else
					choice=0;
				break;


			case WM_LBUTTONDOWN:
				for(p=head;p!=NULL;p=p->next){
					if((m.x>=((p->x)-40)) && (m.x<=((p->x)+40)) && (m.y>=(p->y)-40) && (m.y<=(p->y)+40)){
						for(p1=head;p1!=NULL;p1=p1->next){
							p1->flag=false;
						}
						p->flag=true;
						
					}
				}
				break;
			case WM_LBUTTONUP:
				if(m.x>=22.0/640*WIDE && m.x<=88.0/640*WIDE && m.y>=385.0/480*HIGH && m.y<=409.0/480*HIGH){
					head=creat_bird(head,position(head));
					//增加
				}
				if(m.x>=22.0/640*WIDE && m.x<=88.0/640*WIDE && m.y>=416.0/480*HIGH && m.y<=440.0/480*HIGH){
					head=deleteBird(head);
					//删除
				}
				if(m.x>=92.0/640*WIDE && m.x<=158.0/640*WIDE && m.y>=416.0/480*HIGH && m.y<=440.0/480*HIGH){
					//退出
					exit(0);
				}
				if(m.x>=162.0/640*WIDE && m.x<=228.0/640*WIDE && m.y>=385.0/480*HIGH && m.y<=409.0/480*HIGH){
					if(mode){
						break;
					}
					head=fileRead(head,user,&score,true,&wallPaper);
					FlushMouseMsgBuffer();
					//导入
				}
				if(m.x>=162.0/640*WIDE && m.x<=228.0/640*WIDE && m.y>=416.0/480*HIGH && m.y<=440.0/480*HIGH){
					if(mode){
						break;
					}
					fileWrite(head,user,score);
					FlushMouseMsgBuffer();  //清空暂停时鼠标动作
					//存状态
				}
				if(m.x>=405.0/640*WIDE && m.x<=445.0/640*WIDE && m.y>=390.0/480*HIGH && m.y<=435.0/480*HIGH){
					score=score+judge(head,0);
					if(judge(head,0)==1)
						head=deleteBird(head);
					//choose answer0
				}
				if(m.x>=460.0/640*WIDE && m.x<=505.0/640*WIDE && m.y>=390.0/480*HIGH && m.y<=435.0/480*HIGH){
					score=score+judge(head,1);
					if(judge(head,1)==1)
						head=deleteBird(head);
					//choose answer1
				}
				if(m.x>=520.0/640*WIDE && m.x<=565.0/640*WIDE && m.y>=390.0/480*HIGH && m.y<=435.0/480*HIGH){
					score=score+judge(head,2);
					if(judge(head,2)==1)
						head=deleteBird(head);
					//choose answer2
				}
				if(m.x>=580.0/640*WIDE && m.x<=625.0/640*WIDE && m.y>=390.0/480*HIGH && m.y<=435.0/480*HIGH){
					score=score+judge(head,3);
					if(judge(head,3)==1)
						head=deleteBird(head);
					//choose answer3
				}
				break;
			default:
				break;
			}
		}
		sprintf(s,"%d",score);
		Sleep(5);
		BeginBatchDraw();
				
		show(user,&wallPaper);
		outtextxy(LINE2+(int)(60.0/640*WIDE),LINE1+(int)(60.0/480*HIGH),s); //更新分数
		display(head,&img1,&img2,&img3,&img4,&img1_b,&img2_b,&img3_b,&img4_b,&select,&select_b,&n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8,&n9,&plus,&minus,&multiply,&devide);  //显示所有鸟的位置

		if(mode){
			sprintf(seconds,"%d",t-time(NULL));
			outtextxy(LINE2+(int)(20.0/640*WIDE),LINE1+(int)(100.0/480*HIGH),"时间：");
			outtextxy(LINE2+(int)(60.0/640*WIDE),LINE1+(int)(100.0/480*HIGH),seconds);
		}
		if(choice>=1&&choice<=5)
			setlinecolor(BLACK);
		else
			setlinecolor(WHITE);

		switch(choice){
		case 1:
			line((int)(40.0/1024*WIDE),(int)(650.0/768*HIGH),(int)(110.0/1024*WIDE),(int)(650.0/768*HIGH));
			break;
		case 2:
			line((int)(40.0/1024*WIDE),(int)(698.0/768*HIGH),(int)(110.0/1024*WIDE),(int)(698.0/768*HIGH));
			break;
		case 3:
			line((int)(154.0/1024*WIDE),(int)(698.0/768*HIGH),(int)(193.0/1024*WIDE),(int)(698.0/768*HIGH));
			break;
		case 4:
			line((int)(265.0/1024*WIDE),(int)(650.0/768*HIGH),(int)(310.0/1024*WIDE),(int)(650.0/768*HIGH));
			break;
		case 5:
			line((int)(265.0/1024*WIDE),(int)(698.0/768*HIGH),(int)(310.0/1024*WIDE),(int)(698.0/768*HIGH));
			break;
		case 6:
			line((int)(660.0/1024*WIDE),(int)(680.0/768*HIGH),(int)(700.0/1024*WIDE),(int)(680.0/768*HIGH));
			break;
		case 7:
			line((int)(755.0/1024*WIDE),(int)(680.0/768*HIGH),(int)(795.0/1024*WIDE),(int)(680.0/768*HIGH));
			break;
		case 8:
			line((int)(850.0/1024*WIDE),(int)(680.0/768*HIGH),(int)(890.0/1024*WIDE),(int)(680.0/768*HIGH));
			break;
		case 9:
			line((int)(944.0/1024*WIDE),(int)(680.0/768*HIGH),(int)(984.0/1024*WIDE),(int)(680.0/768*HIGH));
			break;
		}

		FlushBatchDraw();

		move(head);  //移动鸟的坐标
		p=head;
		
		if(mode){
			if(t-time(NULL)<=0){
				scoreList(user,score);
				break;
			}
		}
	}
	system("pause");
}
void scoreList(char user[],int score){
	int i;
	bool flag=false;
	struct list top[5]={{"no_data",0},{"no_data",0},{"no_data",0},{"no_data",0},{"no_data",0}};
	
	FILE *r=fopen("list.txt","r");
    if(r!=NULL){
		for(i=0;i<5;i++){
			if(!feof(r))
				fscanf(r,"%s%d",&top[i].username,&top[i].score);
		}
	}

	if(score>top[4].score){
		flag=true;
		strcpy(top[4].username,user);
		top[4].score=score;
		for(i=4;i>=0;i--){
			if(i-1>=0&&score>top[i-1].score){
				char tempname[10];
				int tempscore;
				strcpy(tempname,top[i].username);
				strcpy(top[i].username,top[i-1].username);
				strcpy(top[i-1].username,tempname);
				tempscore=top[i].score;
				top[i].score=top[i-1].score;
				top[i-1].score=tempscore;
			}
			else
				break;
		}
	}

	FILE *w=fopen("list.txt","w");
	for(i=0;i<5;i++){
		fprintf(w,"\n%s %d",top[i].username,top[i].score);
	}
	fclose(w);
	
	BeginBatchDraw();

	IMAGE endpaper;
	loadimage(&endpaper,"image\\end.jpg",WIDE,HIGH);
	putimage(0,0,&endpaper);
	if(flag)
		outtextxy(400,310,"恭喜您进入高分排行！");
	else
		outtextxy(400,310,"很遗憾您没有进入排行。。。");
	for(i=0;i<5;i++){
		char str[5];
		sprintf(str,"%d",top[i].score);
		outtextxy(400,310+(i+1)*30,top[i].username);
		outtextxy(550,310+(i+1)*30,str);
	}
	outtextxy(400,310+6*30,"按任意键退出程序。。。");

	FlushBatchDraw();

}
bool welcome(){
	int choice=0;
	IMAGE wall;
	loadimage(&wall,"image\\welcome.jpg",WIDE,HIGH);
	initgraph(WIDE,HIGH);
	HCURSOR hcur = (HCURSOR)LoadImage(NULL, "mouse.cur", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	HWND hwnd = GetHWnd();							// 获取绘图窗口句柄
	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);	// 设置窗口类的鼠标样式
	MOUSEMSG m;
	while(true){
		BeginBatchDraw();
		putimage(0,0,&wall);
		switch(choice){
		case 1:
			line((int)(410.0/1024*WIDE),(int)(500.0/768*HIGH),(int)(580.0/1024*WIDE),(int)(500.0/768*HIGH));
			break;
		case 2:
			line((int)(410.0/1024*WIDE),(int)(600.0/768*HIGH),(int)(580.0/1024*WIDE),(int)(600.0/768*HIGH));
			break;
		}
		while(MouseHit()){
			m=GetMouseMsg();
			switch(m.uMsg){
			case WM_MOUSEMOVE:
				if(m.x>=410.0/1024*WIDE && m.x<= 580.0/1024*WIDE && m.y>=450.0/768*HIGH && m.y<=500.0/768*HIGH){
					choice=1;
					
				}
				else if(m.x>=410.0/1024*WIDE && m.x<= 580.0/1024*WIDE && m.y>=540.0/768*HIGH && m.y<=600.0/768*HIGH){
					choice=2;
				}
				else
					choice=0;
				break;
			case WM_LBUTTONDOWN:
				if(m.x>=410.0/1024*WIDE && m.x<= 580.0/1024*WIDE && m.y>=450.0/768*HIGH && m.y<=500.0/768*HIGH){
					return false;
				}
				if(m.x>=410.0/1024*WIDE && m.x<= 580.0/1024*WIDE && m.y>=540.0/768*HIGH && m.y<=600.0/768*HIGH){
					return true;
				}
			}
		}
		FlushBatchDraw();
		clearrectangle(0,0,WIDE,HIGH);
	}
}
void show(char user[],IMAGE *wallPaper){
	putimage(0,0,wallPaper);
	outtextxy(LINE2+(int)(20.0/640*WIDE),LINE1+(int)(20.0/480*HIGH),"用户：");
	outtextxy(LINE2+(int)(60.0/640*WIDE),LINE1+(int)(20.0/480*HIGH),user);
	outtextxy(LINE2+(int)(20.0/640*WIDE),LINE1+(int)(60.0/480*HIGH),"得分：");

	
}

int position(struct bird *head){
	struct bird *p=head;
	bool flag=false;
	int y,i=0;
	do{
		i++;
		flag=false;
		y=50+rand()%(LINE1-120);
		for(p=head;p!=NULL;p=p->next){
			if(p->x<120||p->x>WIDE-120){
				if(y<p->y+120 && y>p->y-120){
					flag=true;
					if(i>10){
						flag=false;
						y=-1;
					}
				}
			}
		}
	}while(flag);
	return y;
}
struct bird *creat_bird(struct bird *head,int y){
	if(y==-1)
		return head;
	struct bird *p=NULL,*pr=head;
	bool flag=false,temp=false;
	int birdtype=randomType();
	int num1=randomNum();
	int num2=randomNum();
	if(num1<num2){
		int temp;
		temp=num1;
		num1=num2;
		num2=temp;
	}
	int type=randomType();
	int answer;
	int i,j;
	switch(type){
	case 1:answer=num1+num2;break;
	case 2:answer=num1-num2;break;
	case 3:answer=num1*num2;break;
	case 4:
		while(num1%num2!=0){
			num1=randomNum();
			num2=randomNum();
		}
		answer=num1/num2;
		break;
	}
	int answerArray[4]={999,999,999,999};
	answerArray[randomAnswerPosition()]=answer;
	for(i=0;i<4;i++){
		if(answerArray[i]==999){
			do{
				temp=false;
				answerArray[i]=answer+randomAnswerAddValue();
				if(answerArray[i]<0){
					temp=true;
				}
				for(j=i-1;j>=0;j--){
					if(answerArray[i]==answerArray[j])
						temp=true;
				}
			}while(temp);
		}
	}
	int x=0;
	p=(struct bird *)malloc(sizeof(struct bird));
	if(p==NULL){
		printf("NO ENOUGH MEMORY!");
		exit(0);
	}
	if(head==NULL){
		head=p;
	}
	else{
		while(pr->next!=NULL){
			pr=pr->next;
		}
		pr->next=p;
	}
	p->flag=flag;
	p->birdtype=birdtype;
	p->num1=num1;
	p->num2=num2;
	p->type=type;
	p->answer=answer;
	p->answerArray[0]=answerArray[0];
	p->answerArray[1]=answerArray[1];
	p->answerArray[2]=answerArray[2];
	p->answerArray[3]=answerArray[3];
	p->x=x;
	p->y=y;
	p->next=NULL;
	return head;
}
void display(struct bird *head,IMAGE *img1,IMAGE *img2,IMAGE *img3,IMAGE *img4,IMAGE *img1_b,IMAGE *img2_b,IMAGE *img3_b,IMAGE *img4_b,
			 IMAGE *select,IMAGE *select_b,IMAGE *n1,IMAGE *n2,IMAGE *n3,IMAGE *n4,IMAGE *n5,IMAGE *n6,IMAGE *n7,IMAGE *n8,IMAGE *n9,
			 IMAGE *plus,IMAGE *minus,IMAGE *multiply,IMAGE *devide){
	struct bird *p=head;
	char a0[3],a1[3],a2[3],a3[3];
	while(p!=NULL){
		switch(p->birdtype){
		case 1:
			putimage(p->x-55,p->y-55,img1_b, NOTSRCERASE);
			putimage(p->x-55,p->y-55,img1,SRCINVERT);
			break;
		case 2:
			putimage(p->x-55,p->y-55,img2_b, NOTSRCERASE);
			putimage(p->x-55,p->y-55,img2,SRCINVERT);
			break;
		case 3:
			putimage(p->x-55,p->y-55,img3_b, NOTSRCERASE);
			putimage(p->x-55,p->y-55,img3,SRCINVERT);
			break;
		case 4:
			putimage(p->x-55,p->y-55,img4_b, NOTSRCERASE);
			putimage(p->x-55,p->y-55,img4,SRCINVERT);
			break;
		}
		if(p->flag){
			putimage(p->x-55,p->y-55,select_b, NOTSRCERASE);
			putimage(p->x-55,p->y-55,select,SRCINVERT);
			sprintf(a0,"%d",p->answerArray[0]);
			sprintf(a1,"%d",p->answerArray[1]);
			sprintf(a2,"%d",p->answerArray[2]);
			sprintf(a3,"%d",p->answerArray[3]);
			outtextxy((int)(415.0/640*WIDE),(int)(402.0/480*HIGH),a0);
			outtextxy((int)(475.0/640*WIDE),(int)(402.0/480*HIGH),a1);
			outtextxy((int)(535.0/640*WIDE),(int)(402.0/480*HIGH),a2);
			outtextxy((int)(595.0/640*WIDE),(int)(402.0/480*HIGH),a3);
		}
		switch(p->num1){
			case 1:
			putimage(p->x-30,p->y+35,n1);
			break;
		case 2:
			putimage(p->x-30,p->y+35,n2);
			break;
		case 3:
			putimage(p->x-30,p->y+35,n3);
			break;
		case 4:
			putimage(p->x-30,p->y+35,n4);
			break;
		case 5:
			putimage(p->x-30,p->y+35,n5);
			break;
		case 6:
			putimage(p->x-30,p->y+35,n6);
			break;
		case 7:
			putimage(p->x-30,p->y+35,n7);
			break;
		case 8:
			putimage(p->x-30,p->y+35,n8);
			break;
		case 9:
			putimage(p->x-30,p->y+35,n9);
			break;

		}
		switch(p->type){
		case 1:
			putimage(p->x-10,p->y+35,plus);
			break;
		case 2:
			putimage(p->x-10,p->y+35,minus);
			break;
		case 3:
			putimage(p->x-10,p->y+35,multiply);
			break;
		case 4:
			putimage(p->x-10,p->y+35,devide);
			break;
		}
		switch(p->num2){
		case 1:
			putimage(p->x+10,p->y+35,n1);
			break;
		case 2:
			putimage(p->x+10,p->y+35,n2);
			break;
		case 3:
			putimage(p->x+10,p->y+35,n3);
			break;
		case 4:
			putimage(p->x+10,p->y+35,n4);
			break;
		case 5:
			putimage(p->x+10,p->y+35,n5);
			break;
		case 6:
			putimage(p->x+10,p->y+35,n6);
			break;
		case 7:
			putimage(p->x+10,p->y+35,n7);
			break;
		case 8:
			putimage(p->x+10,p->y+35,n8);
			break;
		case 9:
			putimage(p->x+10,p->y+35,n9);
			break;
		}
		
		p=p->next;
	}
}
void move(struct bird *head){
	struct bird *p=head;
	while(p!=NULL){
		p->x=(p->x+1)%WIDE;
		p=p->next;
	}
}

struct bird *deleteBird(struct bird *head){
	struct bird *p=head,*pr=head;
	if(head==NULL){
		return head;
	}
	while(p->flag!=true&&p->next!=NULL){
		pr=p;
		p=p->next;
	}
	if(p->flag==true){
		if(p==head){
			head=p->next;
		}
		else{
			pr->next=p->next;
		}
		free(p);
	return head;
	}
	p=head;
	head=p->next;
	free(p);
	return head;
	
}

int randomNum(){
	int num;
	num=rand()%9+1;
	return num;
}
int randomType(){
	int type;
	type=rand()%4+1;
	return type;
}
int randomAnswerPosition(){
	int pos;
	pos=rand()%4;
	return pos;
}
int randomAnswerAddValue(){
	int add,a;
	add=rand()%10+1;
	a=rand()%2;
	if(a==0)
		return add;
	return -add;

}
int judge(struct bird *head,int choiceAnswer){
	struct bird *p=head;
	while(p!=NULL){
		if(p->flag==true)
			break;
		else
			p=p->next;
	}
	if(p==NULL)
		return 0;
	if(p->answer==p->answerArray[choiceAnswer])
		return 1;
	else
		return -1;
}
void fileWrite(struct bird *head,char user[],int score){
	struct bird *p=head;
	char str0[5]=".txt";
	char str[20]="save\\";
	strcat(str,user);
	strcat(str,str0);

	FILE *w=fopen(str,"w");
	if(w==NULL){
		return;
	}
	fprintf(w,"%d",score);
	fprintf(w," %s",user);
	while(p!=NULL){
		fprintf(w,"\n%d",p->flag);
		fprintf(w," %d",p->birdtype);
		fprintf(w," %d",p->num1);
		fprintf(w," %d",p->num2);
		fprintf(w," %d",p->type);
		fprintf(w," %d",p->answer);
		fprintf(w," %d",p->answerArray[0]);
		fprintf(w," %d",p->answerArray[1]);
		fprintf(w," %d",p->answerArray[2]);
		fprintf(w," %d",p->answerArray[3]);
		fprintf(w," %d",p->x);
		fprintf(w," %d",p->y);
		p=p->next;
	}
    fclose(w);
	outtextxy(10,HIGH-30,"文件已保存，按任意键继续...");
	FlushBatchDraw(); 
	system("pause");
}

struct bird *fileRead(struct bird *head,char user[],int *score,bool temp,IMAGE *wallPaper){
	char str[20]="save\\";
	if(temp){
		char str0[5]=".txt";
		
		char user0[10];
		InputBox(user0,10,"输入要导入的用户名：");
		for(int i=0;user0[i]!='\0';i++){
			if(user0[i]==' ')
				user0[i]='_';
		}
		if(user0[0]=='\0'){
			outtextxy(10,HIGH-30,"您没有输入数据，按任意键继续...");
			FlushBatchDraw();
			system("pause");
			return head;
		}
		strcat(str,user0);
		strcat(str,str0);
	}
	else{
		for(int i=0;user[i]!='\0';i++){
			str[i]=user[i];
		}
	}
	bool flag;

	int num1,num2,type,answer,x,y,birdtype;
	int answerArray[4];
	struct bird *q=NULL,*nhead;
	FILE *r=fopen(str,"r");
	if(r==NULL){
		outtextxy(10,HIGH-30,"无此用户，按任意键继续...");
		FlushBatchDraw();
		system("pause");
		return head;
	}
	fscanf(r,"%d",score);
	fscanf(r,"%s",user);
	if(feof(r)){
		return NULL;
	}
	nhead=(struct bird *)malloc(sizeof(struct bird));
	q=nhead;
	while(true){
		fscanf(r,"%d%d%d%d%d%d%d%d%d%d%d%d",&flag,&birdtype,&num1,&num2,&type,&answer,&answerArray[0],
			&answerArray[1],&answerArray[2],&answerArray[3],&x,&y);
		q->flag=flag;
		q->birdtype=birdtype;
		q->num1=num1;
		q->num2=num2;
		q->type=type;
		q->answer=answer;
		q->answerArray[0]=answerArray[0];
		q->answerArray[1]=answerArray[1];
		q->answerArray[2]=answerArray[2];
		q->answerArray[3]=answerArray[3];
		q->x=x;
		q->y=y;
		if(!feof(r)){
			q->next=(struct bird *)malloc(sizeof(struct bird));
			q=q->next;
		}
		else{
			q->next=NULL;
			break;
		}
	}
	if(temp){
		show(user,wallPaper);
	}
	return nhead;
}