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
#define WIDE 8 
#define HIGHT 4 
#define DEPTH 20
#define CACHELINESIZE 8
#define CUT2BIT        0xFFFFFFFC
#define CUT1BIT        0xFFFFFFFE
#define CUT3BIT        0xFFFFFFF8
#define CUT5BITS       0xFFFFFFEF
#define GETHIGH        0xFFFF0000
#define GETLOW         0x0000FFFF
#define GET4BITS        0x0000000E
#define GET3BITS        0x00000007
#define GET2BITS        0x00000003
#define GET1stBIT        0x00000001
#define GET3rdBIT        0x00000004
#define GET4thBIT        0x00000008
#define DIRTYBIT         0x00000001

#define DEB
typedef float ele_t;
typedef int Tag_t;
typedef int tstamp_t ;
typedef struct 
{       
	ele_t d[CACHELINESIZE];
}Cacheline_t;
typedef struct 
{
	Tag_t tag;
	tstamp_t timestamp;
	Cacheline_t data;
	
}CACHELINE;
typedef struct 
{
	int x;
//	#define w x
	int y;
//	#define h y
}address_t;
typedef struct
{
	int w;
	int h;
	
}CSaddr_t;
typedef struct
{ 
	CSaddr_t whichset;
//		 #define w whichset.w
//		 #define h whichset.h
	int d;
}lineaddr_t;
typedef struct 
{
	CSaddr_t whichset;
	Tag_t tag;
	int   offset;
}eleinfo_t;
typedef struct
{
	int w;
	int h;
	void* base;
}arrayinfo_t;
#define reset1(a)  memset((void*)&a,-1,sizeof(a))
#define reset0(a)  memset((void*)&a,0,sizeof(a))
typedef struct
{
	float f1;
	float f2;
	float f3;
	float f4;
}float4;
class CACHE
{
public:
	  CACHE();
          CACHE(ele_t* base,int w,int h);
          ~CACHE();
	  void   Cflush();
	  ele_t  r(address_t addr); 
	  ele_t  r(int w ,int h); 
	  float4 r4(int w ,int h); 
	  int    Cwrite(address_t addr,ele_t data);
	  int 	 gethit(){return hit;} 
      	  int    getaccessnum(){return m_accessnum;} 
          int    getmissnum(){return m_missnum;}
	  address_t getaddrincache(int w,int h,int d);
       
private:
	int        	incache(eleinfo_t m_eleinfo);
	lineaddr_t 	choseonebeout(CSaddr_t thisset);
        eleinfo_t  	getaddrinfo(address_t	addr);
        ele_t      	loadfromL2(address_t addr);
        void       	addarray(ele_t * base,int w,int h);
	int 		gettag(address_t addr,int texid);
        //ele_t  &      operator[] (int x,int y);

	void 		initiate();
	CSaddr_t 	getwhichset(address_t addr);
	
