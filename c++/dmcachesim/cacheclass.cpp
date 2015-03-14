/*
*this is a 2d readonly cache based on nvidia G80 
*any problem please contact with djx.zhenghua@gmail.com 
*
*
*
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cacheclass.h"
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
void CACHE::initiate()
{
	//reset1(m_dataaddr);
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
//#define getdirtybit(a) ((a)& GET1stBIT)
address_t CACHE::getaddrincache(int w,int h,int d)
{
	int x=0,y=0;
	int tag;
	tag=L1[w][h][d].tag;
	int wt;
	address_t tmpaddr;
	if(L1[w][h][d].dirty==-1)//getdirtybit(tag))
	{
		tmpaddr.x=-1;
		tmpaddr.y=-1;
		return tmpaddr;
	}
	y=((tag>>19)<<3);
	y=y|((h)<<2);
	x=((tag>>8)<<5) & GETLOW;
	x=x | ((w & GET2BITS)<<3);
	x=x xor ((y& GET4thBIT)<<1);
	tmpaddr.x=x;
	tmpaddr.y=y;
	return tmpaddr;

}
void CACHE::printdataincache(int w,int h,int d)
{
	printf("(%f %f %f %f) ",L1[w][h][d].data.a[0].d[0],L1[w][h][d].data.a[0].d[1],L1[w][h][d].data.a[0].d[2],L1[w][h][d].data.a[0].d[3]);
	printf("(%f %f %f %f)\n",L1[w][h][d].data.a[1].d[0],L1[w][h][d].data.a[1].d[1],L1[w][h][d].data.a[1].d[2],L1[w][h][d].data.a[1].d[3]);
	printf("(%f %f %f %f) ",L1[w][h][d].data.a[0].d[4],L1[w][h][d].data.a[0].d[5],L1[w][h][d].data.a[0].d[6],L1[w][h][d].data.a[0].d[7]);
	printf("(%f %f %f %f)\n",L1[w][h][d].data.a[1].d[4],L1[w][h][d].data.a[1].d[5],L1[w][h][d].data.a[1].d[6],L1[w][h][d].data.a[1].d[7]);
	printf("(%f %f %f %f) ",L1[w][h][d].data.a[2].d[0],L1[w][h][d].data.a[2].d[1],L1[w][h][d].data.a[2].d[2],L1[w][h][d].data.a[2].d[3]);
	printf("(%f %f %f %f)\n ",L1[w][h][d].data.a[3].d[0],L1[w][h][d].data.a[3].d[1],L1[w][h][d].data.a[3].d[2],L1[w][h][d].data.a[3].d[3]);
	printf("(%f %f %f %f) ",L1[w][h][d].data.a[2].d[4],L1[w][h][d].data.a[2].d[5],L1[w][h][d].data.a[2].d[6],L1[w][h][d].data.a[2].d[7]);
	printf("(%f %f %f %f)\n ",L1[w][h][d].data.a[3].d[4],L1[w][h][d].data.a[3].d[5],L1[w][h][d].data.a[3].d[6],L1[w][h][d].data.a[3].d[7]);
}
inline int CACHE::gettag(address_t addr,int texid)
{
	return ( ( (((addr.y & GETLOW) >> 3) << 19)|(((addr.x & GETLOW) >> 5)<<8) ) |((texid & GET4BITS)<<4)  ) ;
}
inline int getw(address_t addr)
{
	int tmpw=addr.x >> 3;
	return(( (addr.y & GET4thBIT) >> 2 )xor (tmpw & GET2ndBIT )) |(tmpw & GET1stBIT);
}
inline int geth(address_t addr)
{
	return ((addr.y & GET3rdBIT)>>2);
}
inline int getoffs(address_t addr)
{
	return ((addr.y & 1)<<2)|(addr.x & 3);
}
inline int getoffsintile(address_t addr)
{
	return ((addr.y & GET2ndBIT))|((addr.x & GET3rdBIT)>>2);
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
	tmp.tile_offset=getoffsintile(addr);
	tmp.whichset.w=getw(addr);
	tmp.whichset.h=geth(addr);
	tmp.tag=gettag(addr,m_curtex);
	return tmp;
}
int isolder(tstamp_t a1,tstamp_t a2)
{
	return (a1<a2?1:0);
}
lineaddr_t CACHE::choseonebeout(address_t thisset)
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
#define ReplaceLine(replace1,off,loadaddr)\
{\
	load1=*((ele_t*)m_base + m_2dwidth*loadaddr.y+loadaddr.x);\
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.a[off].d[0]=load1;\
	load1=*((ele_t*)m_base + m_2dwidth*loadaddr.y+loadaddr.x + 1);\
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.a[off].d[1]=load1;\
	load1=*((ele_t*)m_base + m_2dwidth*loadaddr.y+loadaddr.x + 2);\
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.a[off].d[2]=load1;\
	load1=*((ele_t*)m_base + m_2dwidth*loadaddr.y+loadaddr.x + 3);\
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.a[off].d[3]=load1;\
	load1=*((ele_t*)m_base + m_2dwidth*(loadaddr.y + 1)+loadaddr.x);\
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.a[off].d[4]=load1;\
	load1=*((ele_t*)m_base + m_2dwidth*(loadaddr.y + 1)+loadaddr.x + 1);\
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.a[off].d[5]=load1;\
	load1=*((ele_t*)m_base + m_2dwidth*(loadaddr.y + 1)+loadaddr.x + 2);\
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.a[off].d[6]=load1;\
	load1=*((ele_t*)m_base + m_2dwidth*(loadaddr.y + 1)+loadaddr.x + 3);\
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.a[off].d[7]=load1;\
}
ele_t CACHE::loadfromL2(eleinfo_t   m_eleinfo, address_t addr)
{
	ele_t tmp;
	int basew;
	address_t loadaddr=addr;
	lineaddr_t replace1;
	address_t m_whichset=m_eleinfo.whichset;
	replace1=choseonebeout(m_whichset);
	//printf("[out:%d,%d]",replace1.whichset.w,replace1.whichset.h);
	if(addr.y & 1)
		loadaddr.y -=1;
	basew=loadaddr.x & CUT2BIT;
	ele_t load1;
	ReplaceLine(replace1,m_eleinfo.tile_offset,loadaddr);
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].timestamp++;
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].tag=m_eleinfo.tag;
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].dirty=-1;
	char * dirtyp=& L1[replace1.whichset.w][replace1.whichset.h][replace1.d].dirty;
	setvalid(dirtyp,m_eleinfo.tile_offset);
	/*
	   load1=*((ele_t*)m_base + m_2dwidth*loadaddr.y+loadaddr.x);
	   L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.d[0]=load1;
	   */
	tmp=*((ele_t*)m_base + m_2dwidth*addr.y+addr.x);
	return tmp;
}
ele_t CACHE::loadfromL2Tocurrentline(lineaddr_t m_whichline, eleinfo_t   m_eleinfo,address_t addr)
{
	ele_t tmp;
	int basew;
	address_t loadaddr=addr;
	lineaddr_t replace1;
	replace1=m_whichline;
	//printf("[out:%d,%d]",replace1.whichset.w,replace1.whichset.h);
	if(addr.y & 1)
		loadaddr.y -=1;
	basew=loadaddr.x & CUT2BIT;
	ele_t load1;
	ReplaceLine(replace1,m_eleinfo.tile_offset,loadaddr);
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].timestamp++;
	L1[replace1.whichset.w][replace1.whichset.h][replace1.d].tag=m_eleinfo.tag;
	char * dirtyp=& L1[replace1.whichset.w][replace1.whichset.h][replace1.d].dirty;
	setvalid(dirtyp,m_eleinfo.tile_offset);
	/*
	   load1=*((ele_t*)m_base + m_2dwidth*loadaddr.y+loadaddr.x);
	   L1[replace1.whichset.w][replace1.whichset.h][replace1.d].data.d[0]=load1;
	   */
	tmp=*((ele_t*)m_base + m_2dwidth*addr.y+addr.x);
	return tmp;
}
address_t CACHE::getwhichset(address_t addr)
{
	address_t tmp;
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
inline char CACHE::getdirty(char dirty,int tile_offs)
{
	return (dirty & ( 1 << tile_offs));
}
inline void CACHE::setdirty(char *dirty,int tile_offs)
{
	*dirty= (*dirty | ( 1 << tile_offs));
}
inline void CACHE::setvalid(char *valid,int tile_offs)
{
	*valid= (*valid & (~( 1 << tile_offs)));
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
	int whichd;//dataincache;
	ele_t data;
	m_accessnum++;
	eleinfo_t	m_eleinfo=getaddrinfo(addr);
	address_t	m_whichset=m_eleinfo.whichset;
	lineaddr_t m_whichline;
	m_whichline.whichset=m_whichset;
	whichd=incache(m_eleinfo);
	if(whichd!=-1)
	{
#ifdef DEB
		//	printf("hit");
		hit=1;
#endif
		m_whichline.d=whichd;
		char dirty = L1[m_whichline.whichset.w][m_whichline.whichset.h][m_whichline.d].dirty;
		if(!getdirty(dirty,m_eleinfo.tile_offset))
		{
			return L1[m_whichline.whichset.w][m_whichline.whichset.h][m_whichline.d].data.a[m_eleinfo.tile_offset].d[m_eleinfo.offset];
		}
		else
		{
#ifdef DEB
			//printf("miss");
			hit=0;
#endif
			m_missnum++;
			data=loadfromL2Tocurrentline(m_whichline,m_eleinfo,addr);
			return data;

		}
	}
#ifdef DEB
	//printf("miss");
	hit=0;
#endif
	m_missnum++;
	data=loadfromL2(m_eleinfo,addr);
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
void CACHE::printarch()
{
	printf("%s\n",arch);
}
