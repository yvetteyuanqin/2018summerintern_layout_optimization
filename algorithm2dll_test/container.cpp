#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "header.h"


//----------------------------------------------------
Container::Container(float width,float length,char field[]="")
{
	float change;

#ifdef FILEOUTPUT
	strcpy(fieldName,field);
#endif

	tSquence = NULL;
	containerArea = width * length;
	
	head = NULL;
	queue = new Queue;
	queue->front = NULL;
	queue->rear =NULL;

	//adjust field param let length>width
	if(width>length)
	{
		change = width;
		width = length;
		length = change;
	}

	Width = width;
	Length = length;
	
#ifdef FILEOUTPUT
		char array[30];
	strcpy(array,"物品摆放位置\\");
	strcat(array,fieldName);
	strcat(array,".txt");
	ofstream out(array,ios::out,0x20);
	if(!out)
	{
		cout<<"文件打开失败，\"物品摆放位置\"文件夹不存在！"<<endl;
		cout<<endl<<"请在工程目录下新建一个"<<endl;
		exit(1);
	}
	out<<"场地  长:"<<Length<<'\t'<<"宽:"<<Width<<endl;
	out.close();

	strcpy(array,"空间分割过程\\");
	strcat(array,fieldName);
	strcat(array,".txt");
	ofstream to(array,0x20);
	if(!to)
	{
		cout<<"文件打开失败，\"空间分割过程\"文件夹不存在！"<<endl;
		cout<<endl<<"请在工程目录下新建一个"<<endl;
		exit(1);
	}
	to.close();
#endif
#ifdef DEBUG
	cout<<"Field  Length:"<<Length<<'\t'<<"Width:"<<Width<<endl;
#endif


	if(object)
	{
		Space *p = new Space;
		p->width = width;
		p->length = length;
		p->t = 0;
		p->x = 0;
		p->y = 0;
		p->level = p->vertical = p->tSquence = NULL;
		AddIntoSpaceLink(p);
		AddIntotSquence(p);
	}
}
//-----------------------------------------------------
Container::~Container()
{
	//occupyPercentage();
	Space *p;
	while(tSquence)
	{
		p = tSquence;
		tSquence = tSquence->tSquence;
		delete p;
	}

	occupy *q = NULL;
	q = popqueue();
	while(q)
	{
		delete q;
		q = popqueue();
	}

}

