/*
*this is a 2d readonly cache based on nvidia G80 
*any problem please contact with zhenghuax.dai@intel.com
*
*
*
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cacheclass.h"
/*
char *arch="\n\
		w								h				\n\
   15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|		15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0| \n\
   				    |   |  |							     |  |  |	 \n\	
				    |   |__|							     |  |__|	 \n\
				    |   |  |                                                         |  |  |	 \n\	
				    |  _|__|_________________________________________________________|  |__|     \n\
				    | | |  |								|  |	 \n\	
				    |+| |__|								|__|	 \n\
				     |  |  | 								|  |	 \n\
				   | 2| 1| 0| 								|__|	 \n\
				   |__|__|__|								|  | 	 \n\	
				      	|								|__|	 \n\
					|								 |   	 \n\
        ________________________________|________________________________________________________________|	 \n\
	|                               |									 \n\
	|				|CSw									 \n\
	|                _______________________________________________________________________		 \n\
	|                |	 |        |        |        |        |        |        |        |	         \n\
	|                |_______|________|________|________|________|________|________|________|                \n\
	|		 |______________________________________________________________________|                \n\
	|		 |	 |        |        |        |        |        |        |        |		 \n\
	|		 |_______|________|________|________|________|________|________|________|	     	 \n\
	| 		 |______________________________________________________________________|		 \n\
	|---CSh-->1|0|   |       |        |        |        |        |        |        |        |		 \n\
	                 |_______|________|________|________|________|________|________|________|		 \n\
			 |______________________________________________________________________|		 \n\	
			 |       |        |        |        |        |        |        |        |		 \n\
                         |_______|________|________|________|________|________|________|________|		 \n\
														 \n\
														 \n\		
tag: 15|14|13|12|11|10| 9| 8| 7| 6| 5| 15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3|Texid|dirtybit|			 \n\
+ stands for xor \n";			
*/
#define isdigital(a) (((a)=='(')||((a)>='0')&&((a)<='9'))
#define isalpha(a)   (  (((a)>='a')&&((a)<= 'z')) || (((a)>='A')&&((a)<= 'Z')))
#define printhitinfo(x,y)  {                 int hit=cache.gethit();\
					if(hit)\
					printf("\033[35mhit[%d,%d]\033[0m\t",x,y);\
					else\
					printf("\033[33mmiss[%d,%d]\033[0m\t",x,y);\
		      }
