/*
 * linux.h
 *
 *  Created on: Jun 21, 2017
 *      Author: xieliming
 */
#ifndef LINUX_H_
#define LINUX_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <termios.h>
#include <sys/io.h>
#include <sys/ioctl.h>

#define rdtsc(low,high) __asm__ __volatile__("rdtsc":"=a"(low), "=d" (high))

#define PACKED __attribute__( ( packed, aligned(1) ) )                                      	//单字节对齐
#pragma pack(1)

typedef unsigned int   DWORD;
typedef unsigned short WORD;

namespace xlm                                                                               	//自定义命名空间
{
	/*一般性函数接口*/
	void setMousePos(unsigned int y,unsigned int x);                                            //设置游标位置
	int  GetKeyWord();                                                                          //不回显检测键盘按下
	int  Rand_value();                                                                          //产生随机数随机度较高
	void clearScreen();                                                                         //清理屏幕

	unsigned long long get_cycles();                                                            //获取cpu周期数
	double  get_cpu_mhz(void);                                                                  //获取cpu频率,单位为MHZ=周期/秒=周期*1000/毫秒

	bool Sec_sleep(int s);                                                                      //秒级别误差在110us左右
	bool Ms_sleep(int ms);                                                                      //毫秒级别误差在110us左右
	DWORD calcDifftime(DWORD StartTime,DWORD EndTime);                                          //计算两个时间的差值,考虑溢出情况
	struct timespec diffTime(struct timespec start,struct timespec end);                        //计算两个时间的差值
	struct timeval  diffTime_u(struct timeval start,struct timeval end);

	bool Is_two_n(int num);                                                                     //3、判断一个数是不是2的n次方。
	int  Bitap(const char *text, const char *find);                                             //Bitap算法主要利用位运算进行字符串的匹配
	bool RegisteSignal(int sig,void (*handler)(int _sig));                                      //信号注册函数
	int  CreateThread(void *(*Dealfunction)(void *),void * aParm,int priority);                 //需要sudo 运行程序
	WORD CalCheckCRC(unsigned char* lpBuf,int iLen);                                            //CRC校验以WORD为单位
	/*配置文件接口*/
	int  GetFileSize(char * path,DWORD *len);
	int  ReplaceStr(char * sSrc,const char * sMatchStr,const char * sReplaceStr);
	int  GetPrivateProfileInt(const char *key,const char * cField,int cDefault,char *filename); //.ini 配置文件操作eg:"./vxcu.ini"
	int  GetPrivateProfileString(const char* key,const char *cField,char * cDefault,char * cRet,int dRetLen,char * filename );
	bool WritePrivateProfileInt(const char * key,const char *cField,int nValue,char * filename);
	bool WritePrivateProfileString(const char * key,const char *cField,char *cValue,char * filename);
	/*网络相关接口*/
	bool getLocalActiveNetworkInfo(char * res_name);                                            //获取本地当前工作的网卡信息
	bool getLocalALLNetworkInfo(char * res_name);                                               //获取本地所有网卡信息
	int  creatbindTcpsock(char * bindip,int bindport);
	int  creatbindUdpsock(char * bindip,int bindport);
	bool setaddrReuse(int sock);                                                                //设置地址复用
	bool setsockNonblock(int sock);                                                             //设置非阻塞模式
	bool setsockBroadcast(int sock);                                                            //设置广播模式
	bool setsockRwbuf(int sock,int rwval);                                                      //设置收发缓存区大小
	bool setsockTimeout(int sock,int tsval,int tusval);                                         //设置阻塞模式收发超时
	/*串口相关接口*/
	int InitSerialPort(int port,int baudrate,int blockflag,char checkflag,int databyte,int stopbyte);//需要sudo 运行程序
	/*位操作相关接口*/
	int  calc_1_Num(int _n);                                                                    //计算二进制数中1的个数
	void showByte8(unsigned char ch);
	void clrAllbyte8(unsigned char * ch);
	void setByte8(unsigned char * ch,unsigned int index);
	void clrByte8(unsigned char * ch,unsigned int index);
	/*端口相关的接口 inb outb*/
	bool getAllPermission();                                                                   //需要sudo 运行程序

	/***************************************************************************************************************/
	/*************c++模板函数与模板类的声明与定义通常放在头文件中，而普通的函数通常是声明放在头文件中，定义放在源文件中***************/
	template<class T>
	void swapdata(T * ta,T * tb)
	{
		*ta=*ta+*tb;
		*tb=*ta-*tb;
		*ta=*ta-*tb;
	}
	template<class T>
	void bubblesort(T*tsd,int len)           			                                      //冒泡排序
	{
		for(int i=0;i<len-1;i++)
		{
			for(int j=i+1;j<len;j++)
			{
				if(*(tsd+i)>*(tsd+j))
				{
					swapdata(tsd+i,tsd+j);
				}
			}
		}
	}
	template<class T>
	void newbubblesort(T*tsd,int len)        			                                     //优化冒泡排序
	{
		for(int i=0;i<len-1;i++)
		{
			T*tmp=tsd+i+1;                  			                                     //保存最小的值
			for(int j=i+1;j<len-1;j++)
			{
				if(*(tmp)>*(tsd+j+1))
				{
					tmp=tsd+j+1;
				}
			}
			if(*(tsd+i)>*tmp)
			{
				swapdata(tsd+i,tmp);
			}
		}
	}
	template<class T>
	void insertsort(T * tsd,int len)                                                        //插入排序算法
	{
		for(int i=1;i<len;i++)
		{
			for(int j=0;j<i;j++)
			{
				if(*(tsd+i)<*(tsd+j))
				{
					swapdata(tsd+i,tsd+j);
				}
			}
		}
	}
	template<class T>
	void shellsort(T * tsd,int len)                                                         //希尔排序就是插入排序的改良版本
	{
		int n=len/2;
		while(n>0)
		{
			for(int i=n;i<len;i+=n)
			{
				for(int j=0;j<i;j+=n)
				{
					if(*(tsd+i)<*(tsd+j))
					{
						swapdata(tsd+i,tsd+j);
					}
				}
			}
			n/=2;
		}
	}
	template<class T>
	void choosesort(T * tsd,int len)     					                               //选择排序
	{
		for(int i=0;i<len-1;i++)
		{
			T * tmp=tsd+i;
			for(int j=i;j<len;j++)
			{
				if(*tmp>*(tsd+j))
				{
					swapdata(tmp,tsd+j);
				}
			}
			if(*(tsd+i)>*tmp)
			{
				swapdata(tsd+i,tmp);
			}
		}
	}
	/*
	 * 永远以第一个为标准来处理
	 *　先用标准后面的数与比标准小的数据交换（１）
	 *　然后用标准与最后一个交换的数据交换　（２）
	 */
	template<class T>
	void quicksort(T*tsd,int s,int e)   //s 起始　 ｅ终点　　ｋ　基准                          //快速排序算法
	{
		if(s<e)
		{
			T key=*(tsd+s);
			int i=s;
			for(int j=(s+1);j<=e;j++)
			{
				if(*(tsd+j)<=key)
				{
					i++;
					if(i!=j)
					{
						swapdata(tsd+i,tsd+j);    //（１）
					}
				}
			}
			if(i!=s)                             //这里一定要注意,同一个地址不能使用这种交换
			{
				swapdata(tsd+s,tsd+i);            //（２）
			}

			quicksort(tsd,s,i-1);
			quicksort(tsd,i+1,e);
		}
	}
}
#endif    /*LINUX_H_*/
