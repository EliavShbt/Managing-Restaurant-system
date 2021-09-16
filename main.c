#include "header.h"

void main() {
	int size_of_Tables, i, choise, Table_num, Quantity;
	PTables arr=NULL;
	PTableNode temp;
	Manot ManotHead;
	FILE* instruc,*manot, *out;
	char ProductName[51];
	ManotHead.head = NULL;
	instruc = fopen("Instructions.txt", "r");
	if (instruc == NULL)
		exit(1);
	manot = fopen("Manot.txt", "r");
	if (manot == NULL)
		exit(1);
	out = fopen("output.txt", "w");
	if (out == NULL)
		exit(1);
	fscanf(instruc, "%d", &size_of_Tables);
	if (size_of_Tables > 0) {
		arr = (PTables)malloc(size_of_Tables * sizeof(Tables));
		if (arr == NULL)
			fprintf(out, "Allocation to Tables Arr");
		for (i = 0; i < size_of_Tables; i++) { //Initialize Tables arr - struct manger
			arr[i].head = NULL;
			arr[i].bill = 0;
		}
	}
	fscanf(instruc, "%d", &choise); //getting '1' digit to call CreateProducts function
	if (CreateProducts(&ManotHead, manot, out) == 0) {
		fprintf(out, "Couldn't create manot list");
		free(arr);
	}
	else {
		fprintf(out, "The kitchen was created");
		while (fscanf(instruc, "%d", &choise) != -1) {
			switch (choise)
			{
			case 2:
				fscanf(instruc, "%s", ProductName);
				fscanf(instruc, "%d", &Quantity);
				AddItems(ProductName, Quantity, ManotHead, out);
				break;
			case 3:
				fscanf(instruc, "%d", &Table_num);
				fscanf(instruc, "%s", ProductName);
				fscanf(instruc, "%d", &Quantity);
				OrderItem(arr, Table_num, ProductName, Quantity, ManotHead, out);
				break;
			case 4:
				fscanf(instruc, "%d", &Table_num);
				fscanf(instruc, "%s", ProductName);
				fscanf(instruc, "%d", &Quantity);
				RemoveItem(arr, Table_num, ProductName, Quantity, ManotHead, out);
				break;
			case 5:
				fscanf(instruc, "%d", &Table_num);
				RemoveTable(&arr[Table_num - 1], Table_num, out);
				break;
			default:
				fprintf(out, "\nWrong number of function to excute");
				break;
			}
		}
	}

	free_Manot(ManotHead.head);

	for (i = 0; i < size_of_Tables; i++) { //free all tables
		temp = arr[i].head;
		while (arr[i].head != NULL) {
			arr[i].head = arr[i].head->next;
			free(temp->mana_name);
			free(temp);
			temp = arr[i].head;
		}
	}
	free(arr);
	fclose(instruc);
	fclose(manot);
	fclose(out);
}