#include "List.h"
//#include "operations.h"
#include <fstream>
#include <iomanip>


int main()
{
	cout << "\t\t*******Welcome to students executive system!*******" << endl << endl << endl
		<< setfill('-') << setw(80) << "";
	cout << "Operation conduction: " << endl
		<< "1 ->  Generate data." << endl
		<< "2 ->  Sort data." << endl
		<< "3 ->  Search data." << endl
		<< "4 ->  Add data." << endl
		<< "5 ->  Erase data." << endl
		<< "6 ->  Modify data." << endl
		<< "7 ->  Print data." << endl
		<< "0 ->  Exit." << endl
		<< setfill('-') << setw(80) << "" << endl;
	
	int order;
	Student get;//when search occurs, the target will assign to this variable
	List data;

	//operations begin
	while(true)
	{
		cout << "Please enter the order: ";
		cin >> order;
		cout << endl << setfill('-') << setw(80) << "" << endl;
		if(order == 1)
		{
			ofstream file("e:\\StudentDataBase.txt", ios::out);
			file << "ID\t\t" << "NAME\t" << "\tGENDER" << endl; 
			int dataNum;//the number of students you want to generate
			cout << "Please enter the number of students you want to generate( num < 10000): ";
			cin >> dataNum;
			data.~List();/*struct the dataList, or it will add new datas to the remain dataset, 
							every time when generate a new set of data, you will get a brand new dataset*/
			
			srand(clock());//seed
			clock_t beg = clock();
			for(int i = 0; i < dataNum; )
			{
				Student stu; stu.randomG();
				if(data.unique(stu.getId()))//if the new object is not unique, it won`t be pushed into the list
				{
					file << stu.getId() << "\t" << stu.getName() << "\t\t" << stu.getGender() <<endl;
					data.append(stu);
					i++;
				}
			}
			clock_t end = clock();
			cout << "Data generated!" << endl
				<< "This operation takes " << end - beg  << "ms!" << endl
				<< setfill('-') << setw(80) << "" << endl;
			//cout << data.size() << endl;
		}
		else if(order == 2)
		{
			cout << "\t\t*******Please choose the methods of sort!*******" << endl
				<< "1 ->  insert sort" << endl
				<< "2 ->  bubble sort" << endl
				<< "3 ->  select sort" << endl
				<< "4 ->  merge sort" << endl
				<< "5 ->  quick sort" << endl
				<< "6 ->  shell sort" << endl
				<< "7 ->  heap sort" << endl
				<< endl << setfill('-') << setw(80) << "" << endl;
			cout << "Please enter the label of the method: ";
			int label;//choose the method of sort
			cin >> label;
			
			clock_t beg = clock();
			switch (label)
			{
			case 1: 
				{
					data.insert_sort(); 
					clock_t end = clock();
					cout << "insert sort used " << end - beg << " ms!" << endl << endl;
					break;
				}
			case 2: 
				{
					data.bubble_sort(); 
					clock_t end = clock();
					cout << "bubble sort used " << end - beg << " ms!" << endl << endl;
					break;
				}
			case 3: 
				{
					data.select_sort(); 
					clock_t end = clock();
					cout << "select sort used " << end - beg << " ms!" << endl << endl;
					break;
				}
			case 4: 
				{
					data.merge_sort(data.getList(), 0, data.size() - 1); 
					clock_t end = clock();
					cout << "merge sort used " << end - beg << " ms!" << endl << endl;
					break;
				}
			case 5: 
				{
					data.quick_sort(0, data.size() - 1); 
					clock_t end = clock();
					cout << "quick sort used " << end - beg << " ms!" << endl << endl;
					break;
				}
			case 6: 
				{
					data.shell_sort(); 
					clock_t end = clock();
					cout << "shell sort used " << end - beg << " ms!" << endl << endl;
					break;
				}
			case 7:
				{	
					data.heap_sort();
					clock_t end = clock();
					cout << "heap sort used " << end - beg << " ms!" << endl << endl;
					break;
				}
			default: 
				{
					data.quick_sort(0, data.size() - 1);
					clock_t end = clock();
					cout << "quick sort used " << end - beg << " ms!" << endl << endl;
					break;
				}
			}
			cout << "Data sucessfully sorted!" << endl;
			cout << "Do you want to cover the disorderly-sorted dataset?(yes/no):";
			string s;
			cin >> s;
			if(s == "yes")
			{
				ofstream file("e:\\StudentDataBase.txt", ios::out);
				file << data;
				cout << "The data orderly-sorted data has been saved!" << endl
					<< setfill('-') << setw(80) << "" << endl;
			}
			else 
				cout << endl << setfill('-') << setw(80) << "" << endl;
			
		}
		else if(order == 3)
		{
			if(data.sorted())//if the data are not sorted, binary search won`t be able to be luanched
			{
				cout << "\t\t*******Please choose the methods of search!*******" << endl << endl;
				cout << "1 ->  forgetful interactive version" << endl
					<< "2 ->  recognizabel interactive version" << endl
					<< "3 ->  forgetful recursive version" << endl
					<< "4 ->  recognizable recursive version" << endl
					<< setfill('-') << setw(80) << "" << endl;
				cout << "Please enter the label of the version: ";
				int version;
				cin >> version;
				cout << "Please enter student ID you want to search: ";
				int id;//key of the student you want to get
				cin >> id;
				if(version == 1)
				{
					clock_t beg = clock(), end;
					if(data.binarySearch1(id, get))
						cout << "Sucessful search!" << endl;
					else
						cout << "Failure search!" << endl;
					
					end = clock();
					cout << "This operation takes " << end - beg << " ms!" << endl
						<< setfill('-') << setw(80) << "" << endl;
				}
				else if(version == 2)
				{
					clock_t beg = clock(), end;
					if(data.binarySearch2(id, get))
						cout << "Sucessful search!" << endl;
					else
						cout << "Failure search!" << endl;
					end = clock();
					cout << "This operation takes " << end - beg << " ms!" << endl
						<< setfill('-') << setw(80) << "" << endl;
				}
				else if(version == 3)
				{
					clock_t beg = clock(), end;
					if(data.binarySearch3(id, get, 0, data.size() - 1))
						cout << "Sucessful search!" << endl;
					else
						cout << "Failure search!" << endl;
					end = clock();
					cout << "This operation takes " << end - beg << " ms!" << endl
						<< setfill('-') << setw(80) << "" << endl;
				}
				else if(version == 4)
				{
					clock_t beg = clock(), end;
					if(data.binarySearch4(id, get, 0, data.size() - 1))
						cout << "Sucessful search!" << endl;
					else
						cout << "Failure search!" << endl;
					end = clock();
					cout << "This operation takes " << end - beg << " ms!" << endl
						<< setfill('-') << setw(80) << "" << endl;
				}
				else
					cout << "Error detected --------- error input!" << endl
						<< setfill('-') << setw(80) << "" << endl;
			}
			else//give a tip
			{
				cout << "Error detected --------- data base is invalidly sorted!" << endl
					<< setfill('-') << setw(80) << "" << endl;
			}
		}
		else if(order == 4)
		{
			if(data.sorted())
			{
				int num;
				cout << "Please enter the number of student you want to add to the data set: ";
				cin >> num;
				for(int i = 0; i < num; i++)
				{
					Student stu;
					cout << endl << "Please enter the ID, name and gender: " << endl;
					cin >> stu;
					if(data.add(stu))
						cout << "successfully added!" << endl;
					else
						cout << "student has been existed!" << endl;
				}
				cout << "Adding data operation done!" << endl
					<< setfill('-') << setw(80) << "" << endl;
			}
			else
				cout << "Error detected --------- data base is invalidly sorted!" << endl
					<< setfill('-') << setw(80) << "" << endl;
		}
		else if(order == 5)
		{
			if(data.sorted())
			{
				int idtmp;
				cout << "Please enter the student's id: ";
				cin >> idtmp;
				if(data.erase(idtmp))
					cout << endl << "successfully erased!" << endl;
				else 
					cout << endl << "student is not existed!" << endl;
				cout << "erasing data operation done!" << endl
					<< setfill('-') << setw(80) << "" << endl;
			}
			else
				cout << "Error detected --------- data base is invalidly sorted!" << endl
					<< setfill('-') << setw(80) << "" << endl;
		}
		else if(order == 6)
		{
			int idtmp;
			cout << "Please enter the student's id: ";
			cin >> idtmp;
			data.modify(idtmp);
			cout << "Modification operation done!" << endl
					<< setfill('-') << setw(80) << "" << endl;
		}
		else if(order == 7)//show the current data set, used to check the operations
		{
			cout << data << endl;
			cout << setfill('-') << setw(80) << "" << endl;
		}
		else if(order == 0)//exit the programme
		{
			cout << "\t\t*******Thanks for using!*******" << endl << endl
				<< setfill('-') << setw(80) << "" << endl;
			break;
		}
		else//give a tip
		{
			cout << "Error detected --------- error input!" << endl
				<< setfill('-') << setw(80) << "" << endl;
			continue;
		}
	}
	system("pause");
	return 0;
}
