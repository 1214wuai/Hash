
#ifndef __HASH_H__
#define __HASH_H__
#include<stdio.h>
#include<assert.h>
#include<malloc.h>
typedef int KeyType;
typedef int ValueType;

typedef enum Status
{
	EMPTY,
	EXITS,
	DELETE,
}Status;

typedef struct HashNode
{
	KeyType _key;
	ValueType _value;
	Status _status;
}HashNode;

typedef struct HashTable
{
	HashNode* _tables;
	size_t _size;
	size_t _N;
}HashTable;

void HashTableInit(HashTable* ht,size_t N);
int HashTableInsert(HashTable* ht, KeyType key, ValueType value);
void HashPrint(HashTable* ht);
HashNode* HashTableFind(HashTable* ht, KeyType key);
int HashTableRemove(HashTable* ht, KeyType key);
int HashTableDestory(HashTable* ht);
///////////////////////////////////////////////////////
typedef int HTBKeyType;
typedef int HTBValueType;

typedef struct HTBashNode
{
	struct HashNode* _next;
	HTBKeyType _key;
	HTBValueType _value;
}HTBashNode;

typedef struct HashTableBucket
{
	HTBashNode** _tables;
	size_t _size;
	size_t _len;
}HTB;

void HTBInit(HTB* htb, size_t len);
void HTBDestory(HTB* htb);
void HTBPrint(HTB* htb);
int HTBInsert(HTB* htb, HTBKeyType key, HTBValueType value);
int HTBRemove(HTB* htb, HTBKeyType key);
HashNode* HTBFind(HTB* htb, HTBKeyType key);

int HTBSize(HTB* htb);
int HTBEmpty(HTB* htb);

#endif //__HASH_H__