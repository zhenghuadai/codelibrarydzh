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
#define WIDE 4 
#define HIGHT 2 
#define DEPTH 20
#define CACHELINESIZE	32 
#define TILESIZE 4
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
#define GET2ndBIT        0x00000002
#define GET3rdBIT        0x00000004
#define GET4thBIT        0x00000008
#define DIRTYBIT         0x00000001

#define DEB
typedef float ele_t;
typedef int Tag_t;
typedef int tstamp_t ;
typedef char  dirty_t;
/*
   typedef struct 
   {       
   ele_t d[CACHELINESIZE];
   }Cacheline_t;
   */
typedef struct
{
	ele_t d[8];
}tile_line_t;

typedef union 
{
	ele_t d[CACHELINESIZE];
	tile_line_t a[4];
}Cacheline_t;

typedef struct 
{
	Tag_t tag;
	dirty_t dirty;
	tstamp_t timestamp;
	Cacheline_t data;

}CACHELINE;

typedef union 
{
	struct{
		int x;
		int y;
	};
	struct{
		int w;
		int h;
	};
}address_t;

typedef struct
{ 
	address_t whichset;
	int d;
}lineaddr_t;

typedef struct 
{
	address_t whichset;
	Tag_t tag;
	int   offset;
	int   tile_offset;
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
		int 	gethit(){return hit;} 
		int    getaccessnum(){return m_accessnum;} 
		int    getmissnum(){return m_missnum;}
		address_t getaddrincache(int w,int h,int d);
		void 	 printarch();
		void   printdataincache(int w,int h,int d);

	private:
		int        	incache(eleinfo_t m_eleinfo);
		lineaddr_t 	choseonebeout(address_t thisset);
		eleinfo_t  	getaddrinfo(address_t	addr);
		ele_t      	loadfromL2(eleinfo_t   m_eleinfo,address_t addr);
		ele_t 		loadfromL2Tocurrentline(lineaddr_t  m_whichline,eleinfo_t   m_eleinfo,address_t);
		void       	addarray(ele_t * base,int w,int h);
		int 		gettag(address_t addr,int texid);
		char 		getdirty(char dirty,int tile_off);
		void 		setdirty(char * dirty,int tile_off);
		void 		setvalid(char * valid,int tile_off);
		void 		initiate();
		address_t 	getwhichset(address_t addr);

		CACHELINE 	L1[WIDE][HIGHT][DEPTH];

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
