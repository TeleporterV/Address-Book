#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include"contact.h"

static int Find_ByName(const struct contact* ps, char name[Max_Name]);

//�����ļ��е����ݵ�ͨѶ¼��
void Load_Contacter(struct contact* ps)
{
	FILE*  pfRead=fopen("contact.dat", "rb");
	//��contact.dat�ļ�������ֻ��������rb������������ļ��������ı��ļ�
	//�ڴ��ļ���ͬʱ�����᷵��һ��FILE*��ָ�����ָ����ļ���Ҳ�൱�ڽ�����ָ����ļ��Ĺ�ϵ��

	if (pfRead == NULL)//�ж��Ƿ�ɹ���
	{
		printf("Load_Contact:%s", strerror(errno));
		//��ӡ���һ��ϵͳ���û��׼�⺯��ʧ�ܵĴ�����Ϣ,��Ҫ����ͷ�ļ�<errno.h>
		return ;
	}

	//��ȡ�ļ��ŵ�ͨѶ¼��
	struct peoinfo tmp = {0};
	//����һ���ṹ����Ա��Ϣ���͵ı���������Ҫ�Ѷ��������ݷŽ�ȥ������ʱ��¼

	while (fread(&tmp, sizeof(tmp), 1, pfRead))
	//fread(�����ݵ�λ�ã�Ԫ�صĴ�С����ȡ����Ŀ��ָ��ָ����ļ��ṹ���ļ��ṹ��ʲô��
	//fread�Ƕ�ȡ�ļ��Ĳ����������ɹ��ͷ���1��û�ɹ��ͷ���0������whilel��������ж�ѭ��
	//ѭ������ fread��ÿ�ζ�ȡһ����¼��struct peoinfo�������ļ�����ʱ��fread ���� 0��ѭ����ֹ
	{
		CheckCapacity(ps);// ���ͨѶ¼�����Ƿ��㹻�������������в���������������������
		ps->data[ps->size] = tmp;//����ʱ��¼����ͨѶ¼����
		ps->size++;// ����ͨѶ¼��ǰ��¼��
		printf("��ȡ�ɹ�\n");
	}

	//�ر��ļ�
	fclose(pfRead);
	pfRead = NULL;//���ļ�ָ���ÿգ����������ѹرյ�ָ��
}




//��ʼ��ͨѶ¼�������Ϣ
void Init_contact(struct contact* ps)
{
	//�����ڴ�ռ䣬�ṹ��peoinfo����ָ��������
	ps->data = (struct peoinfo*) malloc(sizeof(struct peoinfo)*3);//ΪʲôҪ*3������ΪʲôҪ��ָ��

	if (ps->data == NULL)//�ж��Ƿ������ڴ�ռ�ɹ�
	{
		return;
	}

	ps->size = 0;//ͨѶ¼���ֻ��0��ֵ
	ps->capacity = DEFAULT_SZ;
	
	//���ļ����Ѿ���ŵ���Ϣ���ص�ͨѶ¼��
	Load_Contacter(ps);
}


//������ݹ���
void CheckCapacity(struct contact* ps)//ע�⴫���ǵ�ַ��Ҫ��*
{
	if (ps->size == ps->capacity)//˵����ǰ���������������ͬ��
	{
		//����
		struct peoinfo* ptr = realloc(ps->data,(ps->capacity+2)*sizeof(struct peoinfo));
		//realloc�ı�������ڴ�ռ��С
		//realloc(�ڴ��ַ���޸ĺ�Ĵ�С��

		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			printf("���ݳɹ�\n");
		}
		else
		{
			printf("����ʧ��\n");
		}
	}
}


