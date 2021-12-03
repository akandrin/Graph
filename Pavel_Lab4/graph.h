#pragma once

#include <iostream>
#include <map>
#include <list>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
#include <exception>

// Класс графа, данные в котором хранятся в списка смежности.
// Граф может содержать петли и циклы.
template <class NodeType>
class Graph
{
public:
	Graph();
	Graph(const Graph&);
	Graph& operator=(const Graph&);
	~Graph();

	typedef std::list<NodeType> NodeList; // список узлов (списков объектов типа NodeType).
	typedef std::pair<NodeType, NodeType> Edge; // дуга (пара узлов такая, что первый элемент - начало дуги,
	                                            // а второй элемент - конец дуги).
	                                            // Дугой здесь называется направленное ребро из одного узла в другой.
	typedef std::list<Edge> EdgeList; // список дуг.
	
	typedef std::map<NodeType, NodeList> GraphMap; // синоним типа, в котором хранятся данные графа

	// Метод строит граф по списку узлов и списку дуг.
	// - Метод бросает исключение IncorrectGraphException, если была передана дуга такая,
	//   что какой-нибудь её узел не входит в список узлов
	//  (Например, для списков {A, B} и {(A, B), (B, C)}) бросится исключение, потому что дуга (B, C) содержит узел C, который не входит в список {A, B}
	// - Метод игнорирует одинаковые узлы и одинаковые дуги (дуги, у которых одинаковы начальный и конечный узлы).
	void Build(const NodeList& theNodeList, const EdgeList& theEdgeList);

	// Метод добавляет узел theNode в граф. Если в графе уже был узел theNode, ничего не делает.
	// Возвращает true, если узел был добавлен. Иначе возвращает false.
	bool AddNode(const NodeType& theNode);

	// Метод добавляет дугу theNode в граф. Если в графе уже была дуга theEdge, ничего не делает.
	// Возвращает true, если дуга была добавлена. Иначе возвращает false.
	// Если начального или конечного узла дуги нет в списке узлов - то кидает исключение IncorrectGraphException.
	bool AddEdge(const Edge& theEdge);

	// Метод стирает все данные графа
	void Clear();

	// Метод удаляет узел и все дуги, которые содержали данный узел. Если был передан узел, которого нет в графе, ничего не делает.
	// Возвращает true, если удаление было произведено. Иначе возвращает false.
	bool RemoveNode(const NodeType& theNode);

	// Метод удаляет дугу из графа. Если была передана дуга, которой нет в графе, ничего не делает.
	// Возвращает true, если удаление было произведено. Иначе возвращает false.
	bool RemoveEdge(const Edge& theEdge);

	// Метод возвращает истину, если узел содержится в графе. Иначе возвращает ложь.
	bool ContainsNode(const NodeType& theNode) const;

	// Метод возвращает истину, если дуга содержится в графе. Иначе возвращает ложь.
	bool ContainsEdge(const Edge& theEdge) const;

	// Перегрузка оператора вывода для вывода информации о графе в поток.
	friend std::ostream& operator<<(std::ostream& theOut, const Graph<NodeType>& theGraph)
	{
		for (const auto& aKeyValue : theGraph.myAdjacencyMap)
		{
			const NodeType& aKey = aKeyValue.first;
			const Graph<NodeType>::NodeList& aNodeList = aKeyValue.second;

			theOut << aKey << " : {";
			bool aFirstElementWasPrinted = false;
			for (const auto& aNode : aNodeList)
			{
				if (aFirstElementWasPrinted)
				{
					theOut << ", " << aNode;
				}
				else
				{
					theOut << " " << aNode;
					aFirstElementWasPrinted = true;
				}
			}
			theOut << " }" << std::endl;
		}
		return theOut;
	}

	// Метод возвращает true, если граф является связным (то есть из каждой его вершины существует путь в любую другую вершину).
	// Иначе возвращает false.
	bool IsGraphConnected() const;

	// Функция возвращает true, если между узлом theBeginNode и theEndNode существует путь.
	// Иначе возвращает false.
	// Кидает исключение std::invalid_argument, если граф не содержит хотя бы одного из переданных узлов.
	// Примечание 1: Между узлами theBeginNode и theEndNode может не быть прямого путя,
	//               но они могут быть транзитивно связаны через другие узлы.
	// Примечание 2: Методу можно передать одинаковые узлы. При этом он вернет true, если существует петля в переданном узле;
	//               либо существует цикл, включающий переданный узел.
	bool ExistsPathBetweenTwoNodes(const NodeType& theBeginNode, const NodeType& theEndNode) const;

	// Метод возвращает ссылку на std::map, в котором представлены данные графа.
	const GraphMap& GetAdjacencyMap() const { return myAdjacencyMap; }

	// Методы для сравнения графов.
	bool operator==(const Graph& theGraph) const { return myAdjacencyMap == theGraph.myAdjacencyMap; }
	bool operator!=(const Graph& theGraph) const { return !(*this == theGraph); }

public:

