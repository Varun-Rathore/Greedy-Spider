#include<iostream>
#include<graphics.h>
#include<stdio.h>
#include<time.h>
#include<algorithm>
#include<list>
using namespace std;
struct gra
{
    int val;
    int degree;
};
bool comparedegree(gra a, gra b)
{
    if(a.degree > b.degree)
    {
        return true;
    }
    return false;
}
bool isplaner(int web[100][100],int deg[100],int n)
{
    struct gra g[n];
    int i;
    for(i=0;i<n;i++)
    {
        g[i].val=i;
        g[i].degree=deg[i];
    }
    sort(g,g+n,comparedegree);
    list<int> remaining,tmp;
    for(i=0;i<n;i++)
    {
        remaining.push_back(g[i].val);
    }
    int cnt=0;
    while(!remaining.empty())
    {
        list<int>::iterator itr,itr2;
        tmp.clear();
        for(i=0;i<remaining.size()+1;i++)
        {
            if(tmp.empty())
            {
                itr=remaining.begin();
                tmp.push_back(*itr);
                int del=*itr;
                itr++;
                remaining.remove(del);
            }
            else
            {
                for(itr2=tmp.begin();itr2!=tmp.end();itr2++)
                {
                    if(web[*itr][*itr2]==1)
                    {
                        break;
                    }
                }
                if(itr2==tmp.end())
                {
                    tmp.push_back(*itr);
                    int del=*itr;
                    itr++;
                    remaining.remove(del);
                }
                else
                {
                    itr++;
                }
            }
        }
        cnt++;
    }
    if(cnt>4)
    {
        return false;
    }
    else
    {
        return true;
    }
}
void fly1(int x,int y)
{
    setcolor(BROWN);//head
    setfillstyle(SOLID_FILL,BROWN);//head
    pieslice(x,y-16,0,360,6);//head
    line(x-2,y-22,x-3,y-28);
    line(x+2,y-22,x+3,y-28);
    pieslice(x-3,y-28,0,360,2);
    pieslice(x+4,y-28,0,360,2);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    pieslice(x-2,y-19,0,360,1);//eyes L
    pieslice(x+2,y-19,0,360,1);//eyes R
    pieslice(x,y-13,0,360,1);


    setcolor(RED);//body
    setfillstyle(SOLID_FILL,RED);//body
    pieslice(x,y-7,0,360,4);//body
    pieslice(x,y-2,0,360,6);//body
    pieslice(x,y+3,0,360,7);//body
    pieslice(x,y+8,0,360,6);//body
    pieslice(x,y+13,0,360,4);//body

    setcolor(LIGHTGRAY);
    arc(x,y-7,180,360,5);//body scales
    arc(x,y-2,180,360,7);//body scales
    arc(x,y+3,180,360,8);//body scales
    arc(x,y+8,180,360,7);//body scales
    arc(x,y+13,180,360,5);//body scales

}
void fly2(int x,int y)
{
    setcolor(BROWN);//head
    setfillstyle(SOLID_FILL,BROWN);//head
    pieslice(x,y-16,0,360,6);//head
    line(x-2,y-22,x-3,y-28);
    line(x+2,y-22,x+3,y-28);
    pieslice(x-3,y-28,0,360,2);
    pieslice(x+4,y-28,0,360,2);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    pieslice(x-2,y-19,0,360,1);//eyes L
    pieslice(x+2,y-19,0,360,1);//eyes R
    pieslice(x,y-13,0,360,1);


    setcolor(BLUE);//body
    setfillstyle(SOLID_FILL,BLUE);//body
    pieslice(x,y-7,0,360,4);//body
    pieslice(x,y-2,0,360,6);//body
    pieslice(x,y+3,0,360,7);//body
    pieslice(x,y+8,0,360,6);//body
    pieslice(x,y+13,0,360,4);//body

    setcolor(LIGHTGRAY);
    arc(x,y-7,180,360,5);//body scales
    arc(x,y-2,180,360,7);//body scales
    arc(x,y+3,180,360,8);//body scales
    arc(x,y+8,180,360,7);//body scales
    arc(x,y+13,180,360,5);//body scales
}
int findminimum(int web[100][100],int vis[],int dis[],int n)
{
    int mini=999;
    int pos=-1;
    for(int i=0;i<n;i++)
    {
        if(dis[i]<mini && vis[i]==0)
        {
            mini=dis[i];
            pos=i;
        }
    }
    return pos;
}
int finddistance(int web[100][100],int src,int n,int spider)
{
    int dis[n];
    int path[n];
    int vis[n];
    int init=src;
    for(int i=0;i<n;i++)
    {
        dis[i]=9999;
        path[i]=-1;
        vis[i]=0;
    }
    dis[src]=0;
    vis[src]=1;
    for(int cnt=0;cnt<n;cnt++)
    {
        for(int j=0;j<n;j++)
        {
            if(web[src][j]==1)
            {
                if(dis[j]==9999)
                {
                    dis[j]=dis[src]+web[src][j];
                    path[j]=src;
                }
                else
                {
                    if(dis[j]>dis[src]+web[src][j])
                    {
                        dis[j]=dis[src]+web[src][j];
                        path[j]=src;
                    }
                }
            }
        }
        src=findminimum(web,vis,dis,n);
        vis[src]=1;
    }
    int reach=-1;
    if(path[spider]==-1)
    {
        return -1;
    }
    else
        reach=spider;
    while(1)
    {
        if(path[reach]==init)
        {
            return reach;
        }
        else
        {
            reach=path[reach];
        }
    }
}
int finddistance(int web[100][100],int src,int n,int f1,int f2)
{
    int dis[n];
    int path[n];
    int vis[n];
    int init=src;
    for(int i=0;i<n;i++)
    {
        dis[i]=9999;
        path[i]=-1;
        vis[i]=0;
    }
    dis[src]=0;
    vis[src]=1;
    for(int cnt=0;cnt<n;cnt++)
    {
        for(int j=0;j<n;j++)
        {
            if(web[src][j]==1)
            {
                if(dis[j]==9999)
                {
                    dis[j]=dis[src]+web[src][j];
                    path[j]=src;
                }
                else
                {
                    if(dis[j]>dis[src]+web[src][j])
                    {
                        dis[j]=dis[src]+web[src][j];
                        path[j]=src;
                    }
                }
            }
        }
        src=findminimum(web,vis,dis,n);
        vis[src]=1;
    }
    int reach=-1;
    if(path[f1]==-1)
    {
        if(path[f2]==-1)
        {
            return -1;
        }
        else
            reach=f2;
    }
    else if(path[f2]==-1)
        reach=f1;
    else if(dis[f2]<dis[f1])
        reach=f2;
    else
        reach=f1;
    while(1)
    {
        if(path[reach]==init)
        {
            return reach;
        }
        else
        {
            reach=path[reach];
        }
    }
}
void makegraph(int web[100][100],int node[100][2],int n)
{
	int i,j;
	char msg[10];
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
			moveto(node[i][0],node[i][1]);
			sprintf(msg,"%c",i+65);
			setcolor(YELLOW);
			outtext(msg);
			setcolor(WHITE);
			if(web[i][j]==1)
			{
				line(node[i][0],node[i][1],node[j][0],node[j][1]);
			}
		}
	}
}
int spiassign(int web[100][100],int deg[100],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        if(deg[i]>1)
        {
            for(j=i+1;j<n;j++)
                if(web[i][j]==1)
                {
                    return i;
                }
        }
    }
    return -1;
}
int nodeassign(int web[100][100],int n,int a)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
            if(web[i][j]==1 && i!=a && web[i][a]==0)
            {
                return i;
            }
    }
    return -1;
}
int nodeassign(int web[100][100],int n,int a,int b)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
            if(web[i][j]==1 && i!=a && web[i][a]==0 && i!=b)
            {
                return i;
            }
    }
    return -1;
}
void makespider(int x,int y)
{
    setcolor(RED);
    setfillstyle(SOLID_FILL,RED); //head
    pieslice(x,y-6,0,360,6);

    setcolor(LIGHTGRAY);//body
    circle(x-3,y-8,1.5);//eye left
    circle(x+2,y-8,1.5);//eye right
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    pieslice(x,y,150,390,5);//body 1
    pieslice(x,y+4,150,390,4);// body 2

    line(x-7,y-7,x-14,y-13);//left 1
    line(x-14,y-13,x-12,y-23);
    line(x+6,y-7,x+12,y-13);//right 1
    line(x+12,y-13,x+10,y-23);

    line(x-7,y-2,x-16,y-7);//left 2
    line(x-16,y-7,x-21,y-15);
    line(x+6,y-2,x+14,y-7);//right 2
    line(x+14,y-7,x+19,y-15);

    line(x-7,y+3,x-15,y);//left 3
    line(x-15,y,x-25,y-7);
    line(x+6,y+3,x+15,y);//right 3
    line(x+15,y,x+25,y-7);

    line(x-6,y+6,x-12,y+6);//left 4
    line(x-12,y+6,x-20,y+14);
    line(x+6,y+6,x+12,y+6);//right 4
    line(x+12,y+6,x+20,y+14);

    line(x-4,y-12,x-4,y-17); //tongue
    line(x+2,y-12,x+2,y-17); //tongue
    setcolor(WHITE);
}
void circ(int x,int y)
{
    setcolor(GREEN);
	circle(x+5,y+5,12);
    setcolor(WHITE);
}
void normal()
{
	int node[100][2];
	retry:
	system("cls");
	cleardevice();
	int maxx=getmaxx()*0.9,maxy=getmaxy()*0.9;
	srand(time(0));
	int web[100][100];
	int n=6;
	int i,j;
	int spinode=0;
	int diff=1;
	int won=0;
	while(1)
    {
        int deg[100]={0};
        for(i=0;i<n;i++)
        {
            for(j=i;j<n;j++)
            {
                if(i==j)
                {
                    web[i][j]=0;
                }
                else
                {
                    web[i][j]=rand()%2;
                    web[j][i]=web[i][j];
                    if(web[i][j]==1)
                    {
                        deg[i]++;
                        deg[j]++;
                    }
                }
            }
        }
        if(!isplaner(web,deg,n))
        {
            continue;
        }
        for(i=0;i<n;i++)
        {
            reassign:
            node[i][0]=rand()%maxx+5;
            node[i][1]=rand()%maxy+5;
            for(j=0;j<i;j++)
                if(abs(node[i][0]-node[j][0])<30 || abs(node[i][1]-node[j][1])<30)
                    goto reassign;
        }
        spinode=spiassign(web,deg,n);
        int f1=nodeassign(web,n,spinode);
        int f2=nodeassign(web,n,spinode,f1);
        if(f1==-1 || f2==-1 || spinode==-1)
            continue;
        int ispossible=finddistance(web,spinode,n,f1,f2);
        if(ispossible==-1)
            continue;
        while(1)
        {
            system("cls");
            cleardevice();
            fly1(node[f1][0],node[f1][1]);
            fly2(node[f2][0],node[f2][1]);
            makegraph(web,node,n);
            makespider(node[spinode][0],node[spinode][1]);
            if(spinode==-1)
            {
                cleardevice();
                outtextxy(90,10,"YOU WON");
                outtextxy(90,50,"LOADING NEXT LEVEL");
                delay(3000);
                won++;
                break;
            }
            else if(spinode==f1 || spinode==f2)
            {
                delay(2000);
                cleardevice();
                outtextxy(90,10,"YOU LOSE");
                char msg[30];
                sprintf(msg,"YOUR SCORE IS %d",won);
                outtextxy(90,50,msg);
                delay(2000);
                return;
            }
            int a,b;
            a=getch();
            a=a-96;
            circ(node[a-1][0],node[a-1][1]);
            b=getch();
            b=b-96;
            circ(node[b-1][0],node[b-1][1]);
            if(a>n || b>n)
            {
                cout<<"invalid node try again";
                delay(2000);
                continue;
            }
            else
            {
                if(web[a-1][b-1]==1)
                {
                    web[a-1][b-1]=0;
                    web[b-1][a-1]=0;
                    setcolor(GREEN);
                    line(node[a-1][0],node[a-1][1],node[b-1][0],node[b-1][1]);
                    delay(2000);
                    setcolor(WHITE);
                }
                else
                {
                    cout<<"invalid node try again";
                    delay(2000);
                    continue;
                }
            }
            spinode=finddistance(web,spinode,n,f1,f2);
        }
        if(diff%3==0)
        {
            n++;
        }
        diff++;
    }
	system("cls");
	cleardevice();
	return;
}
void hunter()
{
	int node[100][2];
	retry:
	system("cls");
	cleardevice();
	int maxx=getmaxx()*0.9,maxy=getmaxy()*0.9;
	srand(time(0));
	int web[100][100];
	int deg[100]={0};
	int n=6;
	int i,j;
	int spinode=0;
	int diff=1;
	int won=0;
	while(1)
    {
        int deg[100]={0};
        for(i=0;i<n;i++)
        {
            for(j=i;j<n;j++)
            {
                if(i==j)
                {
                    web[i][j]=0;
                }
                else
                {
                    web[i][j]=rand()%2;
                    web[j][i]=web[i][j];
                    if(web[i][j]==1)
                    {
                        deg[i]++;
                        deg[j]++;
                    }
                }
            }
        }
        if(!isplaner(web,deg,n))
        {
            continue;
        }
        for(i=0;i<n;i++)
        {
            reassign:
            node[i][0]=rand()%maxx+5;
            node[i][1]=rand()%maxy+5;
            for(j=0;j<i;j++)
                if(abs(node[i][0]-node[j][0])<30 || abs(node[i][1]-node[j][1])<30)
                    goto reassign;
        }
        spinode=spiassign(web,deg,n);
        int f1=nodeassign(web,n,spinode);
        int f2=nodeassign(web,n,spinode,f1);
        if(f1==-1 || f2==-1 || spinode==-1)
            continue;
        int ispossible=finddistance(web,f1,n,spinode);
        if(ispossible==-1)
            continue;
        ispossible=finddistance(web,f2,n,spinode);
        if(ispossible==-1)
            continue;
        while(1)
        {
            system("cls");
            cleardevice();
            fly1(node[f1][0],node[f1][1]);
            fly2(node[f2][0],node[f2][1]);
            makegraph(web,node,n);
            makespider(node[spinode][0],node[spinode][1]);
            if(f1==-1 && f2==-1)
            {
                cleardevice();
                outtextxy(90,10,"YOU WON");
                outtextxy(90,50,"LOADING NEXT LEVEL");
                delay(3000);
                won++;
                break;
            }
            else if(spinode==f1 || spinode==f2)
            {
                delay(2000);
                cleardevice();
                outtextxy(90,10,"YOU LOSE");
                char msg[30];
                sprintf(msg,"YOUR SCORE IS %d",won);
                outtextxy(90,50,msg);
                delay(2000);
                return;
            }
            int a,b;
            a=getch();
            a=a-96;
            circ(node[a-1][0],node[a-1][1]);
            b=getch();
            b=b-96;
            circ(node[b-1][0],node[b-1][1]);
            if(a>n || b>n)
            {
                cout<<"invalid node try again";
                delay(2000);
                continue;
            }
            else
            {
                if(web[a-1][b-1]==1)
                {
                    web[a-1][b-1]=0;
                    web[b-1][a-1]=0;
                    setcolor(GREEN);
                    line(node[a-1][0],node[a-1][1],node[b-1][0],node[b-1][1]);
                    delay(2000);
                }
                else
                {
                    cout<<"invalid node try again";
                    delay(2000);
                    continue;
                }
            }
            f1=finddistance(web,f1,n,spinode);
            f2=finddistance(web,f2,n,spinode);
        }
        if(diff%3==0)
        {
            n++;
        }
        diff++;
    }
	system("cls");
	cleardevice();
	return;
}
int main()
{
	int gdriver=DETECT,gmode;
	detectgraph(&gdriver,&gmode);
	initgraph(&gdriver,&gmode,NULL);
	int d;
	int y=55;
	bool loop=true;
	while(loop)
    {
        system("cls");
        cleardevice();
        setcolor(CYAN);
        outtextxy(150,50,"NORMAL MODE");
        outtextxy(150,90,"HUNTER MODE");
        outtextxy(150,130,"EXIT");
        setcolor(WHITE);
        line(120,y,140,y);
        line(130,y-5,140,y);
        line(130,y+5,140,y);
        d=getch();
        if(d==80)
        {
            if(y==135)
            {
                y=55;
            }
            else
                y=y+40;
        }
        else if(d==72)
        {
            if(y==55)
            {
                y=135;
            }
            else
                y=y-40;
        }
        else if(d==13)
        {
            switch(y)
            {
                case 55:
                    system("cls");
                    cleardevice();
                    outtextxy(150,150,"ENTERING NORMAL MODE");
                    delay(1000);
                    normal();
                    break;
                case 95:
                    system("cls");
                    cleardevice();
                    outtextxy(150,150,"ENTERING HUNTER MODE");
                    delay(1000);
                    hunter();
                    break;
                case 135:
                    system("cls");
                    cleardevice();
                    outtextxy(150,150,"EXITING");
                    delay(1000);
                    loop=false;
                    break;
            }
        }
    }
    system("cls");
    cleardevice();
    closegraph();
    return 0;
}

