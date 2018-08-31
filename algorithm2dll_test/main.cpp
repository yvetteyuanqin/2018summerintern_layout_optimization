#include <iostream>
#include <stdlib.h>
#include "header.h"
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
				ret[i][4]= p->n;//orientation of object
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
	float in1[34][5]={{1,6.575,14.115,40,1},
					{2,6.575,11.515,40,1},
					{3,9.25,25.6,60,1},
					{4,13.5,13.7,40,1},
					{5,13.5,11.9,40,1},
					{6,13.5,13.7,40,1},
					{7,13.5,11.9,40,1},
					{8,12.77,25.6,40,1},
					{9,12,25.6,40,1},
					{10,10.05,25.6,40,1},
					//{11,0,0,40,1},
					//{12,0,0,40,1},
					{13,7.5,9.895,60,1},
					{14,6.75,4.385,60,1},
					{15,4.92,1.995,60,1},
					{16,6.75,0.75,40,1},
					{17,6.75,0.75,40,1},
					{18,9.8,25.6,60,1},
					{19,7.5,24.43,60,1},
					{20,10.3,20.73,60,1},
					{21,9.8,24.92,60,1},
					{22,7.5,21.26,60,1},
					{23,8.95,14.41,60,1},
					{24,9.8,22.72,60,1},
					{25,12,3,40,1},
					{26,1.8,20,40,1},
					{27,28.25,0.76,40,1},
					{28,28.25,0.76,40,1},
					{29,1.5,20,40,1},
					{30,4.6,21.52,40,1},
					{31,12.6,13.1,40,1},
					{32,12.6,12.5,40,1},
					{33,12.12,23.25,40,1},
					{34,12.94,9.6,40,1},
					{35,11.56,7.34,40,1},
					{36,11.56,7.34,40,1}};//{{1,3,6,3,1},{2,1,4,2,1},{3,1,2,1,1},{4,2,2,2,1},{5,1,1,1,1}};
	float in2[2] ={50,50};//field info
	/*float* field = new float[2];
	float** inarr = new float* [sizeof(in1)];
	for(int i=0;i<sizeof(in1[0]);i++){}*/
	cout<<"Outside: "<<endl;
	float *ret = mainEntrance(in1,in2,"qwerty",sizeof(in1)/sizeof(float)/5);//return value not drawn
	cout<<"Outside: "<<sizeof(in1)/sizeof(float)/5<<endl;
	for (int i = 0; i < sizeof(in1)/sizeof(float)/5; i++)
                {
                     for (int j = 0; j < 8; j++)
                          cout<<ret[i*8+j]<<'\t';
                    cout<<endl;
                }
	getchar();
}