bool Container::Loading(Object *&initobject)
{
	Space *w, *v= tSquence , *p, *q , *brk0, *brk1;
	Object *singleObject,*point,*pri;
	int temp1=0,temp2=0;
	char array[30];

	object = initobject;

#ifdef FILEOUTPUT
	strcpy(array,"空间分割过程\\");
	strcat(array,fieldName);
	strcat(array,".txt");
	ofstream out(array,ios::out|ios::ate,0x20);

	if(!out)
	{
		cout<<"文件打开失败，目标文件状态可能为只读！";
		exit(1);
	}
#endif
	while(object)
	{
		p = tSquence;
#ifdef FILEOUTPUT
		out<<"***********所有空间块************"<<endl;
		out<<"x:\ty:\tflag:\twidth:\tlength:\tt:"<<endl;
#endif


		while(p)
		{	
#ifdef FILEOUTPUT
			out<<p->x<<"\t"<<p->y<<"\t"<<p->flag<<"\t"<<p->width ;
			out<<"\t"<<p->length<<"\t"<<p->t<<endl;		
#endif
			p = p->tSquence;
		}
		//if (v->t+mint > totalt)break;//可以换个集装箱;
		singleObject = NULL;
		point = NULL;
		w = v;		// w取v 的下一个结点
		v = v->tSquence;
#ifdef FILEOUTPUT
		out<<"\n\n********从空间块中选一块***************"<<endl;
		out<<"x:\ty:\tflag:\twidth:\tlength:\tt:"<<endl;
		out<<w->x<<"\t"<<w->y<<"\t"<<w->flag<<"\t"<<w->width;
		out<<"\t"<<w->length<<"\t"<<w->t<<endl;
#endif
 		if(!SelectObject (w,point))  //选择一个可以装得下的物品
		{
			return false;
		}

		//此空间没有可容得下的物品
		if (!point)
		{
			Converge(w);   //合并w并使合并体一起在tSquence中排序
			v = tSquence;
			continue;
		}
//----------------------------------------------------------------------------

//----------w空间够大能容得下物品,把该物品进队--------------------------------

		singleObject = new Object;
		singleObject->length = point->length;
		singleObject->width = point->width;
		singleObject->t = point->t;
		singleObject->id = point->id;
		singleObject->f = true;
		singleObject->next = NULL;
		temp1 = (int)(w->width*100)%(int)(point->width*100);
		temp2 = (int)(w->width*100)%(int)(point->length*100);
		if(temp1 != temp2)
		{

			if(temp1 < temp2) 
				singleObject->n = 0;
			else singleObject->n = 1;
		}
		else {
			temp1 = (int)(w->length*100)%(int)(point->width*100);
			temp2 = (int)(w->length*100)%(int)(point->length*100);
			if(temp1 > temp2) 
				singleObject->n = 1;
			else singleObject->n = 0;
		}

		point->n--;  //物品个数减一
		if(point->n == 0) 
		{
			if(object == point)
			{
				object = object->next;
				initobject = object;
			}
			else{
				pri = object;
				while(pri&&pri->next!=point)
					pri = pri->next;
				pri->next = point->next;
			}
			delete point;
		}
#ifdef FILEOUTPUT
		out<<"\n选择物品:\n"<<w->x<<"\t"<<w->y<<"\t"<<singleObject->n<<"\t";
		out<<singleObject->width <<"\t"<<singleObject->length<<"\t"<<singleObject->t<<endl;
#endif
		//在空间位置存放这个物品,并进栈
		pushqueue( singleObject, w->x, w->y, w->t);

		deltSquence(w);		//可以装得则删除w在tSquence中的位置
	    deltSpaceLink(w);	//和head中的位置


		p = new Space ;
		p->vertical = p->level = p->tSquence = NULL;
		q = new Space ;
		q->vertical = q->level = q->tSquence = NULL;
		brk0 = new Space ;
		brk0->vertical = brk0->level = brk0->tSquence = NULL;
		brk1 = new Space ;
		brk1->vertical = brk1->level = brk1->tSquence = NULL;

		if (singleObject->n == 0)		//物品竖放
		{
			p->x = w->x + singleObject->width;
			p->y = w->y;
			p->t = w->t;
			p->width = w->width - singleObject->width;
			p->length = singleObject->length;
			
			q->x = w->x;
			q->y = w->y + singleObject->length;
			q->t = w->t;
			q->width = w->width;
			q->length = w->length - singleObject->length;

			brk0->x = w->x + singleObject->width;
			brk0->y = w->y;
			brk0->t = w->t;
			brk0->width = w->width- singleObject->width;
			brk0->length = w->length;

			brk1->x = w->x;
			brk1->y = w->y + singleObject->length;
			brk1->t = w->t;
			brk1->width = singleObject->width;
			brk1->length = w->length - singleObject->length;
			
			w->t += singleObject->t;
			w->width = singleObject->width;
			w->length = singleObject->length; 
		}
		else{ // 物品横放
			p->x = w->x + singleObject->length;
			p->y = w->y;
			p->t = w->t;
			p->width = w->width- singleObject->length;
			p->length = singleObject->width;
	
			q->x = w->x;
			q->y = w->y + singleObject->width;
			q->t = w->t;
			q->width = w->width;
			q->length = w->length - singleObject->width;

			brk0->x = w->x + singleObject->length;
			brk0->y = w->y;
			brk0->t = w->t;
			brk0->width = w->width- singleObject->length;
			brk0->length = w->length;
	
			brk1->x = w->x;
			brk1->y = w->y + singleObject->width;
			brk1->t = w->t;
			brk1->width = singleObject->length;
			brk1->length = w->length - singleObject->width;

			w->t += singleObject->t;
			w->width = singleObject->length;
			w->length = singleObject->width; 
		}
	
		if (p->width <=0||p->length <=0)
		{
			delete p; 
			p = NULL; 
		}
		if (q->width <=0||q->length <=0)
		{
			delete q; 
			q = NULL; 
		}

		if (brk0->width <=0||brk0->length <=0)
		{
			delete brk0; 
			brk0 = NULL; 
		}
		if (brk1->width <=0||brk1->length <=0)
		{
			delete brk1; 
			brk1 = NULL; 
		}

		if(p)
		{
			if(p->width <= p->length)p->flag = 0;
			else p->flag = 1;
		}
		if(q)
		{
			if(q->width <= q->length)q->flag = 0;
			else q->flag = 1;
		}
		if(brk0)
		{
			if(brk0->width <= brk0->length)brk0->flag = 0;
			else brk0->flag = 1;
		}
		if(brk1)
		{
			if(brk1->width <= brk1->length)brk1->flag = 0;
			else brk1->flag = 1;
		}

		AddIntoSpaceLink(w);
		AddIntotSquence (w);

		if(!needconverge(p,q,brk0,brk1))
		{
			AddIntoSpaceLink(p);
			AddIntotSquence (p);
			AddIntoSpaceLink(q);
			AddIntotSquence (q);
			delete brk0;
			delete brk1;
		}
		else{
			AddIntoSpaceLink(brk0);
			AddIntotSquence (brk0);
			AddIntoSpaceLink(brk1);
			AddIntotSquence (brk1);
			delete p;
			delete q;
			p = brk0;
			q = brk1;
		}
#ifdef FILEOUTPUT
		out<<"\n----选择的空间块装完物品后的情况-----------"<<endl;
		out<<"x:\ty:\tflag:\twidth:\tlength:\thigh:"<<endl;
		if(w)
		{
			out<<w->x<<"\t"<<w->y<<"\t"<<w->flag<<"\t"<<w->width;
			out<<"\t"<<w->length<<"\t"<<w->t<<endl;
		}
		if(p)
		{
			out<<p->x<<"\t"<<p->y<<"\t"<<p->flag<<"\t";
			out<<p->width <<"\t"<<p->length<<"\t"<<p->t<<endl;
		}
		if(q)
		{
			out<<q->x<<"\t"<<q->y<<"\t"<<q->flag<<"\t";
			out<<q->width <<"\t"<<q->length<<"\t"<<q->t<<endl;
		}
#endif
		break;


	}
#ifdef FILEOUTPUT
	out.close();
#endif
	return true;
}

