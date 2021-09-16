#include "header.h"
/*The function gets pointer to head of Manot list and frees of the string allocated for the name of every Mana and the allocated memory for the each Mana itself*/
void free_Manot(PMana list_head) {
	PMana temp;
	temp = list_head;
	while (list_head != NULL) {
		list_head = list_head->next;
		free(temp->ProductName);
		free(temp);
		temp = list_head;
	}
}

/*The function gets pointer to list of Manot and 2 pointers to file.
  First pointer to read data from file and the second for writing in other file*/
int CreateProducts(PManot list, FILE* in, FILE* out) {
	PMana mana;
	char name[51];
	int Price, Quantity, success = 0;
	while ((fscanf(in, "%s", name)) != -1) {
		fscanf(in, "%d %d", &Quantity, &Price);
		if ((Price < 0) || (Quantity < 0)) {
			fprintf(out, "\nprice/quantity of manot is negative, can't allocate memory to this mana, moving foward");
		}
		else {
			mana = (PMana)malloc(1 * sizeof(Mana));
			if (mana == NULL) {
				fprintf(out, "\nNode Allocation error");
				success = 0;
				free_Manot(list->head);
			}
			else {
				mana->ProductName = (char*)malloc((strlen(name) + 1) * sizeof(char));
				if (mana->ProductName != NULL) {
					strcpy(mana->ProductName, name);
					mana->Price = Price;
					mana->Quantity = Quantity;
					mana->next = list->head;
					list->head = mana;
					success = 1;
				}
				else {
					fprintf(out, "\nName Allocation error");
					free(mana);
					success = 0;
					free_Manot(list->head);
				}
			}
		}
	}
	return success;
}

/*The function adds requested value to the quantity of the available Manot in stock.
  It gets string with the name of the Mana we want to add stock to it, the quantity we want to add,
  pointer to the head of Manot list and pointer to file we want to print the output in*/
void AddItems(char* ProductName, int Quantity, Manot list, FILE* out ) {
	PMana temp;
	int success = 0;
	temp = list.head;
	while (temp != NULL && success == 0) {
		if (strcmp(temp->ProductName, ProductName) == 0)
			if (Quantity > 0) {
				temp->Quantity += Quantity;
				success = 1;
			}
			else
				fprintf(out, "\nQuantity value isn't valid");
		else
			temp = temp->next;
	}
	if (success == 0) fprintf(out, "\nThere is not %s mana in the menu", ProductName);
	else fprintf(out, "\n%d %s were added to the kitchen", Quantity, ProductName);
}

/*The function lets the user to order Manot to a specific table.
  The function gets tables array, 'TableNumber' as the table we want to update order for, 'ProductName' for the name of the Mana the table want to order,
  'Quantity' to update the bill of the table, also to decreament this quantity fromt the available Manot inside manot list, 
  and pointer to file we want to print the output in*/
