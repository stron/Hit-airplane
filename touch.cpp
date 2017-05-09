#include "stdafx.h"
#include "Student.h"
#include "List.h"


List::List()
{
	maxSize = 10000;
	info = new Student [maxSize];
	length = 0;
	flag = false;
}

List::~List()
{
	delete []info;
	length = 0;
	flag = false;
	info = new Student [maxSize];//adapt to dynamicly established data set, every time when delete the info, is just to clear the data in it
}

List::List(const List &l)
{
	info = new Student [5000];
	length = l.size();
	for(int i = 0; i < length; i++)
		info[i] = l.info[i];
}

bool List::empty() const
{
	return length == 0;
}

bool List::full() const
{
	return length == maxSize;
}

int List::size() const
{
	return length;
}

bool List::sorted() const
{
	return flag;
}

Student* List::getList()
{
	return info;
}
bool List::binarySearch1(const int id, Student &get) const
{
	int low = 0, high = length - 1, mid;
	while(low < high)
	{
		mid = (low + high) / 2;
		if(info[mid].id < id)
			low = mid + 1;
		else
			high = mid;
	}
	if(info[low].id == id) 
	{
		get = info[low];
		return true;
	}
	else 
		return false;
}

bool List::binarySearch2(const int id, Student& get) const
{
	int low = 0, high = length - 1, mid;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(info[mid].id == id)
		{
			get = info[mid];
			return true;
		}
		if(info[mid].getId() < id)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return false;
}

bool List::binarySearch3(const int id, Student& get, int low, int high) const
{
	if(low == high)
	{
		get = info[low];
		return true;
	}
	else if(low < high)
	{
		int mid = (low + high) / 2;
		if(info[mid].getId() < id)
			return binarySearch3(id, get, mid + 1, high);
		else
			return binarySearch3(id, get, low, mid);
	}
	else
		return false;
}

bool List::binarySearch4(const int id, Student& get, int low, int high) const
{
	if(low <= high)
	{
		int mid = (low + high) / 2;
		if(info[mid].getId() == id)
		{
			get = info[mid];
			return true;
		}
		else if(info[mid].getId() < id)
			return binarySearch4(id, get, mid + 1, high);
		else 
			return binarySearch4(id, get, low, mid - 1);
	}
	else
		return false;
}

bool List::add(const Student &stu)
{
	Student *tmp = info;
	int i = 0;
	while(i < length && tmp[i].id <= stu.id)
	{
		if(tmp[i].id == stu.id) 
			return false;
		else 
			i++;
	}
	int index = i;
	while(i <= length)
		tmp[i + 1] = tmp[i++];
	
	tmp[index] = stu;
	length++;
	return true;
}

List& List::append(const Student& stu)
{
	info[length++] = stu;
	return *this;
}


bool List::erase(const int id)
{
	//Student *tmp = info;
	int index;
	for(index = 0; index < length; index++)
		if(info[index].getId() == id) 
			break;
	
	if(index != length)
	{
		while(index< length)
			info[index] = info[++index];
		length--;
		return true;
	}
	else 
		return false;
}

void List::modify(const int id)
{
	int i;
	for(i = 0; i < length; i++)
		if(info[i].id == id)
			break;
	if(i == length)
		cout << "Failure search!" << endl;
	else
	{
		cout << "Please enter the new infomation of the target student(name gender): " << endl;
		string name, gender;
		cin >> name >> gender;
		info[i].setName(name);
		info[i].setGender(gender);
	}
	
}

bool List::unique(const int id) const
{
	for(int i = 0; i < length; i++)
		if(info[i].getId() == id)
			return false;
	return true;
}

void List::insert_sort()
{
	for(int i = 0; i < length; i++)
	{
		int index = i; Student tmp = info[i];
		while(index > 0 && info[index - 1].getId() > tmp.getId())
		{
			info[index] = info[index - 1];
			index--;
		}
		info[index] = tmp;
	}
	flag = true;
}

void List::select_sort()
{
	for(int i = 0; i < length; i++)
	{
		int index = i;
		for(int j = i + 1; j < length; j++)
			if(info[index].getId() > info[j].getId())
				index = j;
		Student tmp = info[index];
		info[index] = info[i];
		info[i] = tmp;
	}
	flag = true;
}

