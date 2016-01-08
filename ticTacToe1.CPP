//-------------------------------------------------------------------------
//			Game of tic_tac_toe
//			Pogramer:RAJ_P_SHAH
//			Date:March 2015
//			Compiler:Turbo C7
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//------------------------------HEADER FILES-------------------------------
#include<conio.h>
//	#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
//-------------------------------------------------------------------------

int px,py;
char strp1[20],strp2[20],strtie[20],string1[20],string2[20],string3[20],string4[20];
int x[4][4],count,countp1,countp2,winp1,winp2,tie,flag,pi,pj;
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
//----------------------FUNCTION TO DRAW FIXED ITEMS-----------------------
void fixdraw(void)
{


//	printf("%d %d %d %d",px,py,getmaxx(),getmaxy());
	setcolor(CYAN);                                //MAIN BOX
	rectangle(px-15,py-15,px*19+15,py*19+15);
	rectangle(px-10,py-10,px*19+10,py*19+10);
	settextstyle(7,0,1);
       //	setcolor(LIGHTGRAY);
	moveto(px,py);
	outtext("GAME OF TIC_TAC_TOE...");
	moveto(px,py*2);
	outtext("BY RAJ_P_SHAH");

	setcolor(CYAN);                              //INSTRUCTION BOX
	rectangle(px,py*16,px*19+5,py*19);
	moveto(px,py*16+5);
	settextstyle(0,0,0);
	outtext(" INSTRUCTIONS:                                             POSITIONS:");
	moveto(px,py*17);
	outtext(" Player 1(Cross) will play first & then Player 2(Round)  1,1  1,2  1,3");
	moveto(px,py*18-6);
	outtext(" Enter any key after entry in j..&..Enter 0,0 To EXIT..  2,1  2,2  2,3");
	moveto(px,py*18+10);
	outtext("                    Give position when your turn comes:  3,1  3,2  3,3");


	setcolor(LIGHTBLUE);                             //SCORE BOX
	rectangle(px*13,py*2,px*18,py*15);
	settextstyle(3,0,2);
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
	setcolor(GREEN);
	line(px*14,py*8+10,px*17,py*8+10);
	outtextxy(px*14+7,py*9,"-MOVES-");

	setcolor(WHITE);                            //GAME AREA
	line(px*2,py*11,px*11,py*11);
	line(px*2,py*8,px*11,py*8);
	line(px*5,py*5,px*5,py*14);
	line(px*8,py*5,px*8,py*14);
	for(int q=0;q<20;q++)
	{
		string1[q]=' ';
		string2[q]=' ';
		string3[q]=' ';
		string4[q]=' ';
		strp1[q]=' ';
		strp2[q]=' ';
		strtie[q]=' ';
	}

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
	int posx=px*(0.5);
	int posy=py*(3.5);
	circle(posx+(px*3*b),posy+(py*3*a),py);

}

