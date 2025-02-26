#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include"contact.h"

/*
enum Option
{
	EXIT,//0
	ADD,//1
	DEL,//2
	SEARCH,//3
	MODIFY,//4
	SHOW,//5
	CLEAR,//6
	SORT,//7
	SAVE
};
*/


void menu()
{
	printf("************************************\n");
	printf("****  1.add         2.del       ****\n");
	printf("****  3.search      4.modify    ****\n");
	printf("****  5.show        6.clear     ****\n");
	printf("****  7.sort        8.save      ****\n");
	printf("****  9.destroy     0.exit      ****\n");
	printf("************************************\n");
}








int main()
{
	struct contact con;//结构体，里面包含：data指针，size,capacity
	
	Init_contact(&con);//初始化con这个结构体

	int input = 0;
	int size = 0;;//记录当前人数
	do
	{
		menu();//菜单界面函数

		printf("请输入->");
		//int result = 
		scanf("%d", &input);
		/*
		// 如果输入的不是有效数字，提示错误并清空缓冲区
		if (result != 1 || input < 0 || input > 9) {
			printf("选择错误，请重新输入\n");
			while (getchar() != '\n'); // 清空输入缓冲区
			continue;
		}
		*/
		switch (input)
		{
		case 1:
			//add,添加联系人
			Add_Contacter(&con);
			break;
		case 2:
			//del,删除联系人
			Del_Contacter(&con);
			break;
		case 3:
			//search,查找联系人
			Find_Contacter(&con);
			break;
		case 4:
			//modify,修改联系人
			Mod_Contacter(&con);
			break;
		case 5:
			//show,打印
			Show_Contacter(&con);
			break;
		case 6:
			//clear,清空联系人
			Clear_Contacter(&con);
			break;
		case 7:
			//sort,排序
			Sort_Contacter(&con);
			break;
		case 8:
			//save,保存通讯录
			Save_Contact(&con);
			break;
		case 9:
			//销毁通讯录
			Destory_Contact(&con);
			printf("通讯录已销毁\n");
			exit(0);
			break;
		case 0:
			//exit,退出通讯录
			Save_Contact(&con);
			printf("退出通讯录");
			break;
		default:
			printf("选择错误，请重新输入");
		}
	} while (input);
	return 0;

}