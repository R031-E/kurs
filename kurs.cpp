#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <iomanip>

using namespace std;

struct Flight
{
	int number;
	string	destination,
		plane_type;
};

struct Node
{
	Flight data;
	Node* next;
	Node* prev;
};

struct Planes 
{
	string plane;
	Planes* Next;
};

const string planes[] = { "Boeing 777-300ER", "Boeing 737-800", "Airbus A350-900", "Airbus A330-300", "Airbus A321" };

#pragma region checks
bool check_unique(string& number, Node*& Head)
{
	bool flag = 0;
	int num = stoi(number);
	Node* tmp = Head;
	while (tmp)
	{
		if (num == tmp->data.number)
		{
		flag = 1;
		return false;
		}
	tmp = tmp->next;
	}
	if (flag == 0) return true;
}

bool check_number(string& number)
{
	int size;
	size = number.size();
	if (size > 4 || size < 4 || (number.find_first_not_of("0123456789") == string::npos) == false)
	{
		return false;
	}
	else return true;
}

void check_menu(int& menu)
{
	while (cin.fail() || cin.get() != '\n' || menu < 0 || menu > 9)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "\nНеверный ввод. Повторите: ";
		cin >> menu;
	}
}

void check_choice(int& option)
{
	while (cin.fail() || cin.get() != '\n' || option < 0 || option > 1)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "\nНеверный ввод. Повторите: ";
		cin >> option;
	}
}


void check_option(int& menu)
{
	while (cin.fail() || cin.get() != '\n' || menu < 1 || menu > 5)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "\nНеверный ввод. Повторите: ";
		cin >> menu;
	}
}

bool check_destination(string& dest)
{
	if ((dest.find_first_not_of("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя- ") == string::npos) == false)
	{
		return false;
	}
	else return true;
}

bool check_planes_unique(string& type, Planes*& Start)
{
	bool flag = 0;
	Planes* tmp = Start;
	while (tmp)
	{
		if (type == tmp->plane)
		{
			flag = 1;
			return false;
		}
		tmp = tmp->Next;
	}
	if (flag == 0) return true;
}

bool check_plane(string& type)
{
	if ((type.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-0123456789 ") == string::npos) == false)
	{
		return false;
	}
	else return true;
}
#pragma endregion checks

void ShowPlanes(Planes*& Start)
{
	Planes* temporary = Start;
	while (temporary)
	{
		cout << "-- " << temporary->plane << endl;
		temporary = temporary->Next;
	}
}

void AddFlight(Flight Plane, Node*& Head, Node*& Tail, Planes*& Start)
{
	string number, dest, type;
	int option, size;
	cout << "Введите номер рейса в формате 0001: ";
	cin >> number;
	while (check_number(number) == false || check_unique(number, Head) == false)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Номер рейса должен содержать 4 цифры и быть уникальным: " << endl;
		cin >> number;
	}
	Plane.number = stoi(number);
	cout << "\nВведите пункт назначения: ";
	getline(cin >> ws, dest);
	while (check_destination(dest) == false)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Пункт назначения не должен содержать цифр и специальных знаков: " << endl;
		getline(cin >> ws, dest);
	}
	Plane.destination = dest;
	cout << "\nВведите имя нужного типа самолета:\n";
	ShowPlanes(Start);
	getline(cin >> ws, type);
	while (check_planes_unique(type, Start) == true)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Такой самолет отсутсвует в базе, повторите ввод: " << endl;
		getline(cin >> ws, type);
	}
	Plane.plane_type = type;
	Node* NewElem = new Node;
	NewElem->next = NULL;
	NewElem->data = Plane;
	if (Head == NULL)
	{
		NewElem->prev = NULL;
		Head = Tail = NewElem;
	}
	else
	{
		NewElem->prev = Tail;
		Tail->next = NewElem;
		Tail = NewElem;
	}
	cout << "Рейс добавлен.\n";
}

