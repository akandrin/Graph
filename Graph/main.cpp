#include "pch.h"

#include <iostream>
#include "graph.h"
#include <string>

// Menu
/*
	1. Считать граф из файла.
	2. Вывести список смежности данного графа.
	3. Очистить граф.
	4. Является ли граф связным.
	5. Добавление узла.
	6. Добавление дуги.
	7. Удаление узла.
	8. Удаление дуги.
	9. Выход.
*/

#define FILE_NAME "..\\graph_example.txt"

int main()
{
	Graph<std::string> aGraph;
	while (1)
	{
		std::cout << 
			"1. Read graph from file\n"\
			"2. Output adjacency list for this graph\n"\
			"3. Clear graph\n"\
			"4. Is graph connected?\n"\
			"5. Add node to graph\n"\
			"6. Add edge to graph\n"\
			"7. Remove node from graph\n"\
			"8. Remove edge from graph\n"\
			"9. Exit\n";

		int aChoice = -1;
		std::cin >> aChoice;
		while (getchar() != '\n');
		switch (aChoice)
		{
			case 1:
			{
				if (aGraph.ReadFromFile(FILE_NAME))
				{
					std::cout << "Graph was read successfully\n";
				}
				else
				{
					std::cout << "Error: Graph was not read successfully\n";
				}
				break;
			}
			case 2:
			{
				std::cout << aGraph << std::endl;
				break;
			}
			case 3:
			{
				aGraph.Clear();
				std::cout << "Graph was cleared successfully\n";
				break;
			}
			case 4:
			{
				std::cout << (aGraph.IsGraphConnected() ? "Yes" : "No") << "\n";
				break;
			}
			case 5:
			{
				std::cout << "Enter the Node:\n";
				std::string aNode;
				std::getline(std::cin, aNode);

				std::cout << (aGraph.AddNode(aNode) ? "Node was added successfully" : "Node was not added successfully") << "\n";
				break;
			}
			case 6:
			{
				std::cout << "Enter the Edge (two nodes separated by new-line character):\n";
				std::string aNodeBegin, aNodeEnd;
				std::getline(std::cin, aNodeBegin);
				std::getline(std::cin, aNodeEnd);

				try
				{
					std::cout << (aGraph.AddEdge(std::make_pair(aNodeBegin, aNodeEnd)) ? "Edge was added successfully" : "Edge was not added successfully") << "\n";
				}
				catch (const std::exception& anException)
				{
					std::cout << anException.what() << std::endl;
				}

				break;
			}
			case 7:
			{
				std::cout << "Enter the Node:\n";
				std::string aNode;
				std::getline(std::cin, aNode);

				std::cout << (aGraph.RemoveNode(aNode) ? "Node was removed successfully" : "Node was not removed successfully") << "\n";
				break;
			}
			case 8:
			{
				std::cout << "Enter the Edge (two nodes separated by new-line character):\n";
				std::string aNodeBegin, aNodeEnd;
				std::getline(std::cin, aNodeBegin);
				std::getline(std::cin, aNodeEnd);

				try
				{
					std::cout << (aGraph.RemoveEdge(std::make_pair(aNodeBegin, aNodeEnd)) ? "Edge was removed successfully" : "Edge was not removed successfully");
				}
				catch (const std::exception& anException)
				{
					std::cout << anException.what() << std::endl;
				}

				break;
			}
			case 9:
			{
				exit(0);
				break;
			}
			default:
			{
				std::cout << "Incorrect choice\n";
				break;
			}
		}
		system("pause");
		system("cls");
	}
}
