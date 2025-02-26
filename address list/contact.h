#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#define Max_Name 20
#define Max_Phone 20
#define Max_Sex 20
#define Max_Address 30
#define DEFAULT_SZ 3
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

struct peoinfo
{
	char name[Max_Name];
	char phone[Max_Phone];
	char sex[Max_Sex];
	char address[Max_Address];
	int age;
};

struct contact
{
	struct peoinfo* data;
	//注意这里一定要加指针标记，代表data是一个指针，指向peoinfo结构体
	//people information,结构体嵌套，人员信息

	int size;//记录当前个数
	int capacity;//记录通讯录最大容量

};

//初始化通讯录里面的信息
void Init_contact(struct contact* ps);
//加载文件中的内容到通讯录中
void Load_Contacter(struct contact* ps);
//添加联系人功能
void Add_Contacter(struct contact* ps);
//删除联系人的信息
void Del_Contacter(struct contact* ps);
//查找联系人的信息
void Find_Contacter(const struct contact* ps);
//修改联系人的信息
void Mod_Contacter(struct contact* ps);
//打印通讯录中的信息
void Show_Contacter(struct contact* ps);
//对通讯录中的联系人进行排序
void Sort_Contacter(struct contact* ps);
//清空通讯录中的信息
void Clear_Contacter(struct contact* ps);
//销毁通讯录
void Destory_Contact(struct contact* ps);
//保存通讯录信息
void Save_Contact(struct contact* ps);
//检查扩容功能
void CheckCapacity(struct contact* ps);