	class IncorrectGraphException : public std::exception
	{
	public:
		using std::exception::exception;
	};

private:
	// Функция удаляет дубликаты из списка смежных узлов для каждого узла.
	// Например, для map:
	// A - {B, C, D, C}
	// B - {A, D, D}
	// Функция сделает:
	// A - {B, C, D}
	// B - {A, D}
	void deleteDuplicatesInAdjacencyLists();
	
private:
	GraphMap myAdjacencyMap;
};

//=========================================================
// Function : Graph
// Purpose  : Default constructor
//=========================================================
template <class NodeType>
Graph<NodeType>::Graph() = default;

//=========================================================
// Function : Graph
// Purpose  : Copy constructor
//=========================================================
template <class NodeType>
Graph<NodeType>::Graph(const Graph<NodeType> &) = default;

//=========================================================
// Function : operator=
// Purpose  : Assignment operator
//=========================================================
template <class NodeType>
Graph<NodeType>& Graph<NodeType>::operator=(const Graph<NodeType> &) = default;

//=========================================================
// Function : ~Graph
// Purpose  : Destructor
//=========================================================
template <class NodeType>
Graph<NodeType>::~Graph() = default;

//=========================================================
// Function : Build
// Purpose  : Строит граф по спискам узлов и ребер
//=========================================================
template<class NodeType>
void Graph<NodeType>::Build(const NodeList & theNodeList, const EdgeList & theEdgeList)
{
	for (const auto& aNode : theNodeList)
	{
		myAdjacencyMap[aNode]; // инициализация ключей std::map узлами графа
	}

	// Заполнение значений для ключей std::map
	// (значением является список смежных узлов).
	for (const auto& anEdge : theEdgeList)
	{
		const auto& anEdgeBegin = anEdge.first;
		const auto& anEdgeEnd = anEdge.second;

		if (!ContainsNode(anEdgeBegin) || !ContainsNode(anEdgeEnd))
		{
			// Если узел не найден среди ключей std::map
			throw IncorrectGraphException("Incorrect Node in Edge");
		}
		else
		{
			myAdjacencyMap[anEdgeBegin].push_back(anEdgeEnd);
		}
	}

	deleteDuplicatesInAdjacencyLists();
}

//=========================================================
// Function : AddNode
// Purpose  : Добавляет узел в граф
//=========================================================
template<class NodeType>
bool Graph<NodeType>::AddNode(const NodeType & theNode)
{
	// std::map::insert - "Returns a pair consisting of an iterator to the inserted element
	//                    (or to the element that prevented the insertion)
	//                    and a bool denoting whether the insertion took place".
	// Читай подробности здесь https://en.cppreference.com/w/cpp/container/map/insert
	return myAdjacencyMap.insert({ theNode, {} }).second;
}

//=========================================================
// Function : AddEdge
// Purpose  : Добавляет ребро в граф
//=========================================================
template<class NodeType>
bool Graph<NodeType>::AddEdge(const Edge & theEdge)
{
	const NodeType& anEdgeBegin = theEdge.first;
	const NodeType& anEdgeEnd = theEdge.second;

	if (!ContainsNode(anEdgeBegin) || !ContainsNode(anEdgeEnd))
	{
		// Если узел не найден среди ключей std::map
		throw IncorrectGraphException("Incorrect Node in Edge");
	}
	else
	{
		auto anEdgeBeginIter = myAdjacencyMap.find(anEdgeBegin);
		const NodeList& aNodeList = anEdgeBeginIter->second; // список узлов, смежных с узлом anEdgeBegin
		auto aFoundIter = std::find(aNodeList.cbegin(), aNodeList.cend(), anEdgeEnd);

		bool aNodeIsAlreadyInList = (aFoundIter != aNodeList.cend());

		if (!aNodeIsAlreadyInList)
		{
			myAdjacencyMap[anEdgeBegin].push_back(anEdgeEnd);
			myAdjacencyMap[anEdgeBegin].sort();
		}

		return !aNodeIsAlreadyInList;
	}
}

//=========================================================
// Function : Clear
// Purpose  : Удаление всех данных графа
//=========================================================
template<class NodeType>
void Graph<NodeType>::Clear()
{
	myAdjacencyMap.clear();
}

//=========================================================
// Function : RemoveNode
// Purpose  : Удаление узла из графа
//=========================================================
template<class NodeType>
bool Graph<NodeType>::RemoveNode(const NodeType& theNode)
{
	if (!ContainsNode(theNode))
	{
		// узел не найден в графе
		return false;
	}
	else
	{
		auto aNodeIter = myAdjacencyMap.find(theNode);
		myAdjacencyMap.erase(aNodeIter); // удаление данного узла из графа

		// удаление всех упоминаний данного узла из списков смежных узлов
		for (auto& aKeyValue : myAdjacencyMap)
		{
			NodeList& aNodeList = aKeyValue.second;
			aNodeList.remove(theNode); // удаление всех вхождений theNode в список aNodeList
		}

		return true;
	}
}