void EditFlight(Flight Plane, Node*& Head, Planes*& Start)
{
	Node* othertmp = Head;
	Node* tmp = Head;
	if (tmp == NULL)
	{
		cout << "Нечего редактировать." << endl;
		return;
	}
	bool flag = 0;
	int num, var, p_t, size;
	string numb = "";
	string type;
	cout << endl << "Введите номер рейса (4 цифры), который необходимо редактировать: " << endl;
	cin >> numb;
	while (check_number(numb) == false)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Номер рейса должен содержать 4 цифры: " << endl;
		cin >> numb;
	}
	num = stoi(numb);
	while (tmp)
	{
		if (tmp->data.number == num)
		{
			flag = 1;
			othertmp = tmp;
		}
		tmp = tmp->next;
	}

	if (flag == 1)
	{
		do
		{
			cout << "1) Редактировать номер" << endl;
			cout << "2) Редактировать пункт назначения" << endl;
			cout << "3) Редактировать тип" << endl;
			cout << "0) Назад" << endl;

			cin >> var;
			while (var > 4 || var < 0 || cin.fail())
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << "Введено неверное значение. Повторите ввод: " << endl;
				cin >> var;
			}

			switch (var)
			{
			case 1:
			{
				cout << "Введите новый номер рейса: " << endl;
				cin >> numb;
				while (check_number(numb) == false || check_unique(numb, Head) == false)
				{
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "Номер рейса должен содержать 4 цифры и быть уникальным: " << endl;
					cin >> numb;
				}
				othertmp->data.number = stoi(numb);
				break;
			}
			case 2:
			{
				string _destination;
				getline(cin >> ws, _destination);
				while (check_destination(_destination) == false)
				{
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "Пункт назначения не должен содержать цифр и специальных знаков: " << endl;
					getline(cin >> ws, _destination);
				}
				othertmp->data.destination = _destination;
				break;
			}
			case 3:
			{
				cout << "\nВведите имя нужного типа самолета:\n";
				ShowPlanes(Start);
				getline(cin >> ws, type);
				while (check_planes_unique(type, Start) == true)
				{
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "Такой самолет отсутсвует в базе, повторите ввод: " << endl;
					getline(cin >> ws, type);
				}
				othertmp->data.plane_type = type;
				break;
			}
			case 0:
			{
				return;
			}
			}
			flag = 1;
			cout << endl << "Запись отредактированна." << endl;
		}

		while (var != 0);

	}
	if (flag == 0)
	{
		cout << endl << "Рейс с таким номером не найден." << endl << endl;
	}
	return;
}

void DeleteFlight(Flight Plane, Node*& Head, Node*& Tail)
{
	if (!Head)
	{
		cout << "В приложении нет базы данных.\n";
		return;
	}
	string numb;
	bool del = 0;
	int num;
	cout << "\nВведите номер рейса, который нужно удалить: ";
	cin >> numb;
	while (check_number(numb) == false)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Номер рейса должен содержать 4 цифры: " << endl;
		cin >> numb;
	}
	num = stoi(numb);
	Node* tmp = Head;
	while (tmp)
	{
		if (tmp->data.number == num)
		{
			if (tmp->prev == NULL)
			{
				Head = tmp->next;
			}
			if (tmp->next)
			{
				tmp->next->prev = tmp->prev;
			}
			if (tmp->prev)
			{
				tmp->prev->next = tmp->next;
			}
			if (tmp->data.number == Tail->data.number)
			{
				Tail->prev->next = NULL;
				Tail = Tail->prev;
			}
			del = 1;
			cout << endl << "Запись удалена" << endl << endl;
			return;
		}
		tmp = tmp->next;
	}
	if (del == 0)
	{
		cout << endl << "Рейс с таким номером не найден" << endl << endl;
	}
	return;
}

void ClearList(Flight Plane, Node*& Head, Node*& Tail)
{
	if (!Head)
	{
		cout << "В приложении нет таблицы.\n";
		return;
	}

	while (Head)
	{
		Node* jump = Head->next;
		delete Head;
		Head = jump;
	}
	Tail = NULL;
}

void SortByNumber(Flight Plane, Node*& Head)
{
	if (Head == NULL || Head->next == NULL)
	{
		cout << "Недостаточно элементов для сортировки.\n";
		return;
	}
	Flight store;
	Node* tmp = Head;
	bool flag = 1;
	int k;
	do
	{
		k = 0;
		while (tmp->next != NULL)
		{
			if (tmp->data.number > tmp->next->data.number)
			{
				store = tmp->next->data;
				tmp->next->data = tmp->data;
				tmp->data = store;
				flag = 1;
				k++;
			}
			tmp = tmp->next;
		}
		if (k == 0)
		{
			flag = 0;
		}
		tmp = Head;
	} while (flag != 0);
	cout << "\nРейсы отсортированы по номеру.\n\n";
}

