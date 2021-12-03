#pragma once

#include <iostream>
#include <map>
#include <list>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>

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
	                                                           

	// Метод строит граф по списку узлов и списку дуг.
	// - Метод бросает исключение, если была передана дуга такая, что какой-нибудь её узел не входит в список узлов
	//  (Например, для списков {A, B} и {(A, B), (B, C)}) бросится исключение, потому что дуга (B, C) содержит узел C, который не входит в список {A, B}
	// - Метод игнорирует одинаковые узлы и одинаковые дуги (дуги, у которых одинаковы начальный и конечный узлы).
	void Build(const NodeList& theNodeList, const EdgeList& theEdgeList);

	// Метод добавляет узел theNode в граф. Если в графе уже был узел theNode, ничего не делает.
	// Возвращает true, если узел был добавлен. Иначе возвращает false.
	bool AddNode(const NodeType& theNode);

	// Метод добавляет дугу theNode в граф. Если в графе уже была дуга theEdge, ничего не делает.
	// Возвращает true, если дуга была добавлена. Иначе возвращает false.
	// Если начального или конечного узла дуги нет в списке узлов - то кидает исключение.
	bool AddEdge(const Edge& theEdge);

	// Метод стирает все данные графа
	void Clear();

	// Метод удаляет узел и все дуги, которые содержали данный узел. Если был передан узел, которого нет в графе, ничего не делает.
	// Возвращает true, если удаление было произведено. Иначе возвращает false.
	bool RemoveNode(const NodeType& theNode);

	// Метод удаляет дугу из графа. Если была передана дуга, которой нет в графе, ничего не делает.
	// Возвращает true, если удаление было произведено. Иначе возвращает false.
	bool RemoveEdge(const Edge& theEdge);

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
	// Примечание 1: Между узлами theBeginNode и theEndNode может не быть прямого путя,
	//               но они могут быть транзитивно связаны через другие узлы.
	// Примечание 2: Методу можно передать одинаковые узлы. При этом он вернет true, если существует петля в переданном узле;
	//               либо существует цикл, включающий переданный узел.
	bool ExistsPathBetweenTwoNodes(const NodeType& theBeginNode, const NodeType& theEndNode) const;

	std::map<NodeType, NodeList> GetAdjacencyMap() const;

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
	std::map<NodeType, NodeList> myAdjacencyMap;
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

		if (myAdjacencyMap.find(anEdgeBegin) == myAdjacencyMap.end() ||
			myAdjacencyMap.find(anEdgeEnd) == myAdjacencyMap.end())
		{
			// Если узел не найден среди ключей std::map
			throw std::runtime_error("Incorrect Node in Edge");
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
	return myAdjacencyMap.insert(theNode).second;
}

//=========================================================
// Function : AddEdge
// Purpose  : Добавляет ребро в граф
//=========================================================
template<class NodeType>
bool Graph<NodeType>::AddEdge(const Edge & theEdge)
{

	bool aFunctionResult = false;

	const NodeType& anEdgeBegin = theEdge.first;
	const NodeType& anEdgeEnd = theEdge.second;

	auto anEdgeBeginIter = myAdjacencyMap.find(anEdgeBegin);
	auto anEdgeEndIter = myAdjacencyMap.find(anEdgeEnd);
	if (anEdgeBeginIter == myAdjacencyMap.end() ||
		anEdgeEndIter == myAdjacencyMap.end())
	{
		// Если узел не найден среди ключей std::map
		throw std::runtime_error("Incorrect Node in Edge");
	}
	else
	{
		const NodeList& aNodeList = anEdgeBeginIter->second; // список узлов, смежных с узлом anEdgeBegin
		auto aFoundIter = std::find(aNodeList.cbegin(), aNodeList.cend(), anEdgeEnd);

		bool aNodeIsAlreadyInList = (aFoundIter != aNodeList.cend());

		if (!aNodeIsAlreadyInList)
		{
			myAdjacencyMap[anEdgeBegin].push_back(anEdgeEnd);
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
	auto aNodeIter = myAdjacencyMap.find(theNode);
	if (aNodeIter == myAdjacencyMap.end())
	{
		// узел не найден в графе
		return false;
	}
	else
	{
		myAdjacencyMap.erase(aNodeIter); // удаление данного узла из графа

		// удаление всех упоминаний данного узла из списков смежных узлов
		for (auto aKeyValue : myAdjacencyMap)
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
	auto aNodeIter = myAdjacencyMap.find(anEdgeBegin);
	if (aNodeIter == myAdjacencyMap.end())
	{
		return false;
	}
	else
	{
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

	// проверка наличия путя между каждой парой вершин
	for (int i = 0; i < aNodeVector.size(); ++i)
	{
		for (int j = 0; j < aNodeVector.size(); ++j)
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
	// копия myAdjacencyMap за тем исключением, что значение ключа состоит также из флага.
	// Этот флаг обозначает, посещали ли мы уже данный узел или нет.
	// Изначально этот флаг инициализируется в false.
	std::map<NodeType, std::pair<EdgeList, bool>> aMap;
	for (const auto& aKeyValue : myAdjacencyMap)
	{
		const NodeType& aKey = aKey.first;
		const EdgeList& aValue = aKey.second;

		aMap[aKey] = std::make_pair(aValue, false);
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
		aMap[aCurrentNode].second = true;
		const NodeList& aNodeList = aMap[aCurrentNode].first; // список узлов смежных с текущим
		for (const auto& aNode : aNodeList)
		{
			bool& anIsNodeVisited = aMap[aNode].second;
			if (anIsNodeVisited == false)
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
