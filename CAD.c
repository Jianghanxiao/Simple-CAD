#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "graphics.h"
#include "genlib.h"
#include "conio.h"
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include"extgraph.h"
#include<math.h>
#include<string.h>
struct xing
{
	struct xing *ahead;
	int pp;
	double x;
	double y;
	double xx;
	double yy;
	char st[1001];
	struct xing *next;
}*head,*tail,*zhi,*wen;
int size=sizeof(struct xing),dp=0,cs,cg;
char str[1001];
double cx,cy,ccx,ccy,cz;
double Min(double x,double y,double xx,double yy)
{
	double i;
	i=x;
	if(y<i) i=y;
	if(xx<i) i=xx;
	if(yy<i) i=yy;
	return i;
}
void DrawChu()
{
	char* str;
	int x;
	str="欢迎使用CAD程序";
	MovePen(0,6.7);
	DrawTextString(str);
	str="开发者：蒋含啸、张思慧、吴璇";
	MovePen(0,6.5);
	DrawTextString(str);
	str="F1 画线";
	MovePen(0,6.3);
	DrawTextString(str);
	str="F2 画矩形";
	MovePen(0,6.1);
	DrawTextString(str);
	str="F3 画圆";
	MovePen(0,5.9);
	DrawTextString(str);
	str="F4 画文本框";
	MovePen(0,5.7);
	DrawTextString(str);
	SetPenColor("Red");
	str="注：文本框画出后自动进入文本编辑状态,";
	MovePen(0,5.5);
	DrawTextString(str); 
	str="编辑状态到全部编辑完成按Enter停止,支持";
	MovePen(0,5.3);
	DrawTextString(str);
	str="图形元素的选定移动和删除";
	MovePen(0,5.1);
	DrawTextString(str);
	SetPenColor("Black"); 
	x=GetPenSize();
	SetPenSize(4);
	MovePen(0,5);
	DrawLine(3.1,0);
	DrawLine(0,5);
	SetPenSize(x);
}
void DrawBox(double x,double y,double xx,double yy)
{
	MovePen(x,y);
	DrawLine(xx,0);
	DrawLine(0,-yy);
	DrawLine(-xx,0);
	DrawLine(0,yy);
}
void DrawBox1(double xx,double yy,double zz)
{
	MovePen(xx,yy-0.2);
	DrawLine(0,0.5);
	DrawLine(zz,0);
	DrawLine(0,-0.5);
	DrawLine(-zz,0);
}
void DrawCircle(double x,double y,double xx)
{
	MovePen(x+xx,y);
	DrawArc(xx,0,360);
}
void Remove(double zz)
{
	SetEraseMode(TRUE);
	DrawBox1(cx,cy,zz);
	SetEraseMode(FALSE);
}
void RemoveShi(double zz)
{
	SetEraseMode(TRUE);
	StartFilledRegion(1);
	DrawBox1(cx,cy,zz);
	EndFilledRegion();
	SetEraseMode(FALSE);
}
void Keyboard(int key,int event)
{
	double x,y,xx,yy;
	int i;
	struct xing *p;
	switch(event)
	{
		case KEY_DOWN:
			if(dp==0)
			{
				switch(key)
				{
					case VK_F1:
						x=(double)rand()/((double)RAND_MAX+1)*ccx;
						y=(double)rand()/((double)RAND_MAX+1)*ccy;
						MovePen(x,y);
						xx=(double)rand()/((double)RAND_MAX+1)*ccx;
						yy=(double)rand()/((double)RAND_MAX+1)*ccy;
						DrawLine(xx-x,yy-y);
						p=(struct xing*)malloc(size);
						p->pp=1;
						p->x=x;
						p->y=y;
						p->xx=xx-x;
						p->yy=yy-y;
						p->next=NULL;
						p->ahead=tail;
						if(head==NULL) head=p;
						else tail->next=p;
						tail=p;
						break;
					case VK_F2:
						x=(double)rand()/((double)RAND_MAX+1)*ccx;
						y=(double)rand()/((double)RAND_MAX+1)*ccy;
						xx=(double)rand()/((double)RAND_MAX+1)*ccx;
						yy=(double)rand()/((double)RAND_MAX+1)*ccy;
						DrawBox(x,y,xx-x,y-yy);
						p=(struct xing*)malloc(size);
						p->pp=2;
						p->x=x;
						p->y=y;
						p->xx=xx-x;
						p->yy=y-yy;
						p->next=NULL;
						p->ahead=tail;
						if(head==NULL) head=p;
						else tail->next=p;
						tail=p;
						break;
					case VK_F3:
						x=(double)rand()/((double)RAND_MAX+1)*ccx;
						y=(double)rand()/((double)RAND_MAX+1)*ccy;
						xx=(double)rand()/((double)RAND_MAX+1)*Min(x,y,ccx-x,ccy-y);
						DrawCircle(x,y,xx);
						p=(struct xing*)malloc(size);
						p->pp=3;
						p->x=x;
						p->y=y;
						p->xx=xx;
						p->next=NULL;
						p->ahead=tail;
						if(head==NULL) head=p;
						else tail->next=p;
						tail=p;
						break;
					case VK_F4:
						x=(double)rand()/((double)RAND_MAX+1)*ccx;
						y=(double)rand()/((double)RAND_MAX+1)*ccy;
						dp=1;
						cz=0.2;
						cs=cg=0;
						cx=x;
						cy=y;
						str[cg]='|';
						str[cg+1]='\0';
						startTimer(1,250);
						DrawBox1(cx,cy,cz);
						p=(struct xing*)malloc(size);
						wen=p;
						p->pp=4;
						p->x=cx;
						p->y=cy;
						p->next=NULL;
						p->ahead=tail;
						if(head==NULL) head=p;
						else tail->next=p;
						tail=p;
						break;
					case VK_BACK:
						if(zhi!=NULL)
						{
							if(zhi->ahead==NULL)
							{
								if(head!=tail)
								{
									head=head->next;
									head->ahead=NULL;
								}
								else
								{
									head=NULL;
									tail=NULL;
								}
								zhi=NULL;
								InitGraphics();
								DrawChu();
								for(p=head;p!=NULL;p=p->next)
								{
									switch(p->pp)
									{
										case 1:
											MovePen(p->x,p->y);
											DrawLine(p->xx,p->yy);
											break;
										case 2:
											DrawBox(p->x,p->y,p->xx,p->yy);
											break;
										case 3:
											DrawCircle(p->x,p->y,p->xx);
											break;
										case 4:
											MovePen(p->x,p->y);
											DrawTextString(p->st);
											break;
									}
								}
							}
							else
							{
								p=zhi->ahead;
								if(tail!=zhi) 
								{
									p->next=zhi->next;
									zhi->next->ahead=p;
								}
								else 
								{
									p->next=NULL;
									tail=p;
								}
								zhi=NULL;
								InitGraphics();
								DrawChu();
								for(p=head;p!=NULL;p=p->next)
								{
									switch(p->pp)
									{
										case 1:
											MovePen(p->x,p->y);
											DrawLine(p->xx,p->yy);
											break;
										case 2:
											DrawBox(p->x,p->y,p->xx,p->yy);
											break;
										case 3:
											DrawCircle(p->x,p->y,p->xx);
											break;
										case 4:
											MovePen(p->x,p->y);
											DrawTextString(p->st);
											break;
									}
								}
							}
						} 
				}
			}
			else
			{
				switch(key)
				{
					case VK_LEFT:
						if(cg-1>=0) 
						{
							RemoveShi(cz);
							DrawBox1(cx,cy,cz);
							cg--;
							str[cg+1]=str[cg];
							str[cg]='|';
							MovePen(cx,cy);
							DrawTextString(str);
						}
						break;
					case VK_RIGHT:
						if(cg+1<=cs) 
						{
							RemoveShi(cz);
							DrawBox1(cx,cy,cz);
							cg++;
							str[cg-1]=str[cg];
							str[cg]='|';
							MovePen(cx,cy);
							DrawTextString(str);
						}
						break;
					case VK_BACK:
						if(cg==cs&&cg>0)
						{
							RemoveShi(cz);
							Remove(cz);
							cs--;
							str[cg]='\0';
							str[cs]='|';
							cg--;
							cz=cz-0.09;
							DrawBox1(cx,cy,cz);
							MovePen(cx,cy);
							DrawTextString(str);
						}
						if(cg<cs&&cg>0)
						{
							RemoveShi(cz);
							Remove(cz);
							for(i=cg;i<=cs-1;++i)
							str[i]=str[i+1];
							cg--;
							str[cg]='|';
							str[cs]='\0';
							cs--;
							cz-=0.09;
							DrawBox1(cx,cy,cz);
							MovePen(cx,cy);
							DrawTextString(str);
						}
				}
			}
	}
}
void Char(char aa)
{
	int i;
	if(dp==1)
	{	
		if(aa>=32)
		{
			if(cs==cg)
			{
				RemoveShi(cz);
				Remove(cz);
				cz+=0.09;
				DrawBox1(cx,cy,cz);
				str[cs]=aa;
				cs++;
				cg++;
				str[cg]='|';
				str[cg+1]='\0';
				MovePen(cx,cy);
				DrawTextString(str);
			}
			else
			{
				RemoveShi(cz);
				Remove(cz);
				cz+=0.09;
				DrawBox1(cx,cy,cz);
				cs++;
				for(i=cs;i>=cg+1;--i)
				str[i]=str[i-1];
				str[cg]=aa;
				cg++;
				str[cs+1]='\0';
				MovePen(cx,cy);
				DrawTextString(str);
			}
		} 
		if(aa=='\r')
		{
			cancelTimer(1);
			Remove(cz);
			RemoveShi(cz);
			Remove(cz);
			dp=0;
			if(cg==cs) str[cg]='\0';
			else
			{
				for(i=cg;i<=cs-1;++i)
				str[i]=str[i+1];
				str[cs]='\0';
			}
			wen->xx=cz;
			strcpy(wen->st,str);
			MovePen(cx,cy);
			DrawTextString(str);
		}
	}
}
void Timer(int tt)
{
	static int t=1;
	switch(tt)
	{
		case 1:
			if(t==1) 
			{
				t=-t;
				MovePen(cx,cy);
				DrawTextString(str);
			}
			else
			{
				t=-t;
				RemoveShi(cz);
				Remove(cz);
				str[cg]=' ';
				DrawBox1(cx,cy,cz);
				MovePen(cx,cy);
				DrawTextString(str);
				str[cg]='|';
			}
			break;
	}
}
void Mouse(int x,int y,int button,int event)
{
	double mx,my;
	static double omx,omy;
	struct xing *p;
	static int move=0;
	mx=ScaleXInches(x);
	my=ScaleYInches(y);
	switch(event)
	{
		case BUTTON_DOWN:
			omx=mx;
			omy=my;
			if(button==LEFT_BUTTON)
			{
				move=1;
				if(zhi!=NULL)
				{
					switch(zhi->pp)
					{
						case 1:
							MovePen(zhi->x,zhi->y);
							DrawLine(zhi->xx,zhi->yy);
							break;
						case 2:
							DrawBox(zhi->x,zhi->y,zhi->xx,zhi->yy);
							break;
						case 3:
							DrawCircle(zhi->x,zhi->y,zhi->xx);
							break;
						case 4:
							MovePen(zhi->x,zhi->y);
							DrawTextString(zhi->st);
							break;
					}
				}
				zhi=NULL;
				for(p=head;p!=NULL;p=p->next)
				{
					switch(p->pp)
					{
						case 1:
							if(p->x+p->xx>=p->x)
							{
								if(mx>=p->x&&mx<=p->x+p->xx)
								{
									if(p->y+p->yy>=p->y)
									{
										if(my>=p->y&&my<=p->y+p->yy) zhi=p;	
									}
									else 
									{
										if(my<=p->y&&my>=p->y+p->yy) zhi=p;
									}
								}
							}
							else
							{
								if(mx<=p->x&&mx>=p->x+p->xx)
								{
									if(p->y+p->yy>=p->y)
									{
										if(my>=p->y&&my<=p->y+p->yy) zhi=p;	
									}
									else 
									{
										if(my<=p->y&&my>=p->y+p->yy) zhi=p;
									}
								}
							}
							break;
						case 2:
							if(p->x+p->xx>=p->x)
							{
								if(mx>=p->x&&mx<=p->x+p->xx)
								{
									if(p->y-p->yy>=p->y)
									{
										if(my>=p->y&&my<=p->y-p->yy) zhi=p;	
									}
									else 
									{
										if(my<=p->y&&my>=p->y-p->yy) zhi=p;
									}
								}
							}
							else
							{
								if(mx<=p->x&&mx>=p->x+p->xx)
								{
									if(p->y-p->yy>=p->y)
									{
										if(my>=p->y&&my<=p->y-p->yy) zhi=p;	
									}
									else 
									{
										if(my<=p->y&&my>=p->y-p->yy) zhi=p;
									}
								}
							}
							break;
						case 3:
							if(sqrt(pow(mx-p->x,2)+pow(my-p->y,2))<=p->xx) zhi=p;
							break;
						case 4:
							if(mx>=p->x&&mx<=p->x+p->xx&&my>=p->y-0.2&&my<=p->y+0.3) zhi=p;
							break;
					}
					if(zhi!=NULL) break;
				}
				if(zhi!=NULL)
				{
					SetPenColor("Red");
					switch(zhi->pp)
					{
						case 1:
							MovePen(zhi->x,zhi->y);
							DrawLine(zhi->xx,zhi->yy);
							break;
						case 2:
							DrawBox(zhi->x,zhi->y,zhi->xx,zhi->yy);
							break;
						case 3:
							DrawCircle(zhi->x,zhi->y,zhi->xx);
							break;
						case 4:
							MovePen(zhi->x,zhi->y);
							DrawTextString(zhi->st);
							break;
					}
					SetPenColor("Black");
				}
			}
			break;
		case BUTTON_UP:
			if(button==LEFT_BUTTON) move=0;
			break;
		case MOUSEMOVE:
			if(move==1&&zhi!=NULL)
			{
				switch(zhi->pp)
				{
					case 1:
						zhi->x+=mx-omx;
						zhi->y+=my-omy;
						omx=mx;
						omy=my;
						InitGraphics();
						DrawChu();
						for(p=head;p!=NULL;p=p->next)
						{
							switch(p->pp)
							{
								case 1:
									MovePen(p->x,p->y);
									DrawLine(p->xx,p->yy);
									break;
								case 2:
									DrawBox(p->x,p->y,p->xx,p->yy);
									break;
								case 3:
									DrawCircle(p->x,p->y,p->xx);
									break;
								case 4:
									MovePen(p->x,p->y);
									DrawTextString(p->st);
									break;
							}
						}
						SetPenColor("Red");
						MovePen(zhi->x,zhi->y);
						DrawLine(zhi->xx,zhi->yy);
						SetPenColor("Black");
						break;
					case 2:
						zhi->x+=mx-omx;
						zhi->y+=my-omy;
						omx=mx;
						omy=my;
						InitGraphics();
						DrawChu();
						for(p=head;p!=NULL;p=p->next)
						{
							switch(p->pp)
							{
								case 1:
									MovePen(p->x,p->y);
									DrawLine(p->xx,p->yy);
									break;
								case 2:
									DrawBox(p->x,p->y,p->xx,p->yy);
									break;
								case 3:
									DrawCircle(p->x,p->y,p->xx);
									break;
								case 4:
									MovePen(p->x,p->y);
									DrawTextString(p->st);
									break;
							}
						}
						SetPenColor("Red");
						DrawBox(zhi->x,zhi->y,zhi->xx,zhi->yy);
						SetPenColor("Black");
						break;
					case 3:
						zhi->x+=mx-omx;
						zhi->y+=my-omy;
						omx=mx;
						omy=my;
						InitGraphics();
						DrawChu();
						for(p=head;p!=NULL;p=p->next)
						{
							switch(p->pp)
							{
								case 1:
									MovePen(p->x,p->y);
									DrawLine(p->xx,p->yy);
									break;
								case 2:
									DrawBox(p->x,p->y,p->xx,p->yy);
									break;
								case 3:
									DrawCircle(p->x,p->y,p->xx);
									break;
								case 4:
									MovePen(p->x,p->y);
									DrawTextString(p->st);
									break;
							}
						}
						SetPenColor("Red");
						DrawCircle(zhi->x,zhi->y,zhi->xx);
						SetPenColor("Black");
						break;
					case 4:
						zhi->x+=mx-omx;
						zhi->y+=my-omy;
						omx=mx;
						omy=my;
						InitGraphics();
						DrawChu();
						for(p=head;p!=NULL;p=p->next)
						{
							switch(p->pp)
							{
								case 1:
									MovePen(p->x,p->y);
									DrawLine(p->xx,p->yy);
									break;
								case 2:
									DrawBox(p->x,p->y,p->xx,p->yy);
									break;
								case 3:
									DrawCircle(p->x,p->y,p->xx);
									break;
								case 4:
									MovePen(p->x,p->y);
									DrawTextString(p->st);
									break;
							}
						}
						SetPenColor("Red");
						MovePen(zhi->x,zhi->y);
						DrawTextString(zhi->st);
						SetPenColor("Black");
						break;
				}
			}
	}
}
void Main()
{
	head=tail=NULL;
	InitGraphics();
	ccx=GetWindowWidth();
	ccy=GetWindowHeight();
	Randomize();
	DrawChu();
	registerKeyboardEvent(Keyboard);
	registerCharEvent(Char);
	registerTimerEvent(Timer);
	registerMouseEvent(Mouse);
}
