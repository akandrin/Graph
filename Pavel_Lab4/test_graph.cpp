#include "pch.h"

#include "graph.h"
#include "gtest.h"

#include <string>
#include <iostream>
#include <sstream>

// Used to draw graphs - https://asciiflow.com/

namespace
{
	using IntGraph = Graph<int>;
	using StringGraph = Graph<std::string>;

	template<class NodeType>
	std::string GetInfo(const Graph<NodeType>& theGraph)
	{
		std::stringstream aStrOut;
		aStrOut << theGraph;
		return aStrOut.str();
	}
}

TEST(Graph, can_create_graph)
{
	ASSERT_NO_THROW(IntGraph());
}

TEST(Graph, can_build_correct_graph)
{
/*


        ┌───┐
        │ c │
        └───┘
          ▲
          │
┌───┐   ┌─┴─┐
│ a ├──>│ b │
└───┘   └─┬─┘
  ▲       │
  │       │
  │       ▼
  │     ┌───┐
  └─────┤ d │
        └───┘

*/
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_EQ(GetInfo(aGraph), "a : { b }\nb : { c, d }\nc : { }\nd : { a }\n");
}