//=========================================================
// Function : RemoveEdge
// Purpose  : Удаление дуги из графа.
//=========================================================
template<class NodeType>
bool Graph<NodeType>::RemoveEdge(const Edge& theEdge)
{
	const NodeType& anEdgeBegin = theEdge.first;
	const NodeType& anEdgeEnd = theEdge.second;
	if (!ContainsNode(anEdgeBegin))
	{
		return false;
	}
	else
	{
		auto aNodeIter = myAdjacencyMap.find(anEdgeBegin);
		NodeList& aNodeList = aNodeIter->second; // список узлов, смежных с anEdgeBegin
		auto anEdgeEndIter = std::find(aNodeList.begin(), aNodeList.end(), anEdgeEnd); // поиск узла, соответствующего концу дуги
		if (anEdgeEndIter == aNodeList.end())
		{
			return false;
		}
		else
		{
			aNodeList.erase(anEdgeEndIter);
			return true;
		}
	}
}

//=========================================================
// Function : ContainsNode
// Purpose  : Определяет, содержится ли узел в графе
//=========================================================
template<class NodeType>
bool Graph<NodeType>::ContainsNode(const NodeType& theNode) const
{
	return myAdjacencyMap.find(theNode) != myAdjacencyMap.end();
}

//=========================================================
// Function : IsGraphConnected
// Purpose  : Определяет, является ли граф связным
//=========================================================
template<class NodeType>
bool Graph<NodeType>::IsGraphConnected() const
{
	// заполнение массива всех узлов, которые есть в графе
	std::vector<NodeType> aNodeVector;
	for (const auto& aKeyValue : myAdjacencyMap)
	{
		const NodeType& aNode = aKeyValue.first;
		aNodeVector.push_back(aNode);
	}

	// пустой граф будем считать несвязным
	if (aNodeVector.size() == 0)
		return false;

	// граф, состоящий из одной вершины, будем считать связным
	// (даже если в этой вершине нет петли)
	if (aNodeVector.size() == 1)
		return true;

	// проверка наличия путя между каждой парой вершин
	for (size_t i = 0; i < aNodeVector.size(); ++i)
	{
		for (size_t j = 0; j < aNodeVector.size(); ++j)
		{
			if (!ExistsPathBetweenTwoNodes(aNodeVector[i], aNodeVector[j]))
			{
				return false;
			}
		}
	}
	return true;
}

//=========================================================
// Function : ExistsPathBetweenTwoNodes
// Purpose  : Определяет, существует ли путь между двумя узлами
//=========================================================
template<class NodeType>
bool Graph<NodeType>::ExistsPathBetweenTwoNodes(const NodeType& theBeginNode, const NodeType& theEndNode) const
{
	if (!ContainsNode(theBeginNode) || !ContainsNode(theEndNode))
	{
		throw std::invalid_argument("Graph does not contain at least one of given nodes");
	}

	// копия myAdjacencyMap за тем исключением, что значение ключа состоит также из счетчика int.
	// Этот счетчиик обозначает, сколько раз мы уже посещали данный узел.
	// Изначально этот счетчик инициализируется в 0.
	std::map<NodeType, std::pair<NodeList, int>> aMap;
	for (const auto& aKeyValue : myAdjacencyMap)
	{
		const NodeType& aKey   = aKeyValue.first;
		const NodeList& aValue = aKeyValue.second;

		aMap[aKey] = std::make_pair(aValue, 0);
	}

	std::queue<NodeType> aNodeQueue; // очередь узлов на посещение
	aNodeQueue.push(theBeginNode); // первый узел специально не помечаем

	bool anIsFirstIteration = true;

	// обход графа в ширину
	while (!aNodeQueue.empty())
	{
		const NodeType& aCurrentNode = aNodeQueue.front();
		if (!anIsFirstIteration && aCurrentNode == theEndNode)
		{
			// конечный узел найден и текущая итерация не является первой итерацией
			// (на первой итерации мы достаем из очереди единственный узел, который поместили до цикла,
			//  так что данный узел не может быть конечным узлом, который мы ищем путем обхода графа в ширину)
			return true;
		}
		aMap[aCurrentNode].second += 1;
		const NodeList& aNodeList = aMap[aCurrentNode].first; // список узлов смежных с текущим
		for (const auto& aNode : aNodeList)
		{
			int& aNodeVisitedCounter = aMap[aNode].second;
			if (aNodeVisitedCounter < 2)
			{
				aNodeQueue.push(aNode);
			}
		}

		aNodeQueue.pop();
		if (anIsFirstIteration)
		{
			anIsFirstIteration = false;
		}
	}
	return false;
}

//=========================================================
// Function : deleteDuplicatesInAdjacencyLists
// Purpose  : Удаление дубликатов из списков смежных узлов
//=========================================================
template<class NodeType>
void Graph<NodeType>::deleteDuplicatesInAdjacencyLists()
{
	for (auto anIter = myAdjacencyMap.begin(); anIter != myAdjacencyMap.end(); ++anIter)
	{
		auto& aNodeList = anIter->second;

		// Удаление дубликатов в каждом списке
		// Читай https://en.cppreference.com/w/cpp/container/list/unique для подробностей
		aNodeList.sort(); // сортировка списка
		aNodeList.unique();
	}
}
