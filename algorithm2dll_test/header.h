//#define FILEOUTPUT
#define DEBUG


using namespace std;
/*Object[]�������Կ�ȵݼ���˳���ŷ�;(���<����)
���ڿռ��п�Ȳ�һ�����ڳ���.tSpuence��t����*/

class Container
{
public:
		struct  Space
	{
		float x;				//�ռ�λ��
		float y;
		float t;	 			//�˿ռ�λ��ռ�õĸ߶�
		float width; 			//�ڷſ�������
		float length;	
		int flag;			//if flag =0 width<length else width>length
		struct Space *level;		//ָ������ˮƽ�ռ�ָ��
		struct Space *vertical;	//ָ��������ֱ�ռ�ָ��
		struct Space *tSquence;	//ָ��������t�Ŀռ�
	};

	struct Object
	{
		bool f;//whether loaded or not
		int id;//newly added foi identification of certain obj
		float width;		//��
		float length;		//��
		float t;
		int n;			//��������ĸ���
		struct Object *next;
	};


	struct occupy
	{
		float x;			//����Ķ���ռ�����
		float y;
		float t;
		Object *object;	//object.nΪ0��ʾ����,Ϊ1���
		struct occupy *next;
	};

	struct Queue
	{
		occupy *rear;
		occupy *front;
	};

	Container(float ,float ,char field[]);	//��ʼ��
	~Container();
	bool Loading(Object *&);	//װ��
	void pushqueue(Object *, float,float, float); //װ����Ʒ��ѹ�����
	occupy *popqueue();

	void occupyPercentage(float**);

	
//private:
	float containerArea;
	char fieldName[20];
	float Width,Length;
	Space *head;	//��װ�䱻�ָ�ɺܶ��,�ö�ά��������
	Space *tSquence;//�������������а�t�����������Զ���
	Object *object;	//��Ʒ����,��ȵݼ�����
	Queue *queue;	//��װ�����Ʒ����
	
	bool SelectObject (Space *,Object *&);//ѡ����ʵ���Ʒ�Ϳռ�
	void deltSquence(Space *);		//��t���кͶ�ά������ɾ��w
	void deltSpaceLink(Space *);	
	//��һ�ºϲ���ռ������ʸ�(Ϊ1),���ǲ��ϲ��ռ����ø�(Ϊ0),
	bool needconverge(Space *,Space *,Space *,Space *);
	static void objectSort(Object *&object);

	// �Ѳ�����������Ū����ά������
	void AddIntoSpaceLink(Space *);
	// �Ѳ�����������Ū����t������
	void AddIntotSquence (Space *);

	void Converge(Space *);			//�ϲ��ռ�

	bool upleft(Space *,Space *);
	bool upright(Space *,Space *);
	bool leftup(Space *,Space *);
	bool leftdown(Space *,Space *);
	bool rightup(Space *,Space *);
	bool rightdown(Space *,Space *);
	bool downleft(Space *,Space *);
	bool downright(Space *,Space *);


};