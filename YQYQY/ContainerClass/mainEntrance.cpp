#include <iostream>
#include <stdlib.h>
#include "ContainerClass.h"
#include "mainEntrancedll.h"
//#include "stdafx.h"


//input:inputarr 4 param: x,y,t,n
float* mainEntrance(float inputarr[][5], float fieldinfo[], char fieldname[],int itemnum){
	Container::Object *initObject = NULL,*p = NULL;
	/*float width = 0.0;
	float length = 0.0;
	float t = 0.0;
	int i=0,n=0,flag=0,num=0;
	*/



	initObject = new Container::Object;
	for(int i=0; i<itemnum; i++){
		//head node
		if(i==0)	{
			initObject->id = inputarr[i][0];
			//exchange width and length if length<width
			if(inputarr[i][2] < inputarr[i][1])
			{
				initObject->length = inputarr[i][1];
				initObject->width = inputarr[i][2];
			}
			else 
			{
				initObject->length = inputarr[i][2];
				initObject->width = inputarr[i][1];
			}
			initObject->t =  inputarr[i][3];
			initObject->n =inputarr[i][4];
			initObject->next=NULL;
			continue;
		}else{
			p = new Container::Object;
			p->id = inputarr[i][0];
			if(inputarr[i][2] < inputarr[i][1])
			{
				p->length = inputarr[i][1];
				p->width = inputarr[i][2];
			}
			else 
			{
				p->length = inputarr[i][2];
				p->width = inputarr[i][1];
			}
			//INSERT NEW NODE
			p->t = inputarr[i][3];
			p->n =inputarr[i][4];
			p->next=initObject;		
			initObject = p;
		}
		
	}
#ifdef DEBUG
		Container::Object *curr = initObject;
		cout<<"To be loaded param:"<<endl;
	while(curr!=NULL){
		cout<<curr->width<<","<<curr->length<<endl;
		curr = curr->next;
	}
#endif

	//SORT THE OBJECT BY ASCENDING ORDER
		Container::objectSort(initObject);

#ifdef DEBUG
		Container::Object *curr1 = initObject;
		cout<<"After sorted:"<<endl;
	while(curr1!=NULL){
		cout<<curr1->width<<","<<curr1->length<<endl;
		curr1 = curr1->next;
	}
#endif


		//instantiate one Container for loading one field
		Container *A = new Container(fieldinfo[0],fieldinfo[1],fieldname);
	
		int objcount =0 ;//loaded object number
		//releasing mem AFTER LOADING 

		int flag = 1;
		while(initObject&&flag>0){
			if(A->Loading(initObject)){
				objcount++;
			}else{flag--;}		
		}
		

		//2d ptr for return
		float **ret = new float*[itemnum];//2d array to be returned
		for(int i =0;i<itemnum;i++){
			ret[i] = new float[8];//for return width,length,peried,x,y,orientation
		}

		A->occupyPercentage(ret);


		cout<<endl;

		for(int i=0;i<objcount;i++)
		{
			for(int j =0;j<8;j++)	cout<<ret[i][j]<<"\t";
			cout<<endl;
		}
		

			
		//while deconstructing the container, the layout info would be fetched by objects in queue
		if(A)	delete A;
	
		//showing reminant objects
		p = initObject;
		int i=objcount;
		if(p)
		{
			p->f=false;
			cout<<"没有场地可以装下的物品:"<<endl;
			while(p)
			{
				ret[i][2]= p->length;
				ret[i][3]= p->width;
				ret[i][4]= 0;//orientation of object
				ret[i][5]= 0;
				ret[i][6]= 0;
				ret[i][7]= 0;//which period could start to put
				ret[i][1]= p->f;
				ret[i][0]= p->id;//loaded or not
				
				cout<<"物品  (id:"<<p->id<<",长"<<p->length<<",宽"<<p->width<<",加工周期:"<<p->t<<')'<<endl;
				//cout<<"if loaded?: "<<p->f<<endl;
				initObject = p;
				p = p->next;
				delete initObject;
			}
		}
		for(int i=0;i<itemnum;i++)
		{
			for(int j =0;j<8;j++)	cout<<ret[i][j]<<"\t";
			cout<<endl;
		}
		cout<<endl<<endl<<"Done in function"<<endl<<endl;




		float* retptr = new float[itemnum*8];
		//objcount counts loaded obj
		
		for(i=0;i<itemnum;i++)
			for(int j=0;j<8;j++)
				retptr[i*8+j]=ret[i][j];

		return retptr ;//????

	


}

int main(){
	float in1[4][5]={{1,3,6,3,1},{2,1,4,2,1},{3,1,2,1,1},{4,2,2,2,1}};
	float in2[2] ={5,4};//field info
	/*float* field = new float[2];
	float** inarr = new float* [sizeof(in1)];
	for(int i=0;i<sizeof(in1[0]);i++){}*/
	getchar();
	return 1;
//	mainEntrance(in1,in2,"qwerty");//return value not drawn


}