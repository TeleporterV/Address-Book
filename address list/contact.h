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
	//ע������һ��Ҫ��ָ���ǣ�����data��һ��ָ�룬ָ��peoinfo�ṹ��
	//people information,�ṹ��Ƕ�ף���Ա��Ϣ

	int size;//��¼��ǰ����
	int capacity;//��¼ͨѶ¼�������

};

//��ʼ��ͨѶ¼�������Ϣ
void Init_contact(struct contact* ps);
//�����ļ��е����ݵ�ͨѶ¼��
void Load_Contacter(struct contact* ps);
//�����ϵ�˹���
void Add_Contacter(struct contact* ps);
//ɾ����ϵ�˵���Ϣ
void Del_Contacter(struct contact* ps);
//������ϵ�˵���Ϣ
void Find_Contacter(const struct contact* ps);
//�޸���ϵ�˵���Ϣ
void Mod_Contacter(struct contact* ps);
//��ӡͨѶ¼�е���Ϣ
void Show_Contacter(struct contact* ps);
//��ͨѶ¼�е���ϵ�˽�������
void Sort_Contacter(struct contact* ps);
//���ͨѶ¼�е���Ϣ
void Clear_Contacter(struct contact* ps);
//����ͨѶ¼
void Destory_Contact(struct contact* ps);
//����ͨѶ¼��Ϣ
void Save_Contact(struct contact* ps);
//������ݹ���
void CheckCapacity(struct contact* ps);
