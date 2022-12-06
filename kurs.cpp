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

#pragma region checks
int check_number_unique(string& number, Node*& Head)
{
	Node* tmp = Head;
	int size, num;
	size = number.size();
	while (cin.fail() || size > 4 || size < 4 || (number.find_first_not_of("0123456789") == string::npos) == false)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Номер рейса должен содержать 4 цифры: " << endl;
		cin >> number;
		size = number.size();
	}
	num = stoi(number);
	try 
	{
		while (tmp)
		{
			if (num == tmp->data.number)
			{
				cout << "Номер рейса не уникален, введите другой номер" << endl;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cin >> number;
				throw exception();
			}
			tmp = tmp->next;
		}
	}
	catch (exception& ex) 
	{
		check_number_unique(number, Head);
	}
	return stoi(number);
}

int check_number(string& number)
{
	int size, num;
	size = number.size();
	while (cin.fail() || size > 4 || size < 4 || (number.find_first_not_of("0123456789") == string::npos) == false)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Номер рейса должен содержать 4 цифры: " << endl;
		cin >> number;
		size = number.size();
	}
	return stoi(number);
}

void check_menu(int& menu)
{
	while (cin.fail() || cin.get() != '\n' || menu < 0 || menu > 8)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "\nНеверный ввод. Повторите: ";
		cin >> menu;
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

void check_destination(string& dest)
{
	while ((dest.find_first_not_of("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя-") == string::npos) == false)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Пункт назначения не должен содержать цифр и специальных знаков: " << endl;
		cin >> dest;
	}
}
#pragma endregion checks

