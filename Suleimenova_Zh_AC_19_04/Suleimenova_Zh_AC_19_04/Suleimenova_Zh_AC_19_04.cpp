#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <unordered_map>
#include <map>
#include <set> 
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
		<< "12. Запустить или остановить цех КС.\n"
		<< "13. Выберите части для сети передачи. \n"
		<< "14. Создать / обновить сеть передачи. \n"
		<< "15. Сохранить сеть передачи в файл. \n"
		<< "16. Загрузить сеть передачи из файла. \n"
		<< "17. Показать таблицу веса графа. \n"
		<< "18. Топологическая сортировка графа. \n"
		<< "19. Найти кратчайший путь.\n"
		<< "20. Найти максимальный расход.\n"
		<< "0. Выход.\n";
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

	int IdDel = GetCorrectNumber(0, Pipeline::MaxId,
		"\nПожалуйста, введите правильный ID объекта, который вы хотите удалить: ");
	auto IdToDelete = Pipeline_s.find(IdDel);
	if (IdToDelete == Pipeline_s.end())
		cout << "Объект не найден.\n";
	else
	{
		n.PipeDelChanges(IdDel);
		n.CreateNetwork(Pipeline_s);
		Pipeline_s.erase(IdToDelete->first);
		cout << "Done.\n";
	}
}

void DelKs(unordered_map<int, Ks>& Ks_s, unordered_map <int, Pipeline>& Pipeline_s, Network& n)
{
	int IdDel = GetCorrectNumber(0, Ks::MaxId,
		"\nПожалуйста, введите правильный ID объекта, который вы хотите удалить: ");
	auto IdToDelete = Ks_s.find(IdDel);
	if (IdToDelete == Ks_s.end())
		cout << "Объект не найден.\n";
	else
	{
		n.KsDelChanges(IdDel, Pipeline_s);
		n.CreateNetwork(Pipeline_s);
		Ks_s.erase(IdToDelete->first);
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
		switch (GetCorrectNumber(0, 20, "Пожалуйста, выберите число от 0 до 20.\n"))
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
				DelKs(Ks_s, Pipeline_s, n);
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
		case 12:
		{
			if (Ks_s.size())
			{
				unordered_map<int, Ks>::iterator got = Ks_s.find(GetCorrectNumber(0, INT_MAX,
					"\nПожалуйста, выберите правильный ID КС, который вы хотите отредактировать : "));
				if (got == Ks_s.end())
					cout << "Объект не найден.\n";
				else
				{
					got->second.EditKs(GetCorrectNumber(0, 1, "Пожалуйста, введите 1 для запуска или 0 для остановки : "));
					cout << "Выполнено.\n";
				}
			}
			else cout << "Ks информации пока не поступало.Введите данные, выбрав 2 или 5 точек.\n ";
			break;
		}
		case 13:
		{
			n.CreateConnection(Pipeline_s, Ks_s);
			break;
		}

		case 14:
		{
			n.CreateNetwork(Pipeline_s);
			break;
		}
		case 15:
		{
			n.SaveNetwork(Pipeline_s, Ks_s);
			break;
		}
		case 16:
		{
			n.LoadNetwork(Pipeline_s, Ks_s);
			n.CreateNetwork(Pipeline_s);
			break;
		}
		case 17:
		{
			n.PrintNetwork();
			break;
		}
		case 18:
		{
			n.TopolSort(Pipeline_s);
			break;
		}
		case 19:
		{
			n.ShortDist();
			break;
		}
		case 20:
		{
			n.MaxFlow();
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
