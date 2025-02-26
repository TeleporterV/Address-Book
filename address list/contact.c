#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include"contact.h"

static int Find_ByName(const struct contact* ps, char name[Max_Name]);

//加载文件中的内容到通讯录中
void Load_Contacter(struct contact* ps)
{
	FILE*  pfRead=fopen("contact.dat", "rb");
	//打开contact.dat文件，进行只读操作，rb代表读二进制文件，而非文本文件
	//在打开文件的同时，都会返回一个FILE*的指针变量指向该文件，也相当于建立了指针和文件的关系。

	if (pfRead == NULL)//判断是否成功打开
	{
		printf("Load_Contact:%s", strerror(errno));
		//打印最近一次系统调用或标准库函数失败的错误信息,需要引用头文件<errno.h>
		return ;
	}

	//读取文件放到通讯录中
	struct peoinfo tmp = {0};
	//创建一个结构体人员信息类型的变量，待会要把读到的数据放进去，当临时记录

	while (fread(&tmp, sizeof(tmp), 1, pfRead))
	//fread(存数据的位置，元素的大小，读取的数目，指针指向的文件结构（文件结构是什么）
	//fread是读取文件的操作，若读成功就返回1，没成功就返回0，放在whilel里面可以判断循环
	//循环调用 fread，每次读取一条记录（struct peoinfo）。当文件结束时，fread 返回 0，循环终止
	{
		CheckCapacity(ps);// 检查通讯录容量是否足够，若够，不进行操作；若不够，进行扩容
		ps->data[ps->size] = tmp;//将临时记录存入通讯录数组
		ps->size++;// 更新通讯录当前记录数
		printf("读取成功\n");
	}

	//关闭文件
	fclose(pfRead);
	pfRead = NULL;//将文件指针置空，避免误用已关闭的指针
}




//初始化通讯录里面的信息
void Init_contact(struct contact* ps)
{
	//申请内存空间，结构体peoinfo类型指针来接收
	ps->data = (struct peoinfo*) malloc(sizeof(struct peoinfo)*3);//为什么要*3，还有为什么要用指针

	if (ps->data == NULL)//判断是否申请内存空间成功
	{
		return;
	}

	ps->size = 0;//通讯录最初只有0个值
	ps->capacity = DEFAULT_SZ;
	
	//把文件中已经存放的信息加载到通讯录中
	Load_Contacter(ps);
}


//检查扩容功能
void CheckCapacity(struct contact* ps)//注意传的是地址，要加*
{
	if (ps->size == ps->capacity)//说明当前容量和最大容量相同了
	{
		//扩容
		struct peoinfo* ptr = realloc(ps->data,(ps->capacity+2)*sizeof(struct peoinfo));
		//realloc改变申请的内存空间大小
		//realloc(内存地址，修改后的大小）

		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			printf("扩容成功\n");
		}
		else
		{
			printf("扩容失败\n");
		}
	}
}


//添加联系人功能
void Add_Contacter(struct contact* ps)
{
	// 检测当前通讯录的容量
	//1、如果满了，就增加空间
	//2、如果不满，啥事都不干
	CheckCapacity(ps);

	//添加信息
	printf("请输入名字\n");
	scanf("%s", &ps->data[ps->size].name);
	printf("请输入年龄\n");
	scanf("%d", &ps->data[ps->size].age);
	printf("请输入性别\n");
	scanf("%s", &ps->data[ps->size].sex);
	printf("请输入电话\n");
	scanf("%s", &ps->data[ps->size].phone);
	printf("请输入地址\n");
	scanf("%s", &ps->data[ps->size].address);

	ps->size++;
	printf("添加成功\n");
}


//删除通讯录中的信息
void Del_Contacter(struct contact* ps)
{
	char name[Max_Name];//创一个数组，放你要删的人的名字
	printf("请输入你要删除的人的名字\n");
	scanf("%s", name);

	//查找要删除的人所在的位置
	int pos = Find_byName(ps, name);//新函数，根据名字进行查找，找到了返回名字所在元素的下标，没找到就返回-1

	if (pos == -1)//没查找到
	{
		printf("你要删除的人不存在\n");
	}
	else//查到了，进行删除
	{
		// 如果是唯一联系人
		if (ps->size == 1) {
			ps->size = 0; //清空通讯录
		}
		else {
			for (int j = pos; j < ps->size - 1; j++)//从pos开始，直到比删除前少一个的时候就停止（因为你要删的那个已经被前面的覆盖住了，size就少了一个，size-1就是最后了）
			{
				ps->data[j] = ps->data[j + 1]; //将这个联系人后面的信息逐个向前进行覆盖
			}
			ps->size--;
		}
		printf("删除成功\n");
	}
}


//查找通讯录中的信息
void Find_Contacter(const struct contact* ps)
{
	char name[Max_Name];//max_name名字最长的人的长度，头文件定义
	printf("请输入你要查找的名字\n");
	scanf("%s", name);
	int pos = Find_byName(ps, name);
	if (pos == -1)
	{
		printf("你查找的人不存在\n");
	}
	else
	{
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\n","姓名", "年龄", "性别", "电话", "地址");
		printf("%-20s\t%-4d\t%-5s\t%-12s\t%-20s\n",ps->data[pos].name,
			ps->data[pos].age,
			ps->data[pos].sex,
			ps->data[pos].phone,
			ps->data[pos].address);
	}
}


