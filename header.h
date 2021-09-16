#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef BBB
#define BBB

typedef struct Mana {
	char* ProductName;
	int Price;
	int Quantity;
	struct Mana* next;
}Mana, * PMana;

typedef struct Manot {
	PMana head;
}*PManot, Manot;

typedef struct TableNode {
	char* mana_name;
	int ordered;
	struct TableNode* next;
}TableNode, * PTableNode;

typedef struct Tables {
	TableNode* head;
	int bill;
}Tables, * PTables;

void free_Manot(PMana list_head);
int CreateProducts(PManot list, FILE* in, FILE* out);
void AddItems(char* ProductName, int Quantity, Manot list, FILE* out);
void OrderItem(Tables arr[], int TableNumber, char* ProductName, int Quantity, Manot manot, FILE* out);
void RemoveItem(Tables arr[], int TableNumber, char* ProductName, int Quantity, Manot manot, FILE* out);
void RemoveTable(PTables table, int TableNumber, FILE* out);
#endif