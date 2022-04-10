#include "pch.h"
#include "list.h"

List* initList(void)
{
	List* pRoot = (List*)malloc(sizeof(*pRoot));

	return pRoot;
}

void deinitList(List* pRoot)
{
	free(pRoot->pPlateNum);
    	free(pRoot);
}

// Funkcja dodajaca samochod do listy wjezdzajacy na parking
void addCar(List* pRoot, char* plateNum)
{
	List* lastElem = pRoot;
	
	if (pRoot->pNext != nullptr)
	{
		while (lastElem->pNext != nullptr)
		{
			lastElem = lastElem->pNext;
		}
	} 

	List* addElem = new List;
	lastElem->pNext = addElem;
	addElem->pPlateNum = plateNum;
	addElem->entryTime = time(NULL);
	addElem->pNext = nullptr;
	std::cout << "New element of list was added to end of the list!" << std::endl;
}

void removeCar(List* pRoot, char* plateNum)
{
	List* temp = pRoot;
	List* previousTemp = {};
	List* nextTemp = {};

	bool sPlateNum = false; 

	while (nullptr != temp->pNext)
	{
		if (plateNum == temp->pPlateNum) {
			sPlateNum = true;
			nextTemp = temp->pNext;
				break;
		}

		previousTemp = temp;
		temp = temp->pNext;
	}

	if (sPlateNum) {
		if (nullptr == nextTemp) {
			previousTemp->pNext = nullptr;
			delete temp;
			std::cout << "The element has been removed!" << std::endl;
		}

		previousTemp->pNext = temp->pNext;
		delete temp;
		std::cout << "The element has been removed!" << std::endl;

	}
	else {
		std::cout << "Car wasn't found!!" << std::endl;
	}


}

void printAll(List* pRoot) {

}

int numberOfElements(List* pRoot) //Function showing number of elements.
{
	if(pRoot == NULL) return 1; // Indicates error
	return 0;
}
