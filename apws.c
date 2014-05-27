#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void parse_input(FILE *);
int process_string();
struct status
{
        int knot;
        char knotstats[50];
        int lipr[50];
	int lipc[50];
	int curr;
};
void process(char ,struct status *,int ,int ,int * );
void changedir(int ,int *,int *,int *);
int row,coloumn;
char **grid;

int main(int *argc,char *argv[])
{
	FILE *input;	
	int answer=0;

	if((input=fopen("apws.in","r"))== NULL)
        {
                printf("Error opening configuration file.\n");
                exit(1);
        }

	parse_input(input);

	answer=process_string();

	if(answer==1)
		printf("\nKnotted\n");
	else
		printf("\nStraightiened\n");

	return 0;
}

void parse_input(FILE * input)
{
	int i=0,j=0;
	char line[50];

	while(fgets(line,50,input)!=NULL)
	{
		if(line[0]== ' ' || line[0]== '\n' || line[0]=='\t')
			continue;
		
		else if(sscanf(line,"%d %d",&row,&coloumn))
		{
			grid=(char **)calloc(row,sizeof(char *));
                        if(grid == NULL)
			{
				printf("Grid Memory allocation Failed.\n");
				exit(1);
			}
			for(j=0;j<row;j++)
                        {
				grid[j]=(char *)calloc(coloumn+1,sizeof(char));
                                if(grid[j]==NULL)
                                {
                                    printf("Grid Memory allocation Failed.\n");
                                    exit(0);
                                }
                        }			
			continue;
		}
		else if(sscanf(line,"%s",grid[i]))
		{
			i++;
			continue;
		}
		else
		{
			printf("Input file not proper.\n");
			exit(0);
		}
	}
	for(i=0;i<row;i++)
		printf("%s\n",grid[i]);
}

int process_string()
{
	int startr=-1,startc=-1,endr=-1,endc=-1;
	int i,j,rowt=0,colt=0,direction=0;
	char cur;
	struct status curstat;
	
	curstat.knot=0;
	curstat.curr=1;
	for(i=0;i<50;i++)
	{
		curstat.lipr[i]=-1;
		curstat.lipc[i]=-1;
		curstat.knotstats[i]='\0';
	}
        curstat.knotstats[0]='X';
	for(i=0;i<row;i++)
	{
		if(grid[i][0]=='-' && startr==-1)
		{
			startr=i;
			startc=0;
		}
		else if(grid[i][0]=='-' && startr!=-1)
		{
			endr=i;
			endc=0;
		}
	}
	for(i=0;i<coloumn;i++)
	{
		if(grid[0][i]=='|' && startc==-1)
		{
			startc=i;
			startr=0;
		}
		else if(grid[0][i]=='|' && startc!=-1)
		{
			endc=i;
			endr=0;
		}
	}
	for(i=0;i<row;i++)
        {
                if(grid[i][coloumn-1]=='-' && startr==-1)
        	{
	                startr=i;
			startc=coloumn-1;
		}
                else if(grid[i][coloumn-1]=='-' && startr!=-1)
                {
		        endr=i;
			endc=coloumn-1;
		}
        }
        for(i=0;i<coloumn;i++)
        {
                if(grid[row-1][i]=='|' && startc==-1)
		{
                        startc=i;
			startr=row-1;
		}
                else if(grid[row-1][i]=='|' && startc!=-1)
		{
                        endc=i;
			endr=row-1;
		}
        }
	rowt=startr;
	colt=startc;
	while(rowt!=endr && colt!=endc)
	{
		switch (direction)
		{
			case 0:
			for(;(cur=grid[rowt][colt])!='+'|| (colt==endc && rowt==endr);colt++)
				process(cur,&curstat,rowt,colt,&direction);
			break;

			case 1:
			for(;(cur=grid[rowt][colt])!='+' || (colt==endc && rowt==endr);rowt++)
				process(cur,&curstat,rowt,colt,&direction);
			break;

			case 2:
			for(;(cur=grid[rowt][colt])!='+' || (colt==endc && rowt==endr);colt--)
				process(cur,&curstat,rowt,colt,&direction);
			break;

			case 3:
			for(;(cur=grid[rowt][colt])!='+'|| (colt==endc && rowt==endr);rowt--)
				process(cur,&curstat,rowt,colt,&direction);
			break;
		}
		if(rowt==endr && colt==endc)
			break;

		if(direction==0 || direction==2)
			changedir(0,&direction,&rowt,&colt);
		else
			changedir(1,&direction,&rowt,&colt);
	}
	if(strstr(curstat.knotstats,"DUD")==NULL || strstr(curstat.knotstats,"UDU")==NULL)
		curstat.knot=2;
	else
		curstat.knot=1;

	return curstat.knot;
}
void process(char cur,struct status *curstat,int rowt,int colt,int *direction)
{
	char temp='\0';
	switch(cur)
	{
		case '.':
		printf("Impossible outcome.\n");
		exit(0);

		case '-':
		case '|':
		return;

		case 'H':
		if(*direction==0 || *direction==2)
			temp='U';
		else
			temp='D';
		break;

		case 'I':
		if(*direction==0 || *direction==2)
			temp='D';
		else
			temp='U';
		break;
	}
	if((curstat->lipr[curstat->curr-1]==rowt && curstat->lipc[curstat->curr-1]==colt) || curstat->knotstats[curstat->curr-1]==temp)
	{
		curstat->lipr[curstat->curr-1]=-1;
		curstat->lipc[curstat->curr-1]=-1;
		curstat->knotstats[curstat->curr-1]='\0';
		curstat->curr--;
	}
	else
	{
		curstat->lipr[curstat->curr]=rowt;
		curstat->lipc[curstat->curr]=colt;
		curstat->knotstats[curstat->curr]=temp;
		curstat->curr++;
	}
}
void changedir(int d,int *direction,int *rowt,int *colt)
{
	if(!d)
	{
		if(grid[(*rowt)+1][*colt]=='|')
                {
			*direction=1;
                        (*rowt)++;
                }
		else
                {
			*direction=3;
                        (*rowt)--;
                }
	}
	else
	{
		if(grid[*rowt][(*colt)+1]=='-')
                {
			*direction=0;
                        (*colt)++;
                }
		else
                {
			*direction=2;
                        (*colt)--;
                }
	}
}
