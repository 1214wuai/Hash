#include"Hash.h"

test()
{
	HashTable hash;
	HashTableInit(&hash,10);
	/*HashTableInsert(&hash, 5, 0);
	HashTableInsert(&hash, 15, 0);
	HashTableInsert(&hash, 24, 0);

	HashTableInsert(&hash, 6, 0);
	HashTableInsert(&hash, 8, 0);*/
	for (int i = 0; i < 20; i++)
	{
		HashTableInsert(&hash, i, 0);
	}
	//HashTableRemove(&hash, 15);
	HashNode* H1 = HashTableFind(&hash, 15);
	if (H1 != NULL)
		printf("%d \n", H1->_key);
	else
		printf("ц╩спур╣╫\n");
	HashPrint(&hash);
	HashTableDestory(&hash);
}
test2()
{
	HTB htb;
	HTBInit(&htb, 10);
	/*HTBInsert(&htb, 1, 0);
	HTBInsert(&htb, 1, 0);
	HTBInsert(&htb, 3, 0);
	HTBInsert(&htb, 4, 0);
	HTBInsert(&htb, 5, 0);

	HTBInsert(&htb, 2, 0);*/
	for (int i = 0; i < 20; i++)
	{
		HTBInsert(&htb, i, 0);
	}
	HTBRemove(&htb, 2);
	HTBRemove(&htb, 1);
	HTBPrint(&htb);
	HTBashNode* F = HTBFind(&htb, 5);
	if(F!=NULL)
		printf("Find:%d\n", F->_key);
	size_t sz = HTBSize(&htb);
	printf("sz:%d\n", sz);
	//HTBDestory(&htb);

	int empty = HTBEmpty(&htb);

	if (empty == 0)
		printf("Hash is Empty\n");
	else
		printf("Hash isn't Empty\n");
	HTBDestory(&htb);
}
int main()
{

	//test();
	test2();
	system("pause");
	return 0;
}