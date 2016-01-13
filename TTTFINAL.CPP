//-------------------------------------------------------------------------
//			Game of tic_tac_toe (play with mouse)
//			Pogramer:RAJ_P_SHAH
//			Date:17 April 2015
//			Compiler:Turbo C7
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//------------------------------HEADER FILES-------------------------------
#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
//-------------------------------------------------------------------------

int px,py;
char strp1[20],strp2[20],strtie[20],string2[20],string3[20],string4[20];
int x[4][4],count,countp1,countp2,winp1,winp2,tie,flag,pi,pj;
struct REGS in,out;
//-------------------------------------------------------------------------
//-----------------------FUNCTION TO CREATE_GRAPH--------------------------
void drawgraph(void)
{
	int gdriver=DETECT,gmode,gerror;
	initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
	gerror=graphresult();
	if(gerror!=grOk)
	{
		printf("GRAPHICS ERROR: %s\n",grapherrormsg(gerror));
		printf("PRESS ANY KEY TO EXIT or RESTART THE PROGRAM.");
		getch();
		exit(1);
	}
	px=(int)getmaxx()/20;
	py=(int)getmaxy()/20;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//-------------------------Mouse Initialization----------------------------
void InitMouse(void)
{
	in.x.ax=0;
	int86(0x33,&in,&out);
	if(out.x.ax==0)
	{
		closegraph();
		printf("Mouse Driver Not Found...");
		getch();
		exit(1);
	}
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//-----------------------------Mouse ShowingPtr----------------------------
void ShowMousePtr(void)
{
	in.x.ax=1;
	int86(0x33,&in,&out);
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//-----------------------------Mouse HidingPtr----------------------------
void HideMousePtr(void)
{
	in.x.ax=2;
	int86(0x33,&in,&out);
}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//-------------------------Mouse Restriction----------------------------
void RestrictMousePtr(int x1,int y1,int x2,int y2)
{
	in.x.ax=7;
	in.x.cx=x1;
	in.x.dx=x2;
	int86(0x33,&in,&out);

	in.x.ax=8;
	in.x.cx=y1;
	in.x.dx=y2;
	int86(0x33,&in,&out);
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//-------------------------Geting Mouse Position---------------------------
void GetMousePos(void)
{       int button,graphx,graphy;
	/* calculate the size of the image */
	unsigned size = imagesize(px*8,py*5,px*11,py*8);
	/* allocate memory to hold the image */
	void * area = malloc(size);
	static unsigned int drawx1,drawx2,drawy1,drawy2;
	do
       {
	//	delay(50);
	in.x.ax=3;
	int86(0x33,&in,&out);
	button=out.x.bx;
	graphx=out.x.cx;
	graphy=out.x.dx;


	if((button&1)!=1)
	{	if(graphx>px*8 && graphx<px*11)
			{
				drawx1=px*8;
				drawx2=px*11;
			}
		else if(graphx>px*5 && graphx<px*8)
			{
				drawx1=px*5;
				drawx2=px*8;
			}
		else if(graphx>px*2 && graphx<px*5)
			{
				drawx1=px*2;
				drawx2=px*5;
			}
		if(graphy>py*11 && graphy<py*14)
			{
				drawy1=py*11;
				drawy2=py*14;
			}
		else if(graphy>py*8 && graphy<py*11)
			{
				drawy1=py*8;
				drawy2=py*11;
			}
		else if(graphy>py*5 && graphy<py*8)
			{
				drawy1=py*5;
				drawy2=py*8;
			}
		HideMousePtr();
		getimage(drawx1+3,drawy1+3,drawx2-3,drawy2-3,area);
		putimage(drawx1+3,drawy1+3,area,NOT_PUT);
		ShowMousePtr();
		delay(100);
		HideMousePtr();
		putimage(drawx1+3,drawy1+3,area,COPY_PUT);
		ShowMousePtr();

	}
	if((button&1)==1)
	{
		if(graphx>px*8 && graphx<px*11)
			pj=3;
		else if(graphx>px*5 && graphx<px*8)
			pj=2;
		else if(graphx>px*2 && graphx<px*5)
			pj=1;
		if(graphy>py*11 && graphy<py*14)
			pi=3;
		else if(graphy>py*8 && graphy<py*11)
			pi=2;
		else if(graphy>py*5 && graphy<py*8)
			pi=1;

	}
	if(button==3)
	{
		exit(1);
	}

      }	while(button==0);
	delete area;
}
//-------------------------------------------------------------------------

//-------------------------------MAIN AREA---------------------------------
void MainArea(int ZeroOrOne)
{
	if(ZeroOrOne==0)
		setcolor(BLACK);
	else
		setcolor(WHITE);
	line(px*2,py*11,px*11,py*11);
	line(px*2,py*8,px*11,py*8);
	line(px*5,py*5,px*5,py*14);
	line(px*8,py*5,px*8,py*14);

}
//-------------------------------------------------------------------------
//----------------------FUNCTION TO DRAW FIXED ITEMS-----------------------
void fixdraw(void)
{
	setcolor(CYAN);                                //MAIN BOX
	rectangle(px-15,py-15,px*19+15,py*19+15);
	rectangle(px-10,py-10,px*19+10,py*19+10);
	settextstyle(7,0,1);
	moveto(px,py);
       //	setcolor(8);
	outtext("GAME OF TIC_TAC_TOE...(PLAY WITH MOUSE)");
	moveto(px,py*2);
	outtext("BY RAJ_P_SHAH");

	setcolor(CYAN);                              //INSTRUCTION BOX
	rectangle(px,py*16,px*19+5,py*19);
	moveto(px,py*16+5);
	settextstyle(0,0,0);
	outtext(" INSTRUCTIONS:");                   	   //  POSITIONS:
	moveto(px,py*17);
	outtext(" Player 1(Cross) will play first & then Player 2(Round)");
	moveto(px,py*18-6);				    //  1,1  1,2  1,3
	outtext(" Press LEFT & RIGHT together To EXIT..."); //  2,1  2,2  2,3
	moveto(px,py*18+10);
	outtext(" Press LEFT button when your turn comes:");//  3,1  3,2  3,3

	//setcolor(8);					 //SCORE BOX
	rectangle(px*13,py*2,px*18,py*15);
	settextstyle(3,0,2);
	setcolor(CYAN);
	textwidth(" SCORE BOARED:");
	outtextxy(px*13+2,py*2+1,"SCORE BOARD:");
	settextstyle(1,0,1);
	sprintf(strp1,"PLAYER 1:  %d",winp1);
	sprintf(strp2,"PLAYER 2:  %d",winp2);
	sprintf(strtie,"TIED:  %d",tie);
	outtextxy(px*13+5,py*4,strp1);
	outtextxy(px*13+5,py*5,strp2);
	outtextxy(px*13+54,py*6,strtie);
	line(px*14,py*8,px*17,py*8);
	line(px*14,py*8+10,px*17,py*8+10);
	outtextxy(px*14+7,py*9,"-MOVES-");

				   //GAME AREA
	MainArea(1);
	InitMouse();               //INITIALIZING MOUSE
	ShowMousePtr();            //SHOWINH MOUSE POINTER
	RestrictMousePtr(px*2,py*5,px*11,py*14);   //RESTRICT MOUSE...
							//IN GAME AREA ONLY

		string2[0]='\0';
		string3[0]='\0';
		string4[0]='\0';
		strp1[0]='\0';
		strp2[0]='\0';
		strtie[0]='\0';
}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//--------------------FUNCTION TO DRAW ROUND AND CROSS---------------------
void round(int a,int b,int c)
{
	if(c==1)
	       setcolor(YELLOW);
	else if(c==0)
		setcolor(BLACK);
	HideMousePtr();

	int posx=px*(0.5);
	int posy=py*(3.5);
	circle(posx+(px*3*b),posy+(py*3*a),py);

	ShowMousePtr();

}

void cross(int a,int b,int c)
{
	if(c==1)
		setcolor(BROWN);
	else if(c==0)
		setcolor(BLACK);
	HideMousePtr();
	int posx=px*(0.5)+(px*3*b);
	int posy=py*(3.5)+(py*3*a);

	line(posx-px,posy-py,posx+px,posy+py);
	line(posx+px,posy-py,posx-px,posy+py);
	ShowMousePtr();

}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//---------------------FUNCTION TO INITIALIZE VALUES-----------------------
void startval(void)
{
	for(int i=1;i<4;i++)
		for(int j=1;j<4;j++)
			x[i][j]=0;          //	0 means BLANK
					    //  1 means CROSS by P1
					    //  2 means ROUND by P2
	count=countp1=countp2=0;
	flag=0;
}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//--------FUNCTION TO DISPLAY THE WINNER AND ASK FOR NEXT GAME------------
void nextgame(void)
{
	 moveto(px,py*15);
	 setcolor(LIGHTGREEN);
	 if(winp1==winp2+2)
	 {
		outtext("CONGRATULATIONS PLAYER 1 FOR WINNING THE WHOLE GAME...!");
	 }
	 else
	 {
		outtext("CONGETULATIONS PLAYER 2 FOR WINNING THE WHOLE GAME...!");
	 }
	 getch();
	 setcolor(10);
	 settextstyle(5,0,1);
	 moveto(px*2,py*5);
	 outtext("Enter n/N For NEW Game.");
	 moveto(px*2,py*6);
	 outtext("Enter e/E To EXIT.");

	 moveto(px*2,py*7);
	 outtext("          Enter Your Choice:");
	 MainArea(0);
}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//-----------------FUNCTION TO DISPLAY WINNER OF ROUND---------------------
void winround(void)
{

		settextstyle(1,0,1);
		setcolor(BLACK);

	if(count==9&&flag!=1)
	{
		setcolor(CYAN);
		outtextxy(px*5,py*15,"MATCH TIED...               Enter any Key");
		getch();
		setcolor(BLACK);
		outtextxy(px*5,py*15,"MATCH TIED...               Enter any Key");
		sprintf(strtie,"TIED:  %d",tie);
		outtextxy(px*13+54,py*6,strtie);
		tie++;
		setcolor(CYAN);
		sprintf(strtie,"TIED:  %d",tie);
		outtextxy(px*13+54,py*6,strtie);
	}
	else if(count%2==1)
	{

		setcolor(BROWN);
		outtextxy(px*3,py*15," Congratulations Player1...       Enter any key:");
		getch();
		setcolor(BLACK);
		outtextxy(px*3,py*15," Congratulations Player1...       Enter any key:");
		sprintf(strp1,"PLAYER 1:  %d",winp1);
		outtextxy(px*13+5,py*4,strp1);
		setcolor(CYAN);
		winp1++;
		sprintf(strp1,"PLAYER 1:  %d",winp1);
		outtextxy(px*13+5,py*4,strp1);

	}
	else if(count%2==0)
	{

		setcolor(YELLOW);
		outtextxy(px*3,py*15," Congratulations Player2...       Enter any key:");
		getch();
		setcolor(BLACK);
		outtextxy(px*3,py*15," Congratulations Player2...       Enter any key:");
		sprintf(strp2,"PLAYER 2:  %d",winp2);
		outtextxy(px*13+5,py*5,strp2);
		setcolor(CYAN);
		winp2++;
		sprintf(strp2,"PLAYER 2:  %d",winp2);
		outtextxy(px*13+5,py*5,strp2);
	}

}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//---------------------FINCTION TO CLEAR GAME BOARD------------------------
void cleargame()
{

	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
				if(x[i][j]==1)
					cross(i,j,0);
				else if(x[i][j]==2)
					round(i,j,0);
		}
	}
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//-----------------------FUNCTION TO ASK FOR ENTRY-------------------------
void askentry(void)
{
	start:
	setcolor(BLACK);
	outtextxy(px*13+5,py*14,string4);
       //	outtextxy(px*13+5,py*10,string1);
	outtextxy(px*13+5,py*11,string2);
	outtextxy(px*13+5,py*12,string3);

	//setcolor(GREEN);
	if(count%2==0)
	{       setcolor(BROWN);
		sprintf(string2," __TURN FOR__ ");
		sprintf(string3," ~~ PLAYER 1~~ ");
		outtextxy(px*13+5,py*11,string2);
		outtextxy(px*13+5,py*12,string3);

		GetMousePos();               //GETTING MOUSE POSITION
						//AND INITIALIZING pi & pj
		if(pi<=3&&pj<=3&&pi>=1&&pj>=1&&x[pi][pj]==0)
		{
			cross(pi,pj,1);
			count++;
			countp1++;
			x[pi][pj]=1;
		}
		else
		{
			sprintf(string4,"TRY AGAIN!");
			setcolor(RED);
			outtextxy(px*13+5,py*14,string4);
			goto start;
		}
	}
	else
	{  	setcolor(YELLOW);
		sprintf(string2," __TURN FOR__ ");
		sprintf(string3," ~~ PLAYER 2~~ ");
		outtextxy(px*13+5,py*11,string2);
		outtextxy(px*13+5,py*12,string3);

		GetMousePos();
		if(pi<=3&&pi>=1&&pj<=3&&pj>=1&&x[pi][pj]==0)
		{
			round(pi,pj,1);
			count++;
			countp2++;
			x[pi][pj]=2;
		}
		else
		{
			sprintf(string4,"TRY AGAIN!");
			setcolor(RED);
			outtextxy(px*13+5,py*14,string4);
			goto start;
		}

	}

}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
int chk11(void)
{
	return( (x[1][1]==x[1][2]&&x[1][1]==x[1][3]&&x[1][3]==x[1][2])||(x[1][1]==x[2][1]&&x[2][1]==x[3][1]&&x[3][1]==x[1][1])||(x[1][1]==x[2][2]&&x[2][2]==x[3][3]&&x[3][3]==x[1][1]) );
}
int chk12(void)
{
	return( (x[1][1]==x[1][2]&&x[1][1]==x[1][3]&&x[1][3]==x[1][2])||(x[1][2]==x[2][2]&&x[2][2]==x[3][2]&&x[3][2]==x[1][2]) );
}
int chk13(void)
{
	return( (x[1][1]==x[1][2]&&x[1][1]==x[1][3]&&x[1][3]==x[1][2])||(x[1][3]==x[2][3]&&x[2][3]==x[3][3]&&x[3][3]==x[1][3])||(x[1][3]==x[2][2]&&x[2][2]==x[3][1]&&x[3][1]==x[1][3]) );
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//----------------FUNCTION TO CHECK WINNER OF SINGLE GAME------------------
void winner(void)
{
	int z;
	z=pi*10+pj;
	switch(z)
	{
		case 11:
			flag=chk11();
			break;
		case 12:
			flag=chk12();
			break;
		case 13:
			flag=chk13();
			break;
		case 21:
			if(x[2][1]==x[2][2]&&x[2][1]==x[2][3]&&x[2][3]==x[2][2])
				flag=1;
			else if(x[1][1]==x[2][1]&&x[2][1]==x[3][1]&&x[3][1]==x[1][1])
				flag=1;
			break;
		case 22:
			if(x[2][1]==x[2][2]&&x[2][1]==x[2][3]&&x[2][3]==x[2][2])
				flag=1;
			else if(x[1][2]==x[2][2]&&x[2][2]==x[3][2]&&x[3][2]==x[1][2])
				flag=1;
			else if(x[1][3]==x[2][2]&&x[2][2]==x[3][1]&&x[3][1]==x[1][3])
				flag=1;
			else if(x[1][1]==x[2][2]&&x[2][2]==x[3][3]&&x[3][3]==x[1][1])
				flag=1;
			break;
		case 23:
			if(x[2][1]==x[2][2]&&x[2][1]==x[2][3]&&x[2][3]==x[2][2])
				flag=1;
			else if(x[1][3]==x[2][3]&&x[2][3]==x[3][3]&&x[3][3]==x[1][3])
				flag=1;
			break;
		case 31:
			if(x[3][1]==x[3][2]&&x[3][1]==x[3][3]&&x[3][3]==x[3][2])
				flag=1;
			else if(x[1][1]==x[2][1]&&x[2][1]==x[3][1]&&x[3][1]==x[1][1])
				flag=1;
		       else if(x[1][3]==x[2][2]&&x[2][2]==x[3][1]&&x[3][1]==x[1][3])
				flag=1;
			break;
		case 32:
			if(x[3][1]==x[3][2]&&x[3][1]==x[3][3]&&x[3][3]==x[3][2])
				flag=1;
			else if(x[1][2]==x[2][2]&&x[2][2]==x[3][2]&&x[3][2]==x[1][2])
				flag=1;
			break;
		case 33:
			if(x[3][1]==x[3][2]&&x[3][1]==x[3][3]&&x[3][3]==x[3][2])
				flag=1;
			else if(x[1][3]==x[2][3]&&x[2][3]==x[3][3]&&x[3][3]==x[1][3])
				flag=1;
			else if(x[1][1]==x[2][2]&&x[2][2]==x[3][3]&&x[3][3]==x[1][1])
				flag=1;
			break;
		default:
			flag=0;
	}
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//-----------------------------MAIN FUNCTION-------------------------------
void main()
{
char ch;
clrscr();
do
{
		 closegraph();
		 winp1=winp2=tie=0;
		 drawgraph();
		 fixdraw();

	do
	{
	startval();
		do
		{
			askentry();
						//used	entryerror();
			winner();

		}while(count<9&&flag==0);
	winround();
	cleargame();

	}while(winp1<=winp2+1&&winp2<=winp1+1);

		nextgame();
		ch=getch();

}while(ch=='n'||ch=='N');
moveto(px*2,py*9);
setcolor(12);
outtext("THANK YOU.......");

getch();
	for(int i=0;i<25;i++)
	{	delay(100);
		printf("\n\n\n");
	}
       //	getch();
closegraph();
}