void OrderItem(Tables arr[], int TableNumber, char* ProductName, int Quantity, Manot manot, FILE* out) {
	PMana temp;
	int success = 0;
	PTableNode Tnode;
	temp = manot.head;
	while (temp != NULL && success == 0) {
		if (strcmp(temp->ProductName, ProductName) == 0)
			if (Quantity > 0 && Quantity <= temp->Quantity) {
				if (arr[TableNumber - 1].head == NULL) {
					arr[TableNumber - 1].head = (PTableNode)malloc(1*sizeof(TableNode));
					if (arr[TableNumber - 1].head == NULL)
						fprintf(out, "\nTableNODE allocation error");
					else {
						arr[TableNumber - 1].head->mana_name = (char*)malloc((strlen(ProductName) + 1) * sizeof(char));
						if (arr[TableNumber - 1].head->mana_name == NULL) {
							fprintf(out, "\nTable->mana_name allocation error");
							free(arr[TableNumber - 1].head);
						}
						else {
							strcpy(arr[TableNumber - 1].head->mana_name, ProductName);
							temp->Quantity -= Quantity;
							arr[TableNumber - 1].head->ordered = Quantity;
							success = 1;
							arr[TableNumber - 1].bill += ((temp->Price)*Quantity);
							arr[TableNumber - 1].head->next = NULL;
							fprintf(out, "\n%d %s were added to the table number %d!", Quantity, ProductName, TableNumber);
						}
					}
				}
				else {
					Tnode = arr[TableNumber - 1].head;
					while ((success == 0) && Tnode->next != NULL) {
						if (strcmp(Tnode->mana_name, ProductName) == 0) {
							temp->Quantity -= Quantity;
							Tnode->ordered += Quantity;
							success = 1;
							arr[TableNumber - 1].bill += temp->Price;
							fprintf(out, "\n%d %s were added to the table number %d!", Quantity, ProductName, TableNumber);
						}
					Tnode = Tnode->next;
					}
					if (success == 0) { //If Tnode is pointing on the last node
						if (strcmp(Tnode->mana_name, ProductName) == 0) {
							temp->Quantity -= Quantity;
							Tnode->ordered += Quantity;
							success = 1;
							arr[TableNumber - 1].bill += ((temp->Price) * Quantity);
							fprintf(out, "\n%d %s were added to the table number %d!", Quantity, ProductName, TableNumber);
						}
						else {
							Tnode->mana_name = (char*)malloc((strlen(ProductName) + 1) * sizeof(char));
							if (Tnode->mana_name == NULL)
								fprintf(out, "\nTable->mana_name allocation error");
							else {
								strcpy(Tnode->mana_name, ProductName);
								temp->Quantity -= Quantity;
								Tnode->ordered = Quantity;
								success = 1;
								arr[TableNumber - 1].bill += ((temp->Price) * Quantity);
								Tnode->next = NULL;
								fprintf(out, "\n%d %s were added to the table number %d!", Quantity, ProductName, TableNumber);
							}
						}
					}
				}
			}
			else {
				fprintf(out, "\nQuantity number is not valid (bigger than available in stock/negative)");
				success = 1; //in order to end the loop because we can't procceed
			}
		else
			temp = temp->next;
	}
	if (success == 0) //in case that there is no such name of mana inside the list of manot
		fprintf(out, "\nWe don’t have %s, sorry!", ProductName);
}

void RemoveItem(Tables arr[], int TableNumber, char* ProductName, int Quantity, Manot manot, FILE* out) {
	PMana check = manot.head;
	PTableNode table_mana_check = arr[TableNumber - 1].head;
	int success = 0;
	if ((arr[TableNumber - 1].bill) > 0) {
		if (check != NULL) {
			if (strcmp(check->ProductName, ProductName) == 0) success = 1;
			while (check != NULL && success == 0) {
				check = check->next;
				if (strcmp(check->ProductName, ProductName) == 0) success = 1;
			}
			if (success == 1) { //if there is such mana inside menu of Manot
				success = 0;
				if (Quantity > 0) {
					if (strcmp(table_mana_check->mana_name, ProductName) == 0)
						success = 1;
					while (table_mana_check != NULL && success == 0) {
						table_mana_check = table_mana_check->next;
						if (strcmp(table_mana_check->mana_name, ProductName) == 0)
							success = 1;
					}
					if (success == 1) { //if the table ordered this mana we want to check if the quantity value is valid
						if (Quantity <= table_mana_check->ordered) {
							table_mana_check->ordered -= Quantity;
							arr[TableNumber - 1].bill -= ((check->Price) * (Quantity));
							fprintf(out, "\n%d %s was returned to the kitchen from table number %d", Quantity, ProductName, TableNumber);
						}
						else
							fprintf(out, "\nThe requested amount of manot to return is bigger than what table ordered");
					}
					else fprintf(out, "\nTable number %d didn't order %s", TableNumber, ProductName);
				}
				else //if quantity is negative or equal to zero
					fprintf(out, "\nQuantity value is negative or equal to zero");

			}
			else fprintf(out, "\nThere isn't %s in the MENU", ProductName);
		}
		else fprintf(out, "\nThere is no manot inside the menu");
	}
	else
		fprintf(out, "\nTable number %d has no manot to return", TableNumber);
}

void RemoveTable(PTables table, int TableNumber, FILE* out) {
	PTableNode temp = table->head;
	double tip;
	if (table->head != NULL) {
		if (table->bill != 0) {
			fprintf(out, "\n");
			while (table->head != NULL) {
				fprintf(out, "%d %s. ", temp->ordered, temp->mana_name);
				table->head = table->head->next;
				free(temp->mana_name);
				free(temp);
				temp = table->head;
			}
			tip = table->bill * 0.1;
			fprintf(out, "%d nis+%.lf nis for tips, please!", table->bill, tip);
		}
		else {
			while (table->head != NULL) {
				table->head = table->head->next;
				free(temp->mana_name);
				free(temp);
				temp = table->head;
			}
		}
	}
	else
		fprintf(out, "\nThe table number %d is not ordered yet", TableNumber);
}