#define printaddr(addr) {if(isfloat==1)printf("(%d %d)",addr.x,addr.y);else printf("(%d %d)",addr.x/4,addr.y);}		
#define readone(x, y) { if(isfloat==1)cache.r(x, y);else cache.r4(x, y);}
#define readone2(x, y) { if(isfloat==1)tmp=cache.r(x, y);else tmp4=cache.r4(x, y);}
#define printf4(a)	printf("(%f %f %f %f)",a.f1,a.f2,a.f3,a.f4)
#define printf1(a)	printf("(%f)",a)
int main(int argc,char **argv)
{
#define TEXMAXW 8196 
#define TEXMAXH 1024
//	ele_t tex[TEXMAXW][TEXMAXH];
#define ELE_T float
	ELE_T* tex;
	int isfloat=1;
	tex=(ELE_T*)malloc(TEXMAXH * TEXMAXW *sizeof(ELE_T));
	for(int i=0;i<TEXMAXH * TEXMAXW;i++)
		tex[i]=i;
	int eles=sizeof(ELE_T)/sizeof(float);
	CACHE cache(tex,TEXMAXW,TEXMAXH);
	char buf[128];
	printf("CACHE$:\n\tany problem please type help\n");
	while(1)
	{
		char *pcur=buf;
		printf("CACHE\033[32m$\033[0m");
		fgets(buf,127,stdin);
		while((*pcur == ' ')||(*pcur=='\n'))pcur++;
		if(pcur[0]==0)continue;
		if(pcur[0]=='q')break;
		char cmd[100];
		cmd[0]=0;
		while(*pcur)
		{
			int x=0,y=0,x2=0,y2=0;
			if(isalpha(*pcur))
			{
				sscanf(pcur,"%s(",cmd);
				{
					int i=0;
					while((cmd[i])&&(cmd[i]!=' ')&&(cmd[i]!='('))i++;
					cmd[i]=0;
				}
			//	printf("cmd(%s)\n",cmd);
				while((*pcur)&&(*pcur != '('))pcur++;
			}
			//printf("CMD:%sfrom:%s.....\n",cmd,pcur);
			if(!strcmp(cmd,"rp"))
			{
				sscanf(pcur,"(%d %d)",&x,&y);
			//	printf("%d,%d %s|\n",x,y,pcur);
				if((x>=0) && (y>=0))
				{
					float tmp;
					float4 tmp4;
					readone2(x,y);
			//		cache.r(x,y);
					if(isfloat==1)
					printf1(tmp);
					else
					printf4(tmp4);
					
					int hit=cache.gethit();
					if(hit)
					printf("\033[35mhit[%d,%d]\033[0m\n",x,y);
					else
					printf("\033[33mmiss[%d,%d]\033[0m\n",x,y);
					
				}
			}
			if(!strcmp(cmd,"r"))
			{
				sscanf(pcur,"(%d %d)",&x,&y);
			//	printf("%d,%d %s|\n",x,y,pcur);
				if((x>=0) && (y>=0))
				{
					readone(x,y);
			//		cache.r(x,y);
					int hit=cache.gethit();
					if(hit)
					printf("\033[35mhit[%d,%d]\033[0m\n",x,y);
					else
					printf("\033[33mmiss[%d,%d]\033[0m\n",x,y);
				}
			}
			else if(!strcmp(cmd,"rb"))
			{
				sscanf(pcur,"(%d %d)->(%d %d)",&x,&y,&x2,&y2);
				//printf("%s(%d,%d)->(%d,%d)\n",cmd,x,y,x2,y2);
				   for(int fj=y;fj<=y2;fj++)
				for(int fi=x;fi<=x2;fi++)
				   {
			//	       cache.r(fi,fj);
					readone(fi,fj);
				   }
			}
			else if(!strcmp(cmd,"rbi"))
			{
				sscanf(pcur,"(%d %d)->(%d %d)",&x,&y,&x2,&y2);
				   for(int fj=y;fj<=y2;fj++)
				for(int fi=x;fi<=x2;fi++)
				   {
				//       cache.r(fi,fj);
					readone(fi,fj);
				       printhitinfo(fi,fj);
				   }
			}
			else if(!strcmp(cmd,"pa"))
			{
				int w,h,d;
				address_t ta;
				sscanf(pcur,"(%d %d %d)",&w,&h,&d);
				ta=cache.getaddrincache(w,h,d);
				printaddr(ta);
				cache.printdataincache(w,h,d);
			}
			else if(!strcmp(cmd,"pall"))
			{
				for(int ad=0;ad<DEPTH;ad++)
				{
					for(int ah=0;ah<HIGHT;ah++)
					{
						for(int aw=0;aw<WIDE;aw++)
						{
							address_t ta;
							ta=cache.getaddrincache(aw,ah,ad);
							printaddr(ta);
						}
					printf("\n");
					}
					printf("\n");
				}
				printf("\n");
					
			}
			else if(!strcmp(cmd,"arch"))
			{
			//	printf("%s\n",arch);
				cache.printarch();
			}
			else if(!strcmp(cmd,"flush"))
			{
				cache.Cflush();
			}
			else if(!strcmp(cmd,"float"))
			{
				isfloat=1;
			}
			else if(!strcmp(cmd,"float4"))
			{
				isfloat=4;
			}
			else if(!strcmp(cmd,"help"))
			{
				printf("r(w h)		read (w h)\n");
				printf("rp(w h)		read (w h) and print the data\n");
				printf("r(w h);(w1 h1);(w2 h2)....(wn hn)\n		read (w h) ;(w1 h1);(w2 h2)....(wn hn)\n");
				printf("rb(w0 h0)->(w1 h1)\n		read from (w0 h0) to (w1 h1)\n");
				printf("rbi(w0 h0)->(w1 h1)\n		read from (w0 h0) to (w1 h1) and print hitinfo\n");
				printf("flush		reset L1\n");
				printf("pa(w h d)	get address in cacheline(w h d)\n");
				printf("pall		print all address in cacheline\n");
				printf("float		set the type as float\n");
				printf("float4		set the type as float4\n");
			}
			else
			{
				printf("no cmd %s\n",cmd);
			}
			while((*pcur)&&(*pcur != ';'))pcur++;
			if(!(*pcur))break;
			pcur++;
			while((*pcur)&&((*pcur == ' ')||(*pcur=='\n')))pcur++;
			if(!(*pcur))break;
			x=-1;y=-1;
		}
	        reset1(buf);
	}
}