//-----------------------------------------------------
void Container::occupyPercentage(float **ret)
{
	float totalOccupy = 0;
	float maxt = 0;
	char array[30];

	

#ifdef FILEOUTPUT
	strcpy(array,"物品摆放位置\\");
	strcat(array,fieldName);
	strcat(array,".txt");
	ofstream out(array,ios::out|ios::app,0x20);

	if(!out)
	{
		cout<<"文件打开失败，目标文件状态可能为只读！";
		exit(1);
	}
#endif
	occupy* curr = queue->front;
	int objcnt=0;
	while(curr!=NULL)
		{
			objcnt++;
			curr=curr->next;
		}
	//for ret
	//float **ret = new float*[objcnt];//2d array to be returned
	//	for(int i =0;i<objcnt;i++){
	//		ret[i] = new float[6];//for return width,length,peried,x,y,orientation
	//	}


//end for ret
	occupy *p;
	p = popqueue();
	//counting object loaded
	
	if(!p)
	{
		cout<<"\n\t\t没放物品"<<endl;
		return ;
	}
	int i=0;//objct
	while(p)
	{
		totalOccupy +=  p->object->length *p->object->width *p->object->t;
		//可以写入记事本
#ifdef FILEOUTPUT
		out<<"物体("<<p->object->width<<", id#: "<<p->object->id;
		out<<p->object->length<<")\t加工周期"<<p->object->t<<"\t";
		if(p->object->n==0)out<<"竖放\t";
		else out<<"横放\t";
		out<<"存放空间坐标("<<p->x<<","<<p->y<<","<<p->t<<")"<<endl;
#endif
		//return
		ret[i][2]= p->object->length;
		ret[i][3]= p->object->width;
		ret[i][4]= p->object->n;//orientation of object
		ret[i][5]= p->x;
		ret[i][6]= p->y;
		ret[i][7]= p->t;//which period could start to put
		ret[i][1]= p->object->f;
		ret[i][0]= p->object->id;//loaded or not
		i++;

#ifdef DEBUG
		cout<<"物体("<<p->object->width<<","<<p->object->length<<"), id#:"<<p->object->id
		<<"\t加工周期"<<p->object->t<<"\t";
		if(p->object->n==0)cout<<"竖放\t";
		else cout<<"横放\t";
		cout<<"存放空间坐标("<<p->x<<","<<p->y<<","<<p->t<<")"<<endl;
#endif
		delete p;
		p = popqueue();
	}

	Space *q = tSquence;
	if(!q)
	{
		cout<<"\n\t\t空间没占用"<<endl;
		return;
	}
	maxt = tSquence->t;
	while(q->tSquence)
	{
		q = q->tSquence;
		if(maxt < q->t)maxt = q->t; 
	}
#ifdef OUTPUTFILE
	out<<endl<<endl<<"空间t最大为:"<<maxt<<endl;	
	out<<endl<<endl<<"空间占用率";
	out<<totalOccupy/(containerArea * maxt)*100<<"%";
	out.close();
#endif
#ifdef DEBUG
	cout<<endl<<endl<<"空间t最大为:"<<maxt<<endl;	
	cout<<endl<<endl<<"空间占用率";
	cout<<totalOccupy/(containerArea * maxt)*100<<"%";
		//for(int i=0;i<objcnt;i++)
		//{
		//	for(int j =0;j<6;j++)	cout<<ret[i][j]<<"\t";
		//	cout<<endl;
		//}
#endif
}