	CACHELINE 	L1[WIDE][HIGHT][DEPTH];
	address_t 	m_dataaddr;
	CSaddr_t  	m_whichset;
	lineaddr_t   	m_whichline;
	eleinfo_t 	m_eleinfo;
	Tag_t  		m_tag;
	int 		m_2dwidth;
	int 		m_2dhight;
	ele_t *		m_base;
	int 		m_accessnum;
	int 		m_missnum;
        tstamp_t        m_time;
	arrayinfo_t     m_2darrayinfo[10];
	int             m_2accessnum[10];
	int 		m_2missnum[10];
	int 		m_curtex;
	int 		m_allarray;
	int 		hit;
};
void CACHE::initiate()
{
	reset1(m_dataaddr);
	reset1(L1);
	reset0(m_time);
	m_accessnum=0;
	m_missnum=0;
	m_curtex=0;
	m_allarray=0;
}
CACHE::CACHE()
{
	initiate();	
}
CACHE::~CACHE()
{
}
CACHE::CACHE(ele_t* base,int w,int h)
{
	initiate();	
	m_base=base;
	m_2dwidth=w;
	m_2dhight=h;
}
void CACHE::addarray(ele_t *base,int w,int h)
{
	m_2darrayinfo[m_allarray].base=base;
	m_2darrayinfo[m_allarray].w=w;
	m_2darrayinfo[m_allarray].h=h;
	m_allarray++;
}
#define getdirtybit(a) ((a)& GET1stBIT)
address_t CACHE::getaddrincache(int w,int h,int d)
{
	int x=0,y=0;
	int tag;
	tag=L1[w][h][d].tag;
	int wt;
	address_t tmpaddr;
	if(getdirtybit(tag))
	{
	tmpaddr.x=-1;
	tmpaddr.y=-1;
	return tmpaddr;
	}
	y=((tag>>19)<<3);
	y=y|((h & 3)<<1);
	x=((tag>>8)<<5) & GETLOW;
	x=x | ((w & GET3BITS)<<2);
	x=x xor ((y& GET4thBIT)<<1);
	tmpaddr.x=x;
	tmpaddr.y=y;
	return tmpaddr;
	
}
inline int CACHE::gettag(address_t addr,int texid)
{
	return ( ( (((addr.y & GETLOW) >> 3) << 19)|(((addr.x & GETLOW) >> 5)<<8) ) |((texid & GET4BITS)<<4)  ) ;
}
inline int getw(address_t addr)
{
	int tmpw=addr.x >> 2;
      	return(( (addr.y & 8)>>1 )xor (tmpw & 4 )) |(tmpw & 3);
}
inline int geth(address_t addr)
{
        return ((addr.y & 6)>>1);
}
inline int getoffs(address_t addr)
{
	return ((addr.y & 1)<<2)|(addr.x & 3);
}
eleinfo_t CACHE::getaddrinfo(address_t addr)
{
      int w,h,d,tag,offs;
      eleinfo_t tmp;
      /*
      h=addr.y & 6;
      offs=((addr.y & 1)<<2)|(addr.x & 3);
      int tmpw=addr.x >> 2;
      w=( (addr.y & 8)>>1 )xor( (addr.x & 4 )) |(tmpw & 3);
      */
      tmp.offset=getoffs(addr);
      tmp.whichset.w=getw(addr);
      tmp.whichset.h=geth(addr);
      tmp.tag=gettag(addr,m_curtex);
      return tmp;
}
int isolder(tstamp_t a1,tstamp_t a2)
{
	return (a1<a2?1:0);
}
lineaddr_t CACHE::choseonebeout(CSaddr_t thisset)
{
     lineaddr_t tmp;
     int i;
     tstamp_t toldest;
     int oldestline=0;
     toldest=L1[thisset.w][thisset.h][0].timestamp;
     for(i=0;i<DEPTH;i++)
     {
     	if(isolder(L1[thisset.w][thisset.h][i].timestamp,toldest))
	{
		toldest=L1[thisset.w][thisset.h][i].timestamp;
		oldestline=i;
	}
     }
     tmp.whichset=thisset;
     tmp.d=oldestline;
     return tmp;
}
#define ReplaceLine(replace1,loadaddr)\
{\
     load1=*((ele_t*)m_base + m_2dwidth*loadaddr.y+loadaddr.x);\
     L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.d[0]=load1;\
     load1=*((ele_t*)m_base + m_2dwidth*loadaddr.y+loadaddr.x + 1);\
     L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.d[1]=load1;\
     load1=*((ele_t*)m_base + m_2dwidth*loadaddr.y+loadaddr.x + 2);\
     L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.d[2]=load1;\
     load1=*((ele_t*)m_base + m_2dwidth*loadaddr.y+loadaddr.x + 3);\
     L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.d[3]=load1;\
     load1=*((ele_t*)m_base + m_2dwidth*(loadaddr.y + 1)+loadaddr.x);\
     L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.d[4]=load1;\
     load1=*((ele_t*)m_base + m_2dwidth*(loadaddr.y + 1)+loadaddr.x + 1);\
     L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.d[5]=load1;\
     load1=*((ele_t*)m_base + m_2dwidth*(loadaddr.y + 1)+loadaddr.x + 2);\
     L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.d[6]=load1;\
     load1=*((ele_t*)m_base + m_2dwidth*(loadaddr.y + 1)+loadaddr.x + 3);\
     L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.d[7]=load1;\
}
ele_t CACHE::loadfromL2(address_t addr)
{
	ele_t tmp;
	int basew;
	address_t loadaddr=addr;
	lineaddr_t replace1;
	replace1=choseonebeout(m_whichset);
	//printf("[out:%d,%d]",replace1.whichset.w,replace1.whichset.h);
	if(addr.y & 1)
	 loadaddr.y -=1;
        basew=loadaddr.x & CUT2BIT;
	ele_t load1;
	ReplaceLine(replace1,loadaddr);
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].timestamp++;
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].tag=m_eleinfo.tag;
	/*
	load1=*((ele_t*)m_base + m_2dwidth*loadaddr.y+loadaddr.x);
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.d[0]=load1;
	*/
	tmp=*((ele_t*)m_base + m_2dwidth*addr.y+addr.x);
	return tmp;
}
CSaddr_t CACHE::getwhichset(address_t addr)
{
	CSaddr_t tmp;
	return tmp;
}
int CACHE::incache(eleinfo_t m_eleinfo)
{
	int i;
	for(i=0;i<DEPTH;i++)
	{
		if(L1[m_eleinfo.whichset.w][m_eleinfo.whichset.h][i].tag==m_eleinfo.tag)
		return i;
	}
	return -1;
}
inline ele_t CACHE::r(int w,int h)
{
     address_t thisaddr;
     thisaddr.x=w;
     thisaddr.y=h;
    return r(thisaddr);
}
ele_t CACHE::r(address_t addr)
{
	int dataincache;
	ele_t data;
	m_accessnum++;
	m_eleinfo=getaddrinfo(addr);
	m_whichset=m_eleinfo.whichset;
	m_whichline.whichset=m_whichset;
	dataincache=incache(m_eleinfo);
	if(dataincache!=-1)
	{
	#ifdef DEB
//	printf("hit");
		hit=1;
	#endif
		m_whichline.d=dataincache;
		return L1[m_whichline.whichset.w][m_whichline.whichset.h][m_whichline.d].data.d[m_eleinfo.offset];
	}
	#ifdef DEB
	//printf("miss");
	hit=0;
	#endif
	m_missnum++;
	data=loadfromL2(addr);
	return data;
}
float4 CACHE::r4(int x,int y)
{
	float4 tmp4;
	int firsthit;
	tmp4.f1=r(x*4,y);
	firsthit=hit;
	tmp4.f2=r(x*4+1,y);
	tmp4.f3=r(x*4+2,y);
	tmp4.f4=r(x*4+3,y);
	hit=firsthit;
	return tmp4;

}
/*
ele_t operator CACHE::[](int x,inty)
{
	return r(x,y);
}
*/
int CACHE::Cwrite(address_t addr,ele_t data)
{
	int tmp;
	return tmp;
}
void CACHE::Cflush()
{
	reset1(L1);
	m_time=0;

}
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
int main(int argc,char **argv)
{
#define TEXMAXW 8196 
#define TEXMAXH 1024
//	ele_t tex[TEXMAXW][TEXMAXH];
#define ELE_T float
	ELE_T* tex;
	int isfloat=1;
	tex=(ELE_T*)malloc(TEXMAXH * TEXMAXW *sizeof(ELE_T));
	int eles=sizeof(ELE_T)/sizeof(float);
	CACHE cache(tex,TEXMAXW,TEXMAXH);
	char buf[128];
	printf("CACHE$:\n\tany problem please type help\n");
	while(1)
	{
		char *pcur=buf;
		printf("CACHE\033[34m$\033[0m");
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
				printf("%s\n",arch);
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
