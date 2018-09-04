
#include"Hash.h"
int HashFunc(HashTable *ht, KeyType key)
{
	assert(ht);
	return key % ht->_N;
}
size_t GetNextPrimeNum(size_t cur)
{
	const int _PrimeSize = 28;
	static const unsigned long _PrimeList[28] =
	{
		53ul, 97ul, 193ul, 389ul, 769ul, 1543ul, 3079ul,
		6161ul, 12289ul, 24593ul, 49157ul, 98317ul, 196613ul,
		393241ul, 786433ul, 1572869ul, 3145739ul, 6291469ul, 12582917ul,
		25165843ul, 50331653ul, 100663319ul, 201326611ul, 402653189ul,
		805306457ul, 1610612741ul, 3221225473ul, 4294967291ul
	};
	for (size_t i = 0; i < _PrimeSize; ++i)
	{
		if (_PrimeList[i]>cur)
		{
			return _PrimeList[i];
		}
	}
	return _PrimeList[_PrimeSize - 1];
}

void HashPrint(HashTable* ht)
{
	assert(ht);
	for (int i = 0; i < ht->_N; i++)
	{
		printf("%d:%d:%d  £º %d\n", ht->_tables[i]._status, ht->_tables[i]._key, ht->_tables[i]._value, i);
	}
}

void HashTableInit(HashTable* ht,size_t N)
{
	assert(ht);
	ht->_N = N;
	ht->_size = 0;
	ht->_tables = (HashNode*)malloc(sizeof(HashNode)*ht->_N);
	for (int i = 0; i < ht->_N; i++)
	{
		ht->_tables[i]._status = EMPTY;
	}
}
int HashTableInsert(HashTable* ht, KeyType key, ValueType value)
{
	assert(ht);
	if (ht->_size*10/ht->_N>7)//À©ÈÝ
	{
		size_t newN = GetNextPrimeNum(ht->_N);
		HashTable tmp ;
		
		HashTableInit(&tmp, newN);


		for (int i = 0; i < ht->_N; i++)
		{
			if(ht->_tables[i]._status==EXITS)
				HashTableInsert(&tmp, ht->_tables[i]._key, ht->_tables[i]._value);
		}
		HashTableDestory(ht);
		ht->_N = newN;
		ht->_size = tmp._size;
		ht->_tables = tmp._tables;
		
		
	}
	int X = HashFunc(ht, key);
	while (1)
	{
		if (ht->_tables[X]._status == EMPTY || ht->_tables[X]._status == DELETE)
		{
			ht->_tables[X]._key = key;
			ht->_tables[X]._status = EXITS;
			ht->_tables[X]._value = value;
			ht->_size++;
			return 1;
		}
		X++;
		if (X = ht->_N - 1)
			X = 0;
	}
	/*else
	{
		int X = HashFunc(ht, key);
		
		while (1)
		{
			if (ht->_tables[X]._status == EMPTY || ht->_tables[X]._status == DELETE)
			{
				ht->_tables[X]._key = key;
				ht->_tables[X]._status = EXITS;
				ht->_tables[X]._value = value;
				ht->_size++;
				return 1;
			}
			X++;
			if (X = ht->_N - 1)
				X = 0;
		}
	}*/
}
HashNode* HashTableFind(HashTable* ht, KeyType key)
{
	assert(ht);
	
	int X = HashFunc(ht, key);
	//HashNode node = ht->_tables[X];

	while (X<ht->_N)
	{
		if(ht->_tables[X]._key == key)
		{ 
			if(ht->_tables[X]._status==EXITS)
				return &ht->_tables[X];
		}
		X++;
	}
	return NULL;
}
int HashTableRemove(HashTable* ht, KeyType key)
{
	assert(ht);
	int X = HashFunc(ht, key);
	HashNode node = ht->_tables[X];
	while (X<ht->_N)
	{
		if (ht->_tables[X]._value == key)
		{
			ht->_tables[X]._status = DELETE;
			ht->_size--;
			return 1;
		}
		X++;
	}


}
int HashTableDestory(HashTable* ht)
{
	assert(ht);
	free(ht->_tables);
	ht->_size = 0;
	ht->_N = 0;
}
/////////////////////////////////////////////////////////////////////
int HTBashFunc(HTB* htb, HTBKeyType key)
{
	return key % htb->_len;
}
HTBashNode* BuyHTBNode( HTBKeyType key, HTBValueType value)
{
	HTBashNode* h = (HTBashNode*)malloc(sizeof(HTBashNode));
	h->_key = key;
	h->_value = value;
	h->_next = NULL;
}
void HTBInit(HTB* htb, size_t len)
{
	assert(htb);
	htb->_len = len;
	htb->_size = 0;
	htb->_tables = (HTBashNode**)malloc(sizeof(HTBashNode*)*htb->_len);
	assert(htb->_tables);
	for (int i = 0; i < htb->_len; i++)
	{
		htb->_tables[i] = NULL;
	}
}
void HTBDestory(HTB* htb)
{
	assert(htb);
	for (int i = 0; i < htb->_len; i++)
	{
		HTBashNode* cur = htb->_tables[i];
		HTBashNode* prev = htb->_tables[i];

		while (cur)
		{
			prev->_next = cur->_next;
			free(cur);
			cur = NULL;
		}
	}
	free(htb->_tables);
	htb->_tables = NULL;
	htb->_len = 0;
	htb->_size = 0;
}

