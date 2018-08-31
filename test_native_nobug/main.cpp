#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "header.h"

void objectSort(Object *&object)
{
	float area0,area1;
	Object *p,*q = NULL,*v;
	if(!object)return;

	p = NULL;
	if(object->next)
	{
		p = object->next;
		object->next = NULL;
	}

	while(p)
	{
		q = p->next;
		area0 = p->width * p->length;
		area1 = object->width * object->length;
		if(area0 > area1)
		{
			p->next = object;
			object = p;
		}
		else{
			v = object;
			while(v->next  && area0 <= v->next->width * v->next->length)
			{
				v = v->next;
			}
			p->next = v->next;
			v->next = p;
		}

		p = q;
	}
}


void main()
{
	//(int width,int length,int num,Object *initobject)
	Object *initobject = NULL,*p = NULL;
	float width = 0.0;
	float length = 0.0;
	float t = 0.0;
	int i=0,n=0,flag=0,num=0;
	
	char field[10];
	char array[20];
	char ch[2]={'\0','\0'};

	container *A[20];
	for(i=0;i<20;i++)A[i]=NULL;


	strcpy(field,"场地");
	ifstream in("数据源\\object.txt");
	if(!in)
	{
		cout<<"文件打开失败，\"数据源文件夹\"不存在！";
		cout<<"或没有数据文件object.txt"<<endl;
		exit(1);
	}

	while(!in.eof())
	{
		in>>length;
		in.ignore();
		in>>width;
		in.ignore();
		in>>t;
		in.ignore();
		in>>num;
		if(length <= 0 || width <= 0 || t <= 0||num <= 0)
		{
			cout<<"物品:"<<"(length:"<<length<<",width:"<<width;
			cout<<",t:"<<t<<")数据有误"<<"\n\t\t系统自动删除"<<endl;
			continue;
		}
		initobject = new Object;
		initobject->t = t;
		if(length < width)
		{
			initobject->length = width;
			initobject->width = length;
		}
		else 
		{
			initobject->length = length;
			initobject->width = width;
		}
		initobject->t = t;
		initobject->n =num;
		initobject->next=NULL;
		break;
	}
	while(!in.eof())
	{
		in>>length;
		in.ignore();;
		in>>width;
		in.ignore();
		in>>t;
		in.ignore();
		in>>num;
		if(length <= 0 || width <= 0 || t <= 0 || num <= 0)
		{
			cout<<"物品:"<<"(length:"<<length<<",width:"<<width;
			cout<<",t:"<<t<<")数据有误"<<"\n\t\t系统自动删除"<<endl;
			continue;
		}
		p = new Object;
		p->t = t;
		if(length < width)
		{
			p->length = width;
			p->width = length;
		}
		else 
		{
			p->length = length;
			p->width = width;
		}
		p->n =num;
		p->next=initobject;		
		initobject = p;
	}

	length = 100;
	width = 9;
	objectSort(initobject);

	ifstream inf("数据源\\field.txt");
	if(!inf)
	{
		cout<<"文件打开失败，\"数据源文件夹\"不存在！";
		cout<<"或没有数据文件field.txt"<<endl;
		exit(1);
	}

	i = 0;
	while(!inf.eof())
	{
		inf>>length;
		inf.ignore();;
		inf>>width;
		if(length <= 0 || width <= 0)
		{
			cout<<"场地:"<<"(length:"<<length<<",width:"<<width;
			cout<<")数据有误"<<"\n\t\t系统自动删除"<<endl;
			continue;
		}
		ch[0] = i+49;
		strcpy(array,field);
		strcat(array,ch);
		A[i] = new container (width,length,array);
		i++;
	}
	inf.close();
	cout<<"flag"<<i<<endl;
	//装载,装载完结果写入文件
	n = i;
	flag = n;
	i = 0;
	while(initobject && flag>0)
	{
		if(!A[i]->Loading(initobject))
		{
			delete A[i];
			A[i] = NULL;
			flag--;
		}
		i++;
		i = i%n;
	}

	//销毁对象
	i = 0;
	while(i<n)
	{
		if(A[i])delete A[i];
		i++;
	}

	//显示装不下的物品
	p = initobject;
	if(p)
	{
		cout<<"没有场地可以装下的物品:"<<endl;
		while(p)
		{
			cout<<"物品  (长:"<<p->length<<",宽"<<p->width<<",加工周期:"<<p->t<<')'<<endl;
			initobject = p;
			p = p->next;
			delete initobject;
		}
	}
	cout<<endl<<endl<<"结果都在工程文件夹中"<<endl<<endl;
	getchar();
	return;
}