void SearchDestinations(Flight Plane, Node*& Head)
{
	if (!Head)
	{
		cout << "В приложении нет таблицы.\n";
		return;
	}
	bool flag = 0;
	Node* tmp = Head;
	string des;
	cout << "\nВведите пункт назначения: ";
	getline(cin >> ws, des);
	while (check_destination(des) == false)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Пункт назначения не должен содержать цифр и специальных знаков: " << endl;
		getline(cin >> ws, des);
	}
	while (tmp)
	{
		if (tmp->data.destination == des)
		{
			cout << "\nНомер рейса : " << tmp->data.number << "  Пункт назначения : " << tmp->data.destination << "  Тип самолёта : " << tmp->data.plane_type << "\n";
			flag = 1;
		}
		tmp = tmp->next;
	}
	cout << "\n";
	if (flag == 0) cout << "Рейсы с пунктом назначения " << des << " не найдены.\n";
}

void ShowFlights(Flight Plane, Node*& Head, Node*& Tail)
{
	if (!Head)
	{
		cout << "В приложении нет таблицы.\n";
		return;
	}
	Node* tmp = Head;
	cout << "\n| " << " Номер рейса " << " | " << "Пункт прибытия" << " | " << "    Тип самолёта    " << " |\n" << "+---------------+----------------+----------------------+\n";
	while (tmp)
	{
		cout << "| " << setw(13) << tmp->data.number << " | " << setw(14) << tmp->data.destination << " | "
			<< setw(20) << tmp->data.plane_type << " |" << endl;
		cout << "+---------------+----------------+----------------------+" << endl;
		tmp = tmp->next;
	}
}

void ReadHelp(Flight Plane, Node*& Head, Node*& Tail)
{
	Node* NewElem = new Node;
	NewElem->next = NULL;
	NewElem->data = Plane;
	if (Head == NULL)
	{
		NewElem->prev = NULL;
		Head = Tail = NewElem;
	}
	else
	{
		NewElem->prev = Tail;
		Tail->next = NewElem;
		Tail = NewElem;
	}
}

void Read(Flight Plane, Node*& Head, Node*& Tail, Planes*& Start, string inpath)
{
	bool flag;
	ifstream read_file;
	read_file.open(inpath);
	string num, dest, typ;
	if (!read_file.is_open())
	{
		cout << "Файл не существует." << endl;
		return;
	}
	while (read_file.good())
	{
		flag = 0;
		getline(read_file, num, '|');
		if (num.length() == 0) continue;
		size_t pos;
		while (((pos = num.find('\n')) != string::npos))
			num.erase(pos, 1);

		if (check_number(num) == false || check_unique(num, Head) == false || ((pos = num.find(';')) != string::npos)) flag = 1;
	
		getline(read_file >> ws, dest, '|');
		if (check_destination(dest) == false) flag = 1;
		
		getline(read_file >> ws, typ, ';');
		if (check_planes_unique(typ, Start) == true) flag = 1;

		if (flag == 0) 
		{
			Plane.number = stoi(num);
			Plane.destination = dest;
			Plane.plane_type = typ;
			ReadHelp(Plane, Head, Tail);
			num.clear();
			dest.clear();
			typ.clear();
		}
		else 
		{
			cout << "Рейс " << num << " не был добавлен, так как имеет ошибки в полях\n";
			num.clear();
			dest.clear();
			typ.clear();
			continue;
		}
	} 
	cout << endl << "База данных загружена" << endl << endl;
	read_file.close();
}

void Record(Flight Plane, Node*& Head, string& outpath, string& inpath)
{
	Node* tmp = Head;
	ofstream record_file;
	if (outpath != inpath)
	{
		record_file.open(outpath, ofstream::app);
		if (!record_file.is_open())
		{
			cout << "Не удалось открыть файл.\n";
			return;
		}
		else
		{
			while (tmp)
			{
				record_file << tmp->data.number << "|" << tmp->data.destination
					<< "|" << tmp->data.plane_type << ";" << endl;
				tmp = tmp->next;
			}
			cout << endl << "Таблица была сохранена" << endl << endl;
		}
	}
	else
	{
		record_file.open(outpath);
		if (!record_file.is_open())
		{
			cout << "Не удалось открыть файл.\n";
			return;
		}
		else
		{
			while (tmp)
			{
				record_file << tmp->data.number << "|" << tmp->data.destination
					<< "|" << tmp->data.plane_type << ";" << endl;
				tmp = tmp->next;
			}
			cout << endl << "Таблица была сохранена" << endl << endl;
		}
	}
	record_file.close();
}

