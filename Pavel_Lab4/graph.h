#pragma once

#include <iostream>
#include <map>
#include <list>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
#include <exception>

// ����� �����, ������ � ������� �������� � ������ ���������.
// ���� ����� ��������� ����� � �����.
template <class NodeType>
class Graph
{
public:
	Graph();
	Graph(const Graph&);
	Graph& operator=(const Graph&);
	~Graph();

	typedef std::list<NodeType> NodeList; // ������ ����� (������� �������� ���� NodeType).
	typedef std::pair<NodeType, NodeType> Edge; // ���� (���� ����� �����, ��� ������ ������� - ������ ����,
	                                            // � ������ ������� - ����� ����).
	                                            // ����� ����� ���������� ������������ ����� �� ������ ���� � ������.
	typedef std::list<Edge> EdgeList; // ������ ���.
	
	typedef std::map<NodeType, NodeList> GraphMap; // ������� ����, � ������� �������� ������ �����

	// ����� ������ ���� �� ������ ����� � ������ ���.
	// - ����� ������� ���������� IncorrectGraphException, ���� ���� �������� ���� �����,
	//   ��� �����-������ � ���� �� ������ � ������ �����
	//  (��������, ��� ������� {A, B} � {(A, B), (B, C)}) �������� ����������, ������ ��� ���� (B, C) �������� ���� C, ������� �� ������ � ������ {A, B}
	// - ����� ���������� ���������� ���� � ���������� ���� (����, � ������� ��������� ��������� � �������� ����).
	void Build(const NodeList& theNodeList, const EdgeList& theEdgeList);

	// ����� ��������� ���� theNode � ����. ���� � ����� ��� ��� ���� theNode, ������ �� ������.
	// ���������� true, ���� ���� ��� ��������. ����� ���������� false.
	bool AddNode(const NodeType& theNode);

	// ����� ��������� ���� theNode � ����. ���� � ����� ��� ���� ���� theEdge, ������ �� ������.
	// ���������� true, ���� ���� ���� ���������. ����� ���������� false.
	// ���� ���������� ��� ��������� ���� ���� ��� � ������ ����� - �� ������ ���������� IncorrectGraphException.
	bool AddEdge(const Edge& theEdge);

	// ����� ������� ��� ������ �����
	void Clear();

	// ����� ������� ���� � ��� ����, ������� ��������� ������ ����. ���� ��� ������� ����, �������� ��� � �����, ������ �� ������.
	// ���������� true, ���� �������� ���� �����������. ����� ���������� false.
	bool RemoveNode(const NodeType& theNode);

	// ����� ������� ���� �� �����. ���� ���� �������� ����, ������� ��� � �����, ������ �� ������.
	// ���������� true, ���� �������� ���� �����������. ����� ���������� false.
	bool RemoveEdge(const Edge& theEdge);

	// ����� ���������� ������, ���� ���� ���������� � �����. ����� ���������� ����.
	bool ContainsNode(const NodeType& theNode) const;

	// ����� ���������� ������, ���� ���� ���������� � �����. ����� ���������� ����.
	bool ContainsEdge(const Edge& theEdge) const;

	// ���������� ��������� ������ ��� ������ ���������� � ����� � �����.
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

	// ����� ���������� true, ���� ���� �������� ������� (�� ���� �� ������ ��� ������� ���������� ���� � ����� ������ �������).
	// ����� ���������� false.
	bool IsGraphConnected() const;

	// ������� ���������� true, ���� ����� ����� theBeginNode � theEndNode ���������� ����.
	// ����� ���������� false.
	// ������ ���������� std::invalid_argument, ���� ���� �� �������� ���� �� ������ �� ���������� �����.
	// ���������� 1: ����� ������ theBeginNode � theEndNode ����� �� ���� ������� ����,
	//               �� ��� ����� ���� ����������� ������� ����� ������ ����.
	// ���������� 2: ������ ����� �������� ���������� ����. ��� ���� �� ������ true, ���� ���������� ����� � ���������� ����;
	//               ���� ���������� ����, ���������� ���������� ����.
	bool ExistsPathBetweenTwoNodes(const NodeType& theBeginNode, const NodeType& theEndNode) const;