int HTBInsert(HTB* htb, HTBKeyType key, HTBValueType value)
{
	assert(htb);
	if (htb->_size * 10 / htb->_len > 7)//À©ÈÝ
	{
		size_t newlen = GetNextPrimeNum(htb->_len);
		HTB newhtb;
		HTBInit(&newhtb, newlen);
		//HTBashNode** NnewNode = (HTBashNode**)malloc(sizeof(HTBashNode*)*newlen);
		for (int i = 0; i < htb->_len; i++)
		{
			HTBashNode* cur = htb->_tables[i];
			if (cur != NULL)
			{
				while (cur)
				{
					HTBInsert(&newhtb, cur->_key, cur->_value);
					cur = cur->_next;
				}
			}
		}
		HTBDestory(htb);
		htb->_len = newlen;
		htb->_size = newhtb._size;
		htb->_tables = newhtb._tables;
	}
	int X = HTBashFunc(htb, key);
	HTBashNode* cur = htb->_tables[X];
	while (cur)
	{
		if (cur->_key == key)
		{
			cur->_value++;
			htb->_size++;
			return 1;
		}
		cur = cur->_next;
	}
	HTBashNode* newNode = BuyHTBNode(key, value);
	newNode->_next = htb->_tables[X];
	htb->_tables[X] = newNode;
	htb->_size++;
	return 1;
}
void HTBPrint(HTB* htb)
{
	assert(htb);
	int i = 0;
	for (i = 0; i < htb->_len; i++)
	{
		if (htb->_tables[i] != NULL)
		{
			HTBashNode* cur = htb->_tables[i];
			if (cur != NULL)
				printf("[%d]:", HTBashFunc(htb, cur->_key));
			while (cur)
			{
				printf("%d:%d-->",cur->_key,cur->_value);
				cur = cur->_next;
			}
			printf("NULL\n");
		}
	}

}
int HTBRemove(HTB* htb, HTBKeyType key)
{
	assert(htb);
	int X = HTBashFunc(htb, key);
	HTBashNode* cur = htb->_tables[X];
	HTBashNode* prev = htb->_tables[X];

	while (cur)
	{
		if (cur->_key == key)
		{
			if (cur->_value == 0)
			{
				if (cur == htb->_tables[X])
				{
					htb->_tables[X] = cur->_next;
					free(cur);
					cur = NULL;
				}
				else
				{
					prev->_next = cur->_next;
					free(cur);
					cur = NULL;
				}
				htb->_size--;
				return 1;
			}
			else
			{
				cur->_value--;
				htb->_size--;
				return 1;
			}
		}
		prev = cur;
		cur = cur->_next;
	}
	return -1;
}
HashNode* HTBFind(HTB* htb, HTBKeyType key)
{
	assert(htb);
	int X = HTBashFunc(htb, key);
	HTBashNode* cur = htb->_tables[X];
	while (cur)
	{
		if (cur->_key == key)
		{
			return cur;
		}
		cur = cur->_next;
	}
	return NULL;
}
int HTBSize(HTB* htb)
{
	assert(htb);
	return htb->_size;
}
int HTBEmpty(HTB* htb)
{
	if (htb->_size == 0)
		return 0;
	else
		return 1;
}