void PlanesHelp(string plane_type, Planes*& Start)
{
	Planes* NewElem = new Planes;
	NewElem->Next = NULL;
	NewElem->plane = plane_type;
	if (Start == NULL) Start = NewElem;
	else
	{
		Planes* tmp = Start;
		while (tmp->Next != NULL)
		{
			tmp = tmp->Next;
		}
		tmp->Next = NewElem;
	}
}

void CreatePlanes(Planes*& Start)
{
	ofstream base;
	base.open("Planes.txt");
	if (!base.is_open())
	{
		cout << "Не удалось создать файл.\n";
		return;
	}
	else 
	{
		for (int i = 0; i < sizeof(planes) / sizeof(planes[0]); i++)
		{
			base << planes[i] << ";" << endl;
		}
	}
	base.close();
}

void AddPlanes(Planes*& Start)
{
	bool flag;
	string type;
	ifstream planesbase;
	planesbase.open("Planes.txt");
	if (!planesbase.is_open()) 
	{
		cout << "Не удалось найти файл с базой самолетов (Planes.txt), файл будет создан автоматически\n";
		CreatePlanes(Start);
	}
	planesbase.close();
	planesbase.open("Planes.txt");
	while (planesbase.good()) 
	{
		flag = 0;
		getline(planesbase >> ws, type, ';');
		if (type.length() == 0) continue;
		size_t pos;
		while (((pos = type.find('\n')) != string::npos))
			type.erase(0, pos + 1);
		if (check_planes_unique(type, Start) == false || check_plane(type) == false)
		{
			type.clear();
			continue;
		}
		PlanesHelp(type, Start);
		type.clear();
	}
	planesbase.close();
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Planes* Start = NULL;
	Node* Head = NULL;
	Node* Tail = NULL;
	Flight Plane;
	string outpath, inpath = "";
	int menu, choice;
	AddPlanes(Start);

	do
	{
		cout << "1) Добавить рейс\n2) Редактировать рейс\n3) Удалить рейс\n4) Поиск рейсов по пункту назначения\n5) Показать все рейсы\n6) Сортировка по номеру рейса\n7) Сохранить всё в базу данных\n";
		cout << "8) Загрузить из базы данных\n9) Очистить таблицу\n0) Выход\nВведите цифру соответствующую нужной опции: ";
		cin >> menu;
		check_menu(menu);
		system("cls");

		switch (menu)
		{
		case 1:
		{
			AddFlight(Plane, Head, Tail, Start);
			break;
		}
		case 2:
		{
			EditFlight(Plane, Head, Start);
			break;
		}
		case 3:
		{
			DeleteFlight(Plane, Head, Tail);
			break;
		}
		case 4:
		{
			SearchDestinations(Plane, Head);
			break;
		}
		case 5:
		{
			ShowFlights(Plane, Head, Tail);
			break;
		}
		case 6:
		{
			SortByNumber(Plane, Head);
			break;
		}
		case 7:
		{
			if (!Head)
			{
				cout << "В приложении нет таблицы для сохранения.\n";
				break;
			}
			cout << "Введите полный путь до файла: ";
			cin >> outpath;
			Record(Plane, Head, outpath, inpath);
			break;
		}
		case 8:
		{
			cout << "Хотите перед этим очистить таблицу в приложении?\nВведите 1, если хотите очистить и 0, если нет: ";
			cin >> choice;
			check_choice(choice);
			if (choice == 1)
			{
				ClearList(Plane, Head, Tail);
			}
			cout << "\nВведите полный путь до файла: ";
			cin >> inpath;
			Read(Plane, Head, Tail, Start, inpath);
			break;
		}
		case 9:
		{
			ClearList(Plane, Head, Tail);
			break;
		}
		case 0:
		{
			return 0;
		}
		}
	} while (menu != 0);
}