	// ����� ���������� ������ �� std::map, � ������� ������������ ������ �����.
	const GraphMap& GetAdjacencyMap() const { return myAdjacencyMap; }

	// ������ ��� ��������� ������.
	bool operator==(const Graph& theGraph) const { return myAdjacencyMap == theGraph.myAdjacencyMap; }
	bool operator!=(const Graph& theGraph) const { return !(*this == theGraph); }

public:

	class IncorrectGraphException : public std::exception
	{
	public:
		using std::exception::exception;
	};

private:
	// ������� ������� ��������� �� ������ ������� ����� ��� ������� ����.
	// ��������, ��� map:
	// A - {B, C, D, C}
	// B - {A, D, D}
	// ������� �������:
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
// Purpose  : ������ ���� �� ������� ����� � �����
//=========================================================
template<class NodeType>
void Graph<NodeType>::Build(const NodeList & theNodeList, const EdgeList & theEdgeList)
{
	for (const auto& aNode : theNodeList)
	{
		myAdjacencyMap[aNode]; // ������������� ������ std::map ������ �����
	}

	// ���������� �������� ��� ������ std::map
	// (��������� �������� ������ ������� �����).
	for (const auto& anEdge : theEdgeList)
	{
		const auto& anEdgeBegin = anEdge.first;
		const auto& anEdgeEnd = anEdge.second;

		if (!ContainsNode(anEdgeBegin) || !ContainsNode(anEdgeEnd))
		{
			// ���� ���� �� ������ ����� ������ std::map
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
// Purpose  : ��������� ���� � ����
//=========================================================
template<class NodeType>
bool Graph<NodeType>::AddNode(const NodeType & theNode)
{
	// std::map::insert - "Returns a pair consisting of an iterator to the inserted element
	//                    (or to the element that prevented the insertion)
	//                    and a bool denoting whether the insertion took place".
	// ����� ����������� ����� https://en.cppreference.com/w/cpp/container/map/insert
	return myAdjacencyMap.insert({ theNode, {} }).second;
}

//=========================================================
// Function : AddEdge
// Purpose  : ��������� ����� � ����
//=========================================================
template<class NodeType>
bool Graph<NodeType>::AddEdge(const Edge & theEdge)
{
	const NodeType& anEdgeBegin = theEdge.first;
	const NodeType& anEdgeEnd = theEdge.second;

	if (!ContainsNode(anEdgeBegin) || !ContainsNode(anEdgeEnd))
	{
		// ���� ���� �� ������ ����� ������ std::map
		throw IncorrectGraphException("Incorrect Node in Edge");
	}
	else
	{
		auto anEdgeBeginIter = myAdjacencyMap.find(anEdgeBegin);
		const NodeList& aNodeList = anEdgeBeginIter->second; // ������ �����, ������� � ����� anEdgeBegin
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
// Purpose  : �������� ���� ������ �����
//=========================================================
template<class NodeType>
void Graph<NodeType>::Clear()
{
	myAdjacencyMap.clear();
}

//=========================================================
// Function : RemoveNode
// Purpose  : �������� ���� �� �����
//=========================================================
template<class NodeType>
bool Graph<NodeType>::RemoveNode(const NodeType& theNode)
{
	if (!ContainsNode(theNode))
	{
		// ���� �� ������ � �����
		return false;
	}
	else
	{
		auto aNodeIter = myAdjacencyMap.find(theNode);
		myAdjacencyMap.erase(aNodeIter); // �������� ������� ���� �� �����

		// �������� ���� ���������� ������� ���� �� ������� ������� �����
		for (auto& aKeyValue : myAdjacencyMap)
		{
			NodeList& aNodeList = aKeyValue.second;
			aNodeList.remove(theNode); // �������� ���� ��������� theNode � ������ aNodeList
		}

		return true;
	}
}

//=========================================================
// Function : RemoveEdge
// Purpose  : �������� ���� �� �����.
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
		NodeList& aNodeList = aNodeIter->second; // ������ �����, ������� � anEdgeBegin
		auto anEdgeEndIter = std::find(aNodeList.begin(), aNodeList.end(), anEdgeEnd); // ����� ����, ���������������� ����� ����
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
// Purpose  : ����������, ���������� �� ���� � �����
//=========================================================
template<class NodeType>
bool Graph<NodeType>::ContainsNode(const NodeType& theNode) const
{
	return myAdjacencyMap.find(theNode) != myAdjacencyMap.end();
}

//=========================================================
// Function : IsGraphConnected
// Purpose  : ����������, �������� �� ���� �������
//=========================================================
template<class NodeType>
bool Graph<NodeType>::IsGraphConnected() const
{
	// ���������� ������� ���� �����, ������� ���� � �����
	std::vector<NodeType> aNodeVector;
	for (const auto& aKeyValue : myAdjacencyMap)
	{
		const NodeType& aNode = aKeyValue.first;
		aNodeVector.push_back(aNode);
	}

	// ������ ���� ����� ������� ���������
	if (aNodeVector.size() == 0)
		return false;

	// ����, ��������� �� ����� �������, ����� ������� �������
	// (���� ���� � ���� ������� ��� �����)
	if (aNodeVector.size() == 1)
		return true;

	// �������� ������� ���� ����� ������ ����� ������
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
// Purpose  : ����������, ���������� �� ���� ����� ����� ������
//=========================================================
template<class NodeType>
bool Graph<NodeType>::ExistsPathBetweenTwoNodes(const NodeType& theBeginNode, const NodeType& theEndNode) const
{
	if (!ContainsNode(theBeginNode) || !ContainsNode(theEndNode))
	{
		throw std::invalid_argument("Graph does not contain at least one of given nodes");
	}

	// ����� myAdjacencyMap �� ��� �����������, ��� �������� ����� ������� ����� �� �������� int.
	// ���� �������� ����������, ������� ��� �� ��� �������� ������ ����.
	// ���������� ���� ������� ���������������� � 0.
	std::map<NodeType, std::pair<NodeList, int>> aMap;
	for (const auto& aKeyValue : myAdjacencyMap)
	{
		const NodeType& aKey   = aKeyValue.first;
		const NodeList& aValue = aKeyValue.second;

		aMap[aKey] = std::make_pair(aValue, 0);
	}

	std::queue<NodeType> aNodeQueue; // ������� ����� �� ���������
	aNodeQueue.push(theBeginNode); // ������ ���� ���������� �� ��������

	bool anIsFirstIteration = true;

	// ����� ����� � ������
	while (!aNodeQueue.empty())
	{
		const NodeType& aCurrentNode = aNodeQueue.front();
		if (!anIsFirstIteration && aCurrentNode == theEndNode)
		{
			// �������� ���� ������ � ������� �������� �� �������� ������ ���������
			// (�� ������ �������� �� ������� �� ������� ������������ ����, ������� ��������� �� �����,
			//  ��� ��� ������ ���� �� ����� ���� �������� �����, ������� �� ���� ����� ������ ����� � ������)
			return true;
		}
		aMap[aCurrentNode].second += 1;
		const NodeList& aNodeList = aMap[aCurrentNode].first; // ������ ����� ������� � �������
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
// Purpose  : �������� ���������� �� ������� ������� �����
//=========================================================
template<class NodeType>
void Graph<NodeType>::deleteDuplicatesInAdjacencyLists()
{
	for (auto anIter = myAdjacencyMap.begin(); anIter != myAdjacencyMap.end(); ++anIter)
	{
		auto& aNodeList = anIter->second;

		// �������� ���������� � ������ ������
		// ����� https://en.cppreference.com/w/cpp/container/list/unique ��� ������������
		aNodeList.sort(); // ���������� ������
		aNodeList.unique();
	}
}