//�����ϵ�˹���
void Add_Contacter(struct contact* ps)
{
	// ��⵱ǰͨѶ¼������
	//1��������ˣ������ӿռ�
	//2�����������ɶ�¶�����
	CheckCapacity(ps);

	//�����Ϣ
	printf("����������\n");
	scanf("%s", &ps->data[ps->size].name);
	printf("����������\n");
	scanf("%d", &ps->data[ps->size].age);
	printf("�������Ա�\n");
	scanf("%s", &ps->data[ps->size].sex);
	printf("������绰\n");
	scanf("%s", &ps->data[ps->size].phone);
	printf("�������ַ\n");
	scanf("%s", &ps->data[ps->size].address);

	ps->size++;
	printf("��ӳɹ�\n");
}


//ɾ��ͨѶ¼�е���Ϣ
void Del_Contacter(struct contact* ps)
{
	char name[Max_Name];//��һ�����飬����Ҫɾ���˵�����
	printf("��������Ҫɾ�����˵�����\n");
	scanf("%s", name);

	//����Ҫɾ���������ڵ�λ��
	int pos = Find_byName(ps, name);//�º������������ֽ��в��ң��ҵ��˷�����������Ԫ�ص��±꣬û�ҵ��ͷ���-1

	if (pos == -1)//û���ҵ�
	{
		printf("��Ҫɾ�����˲�����\n");
	}
	else//�鵽�ˣ�����ɾ��
	{
		// �����Ψһ��ϵ��
		if (ps->size == 1) {
			ps->size = 0; //���ͨѶ¼
		}
		else {
			for (int j = pos; j < ps->size - 1; j++)//��pos��ʼ��ֱ����ɾ��ǰ��һ����ʱ���ֹͣ����Ϊ��Ҫɾ���Ǹ��Ѿ���ǰ��ĸ���ס�ˣ�size������һ����size-1��������ˣ�
			{
				ps->data[j] = ps->data[j + 1]; //�������ϵ�˺������Ϣ�����ǰ���и���
			}
			ps->size--;
		}
		printf("ɾ���ɹ�\n");
	}
}


//����ͨѶ¼�е���Ϣ
void Find_Contacter(const struct contact* ps)
{
	char name[Max_Name];//max_name��������˵ĳ��ȣ�ͷ�ļ�����
	printf("��������Ҫ���ҵ�����\n");
	scanf("%s", name);
	int pos = Find_byName(ps, name);
	if (pos == -1)
	{
		printf("����ҵ��˲�����\n");
	}
	else
	{
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\n","����", "����", "�Ա�", "�绰", "��ַ");
		printf("%-20s\t%-4d\t%-5s\t%-12s\t%-20s\n",ps->data[pos].name,
			ps->data[pos].age,
			ps->data[pos].sex,
			ps->data[pos].phone,
			ps->data[pos].address);
	}
}


//���Һ���ʵ��
static int Find_byName(const struct contact* ps,char name[Max_Name])
{
	for (int i = 0; i < ps->size; i++)//�����Ѿ��е�����
	{
		if (0 == strcmp(ps->data[i].name, name))//��name������������ֺ�ͨѶ¼�����е��������ֽ��бȽϣ����Ƿ�����ͬ��
		//strcmp�ǱȽ����ַ����Ĵ�С��ASCII�룩��strcmp(char* a,char* b)
		//����ֵ��<0,��a<b, a��bǰ��; 0, a��b��ȫ��ͬ; >0��a����b��a��b����
	    //����ֵ���Ϊǰ�������Ĵ�С�����˭С˭��ǰ��
		{
			return i;
		}
	}
	return -1;
}


//�޸�ͨѶ¼�е���Ϣ
void Mod_Contacter(struct contact* ps)
{
	char name[Max_Name];
	printf("��������Ҫ�޸ĵ���ϵ�˵�����\n");
	scanf("%s", name);
	int pos = Find_byName(ps, name);
	if (pos == -1)//�޸ĵ��˲�����
	{
		printf("Ҫ�޸ĵ��˲����ڣ�\n");
	}
	else
	{
		printf("����������:");
		scanf("%s", &ps->data[pos].name);
		printf("����������:");
		scanf("%d", &ps->data[pos].age);
		printf("�������Ա�:");
		scanf("%s", &ps->data[pos].sex);
		printf("������绰:");
		scanf("%s", &ps->data[pos].phone);
		printf("�������ַ:");
		scanf("%s", &ps->data[pos].address);
		printf("�޸ĳɹ���\n");
	}
}