//-----------------------------------------------------------------
void Container::AddIntoSpaceLink(Space *w)
{
	Space *point,*v;
	if(!w) return;
	if (w->width ==0||w->length ==0)
	{
		delete w; 
		return;
	}

	if(w->width <= w->length)w->flag = 0;
	else w->flag = 1;
	w->level = w->vertical = NULL;

	if(head==NULL)head = w;
	else if(w->y < head->y)
	{
		w->vertical = head;
		head = w;
	}
	else {
		v = point = head;
	
		while(point->vertical && point->vertical->y <= w->y )
		{
			v = point;
			point = point->vertical;
		}

		while(point->y == w->y && point->level && point->level->x < w->x)
		{
			point = point->level;
		}

		if(v == point)
		{
			if(point->y < w->y)
			{
				w->vertical = point->vertical;
				point->vertical = w;
			}
			else if(point->x < w->x)
			{
				w->level = point->level;
				point->level = w;
			}
			else{
				w->level = point;
				w->vertical = point->vertical;
				point->vertical = NULL;
				head = w;
			}
		}
		else if(v->vertical == point)
		{
			if(point->y == w->y)
			{
				if(w->x < point->x)
				{
					w->vertical = point->vertical;
					w->level = point;
					v->vertical = w;
					point->vertical = NULL;
				}
				else{
					w->level = point->level;
					point->level = w;
				}
			}
			else{
				w->vertical = point->vertical;
				point->vertical = w;
				w->level = NULL;
			}
		}
		else{
			w->vertical = NULL;
			w->level = point->level;
			point->level = w;
		}
	}
}

//------------------------------------------------------------------

void Container::AddIntotSquence(Space *w)
{
	Space *point = tSquence;

	if(!w) return;
	if (w->width <=0||w->length <=0)
	{
		delete w; 
		return;
	}
	if(w->width <= w->length)w->flag = 0;
	else w->flag = 1;
	if(tSquence==NULL) 
	{
		tSquence = w;
		w->tSquence = NULL;
		return;
	}

	if(tSquence->t > w->t)
	{
		w->tSquence = tSquence;			
		tSquence = w;
	}	
	else if(tSquence->t < w->t)
	{
		while(point->tSquence && point->tSquence->t <= w->t)
		{
			if(point->tSquence->t == w->t)
			{
				
				if(point->tSquence->y > w->y)break;			
				if(point->tSquence->y == w->y && point->tSquence->x > w->x)
					break;
			}
			point = point->tSquence;
		}
		w->tSquence = point->tSquence ;
		point->tSquence = w;
	}
	else{
		if(tSquence->y > w->y)
		{
			w->tSquence = tSquence;			
			tSquence = w;		
		}
		else{
					
			while(point->tSquence && point->tSquence->t <= w->t)
			{
				if(point->tSquence->y > w->y)break;
				if(point->tSquence->y == w->y && point->tSquence->x > w->x)
					break;
				point = point->tSquence;
			}
			w->tSquence = point->tSquence ;
			point->tSquence =w;
		}
	}

}

//-----------------------------------------------------
void Container::deltSpaceLink(Space *w)
{
	Space *p,*q;
	p = q = head;
	if(!w) return;
	if(head == w)
	{
		if(w->level)
		{
			w->level->vertical = head->vertical;
			head = w->level;
		}
		else head = head->vertical;
		w->level = w->vertical = NULL;
		return;
	}

	while(p->vertical && p->vertical->y <= w->y)
	{
		q = p;
		p = p->vertical;
	}
	while(p->level && p->level->x < w->x)
	{
		p = p->level;
	}
	
	if(q->vertical == p)
	{
		if(p==w)
		{
			if(p->level)
			{
				q->vertical = p->level;
				p->level->vertical = p->vertical;
			}
			else q->vertical = p->vertical;
		}
		else{
			p->level = p->level->level;
		}
	}
	else 
	{
		p->level = p->level->level;
	}
	w->level = w->vertical = NULL;
}

//--------------------------------------------------------------------
void Container::deltSquence(Space *w)
{

	Space *p = tSquence;
	if(!w)return;
	if (w->width <=0||w->length <=0)
	{
		delete w;
		return;
	}
	if(tSquence == w)tSquence = w->tSquence;
	else
	{
		while(p->tSquence != w) p = p->tSquence;
		p->tSquence = w->tSquence ;
	}
	w->tSquence = NULL;
}
//---------------------------------------------------------------------

//---------------------------------------------------------------------------------
bool Container::SelectObject (Space *w,Object *&point)
{


	if(!w)
	{
		point = NULL;
		return true;
	}
	point = object;
	while (point)
	{
		if(!point->next && (point->width > Width || point->length > Length))
			return false;
		if (//w空间是竖的(宽或长都装不下)
			(w->flag==0 && (point->width > w->width || point->length > w->length))||
			//w空间是横的(宽或长都装不下)
			(w->flag==1 && (point->width > w->length || point->length > w->width)))
		{
 			point = point->next;
			continue;
		}

		//空间够大 return 1
		if ((w->flag==0 && point->width<= w->width && point->length <= w->length)
			||(w->flag==1 && point->width <= w->length && point->length <= w->width))
			return true;
	}
	point = NULL;
	return true;
}
//---------------------------------------------------------------------------------

