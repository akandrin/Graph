#pragma once

#include <iostream>
#include <map>
#include <list>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>

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
	                                                           

	// ����� ������ ���� �� ������ ����� � ������ ���.
	// - ����� ������� ����������, ���� ���� �������� ���� �����, ��� �����-������ � ���� �� ������ � ������ �����
	//  (��������, ��� ������� {A, B} � {(A, B), (B, C)}) �������� ����������, ������ ��� ���� (B, C) �������� ���� C, ������� �� ������ � ������ {A, B}
	// - ����� ���������� ���������� ���� � ���������� ���� (����, � ������� ��������� ��������� � �������� ����).
	void Build(const NodeList& theNodeList, const EdgeList& theEdgeList);

	// ����� ��������� ���� theNode � ����. ���� � ����� ��� ��� ���� theNode, ������ �� ������.
	// ���������� true, ���� ���� ��� ��������. ����� ���������� false.
	bool AddNode(const NodeType& theNode);

	// ����� ��������� ���� theNode � ����. ���� � ����� ��� ���� ���� theEdge, ������ �� ������.
	// ���������� true, ���� ���� ���� ���������. ����� ���������� false.
	// ���� ���������� ��� ��������� ���� ���� ��� � ������ ����� - �� ������ ����������.
	bool AddEdge(const Edge& theEdge);

	// ����� ������� ��� ������ �����
	void Clear();

	// ����� ������� ���� � ��� ����, ������� ��������� ������ ����. ���� ��� ������� ����, �������� ��� � �����, ������ �� ������.
	// ���������� true, ���� �������� ���� �����������. ����� ���������� false.
	bool RemoveNode(const NodeType& theNode);

	// ����� ������� ���� �� �����. ���� ���� �������� ����, ������� ��� � �����, ������ �� ������.
	// ���������� true, ���� �������� ���� �����������. ����� ���������� false.
	bool RemoveEdge(const Edge& theEdge);

	// ���������� ��������� ������ ��� ������ ���������� � ����� � �����.
	friend std::ostream& operator<<(std::ostream& theOut, const Graph<NodeType>& theGraph)
	{
		for (const auto& aKeyValue : theGraph.myAdjacencyList)
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
	// ���������� 1: ����� ������ theBeginNode � theEndNode ����� �� ���� ������� ����,
	//               �� ��� ����� ���� ����������� ������� ����� ������ ����.
	// ���������� 2: ������ ����� �������� ���������� ����. ��� ���� �� ������ true, ���� ���������� ����� � ���������� ����;
	//               ���� ���������� ����, ���������� ���������� ����.
	bool ExistsPathBetweenTwoNodes(const NodeType& theBeginNode, const NodeType& theEndNode) const;

private:
	// ������� ������� ��������� �� ������ ������� ����� ��� ������� ����.
	// ��������, ��� map:
	// A - {B, C, D, C}
	// B - {A, D, D}
	// ������� �������:
	// A - {B, C, D}
	// B - {A, D}
	void deleteDuplicatesInAdjencyLists();
	
private:
	std::map<NodeType, NodeList> myAdjacencyList;
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
		myAdjacencyList[aNode]; // ������������� ������ std::map ������ �����
	}

	// ���������� �������� ��� ������ std::map
	// (��������� �������� ������ ������� �����).
	for (const auto& anEdge : theEdgeList)
	{
		const auto& anEdgeBegin = anEdge.first;
		const auto& anEdgeEnd = anEdge.second;

		if (myAdjacencyList.find(anEdgeBegin) == myAdjacencyList.end() ||
			myAdjacencyList.find(anEdgeEnd) == myAdjacencyList.end())
		{
			// ���� ���� �� ������ ����� ������ std::map
			throw std::runtime_error("Incorrect Node in Edge");
		}
		else
		{
			myAdjacencyList[anEdgeBegin].push_back(anEdgeEnd);
		}
	}

	deleteDuplicatesInAdjencyLists();
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
	return myAdjacencyList.insert(theNode).second;
}

