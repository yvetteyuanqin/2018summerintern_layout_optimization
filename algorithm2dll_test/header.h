//#define FILEOUTPUT
#define DEBUG


using namespace std;
/*Object[]数组中以宽度递减的顺序排放;(宽度<长度)
而在空间中宽度不一定大于长度.tSpuence中t升序*/

class Container
{
public:
		struct  Space
	{
		float x;				//空间位置
		float y;
		float t;	 			//此空间位置占用的高度
		float width; 			//摆放宽长度与宽度
		float length;	
		int flag;			//if flag =0 width<length else width>length
		struct Space *level;		//指向相连水平空间指针
		struct Space *vertical;	//指向相连垂直空间指针
		struct Space *tSquence;	//指向比它大的t的空间
	};

	struct Object
	{
		bool f;//whether loaded or not
		int id;//newly added foi identification of certain obj
		float width;		//宽
		float length;		//长
		float t;
		int n;			//这种物件的个数
		struct Object *next;
	};


	struct occupy
	{
		float x;			//存入的定点空间坐标
		float y;
		float t;
		Object *object;	//object.n为0表示竖放,为1横放
		struct occupy *next;
	};

	struct Queue
	{
		occupy *rear;
		occupy *front;
	};

	Container(float ,float ,char field[]);	//初始化
	~Container();
	bool Loading(Object *&);	//装载
	void pushqueue(Object *, float,float, float); //装入物品，压入队列
	occupy *popqueue();

	void occupyPercentage(float**);

	
//private:
	float containerArea;
	char fieldName[20];
	float Width,Length;
	Space *head;	//集装箱被分割成很多块,用二维链表串起来
	Space *tSquence;//串起来的链表中按t升序组成有序对队列
	Object *object;	//物品队列,宽度递减序列
	Queue *queue;	//已装入的物品队列
	
	bool SelectObject (Space *,Object *&);//选择合适的物品和空间
	void deltSquence(Space *);		//在t序列和二维链表中删除w
	void deltSpaceLink(Space *);	
	//看一下合并后空间利用率高(为1),还是不合并空间利用高(为0),
	bool needconverge(Space *,Space *,Space *,Space *);
	static void objectSort(Object *&object);

	// 把产生的三个块弄到二维链表中
	void AddIntoSpaceLink(Space *);
	// 把产生的三个块弄到在t序列中
	void AddIntotSquence (Space *);

	void Converge(Space *);			//合并空间

	bool upleft(Space *,Space *);
	bool upright(Space *,Space *);
	bool leftup(Space *,Space *);
	bool leftdown(Space *,Space *);
	bool rightup(Space *,Space *);
	bool rightdown(Space *,Space *);
	bool downleft(Space *,Space *);
	bool downright(Space *,Space *);


};