//查找函数实现
static int Find_byName(const struct contact* ps,char name[Max_Name])
{
	for (int i = 0; i < ps->size; i++)//遍历已经有的所有
	{
		if (0 == strcmp(ps->data[i].name, name))//将name数组里面的名字和通讯录中现有的所有名字进行比较，看是否有相同的
		//strcmp是比较两字符串的大小（ASCII码），strcmp(char* a,char* b)
		//返回值：<0,即a<b, a排b前面; 0, a和b完全相同; >0，a大于b，a排b后面
	    //返回值理解为前面减后面的大小，最后谁小谁排前面
		{
			return i;
		}
	}
	return -1;
}


//修改通讯录中的信息
void Mod_Contacter(struct contact* ps)
{
	char name[Max_Name];
	printf("请输入你要修改的联系人的姓名\n");
	scanf("%s", name);
	int pos = Find_byName(ps, name);
	if (pos == -1)//修改的人不存在
	{
		printf("要修改的人不存在！\n");
	}
	else
	{
		printf("请输入名字:");
		scanf("%s", &ps->data[pos].name);
		printf("请输入年龄:");
		scanf("%d", &ps->data[pos].age);
		printf("请输入性别:");
		scanf("%s", &ps->data[pos].sex);
		printf("请输入电话:");
		scanf("%s", &ps->data[pos].phone);
		printf("请输入地址:");
		scanf("%s", &ps->data[pos].address);
		printf("修改成功！\n");
	}
}


//打印通讯录中的信息
void Show_Contacter(struct contact* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\n", "姓名", "年龄", "性别", "电话", "地址");
		int i = 0;
		while (i < ps->size)
		{
			//从0开始到size里面所有都遍历一遍
			printf("%-20s\t%-4d\t%-5s\t%-12s\t%-20s\n", ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].phone,
				ps->data[i].address);
			i++;
		}
	}
}


//对通讯录中的信息进行排序
//1.按姓名进行排序
int Compar_ByName(const void* x,const void* y)
//比较函数 int compar(const void*a,const void*b)
//a,b是指向数组元素的指针，类型是void*(这在比较函数里面是固定的），必须要强制转换成需要的类型
//返回值：<0,a x排在y前面；0,x和y顺序不变；>0,x排在y后面
//利用strcmp实现，原理基本一样
{
	return strcmp(((struct peoinfo*)x)->name, ((struct peoinfo*)y)->name);
}

//2.按年龄进行排序
int Compar_ByAge(const void* x, const void* y)
{
	return ((struct peoinfo*)x)->age - ((struct peoinfo*)y)->age;
	//这块注意一下，age是int，要相减的，不用strcmp因为不是字符串，比大小就能排出来了
}

//3.按地址进行排序
int Compar_ByAddress(const void* x, const void* y)
{
	return strcmp(((struct peoinfo*)x)->address, ((struct peoinfo*)y)->address);
}


//排序函数
void Sort_Contacter(struct contact* ps)
{
	printf("请输入你想排序的方式\n");
	printf("1.姓名\n2.年龄\n3.地址\n");
	int input = 0;
	scanf("%d", &input);
	switch (input)
	{
	case 1:
		qsort(ps->data, ps->size, sizeof(ps->data[0]), Compar_ByName);
		//qsort(数组起始地址，元素个数，每个元素大小，比较函数）
		printf("排序成功\n");
		break;
	case 2:
		qsort(ps->data, ps->size, sizeof(ps->data[0]), Compar_ByAge);
		printf("排序成功\n");
		break;
	case 3:
		qsort(ps->data, ps->size, sizeof(ps->data[0]), Compar_ByAddress);
		printf("排序成功\n");
		break;
	}
}





//清空通讯录中的信息
void Clear_Contacter(struct contact* ps)
{
	memset(ps->data, 0, sizeof(ps->data));//memset函数
	ps->size = 0;
	printf("清空成功！\n");
}



//销毁通讯录
void Destory_Contact(struct contact* ps)
{
	free(ps->data);//释放空间
	ps->data = NULL;//避免指针误用
}



//保存通讯录信息
void Save_Contact(struct contact* ps)
{
	FILE* pfWrite = fopen("contact.dat", "wb");//打开文件，同时给一个指针指向该文件，将文件和地址联系起来

	if (pfWrite == NULL)//若未成功打开文件
	{
		printf("Save_Contact::%s", strerror(errno));
		//打印最近一次系统调用或标准库函数失败的错误信息,需要引用头文件<errno.h>
		return;
	}
	
	//将通讯录中的数据写入文件中，即保存
	for (int i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->data[i]), sizeof(struct peoinfo), 1, pfWrite);
		//fwrie(指针指向写入的数据，写入的大小单位字节，写入的数量，写入的目的流）
	}
		printf("保存成功\n");
		//关闭文件
		fclose(pfWrite);
		pfWrite = NULL;
	
}