//��ӡͨѶ¼�е���Ϣ
void Show_Contacter(struct contact* ps)
{
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}
	else
	{
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
		int i = 0;
		while (i < ps->size)
		{
			//��0��ʼ��size�������ж�����һ��
			printf("%-20s\t%-4d\t%-5s\t%-12s\t%-20s\n", ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].phone,
				ps->data[i].address);
			i++;
		}
	}
}


//��ͨѶ¼�е���Ϣ��������
//1.��������������
int Compar_ByName(const void* x,const void* y)
//�ȽϺ��� int compar(const void*a,const void*b)
//a,b��ָ������Ԫ�ص�ָ�룬������void*(���ڱȽϺ��������ǹ̶��ģ�������Ҫǿ��ת������Ҫ������
//����ֵ��<0,a x����yǰ�棻0,x��y˳�򲻱䣻>0,x����y����
//����strcmpʵ�֣�ԭ�����һ��
{
	return strcmp(((struct peoinfo*)x)->name, ((struct peoinfo*)y)->name);
}

//2.�������������
int Compar_ByAge(const void* x, const void* y)
{
	return ((struct peoinfo*)x)->age - ((struct peoinfo*)y)->age;
	//���ע��һ�£�age��int��Ҫ����ģ�����strcmp��Ϊ�����ַ������ȴ�С�����ų�����
}

//3.����ַ��������
int Compar_ByAddress(const void* x, const void* y)
{
	return strcmp(((struct peoinfo*)x)->address, ((struct peoinfo*)y)->address);
}


//������
void Sort_Contacter(struct contact* ps)
{
	printf("��������������ķ�ʽ\n");
	printf("1.����\n2.����\n3.��ַ\n");
	int input = 0;
	scanf("%d", &input);
	switch (input)
	{
	case 1:
		qsort(ps->data, ps->size, sizeof(ps->data[0]), Compar_ByName);
		//qsort(������ʼ��ַ��Ԫ�ظ�����ÿ��Ԫ�ش�С���ȽϺ�����
		printf("����ɹ�\n");
		break;
	case 2:
		qsort(ps->data, ps->size, sizeof(ps->data[0]), Compar_ByAge);
		printf("����ɹ�\n");
		break;
	case 3:
		qsort(ps->data, ps->size, sizeof(ps->data[0]), Compar_ByAddress);
		printf("����ɹ�\n");
		break;
	}
}





//���ͨѶ¼�е���Ϣ
void Clear_Contacter(struct contact* ps)
{
	memset(ps->data, 0, sizeof(ps->data));//memset����
	ps->size = 0;
	printf("��ճɹ���\n");
}



//����ͨѶ¼
void Destory_Contact(struct contact* ps)
{
	free(ps->data);//�ͷſռ�
	ps->data = NULL;//����ָ������
}



//����ͨѶ¼��Ϣ
void Save_Contact(struct contact* ps)
{
	FILE* pfWrite = fopen("contact.dat", "wb");//���ļ���ͬʱ��һ��ָ��ָ����ļ������ļ��͵�ַ��ϵ����

	if (pfWrite == NULL)//��δ�ɹ����ļ�
	{
		printf("Save_Contact::%s", strerror(errno));
		//��ӡ���һ��ϵͳ���û��׼�⺯��ʧ�ܵĴ�����Ϣ,��Ҫ����ͷ�ļ�<errno.h>
		return;
	}
	
	//��ͨѶ¼�е�����д���ļ��У�������
	for (int i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->data[i]), sizeof(struct peoinfo), 1, pfWrite);
		//fwrie(ָ��ָ��д������ݣ�д��Ĵ�С��λ�ֽڣ�д���������д���Ŀ������
	}
		printf("����ɹ�\n");
		//�ر��ļ�
		fclose(pfWrite);
		pfWrite = NULL;
	
}