void Container::pushqueue(Object * singleObject ,float x,float y ,float t)
{
	occupy *p = new occupy;
	p->object = singleObject;
	p->x =x;
	p->y =y;
	p->t =t;
	p->next = NULL;
	if(queue->rear != NULL)
		queue->rear->next = p;
	queue->rear = p;
	if(queue->front == NULL)queue->front = p;
}
//----------------------------------------------------------------------------

Container::occupy *Container::popqueue()
{	
	occupy *p;
	if(queue->front == NULL)p = NULL;
	else{
		p = queue->front;
		queue->front = queue->front->next;
		if(queue->front == NULL)queue->rear = NULL;
	}
	return p;
}

//-------------------------------------------------------------------------------

void Container::Converge(Space *w)
{
	Space *p,*q;
	Space *array[8],*squence[8];
	int flag = 0;
	for(int i=0;i<8;i++)
	{
		array[i] = NULL;
		squence[i] = NULL;
	}

	deltSquence(w); 
	deltSpaceLink(w);

	//寻找同一直线边
	for(q = head; q && q->y <= w->y+w->length; q = q->vertical)
		for(p = q; p && p->x <= w->x+w->width ;p = p->level )
		{
			//上
			//左边相等
			if(p->x == w->x && p->y+p->length == w->y)
				array[0] = p;	
			//右边相等
			else if(p->x+p->width == w->x+w->width && p->y+p->length == w->y)
				array[1] = p;			

			//左
			//上边相等
			else if(p->y == w->y && p->x+p->width == w->x)
				array[2] = p;
			//下边相等
			else if(p->y+p->length == w->y+w->length && p->x+p->width == w->x)
				array[3] = p;

			//右
			//上边相等
			else if(p->y == w->y && p->x == w->x+w->width)
				array[4] = p;
			//下边相等
			if(p->y+p->length == w->y+w->length && p->x == w->x+w->width)
				array[5] = p;			

			//下
			//左边相等
			else if(p->x == w->x && p->y == w->y+w->length)
				array[6] = p;
			//右边相等
			else if(p->x + p->width == w->x+w->width && w->y+w->length == p->y)
				array[7] = p;
		}

//找合并连接块------------------------------------------------------------
	//按t从小到大排序到squence数组中
		int j = 0,m;
		for(int i = 0;i < 8;i++)
		{
			if(array[i])
			{
				m = j;				
				while(m-1>=0 && array[i]->t < squence[m-1]->t)
				{
					m--;
					squence[m+1] = squence[m];					
				}
				squence[m]=array[i];

				j++;
			}
		}
		

	//根t最小的块合并,不能合并就选择次小的
		int i = 0;		
		while(squence[i])
		{
			p = squence[i];	
			//上***************************************************************
			if(p->x == w->x && p->y+p->length == w->y)//左边相等
			{				
				if(upleft(p,w))return;
			}
			//右边相等------------------------------------------------------------
			else if(p->x+p->width == w->x+w->width && p->y+p->length == w->y)
			{				
				if(upright(p,w))return;
			}

			//左************************************************************************
			else if(p->y == w->y && p->x+p->width == w->x)//上边相等
			{			
				if(leftup(p,w))return;
			}
			//下边相等------------------------------------------------------------------
			else if(p->y+p->length == w->y+w->length && p->x+p->width == w->x)
			{			
				if(leftdown(p,w))return;
			}

			//右*************************************************************************
			else if(p->y == w->y && p->x == w->x+w->width)//上边相等
			{
			
				if(rightup(p,w))return;
			}
			//下边相等-------------------------------------------------------------------
			else if(p->y+p->length == w->y+w->length && p->x == w->x+w->width)
			{
			
				if(rightdown(p,w))return;
			}

			//下*************************************************************************
			else if(p->x == w->x && p->y == w->y+w->length)//左边相等
			{
			
				if(downleft(p,w))return;
			}
			//右边相等------------------------------------------------------------------
			else if(p->x + p->width == w->x + w->width && w->y + w->length == p->y)
			{
			
				if(downright(p,w))return;
			}
		
			i++;
		}

		//w空间的两个端点都有相连的
		if(array[0] && array[1]&&array[0]!=array[1])//上
		{
			p = head;			
			while(p && p->y < w->y)
			{
				q = p;
				while(q->x < w->x && q->level) q = q->level;
				while(q->x < w->x + w->width)
				{
					if(q->y + q->length == w->y)
					{
						q->length += w->length;
						if(q->width < q->length) q->flag = 0;
						else q->flag = 1;
					}
					if(q->level) q = q->level;
					else break;
				}
				p = p->vertical;
			}
			delete w;
			return;
		}

		else if(array[2] && array[3]&&array[2]!=array[3])//左
		{
			p = head;
			while(p->y < w->y) p = p->vertical;
			while(p && p->y < w->y+w->length)
			{
				q = p;
				while(q->level && q->level->x+q->level->width <= w->x)
					q = q->level;
				if(q->x + q->width == w->x)
				{
					q->width += w->width;
					if(q->width < q->length) q->flag = 0;
					else q->flag = 1;
				}
				p = p->vertical;
			}
			
			delete w;
			return;
		}
		else if(array[4] && array[5]&&array[4]!=array[5])//右
		{
			p = head;
			while(p->y < w->y)p = p->vertical;
			while(p && p->y < w->y + w->length)
			{
				q = p;
				while(q->level && q->level->x <= w->x +w->width)
					q = q->level;
				if(q->x == w->x + w->width)
				{
					deltSquence(q); 
					deltSpaceLink(q);
					q->x -= w->width;
					q->width += w->width;
					if(q->width < q->length) q->flag = 0;
					else q->flag = 1;
					AddIntoSpaceLink(q);
					AddIntotSquence(q);
				}
				p = p->vertical;
			}
			delete w;
			return;
		}
		else if(array[6] && array[7]&&array[6]!=array[7])//下
		{
			p = head;
			while(p->y <= w->y)p = p->vertical;
			while(p)
			{
				q = p;
				while(q->x < w->x && q->level) q = q->level;
				while(q->x < w->x + w->width)
				{
					if(q->y  == w->y + w->length)
					{
						deltSquence(q); 
						deltSpaceLink(q);
						q->length += w->length;
						q->y -=w->length;
						if(q->width < q->length) q->flag = 0;
						else q->flag =1;
						AddIntoSpaceLink(q);
						AddIntotSquence (q);
					}
					if(q->level) q = q->level;
					else break;
				}
				p = p->vertical;
			}
			delete w;
			return;
		}
	
//找不到并连接块,使w中的t跟周围最大的一样大--------------------------------
	p = tSquence;
	while(p && p->t == w->t) p = p->tSquence;
	if(p) w->t = p->t;
	AddIntoSpaceLink(w);
	AddIntotSquence (w);
}