void List::shell_sort()
{
	int inc = 0;
	while(inc <= length) inc = inc * 3 + 1;
	while(inc > 0)
	{
		for(int i = inc; i < length; i++)
		{
			int j = i;
			Student tmp = info[j];
			while(j >= inc && tmp.getId() < info[j - inc].getId())
			{
				info[j] = info[j - inc];
				j -= inc;
			}
			info[j] = tmp;
		}
		inc = (inc - 1) / 3;
	}
	flag = true;
}

void List::quick_sort(int left, int right)//recursive version of quick sort
{
	int l = left, r = right;
	Student pivot = info[l];//middle value
	if(l >= r) return;
	while(l < r)
	{
		while(l < r && info[r].id >= pivot.id)
			r--;
		info[l] = info[r];
		while(l < r && info[l].id <= pivot.id)
			l++;
		info[r] = info[l];
	}
	info[r] = pivot;
	quick_sort(left, l - 1);
	quick_sort(l + 1, right);
	flag = true;
}

void List::bubble_sort()
{
	for(int i = 0; i < length; i++)
		for(int j = i + 1; j < length; j++)
		{
			if(info[i].getId() > info[j].getId())
			{
				Student tmp = info[i];
				info[i] = info[j];
				info[j] = tmp;
			}
		}
	flag = true;
}

void List::output(std::ostream &os) const
{
	os << "ID\t" << "\tNAME\t" << "\tGENDER" << endl;
	for(int i = 0; i< length; i++)
		os << info[i].getId() << "\t" << info[i].getName() << "\t\t" << info[i].getGender() << endl;
	
}

ostream& operator <<(ostream& os, List& l)
{
	l.output(os);
	return os;
}

void List::merge_sort(Student *arr, int low, int high)
{
	int mid;
	if(low < high)
	{
		mid = (low + high) / 2;
		merge_sort(arr, low, mid);
		merge_sort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
	flag = true;
}

void List::merge(Student *arr, int low, int mid, int high)
{
	Student *tmp = new Student [high - low + 1];
	int beg1 = low;
	int end1 = mid;
	int beg2 = mid + 1;
	int end2 = high;
	int i = 0;
	for(i = 0; beg1 <= end1 && beg2 <= end2; i++)
	{
		if(arr[beg1].getId() < arr[beg2].getId())
			tmp[i] = arr[beg1++];
		else
			tmp[i] = arr[beg2++];
	}
	/*while((beg1 <= end1) && ( beg2 <= end2))
	{
		if(arr[beg1].getId() < arr[beg2].getId())
		{ 
		tmp[i] = arr[beg1];
		beg1++;
		}
		else
		{
		tmp[i] = arr[beg2];
		beg2++;
		}
		i++;
	}*/
	while(beg1 <= end1 || beg2 <= end2)
	{
		if(beg1<=end1)
			tmp[i++] = arr[beg1++];
		if(beg2 <= end2)
			tmp[i++] = arr[beg2++];
		
	}
	for(i = 0; i <= high - low; i++)
		arr[low + i] = tmp[i];//ÕâÀï²»¿ÉÒÔÓÃbeg1 end1µÈÁÙÊ±±äÁ¿£¬ÒòÎª¾­¹ýÉÏÃæ²Ù×÷Ö®ºóÒÑ¾­¸Ä±äÁË£¬²»ÄÜ¹»´ú±íÆðµãÖÕµãÁË
	delete []tmp;
}

void List::heap_sort()
{
	for(int low = length / 2 - 1; low >= 0; low--)
		heap(low, length - 1);
	for(int high = length - 1; high > 0; high--)
	{
		Student stu = info[high];
		info[high] = info[0];
		info[0] = stu;
		heap(0, high - 1);
	}
}

void List::heap(int current, int high)
{
	int child = 2 * current + 1;
	
	//Ò»´ÎÑ­»·Ö»½øÐÐÒ»´Î¸¸×ÓÔªËØµÄ½»»»
	while(child <= high)
	{	
		Student tmp = info[current];
		if(child < high && info[child].getId() < info[child + 1].getId())
			child++;
		if(info[current].getId() >= info[child].getId())
			break;
		else
		{
			info[current] = info[child];
			current = child;
			child = 2 * current + 1;
		}
		info[current] = tmp;
	}
	
}
