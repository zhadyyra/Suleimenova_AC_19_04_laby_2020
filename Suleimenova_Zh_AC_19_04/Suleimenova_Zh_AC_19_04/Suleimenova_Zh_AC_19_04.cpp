#include <iostream>
#include <fstream>
#include <string>
#include "Pipeline.h"
#include "Ks.h"
#include "Utils.h"
#include "Network.h"
using namespace std;

void PrintMenu()
{
	cout << "\n1. Добавить трубопровод.\n"
		<< "2. Добавить КС.\n"
		<< "3. Удалить информацию трубопроводов.\n"
		<< "4. Удалить информацию КС.\n"
		<< "5. Загрузить трубопроводы и КС из файла.\n"
		<< "6. Показать информацию обо всех трубопроводах.\n"
		<< "7. Показать информацию обо всех КС.\n"
		<< "8. Сохранить всю информацию в файл.\n"
		<< "9. Пакетное редактирование трубопроводов.\n"
		<< "10. Поиск трубопроводов по фильтру.\n"
		<< "11. Поиск КС по фильтру.\n"
		<< "0. Выход.\n";
}

string AskingForName()    //Для сохранения файла по имени и для загрузки из файла
{
	string filename;
	cout << "\nПожалуйства, введите имя: ";
	cin.ignore(1, '\n');
	getline(cin, filename);
	return filename;
}

void LoadAll(unordered_map<int, Pipeline>& Pipeline_s, unordered_map <int, Ks>& Ks_s)
{
	ifstream fin;
	fin.open(AskingForName(), ios::in);
	if (fin.is_open())
	{
		char ch;
		while (fin.get(ch))
		{
			cout << ch;
		}
	}
	else cout << "Файл с этим именем не найден.\n";
	fin.close();
}
void SaveAll(const unordered_map<int, Pipeline>& Pipeline_s, const unordered_map <int, Ks>& Ks_s)
{
	if ((!Pipeline_s.size()) and (!Ks_s.size()))
		cout << "Информация о трубопроводов и КС пока не поступала. Введите данные, выбрав 1, 2 или 5.\n ";
	else
	{
		ofstream fout;
		fout.open(AskingForName(), ios::out);
		if (fout.is_open())
		{
			fout << Pipeline_s.size() << endl;
			fout << Ks_s.size() << endl;
			for (const auto& p : Pipeline_s)
				fout << p.second;
			for (const auto& k : Ks_s)
				fout << k.second;
			fout.close();
			cout << "Выполнено.\n";
		}
		else cout << "Произошла ошибка при записи файла.";
	}
}

template<typename C, typename T>
using Filter = bool(*)(const C& pk, T param);
bool CheckByRepear(const Pipeline& p, bool repear)   //Проверить по ремонту
{
	return p.repear == repear;
}
bool CheckByName(const Ks& k, string name) //По названию
{
	return k.name == name;
}
bool CheckBy_Percent_Unused_Ceh(const Ks& k, double percent) //По проценту незадейтвованных цехов
{
	return percent <= (double)(100 * (k.ceh - k.cehwork) / k.ceh);
}
template<typename C, typename T>
vector<int> FindObjectsByFilter(const unordered_map<int, C>& PK_s, Filter<C, T> f, T param)
{
	vector <int> res;
	int i = 0;
	for (const auto& object : PK_s)
	{
		if (f(object.second, param))
			res.push_back(i);
		i++;
	}
	if (res.size() == 0) cout << "Объект не найден.\n";
	return res;
}
void BatchEditPipes(unordered_map<int, Pipeline>& Pipeline_s, Network& n) //Пакетное редактирование труб
{
	int choice;
	while ((choice = GetCorrectNumber(-1, INT_MAX,
		"\nПожалуйста, выберите правильный ID трубы, который вы хотите редактировать; введите -1, чтобы остановиться и перейти в меню : ")) != -1)
	{
		unordered_map<int, Pipeline>::iterator got = Pipeline_s.find(choice);
		if (got == Pipeline_s.end())
			cout << "Объект не найден.\n";
		else
		{
			got->second.EditPipeline();
			cout << "ВЫполнено.\n";
			for (const auto& obj : n.GtsPipe)
			{
				if (obj == got->first)
					n.NetworkExist = false;
			}
		}
	}
}

void EditAllPipes(unordered_map <int, Pipeline>& Pipeline_s, Network& n) //Редактировать все трубы
{
	for (auto& p : Pipeline_s)
	{
		p.second.EditPipeline();
	}
	cout << "Выполнено.\n";
	n.NetworkExist = false;
}

void DelPipe(unordered_map<int, Pipeline>& Pipeline_s, Network& n)
{
	unordered_map<int, Pipeline>::iterator got = Pipeline_s.find(GetCorrectNumber(0, INT_MAX,
		"\nПожалуйста, выберите правильный ID объекта, который вы хотите удалить : "));
	if (got == Pipeline_s.end())
		cout << "Объект не найден.\n";
	else
	{
		for (const auto& obj : n.GtsPipe)
		{
			if (obj == got->second.GetId())
				n.NetworkExist = false;
		}
		Pipeline_s.erase(got->first);
		cout << "Выполнено.\n";
	}
}