void AddFlight(Flight Plane, Node *& Head, Node*& Tail) 
{
	string number;
	int option, size;
	cout << "Введите номер рейса в формате 0001: ";
	cin >> number;
	Plane.number = check_number_unique(number, Head);
	cout << "\nВведите пункт назначения: ";
	cin >> Plane.destination;
	check_destination(Plane.destination);
	cout << "\nВыберите тип самолета: \n1) Boeing 777-300ER\n2) Boeing 737-800\n3) Airbus A350-900\n4) Airbus А330-300\n5) Airbus А321\n";
	cin >> option;
	check_option(option);
	switch (option) 
	{
	case 1:
		Plane.plane_type = "Boeing 777-300ER";
		break;
	case 2:
		Plane.plane_type = "Boeing 737-800";
		break;
	case 3:
		Plane.plane_type = "Airbus A350-900";
		break;
	case 4:
		Plane.plane_type = "Airbus А330-300";
		break;
	case 5:
		Plane.plane_type = "Airbus А321";
		break;
	}
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

void EditFlight(Flight Plane, Node*& Head)
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
	cout << endl << "Введите номер рейса (4 цифры), который необходимо редактировать: " << endl;
	cin >> numb;
	num = check_number(numb);

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
				num = check_number_unique(numb, Head);
				othertmp->data.number = num;
				break;
			}
			case 2:
			{
				string _destination;
				cout << "Введите новый пункт назначения: " << endl;
				cin >> _destination;
				check_destination(_destination);
				othertmp->data.destination = _destination;
				break;
			}
			case 3:
			{
				cout << "\nВыберите тип самолета: \n1) Boeing 777-300ER\n2) Boeing 737-800\n3) Airbus A350-900\n4) Airbus А330-300\n5) Airbus А321\n";
				cin >> p_t;
				check_option(p_t);
				switch (p_t)
				{
				case 1:
					othertmp->data.plane_type = "Boeing 777-300ER";
					break;
				case 2:
					othertmp->data.plane_type = "Boeing 737-800";
					break;
				case 3:
					othertmp->data.plane_type = "Airbus A350-900";
					break;
				case 4:
					othertmp->data.plane_type = "Airbus А330-300";
					break;
				case 5:
					othertmp->data.plane_type = "Airbus А321";
					break;
				}
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
	num = check_number(numb);
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

void SortByNumber(Flight Plane, Node*& Head)
{
	if (Head == NULL || Head->next == NULL)
	{
		cout << "Недостаточно элементов для сортировки.\n";
		return;
	}
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
				swap(tmp->data, tmp->next->data);
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
	cout  << "\nРейсы отсортированы по номеру.\n\n";
}

void SearchDestinations(Flight Plane, Node*& Head)
{
	bool flag = 0;
	Node* tmp = Head;
	string des;
	cout << "\nВведите пункт назначения: ";
	cin >> des;
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

void Read(Flight Plane, Node*& Head, Node*& Tail, string inpath)
{
	Node* tmp = Head;
	ifstream read_file;
	read_file.open(inpath + ".txt");
	string str, num, dest, typ;
	string Boeing1 = "Boeing 777-300ER",
		Boeing2 = "Boeing 737-800",
		Airbus1 = "Airbus A350-900",
		Airbus2 = "Airbus А330-300",
		Airbus3 = "Airbus А321";
	Flight obj;
	int x;
	if (!read_file.is_open())
	{
		cout << "Файл не существует." << endl;
		return;
	}
	do
	{
		getline(read_file, str);

		if (str.size() == 0)
			continue;

		int stick = 0;
		int dot = 0;
		int ind = 0;
		while (ind < str.size())
		{
			if (str[ind] == '|')
			{
				stick++;
			}
			if (str[ind] == ';')
			{
				dot++;
			}
			ind++;
		}
		if (stick != 2 || dot != 1)
		{
			ind = 0;//обнуляем индекс для строки
			str.clear();
			num.clear();
			dest.clear();
			typ.clear();
			continue;
		}

		x = 0;
		while (str[x] != '|')
		{
			num += str[x];
			x++;
		}
		if (num.size() < 4 || num.size() > 4 || (num.find_first_not_of("0123456789") == string::npos) == false)
		{
			cout << "Рейс " << str << " не был добавлен, так как имеет ошибки в полях\n";
			num.clear();
			dest.clear();
			typ.clear();
			continue;
		}

		x++;
		while (str[x] != '|')
		{
			dest += str[x];
			x++;
		}
		if ((dest.find_first_not_of("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя-") == string::npos) == false)
		{
			cout << "Рейс " << str << " не был добавлен, так как имеет ошибки в полях\n";
			num.clear();
			dest.clear();
			typ.clear();
			continue;
		}

		x++;
		while (str[x] != ';')
		{
			typ += str[x];
			x++;
		}
		if (typ != Boeing1 && typ != Boeing2 && typ != Airbus1 && typ != Airbus2 && typ != Airbus3)
		{
			cout << "Рейс " << str << " не был добавлен, так как имеет ошибки в полях\n";
			num.clear();
			dest.clear();
			typ.clear();
			continue;
		}
		x++;

		Plane.number = stoi(num);
		Plane.destination = dest;
		Plane.plane_type = typ;
		ReadHelp(Plane, Head, Tail);
		str.clear();
		num.clear();
		dest.clear();
		typ.clear();
	} while (!read_file.eof());
	cout << endl << "База данных загружена" << endl << endl;
	read_file.close();
}

void Record(Flight Plane, Node*& Head, string& inpath, string& outpath)
{
	Node* tmp = Head;
	ofstream record_file;
	if (outpath != inpath)
	{
		record_file.open(outpath + ".txt", ofstream::app);
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
		record_file.open(outpath + ".txt");
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
	inpath = "";
}

int main() 
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Node* Head = NULL;
	Node* Tail = NULL;
	Flight Plane;
	string outpath, inpath = "";
	int menu;

	do
	{
		cout << "1) Добавить рейс\n2) Редактировать рейс\n3) Удалить рейс\n4) Поиск рейсов по пункту назначения\n5) Показать все рейсы\n6) Сортировка по номеру рейса\n7) Сохранить всё в базу данных\n";
		cout << "8) Загрузить из базы данных\n0) Выход\nВведите цифру соответствующую нужной опции: ";
		cin >> menu;
		check_menu(menu);
		system("cls");

		switch (menu)
		{
		case 1:
		{
			AddFlight(Plane, Head, Tail);
			break;
		}
		case 2:
		{
			EditFlight(Plane, Head);
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
			cout << "Введите имя файла: ";
			cin >> outpath;
			Record(Plane, Head, outpath, inpath);
			break;
		}
		case 8:
		{
			cout << "Введите имя файла: ";
			cin >> inpath;
			Read(Plane, Head, Tail, inpath);
			break;
		}
		case 0:
		{
			return 0;
		}
		}
	} while (menu != 0);
}