//=========================================================
// Function : AddEdge
// Purpose  : ��������� ����� � ����
//=========================================================
template<class NodeType>
bool Graph<NodeType>::AddEdge(const Edge & theEdge)
{

	bool aFunctionResult = false;

	const NodeType& anEdgeBegin = theEdge.first;
	const NodeType& anEdgeEnd = theEdge.second;

	auto anEdgeBeginIter = myAdjacencyList.find(anEdgeBegin);
	auto anEdgeEndIter = myAdjacencyList.find(anEdgeEnd);
	if (anEdgeBeginIter == myAdjacencyList.end() ||
		anEdgeEndIter == myAdjacencyList.end())
	{
		// ���� ���� �� ������ ����� ������ std::map
		throw std::runtime_error("Incorrect Node in Edge");
	}
	else
	{
		const NodeList& aNodeList = anEdgeBeginIter->second; // ������ �����, ������� � ����� anEdgeBegin
		auto aFoundIter = std::find(aNodeList.cbegin(), aNodeList.cend(), anEdgeEnd);

		bool aNodeIsAlreadyInList = (aFoundIter != aNodeList.cend());

		if (!aNodeIsAlreadyInList)
		{
			myAdjacencyList[anEdgeBegin].push_back(anEdgeEnd);
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
	myAdjacencyList.clear();
}

//=========================================================
// Function : RemoveNode
// Purpose  : �������� ���� �� �����
//=========================================================
template<class NodeType>
bool Graph<NodeType>::RemoveNode(const NodeType& theNode)
{
	auto aNodeIter = myAdjacencyList.find(theNode);
	if (aNodeIter == myAdjacencyList.end())
	{
		// ���� �� ������ � �����
		return false;
	}
	else
	{
		myAdjacencyList.erase(aNodeIter); // �������� ������� ���� �� �����

		// �������� ���� ���������� ������� ���� �� ������� ������� �����
		for (auto aKeyValue : myAdjacencyList)
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
	auto aNodeIter = myAdjacencyList.find(anEdgeBegin);
	if (aNodeIter == myAdjacencyList.end())
	{
		return false;
	}
	else
	{
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
// Function : IsGraphConnected
// Purpose  : ����������, �������� �� ���� �������
//=========================================================
template<class NodeType>
bool Graph<NodeType>::IsGraphConnected() const
{
	// ���������� ������� ���� �����, ������� ���� � �����
	std::vector<NodeType> aNodeVector;
	for (const auto& aKeyValue : myAdjacencyList)
	{
		const NodeType& aNode = aKeyValue.first;
		aNodeVector.push_back(aNode);
	}

	// �������� ������� ���� ����� ������ ����� ������
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
// Purpose  : ����������, ���������� �� ���� ����� ����� ������
//=========================================================
template<class NodeType>
bool Graph<NodeType>::ExistsPathBetweenTwoNodes(const NodeType& theBeginNode, const NodeType& theEndNode) const
{
	// ����� myAdjencyMap �� ��� �����������, ��� �������� ����� ������� ����� �� �����.
	// ���� ���� ����������, �������� �� �� ��� ������ ���� ��� ���.
	// ���������� ���� ���� ���������������� � false.
	std::map<NodeType, std::pair<EdgeList, bool>> aMap;
	for (const auto& aKeyValue : myAdjacencyList)
	{
		const NodeType& aKey = aKey.first;
		const EdgeList& aValue = aKey.second;

		aMap[aKey] = std::make_pair(aValue, false);
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
		aMap[aCurrentNode].second = true;
		const NodeList& aNodeList = aMap[aCurrentNode].first; // ������ ����� ������� � �������
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
// Function : deleteDuplicatesInAdjencyLists
// Purpose  : �������� ���������� �� ������� ������� �����
//=========================================================
template<class NodeType>
void Graph<NodeType>::deleteDuplicatesInAdjencyLists()
{
	for (auto anIter = myAdjacencyList.begin(); anIter != myAdjacencyList.end(); ++anIter)
	{
		auto& aNodeList = anIter->second;

		// �������� ���������� � ������ ������
		// ����� https://en.cppreference.com/w/cpp/container/list/unique ��� ������������
		aNodeList.sort(); // ���������� ������
		aNodeList.unique();
	}
}