void cross(int a,int b,int c)
{
	if(c==1)
		setcolor(BROWN);
	else if(c==0)
		setcolor(BLACK);
	int posx=px*(0.5)+(px*3*b);
	int posy=py*(3.5)+(py*3*a);

	line(posx-px,posy-py,posx+px,posy+py);
	line(posx+px,posy-py,posx-px,posy+py);

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
	 setcolor(GREEN);
	 if(winp1==winp2+2)
	 {
		outtext("CONGRATULATIONS PLAYER1 FOR WINNING THE WHOLE GAME....!");
	 }
	 else
	 {
		outtext("CONGETULATIONS PLAYER2 FOR WINNING THE WHOLE GAME.....!");
	 }
	 getch();
       //	 setviewport(px*2,py*5,px*11,py*14,0);
       //	 clearviewport();
	 settextstyle(5,0,1);
	 moveto(px*2,py*5);
	 outtext("Enter n/N For NEW Game.");
	 moveto(px*2,py*6);
	 outtext("Enter e/E To EXIT.");

	 moveto(px*2,py*7);
	 outtext("          Enter Your Choice:");
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
		outtextxy(px*2,py*15,"MATCH TIED...    Enter any Key");
		getch();
		setcolor(BLACK);
		outtextxy(px*2,py*15,"MATCH TIED...    Enter any Key");
		sprintf(strtie,"TIED:  %d",tie);
		outtextxy(px*13+54,py*6,strtie);
		tie++;
		setcolor(LIGHTBLUE);
		sprintf(strtie,"TIED:  %d",tie);
		outtextxy(px*13+54,py*6,strtie);
	}
	else if(count%2==1)
	{

		setcolor(BROWN);
		outtextxy(px*2,py*15,"Congratulations Player1...    Enter any key:");
		getch();
		setcolor(BLACK);
		outtextxy(px*2,py*15,"Congratulations Player1...    Enter any key:");
		sprintf(strp1,"PLAYER 1:  %d",winp1);
		outtextxy(px*13+5,py*4,strp1);
		setcolor(LIGHTBLUE);
		winp1++;
		sprintf(strp1,"PLAYER 1:  %d",winp1);
		outtextxy(px*13+5,py*4,strp1);

	}
	else if(count%2==0)
	{

		setcolor(YELLOW);
		outtextxy(px*2,py*15,"Congratulations Player2...    Enter any key:");
		getch();
		setcolor(BLACK);
		outtextxy(px*2,py*15,"Congratulations Player2...    Enter any key:");
		sprintf(strp2,"PLAYER 2:  %d",winp2);
		outtextxy(px*13+5,py*5,strp2);
		setcolor(LIGHTBLUE);
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
//-------------------FUNCTION TOCHECK ERROR IN ENTRY-----------------------
//int inputerr(void)
//{
//	if(pi<=3&&pi>=1&&pj<=3&&pj>=1&&x[pi][pj]==0)
//		return 1;
//	else
//		return 0;
//}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//-----------------------FUNCTION TO ASK FOR ENTRY-------------------------
void askentry(void)
{ // int error=0;
	start:
	setcolor(BLACK);
	outtextxy(px*13+5,py*14,string4);
	outtextxy(px*13+5,py*10,string1);
	outtextxy(px*13+5,py*11,string2);
	outtextxy(px*13+5,py*12,string3);

	//setcolor(GREEN);
	if(count%2==0)
	{       setcolor(GREEN);
		sprintf(string1,"PLAYER 1:");
		sprintf(string2,"ENTER i:");
		sprintf(string3,"ENTER j:");
		outtextxy(px*13+5,py*10,string1);
		outtextxy(px*13+5,py*11,string2);
		pi=getch()-48;
		sprintf(string2,"ENTER i:%d",pi);
		outtextxy(px*13+5,py*11,string2);
		outtextxy(px*13+5,py*12,string3);
		pj=getch()-48;
		sprintf(string3,"ENTER j:%d",pj);
		outtextxy(px*13+5,py*12,string3);
		getch();
		if(pi==0&&pj==0)
			exit(1);
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
			getch();
			goto start;
		}
	}
	else
	{  	setcolor(GREEN);
		sprintf(string1,"PLAYER 2:");
		sprintf(string2,"ENTER i:");
		sprintf(string3,"ENTER j:");
		outtextxy(px*13+5,py*10,string1);
		outtextxy(px*13+5,py*11,string2);
		pi=getch()-48;
		sprintf(string2,"ENTER i:%d",pi);
		outtextxy(px*13+5,py*11,string2);
		outtextxy(px*13+5,py*12,string3);
		pj=getch()-48;
		sprintf(string3,"ENTER j:%d",pj);
		outtextxy(px*13+5,py*12,string3);
		getch();
		if(pi==0&&pj==0)
			exit(1);
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
			getch();
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
{ 		 winp1=winp2=tie=0;
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
		closegraph();
}while(ch=='n'||ch=='N');
moveto(px*2,py*9);
outtext("THANK YOU.......");

getch();
/*for(int i=0;i<25;i++)
	{	delay(50);
		printf("\n\n\n");
	}
*/
closegraph();
}