//--------------------------------------------------------------------------
bool Container::upleft(Space *p,Space *w)
{
	Space *brk[2] = {NULL,NULL};
	//两边都相等,直接合并
	if(p->width == w->width)
	{
		brk[0] = new Space;
		brk[0]->x = p->x;
		brk[0]->y = p->y;
		brk[0]->t = p->t;
		brk[0]->width = p->width;
		brk[0]->length = p->length + w->length;
		if(brk[0]->width < brk[0]->length) brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;
					
		deltSpaceLink(p);
		deltSquence(p);
		delete p;
		delete w;
		AddIntoSpaceLink(brk[0]);
		AddIntotSquence(brk[0]);	
		return true;
	}
	else if(p->width > w->width)
	{
		brk[0] = new Space;
		brk[0]->x = p->x;
		brk[0]->y = p->y;
		brk[0]->t = p->t;
		brk[0]->width  = w->width ;
		brk[0]->length = p->length+w->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = p->x+w->width;
		brk[1]->y = p->y;
		brk[1]->t = p->t;
		brk[1]->width = p->width - w->width;
		brk[1]->length = p->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	else if(p->width < w->width)
	{
		brk[0] = new Space;
		brk[0]->x = p->x;
		brk[0]->y = p->y;
		brk[0]->t = p->t;
		brk[0]->width  = p->width ;
		brk[0]->length = p->length + w->length;
		if(brk[0]->width < brk[0]->length) brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = w->x+p->width;
		brk[1]->y = w->y;
		brk[1]->t = w->t;
		brk[1]->width = w->width - p->width;
		brk[1]->length = w->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	return false;
}
//--------------------------------------------------------------------------
bool Container::upright(Space *p,Space *w)
{
	Space *brk[2] = {NULL,NULL};
	if(p->width > w->width)
	{
		brk[0] = new Space;
		brk[0]->x = p->x;
		brk[0]->y = p->y;
		brk[0]->t = p->t;
		brk[0]->width  = p->width - w->width ;
		brk[0]->length = p->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = p->x+brk[0]->width;
		brk[1]->y = p->y;
		brk[1]->t = p->t;
		brk[1]->width = w->width;
		brk[1]->length = p->length + w->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	else if(p->width < w->width)
	{
		brk[0] = new Space;
		brk[0]->x = p->x;
		brk[0]->y = p->y;
		brk[0]->t = p->t;
		brk[0]->width  = p->width ;
		brk[0]->length = p->length+w->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = w->x;
		brk[1]->y = w->y;
		brk[1]->t = w->t;
		brk[1]->width = w->width - p->width;
		brk[1]->length = w->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}	
	return false;
}
//--------------------------------------------------------------------------
bool Container::leftup(Space *p,Space *w)
{
	Space *brk[2] = {NULL,NULL};
	//两边都相等,直接合并
	if(p->length == w->length)
	{
		brk[0] = new Space;
		brk[0]->x = p->x;
		brk[0]->y = p->y;
		brk[0]->t = p->t;
		brk[0]->width = p->width+w->width;
		brk[0]->length = p->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;
					
		deltSpaceLink(p);
		deltSquence(p);
		delete p;
		delete w;
		AddIntoSpaceLink(brk[0]);
		AddIntotSquence(brk[0]);	
		return true;
	}
	else if(p->length > w->length)
	{
		brk[0] = new Space;
		brk[0]->x = p->x;
		brk[0]->y = p->y;
		brk[0]->t = p->t;
		brk[0]->width  = p->width + w->width ;
		brk[0]->length = w->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = p->x;
		brk[1]->y = p->y + w->length;
		brk[1]->t = p->t;
		brk[1]->width = p->width;
		brk[1]->length = p->length - w->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	else if(p->length < w->length)
	{
		brk[0] = new Space;
		brk[0]->x = p->x;
		brk[0]->y = p->y;
		brk[0]->t = p->t;
		brk[0]->width  = p->width + w->width;
		brk[0]->length = p->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = w->x;
		brk[1]->y = w->y + p->length;
		brk[1]->t = w->t;
		brk[1]->width = w->width;
		brk[1]->length = w->length - p->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}	
	return false;
}
//--------------------------------------------------------------------------
bool Container::leftdown(Space *p,Space *w)
{
	Space *brk[2] = {NULL,NULL};
	if(p->length > w->length)
	{
		brk[0] = new Space;
		brk[0]->x = p->x;
		brk[0]->y = p->y;
		brk[0]->t = p->t;
		brk[0]->width  = p->width;
		brk[0]->length = p->length - w->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = p->x;
		brk[1]->y = p->y + brk[0]->length;
		brk[1]->t = p->t;
		brk[1]->width = p->width + w->width;
		brk[1]->length = w->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	else if(p->length < w->length)
	{
		brk[0] = new Space;
		brk[0]->x = w->x;
		brk[0]->y = w->y;
		brk[0]->t = w->t;
		brk[0]->width  = w->width;
		brk[0]->length = w->length - p->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = p->x;
		brk[1]->y = p->y;
		brk[1]->t = p->t;
		brk[1]->width = p->width + w->width;
		brk[1]->length = p->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	return false;
}
//--------------------------------------------------------------------------
bool Container::rightup(Space *p,Space *w)
{
	Space *brk[2] = {NULL,NULL};
	//两边都相等,直接合并
	if(p->length == w->length)
	{
		brk[0] = new Space;
		brk[0]->x = w->x;
		brk[0]->y = w->y;
		brk[0]->t = p->t;
		brk[0]->width = p->width+w->width;
		brk[0]->length = w->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;
					
		deltSpaceLink(p);
		deltSquence(p);
		delete p;
		delete w;
		AddIntoSpaceLink(brk[0]);
		AddIntotSquence(brk[0]);	
		return true;
	}
	else if(p->length > w->length)
	{
		brk[0] = new Space;
		brk[0]->x = w->x;
		brk[0]->y = w->y;
		brk[0]->t = p->t;
		brk[0]->width  = w->width + p->width;
		brk[0]->length = w->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = p->x;
		brk[1]->y = p->y + w->length;
		brk[1]->t = p->t;
		brk[1]->width = p->width;
		brk[1]->length = p->length - w->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	else if(p->length < w->length)
	{
		brk[0] = new Space;
		brk[0]->x = w->x;
		brk[0]->y = w->y;
		brk[0]->t = p->t;
		brk[0]->width  = w->width +p->width;
		brk[0]->length = p->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = w->x;
		brk[1]->y = w->y + p->length;
		brk[1]->t = w->t;
		brk[1]->width = w->width;
		brk[1]->length = w->length - p->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	return false;
}
//--------------------------------------------------------------------------
bool Container::rightdown(Space *p,Space *w)
{
	Space *brk[2] = {NULL,NULL};
	if(p->length > w->length)
	{
		brk[0] = new Space;
		brk[0]->x = p->x;
		brk[0]->y = p->y;
		brk[0]->t = p->t;
		brk[0]->width  = p->width;
		brk[0]->length = p->length - w->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = w->x;
		brk[1]->y = w->y;
		brk[1]->t = p->t;
		brk[1]->width = w->width + p->width;
		brk[1]->length = w->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	else if(p->length < w->length)
	{
		brk[0] = new Space;
		brk[0]->x = w->x;
		brk[0]->y = w->y;
		brk[0]->t = w->t;
		brk[0]->width  = w->width;
		brk[0]->length = w->length - p->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = w->x;
		brk[1]->y = w->y + brk[0]->length;
		brk[1]->t = p->t;
		brk[1]->width = w->width + p->width;
		brk[1]->length = p->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	return false;
}
//-------------------------------------------------------------------------
bool Container::downleft(Space *p,Space *w)
{
	Space *brk[2] = {NULL,NULL};
	//两边都相等,直接合并
	if(p->width == w->width)
	{
		brk[0] = new Space;
		brk[0]->x = w->x;
		brk[0]->y = w->y;
		brk[0]->t = p->t;
		brk[0]->width = w->width ;
		brk[0]->length = w->length + p->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;
					
		deltSpaceLink(p);
		deltSquence(p);
		delete p;
		delete w;
		AddIntoSpaceLink(brk[0]);
		AddIntotSquence(brk[0]);	
		return true;
	}
	else if(p->width > w->width)
	{
		brk[0] = new Space;
		brk[0]->x = w->x;
		brk[0]->y = w->y;
		brk[0]->t = p->t;
		brk[0]->width  = w->width ;
		brk[0]->length = w->length + p->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = p->x+w->width;
		brk[1]->y = p->y;
		brk[1]->t = p->t;
		brk[1]->width = p->width - w->width;
		brk[1]->length = p->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	else if(p->width < w->width)
	{
		brk[0] = new Space;
		brk[0]->x = w->x;
		brk[0]->y = w->y;
		brk[0]->t = p->t;
		brk[0]->width  = p->width ;
		brk[0]->length = p->length+w->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = w->x+p->width;
		brk[1]->y = w->y;
		brk[1]->t = w->t;
		brk[1]->width = w->width - p->width;
		brk[1]->length = w->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	return false;
}
//---------------------------------------------------------------------------
bool Container::downright(Space *p,Space *w)
{
	Space *brk[2] = {NULL,NULL};
	if(p->width > w->width)
	{
		brk[0] = new Space;
		brk[0]->x = p->x;
		brk[0]->y = p->y;
		brk[0]->t = p->t;
		brk[0]->width  = p->width - w->width ;
		brk[0]->length = p->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = w->x;
		brk[1]->y = w->y;
		brk[1]->t = p->t;
		brk[1]->width = w->width;
		brk[1]->length = p->length + w->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高		
		if(needconverge(p,w,brk[0],brk[1]))
		{	
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	else if(p->width < w->width)
	{
		brk[0] = new Space;
		brk[0]->x = w->x;
		brk[0]->y = w->y;
		brk[0]->t = w->t;
		brk[0]->width  = w->width - p->width;
		brk[0]->length = w->length;
		if(brk[0]->width < brk[0]->length)brk[0]->flag=0;
		else brk[0]->flag = 1;
		brk[0]->level =brk[0]->tSquence =brk[0]->vertical =NULL;

		brk[1] = new Space;
		brk[1]->x = w->x + brk[0]->width;
		brk[1]->y = w->y;
		brk[1]->t = p->t;
		brk[1]->width = p->width;
		brk[1]->length = w->length + p->length;
		if(brk[1]->width < brk[1]->length)brk[1]->flag=0;
		else brk[1]->flag = 1;
		brk[1]->level =brk[1]->tSquence =brk[1]->vertical =NULL;
		//看一下合并后空间利用率高,还是不合并空间利用高
		if(needconverge(p,w,brk[0],brk[1]))
		{
			deltSpaceLink(p);
			deltSquence(p);
			delete p;
			delete w;
			AddIntoSpaceLink(brk[0]);
			AddIntotSquence(brk[0]);
			AddIntoSpaceLink(brk[1]);
			AddIntotSquence(brk[1]);
			return true;
		}
		else{
			delete brk[0];
			delete brk[1];
		}
	}
	return false;
}
//-------------------------------------------------------------------------
bool Container::needconverge(Space *p,Space *w,Space *brk0,Space *brk1)
{
	Object *q[4] = {NULL,NULL,NULL,NULL};
	float before=0.0,after=0.0;
	float temp1 = 0.0,temp2 = 0.0,total = 0.0;
	
	SelectObject(p,q[0]);
	SelectObject(w,q[1]);
	SelectObject(brk0,q[2]);
	SelectObject(brk1,q[3]);

	if(p)temp1 = p->length*p->width;
	if(w)temp2 = w->length*w->width;
	total = temp1 + temp2;

	temp1 = temp2 = 0.0;
	if(q[0])
		temp1 = q[0]->length * q[0]->width;
	if(q[1])
		temp2 = q[1]->length *q[1]->width;
	before = (temp1+temp2)/total;

	temp1 = temp2 = 0.0;
	if(brk0)temp1 = brk0->length*brk0->width;
	if(brk1)temp2 = brk1->length*brk1->width;
	total = temp1 + temp2;

	temp1 = temp2 = 0.0;
	if(q[2])temp1 = q[2]->length*q[2]->width;
	if(q[3])temp2 = q[3]->length*q[3]->width;
	after = (temp1+temp2)/total;

	if(before >= after)return false;	
	return true;	
}

void Container::objectSort(Object *&object)
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

//-----------------------------------------------------------------------