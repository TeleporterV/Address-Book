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
	struct contact con;//�ṹ�壬���������dataָ�룬size,capacity
	
	Init_contact(&con);//��ʼ��con����ṹ��

	int input = 0;
	int size = 0;;//��¼��ǰ����
	do
	{
		menu();//�˵����溯��

		printf("������->");
		//int result = 
		scanf("%d", &input);
		/*
		// �������Ĳ�����Ч���֣���ʾ������ջ�����
		if (result != 1 || input < 0 || input > 9) {
			printf("ѡ���������������\n");
			while (getchar() != '\n'); // ������뻺����
			continue;
		}
		*/
		switch (input)
		{
		case 1:
			//add,�����ϵ��
			Add_Contacter(&con);
			break;
		case 2:
			//del,ɾ����ϵ��
			Del_Contacter(&con);
			break;
		case 3:
			//search,������ϵ��
			Find_Contacter(&con);
			break;
		case 4:
			//modify,�޸���ϵ��
			Mod_Contacter(&con);
			break;
		case 5:
			//show,��ӡ
			Show_Contacter(&con);
			break;
		case 6:
			//clear,�����ϵ��
			Clear_Contacter(&con);
			break;
		case 7:
			//sort,����
			Sort_Contacter(&con);
			break;
		case 8:
			//save,����ͨѶ¼
			Save_Contact(&con);
			break;
		case 9:
			//����ͨѶ¼
			Destory_Contact(&con);
			printf("ͨѶ¼������\n");
			exit(0);
			break;
		case 0:
			//exit,�˳�ͨѶ¼
			Save_Contact(&con);
			printf("�˳�ͨѶ¼");
			break;
		default:
			printf("ѡ���������������");
		}
	} while (input);
	return 0;

}