void DelKs(unordered_map<int, Ks>& Ks_s, Network& n)
{
	unordered_map<int, Ks>::iterator got = Ks_s.find(GetCorrectNumber(0, INT_MAX,
		"\nПожалуйста, выберите правильный ID объекта, который вы хотите удалить : "));
	if (got == Ks_s.end())
		cout << "Объект не найден.\n";
	else
	{
		for (const auto& obj : n.GtsKs)
		{
			if (obj == got->second.GetId())
				n.NetworkExist = false;
		}
		Ks_s.erase(got->first);
		cout << "Выполнено.\n";
	}
}

int main()
{
	unordered_map <int, Pipeline> Pipeline_s;
	unordered_map <int, Ks> Ks_s;
	Network n;
	setlocale(LC_ALL, "Russian");  //Поддрержка русского языка
	for (; ; ) 
	{
		PrintMenu();
		switch (GetCorrectNumber(0, 16, "Пожалуйста, выберите число от 0 до 11.\n"))
		{
		case 1:
		{
			Pipeline p;
			cin >> p;
			Pipeline_s.insert(pair<int, Pipeline>(p.GetId(), p));
			break;
		}
		case 2:
		{
			Ks k;
			cin >> k;
			Ks_s.insert(pair<int, Ks>(k.GetId(), k));
			break;
		}
		case 3:
		{
			if (Pipeline_s.size())
			{
				DelPipe(Pipeline_s, n);
			}
			else cout << "Информация о трубе пока не поступала.Введите данные, выбрав 1 или 5 точек.\n ";
			break;
		}
		case 4:
		{
			if (Ks_s.size())
			{
				DelKs(Ks_s, n);
			}
			else cout << "Информация о КС пока не поступала.Введите данные, выбрав 1 или 5 точек.\n ";
			break;
		}
		case 5:
		{
			LoadAll(Pipeline_s, Ks_s);
			break;
		}
		case 6:
		{
			if (Pipeline_s.size())
			{
				for (const auto& p : Pipeline_s) cout << p.second << endl;
			}
			else cout << "Информация о трубе пока не поступала.Введите данные, выбрав 1 или 5 точек.\n ";
			break;
		}
		case 7:
		{
			if (Ks_s.size())
			{
				for (const auto& k : Ks_s) cout << k.second << endl;
			}
			else cout << "Информация о КС пока не поступала.Введите данные, выбрав 2 или 5 точек.\n ";
			break;
		}
		case 8:
		{
			SaveAll(Pipeline_s, Ks_s);
			break;
		}

		case 9:
		{
			if (Pipeline_s.size())
			{
				if (GetCorrectNumber(0, 1, "Пожалуйста, введите 0 для редактирования всех труб или 1 для пакетного редактирования конвейеров : "))
				{
					BatchEditPipes(Pipeline_s, n);
				}
				else {
					EditAllPipes(Pipeline_s, n);
				}
			}
			else cout << "Информация о трубе пока не поступала. Введите данные, выбрав 1 или 5 точек.\n ";
			break;
		}
		case 10:
		{
			if (Pipeline_s.size())
			{
				if (GetCorrectNumber(0, 1, "Пожалуйста, введите 0 для поиска трубы по ID или 1 для поиска трубы, которые 'в ремонте': "))
				{
					for (int i : FindObjectsByFilter(Pipeline_s, CheckByRepear, (bool)GetCorrectNumber(-1, 1,
						"\nПожалуйста, введите 0, чтобы найти трубы, которые не в ремонте, и 1, чтобы найти трубы, которые в ремонте:: ")))
						cout << Pipeline_s[i];
				}
				else
				{
					unordered_map<int, Pipeline>::iterator got = Pipeline_s.find(GetCorrectNumber(0, INT_MAX, "\nПожалуйста, выберите правильный id конвейера, который вы хотите найти : "));
					if (got == Pipeline_s.end())
						cout << "Объект не найден.\n";
					else
					{
						cout << got->second;
					}
				}
			}
			else cout << "Информация о трубе пока не поступала.Введите данные, выбрав 1 или 5 точек.\n ";
			break;
		}
		case 11:
		{
			if (Ks_s.size())
			{
				if (GetCorrectNumber(0, 1, "Пожалуйста, введите 0 для поиска КС по имени или 1 для поиска КС по проценту неиспользованных количеств цехов в работе : "))
				{
					for (int i : FindObjectsByFilter(Ks_s, CheckBy_Percent_Unused_Ceh, GetCorrectNumber(0.0, 100.0,
						"\nПожалуйста, введите процент неиспользованных количеств цехов в работе (%): ")))
						cout << Ks_s[i];
				}
				else {
					for (int i : FindObjectsByFilter(Ks_s, CheckByName, AskingForName()))
						cout << Ks_s[i];
				}
			}
			else  cout << "Информация о КС пока не поступала.Введите данные, выбрав 2 или 5 точек.\n ";
			break;
		}

		case 0:
		{
			return 0;
			break;
		}
		}
	}
}
