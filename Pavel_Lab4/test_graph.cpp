#include "pch.h"

#include "graph.h"
#include "gtest.h"

#include <string>
#include <iostream>
#include <sstream>

// Использовалось для рисования графиков - https://asciiflow.com/

/*
       Граф 1

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

/*
	   Граф 2

		┌───┐
		│ c │
		└───┘
		  ▲
		  │
┌───┐   ┌─┴─┐     ┌───┐
│ a ├──>│ b │	  │ e │
└───┘   └─┬─┘	  └───┘
  ▲       │
  │       │
  │       ▼
  │     ┌───┐
  └─────┤ d │
		└───┘

*/

/*
	   Граф 3

				┌───┐
				│ c │
				└───┘
				  ▲
	 ┌────┐		  │       ┌────┐	
	 │    ▼       │		  │    ▼  
	 │	┌───┐   ┌─┴─┐     │	 ┌───┐
     └──┤ a ├──>│ b │	  └──┤ e │
		└───┘   └─┬─┘	  	 └───┘
		  ▲       │
		  │       │
		  │       ▼
		  │     ┌───┐
		  └─────┤ d │
				└───┘

*/

/*
	   Граф 3

				┌───┐
				│ c │
				└───┘
				  ▲
	 ┌────┐		  │       ┌────┐
	 │    ▼       │		  │    ▼
	 │	┌───┐   ┌─┴─┐     │	 ┌───┐    ┌───┐
	 └──┤ a ├──>│ b │	  └──┤ e │	  │ f │
		└───┘   └─┬─┘	  	 └───┘	  └───┘
		  ▲       │
		  │       │
		  │       ▼
		  │     ┌───┐
		  └─────┤ d │
				└───┘

*/

/*
           Граф 5.


			┌─────┐      ┌─────┐
			│     ├─────►│     │
   ┌───────►│  b  │      │  c  │◄─────┐
   │        └─────┘  ┌───┴┬────┘      │
   │                 │    │ ▲         │
   │                 │    │ │         │
   │                 │    │ │         │
┌──┴─┐               │    │ │      ┌──┴─┐
│    │◄──────────────┘    │ │      │    │
│  a │                    │ │      │  f │
└──┬─┘       ┌────────────┘ │      └────┘
   │         │              │         ▲
   │         │              │         │
   │         ▼              │         │
   │      ┌────┐         ┌──┴──┐      │
   │      │    │         │     │      │
   └─────►│  d ├────────►│  e  ├──────┘
		  └────┘         └─────┘


*/

/*

         Граф 6.

		 ┌───┐
		 │ a │
		 └───┘

*/

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
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
	{
		{"a", {"b"}},
		{"b", {"c", "d"}},
		{"c", {}},
		{"d", {"a"}}
	}));
}

TEST(Graph, throws_when_build_incorrect_graph)
{
	StringGraph aGraph;
	ASSERT_ANY_THROW(aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "e"}, {"b", "d"}, {"d", "a"} }));
	// Граф не содержит узел "e", но "e" содержится в списке дуг.
}

TEST(Graph, can_add_node_to_empty_graph)
{
	StringGraph aGraph;
	aGraph.AddNode("a");
	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {}}
		}));
}

TEST(Graph, adding_node_to_empty_graph_returns_true)
{
	StringGraph aGraph;
	ASSERT_TRUE(aGraph.AddNode("a"));
}

TEST(Graph, can_add_node_that_is_not_in_the_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.AddNode("e");
	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {"b"}},
			{"b", {"c", "d"}},
			{"c", {}},
			{"d", {"a"}},
			{"e", {}}
		}));
}

TEST(Graph, adding_node_to_graph_that_does_not_have_this_node_returns_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.AddNode("e"));
}

TEST(Graph, can_not_add_node_that_is_not_in_the_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.AddNode("a");
	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {"b"}},
			{"b", {"c", "d"}},
			{"c", {}},
			{"d", {"a"}}
		}));
}

TEST(Graph, adding_node_to_graph_that_contains_this_node_returns_false)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.AddNode("a"));
}

TEST(Graph, can_add_edge_to_node_that_does_not_have_adjacent_nodes)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.AddEdge({"c", "a"});
	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {"b"}},
			{"b", {"c", "d"}},
			{"c", {"a"}},
			{"d", {"a"}}
		}));
}

TEST(Graph, adding_edge_to_node_that_does_not_have_adjacent_nodes_returns_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.AddEdge({"c", "a"}));
}

TEST(Graph, can_add_edge_to_node_that_already_has_adjacent_nodes)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.AddEdge({ "b", "a" });
	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {"b"}},
			{"b", {"a", "c", "d"}},
			{"c", {}},
			{"d", {"a"}}
		}));
}

TEST(Graph, adding_edge_to_graph_that_does_not_have_this_node_returns_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.AddEdge({ "b", "a" }));
}

TEST(Graph, can_not_add_edge_that_is_already_in_the_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.AddEdge({ "a", "b" });
	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {"b"}},
			{"b", {"c", "d"}},
			{"c", {}},
			{"d", {"a"}}
		}));
}

TEST(Graph, adding_edge_that_is_already_in_the_graph_returns_false)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.AddEdge({ "a", "b" }));
}

TEST(Graph, throws_when_add_incorrect_edge)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_ANY_THROW(aGraph.AddEdge({ "a", "e" }));
}

TEST(Graph, graphs_constructed_in_different_ways_are_the_same)
{
	// Граф 1 строится разными способами
	StringGraph aGraph1;
	aGraph1.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	
	StringGraph aGraph2;
	aGraph2.AddNode("a");
	aGraph2.AddNode("b");
	aGraph2.AddNode("c");
	aGraph2.AddNode("d");

	aGraph2.AddEdge({ "a", "b" });
	aGraph2.AddEdge({ "b", "c" });
	aGraph2.AddEdge({ "b", "d" });
	aGraph2.AddEdge({ "d", "a" });

	ASSERT_EQ(aGraph1, aGraph2);
}

TEST(Graph, can_clear_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.Clear();
	ASSERT_EQ(aGraph, StringGraph());
}

TEST(Graph, can_remove_node_that_has_no_adjacent_nodes)
{
	// Используется граф 1.
	StringGraph aGraph1;
	aGraph1.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });

	// Используется граф 2.
	StringGraph aGraph2;
	aGraph2.Build({ "a", "b", "c", "d", "e" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph2.RemoveNode("e");
	ASSERT_EQ(aGraph1, aGraph2);
}

TEST(Graph, can_remove_node_that_has_incomming_connections)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.RemoveNode("c");

	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {"b"}},
			{"b", {"d"}},
			{"d", {"a"}}
		}));
}

TEST(Graph, can_remove_node_that_has_outgoing_connections)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.RemoveNode("a");

	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"b", {"c", "d"}},
			{"c", {}},
			{"d", {}}
		}));
}

TEST(Graph, can_remove_node_that_has_incomming_and_outgoing_connections)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.RemoveNode("b");

	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {}},
			{"c", {}},
			{"d", {"a"}}
		}));
}

TEST(Graph, removal_of_node_that_has_incomming_connections_returs_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.RemoveNode("c"));
}

TEST(Graph, removal_of_node_that_has_outgoing_connections)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.RemoveNode("a"));
}

TEST(Graph, removal_of_node_that_has_incomming_and_outgoing_connections)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.RemoveNode("b"));
}

TEST(Graph, can_not_remove_node_that_is_not_contained_in_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.RemoveNode("e");

	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {"b"}},
			{"b", {"c","d"}},
			{"c", {}},
			{"d", {"a"}}
		}));
}

TEST(Graph, removal_of_node_that_is_not_contained_in_graph_returns_false)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.RemoveNode("e"));
}

TEST(Graph, can_remove_edge_that_is_contained_in_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.RemoveEdge({ "b", "c" });

	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {"b"}},
			{"b", {"d"}},
			{"c", {}},
			{"d", {"a"}}
		}));
}

TEST(Graph, can_not_remove_edge_that_is_not_contained_in_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.RemoveEdge({ "a", "d" });

	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {"b"}},
			{"b", {"c", "d"}},
			{"c", {}},
			{"d", {"a"}}
		}));
}

TEST(Graph, can_not_remove_incorrect_edge)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.RemoveEdge({ "a", "e" });

	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {"b"}},
			{"b", {"c", "d"}},
			{"c", {}},
			{"d", {"a"}}
		}));
}

TEST(Graph, removal_of_edge_that_is_contained_in_graph_returns_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.RemoveEdge({ "b", "c" }));
}

TEST(Graph, removal_of_edge_that_is_not_contained_in_graph_retunrs_false)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.RemoveEdge({ "a", "d" }));
}

TEST(Graph, removal_of_incorrect_edge)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.RemoveEdge({ "a", "e" }));
}

TEST(Graph, can_output_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_EQ(GetInfo(aGraph), "a : { b }\nb : { c, d }\nc : { }\nd : { a }\n");
}

TEST(Graph, compare_equal_graphs_returns_true)
{
	// Используется граф 1.
	StringGraph aGraph1;
	aGraph1.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });

	// Используется граф 2.
	StringGraph aGraph2;
	aGraph2.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph1 == aGraph2 && !(aGraph1 != aGraph2));
}

TEST(Graph, compare_different_graphs_returns_false)
{
	// Используется граф 1.
	StringGraph aGraph1;
	aGraph1.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });

	// Используется граф 2.
	StringGraph aGraph2;
	aGraph2.Build({ "a", "b", "c", "d", "e" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph1 == aGraph2 || !(aGraph1 != aGraph2));
}

TEST(Graph, exists_path_between_two_nodes_returns_true_for_adjacent_nodes_if_exists_edge_between_them)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.ExistsPathBetweenTwoNodes("a", "b") &&
		aGraph.ExistsPathBetweenTwoNodes("b", "c") &&
		aGraph.ExistsPathBetweenTwoNodes("b", "d") &&
		aGraph.ExistsPathBetweenTwoNodes("d", "a"));
}

TEST(Graph, exists_path_between_two_nodes_returns_true_for_non_adjacent_nodes_if_exists_path_between_them)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.ExistsPathBetweenTwoNodes("a", "c") &&
		aGraph.ExistsPathBetweenTwoNodes("a", "d") &&
		aGraph.ExistsPathBetweenTwoNodes("a", "a") &&
		aGraph.ExistsPathBetweenTwoNodes("b", "a"));
}

TEST(Graph, exists_path_between_two_nodes_returns_true_for_loop)
{
	// Используется граф 3.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d", "e" }, { {"a", "a"}, {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"}, { "e", "e"} });
	ASSERT_TRUE(aGraph.ExistsPathBetweenTwoNodes("a", "a") &&
		aGraph.ExistsPathBetweenTwoNodes("e", "e"));
}

TEST(Graph, exists_path_between_two_nodes_returns_false_if_path_does_not_exist)
{
	// Используется граф 4.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d", "e", "f" }, { {"a", "a"}, {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"}, { "e", "e"} });
	ASSERT_TRUE(!aGraph.ExistsPathBetweenTwoNodes("c", "b") &&
		!aGraph.ExistsPathBetweenTwoNodes("c", "c") &&
		!aGraph.ExistsPathBetweenTwoNodes("c", "e") &&
		!aGraph.ExistsPathBetweenTwoNodes("e", "c") &&
		!aGraph.ExistsPathBetweenTwoNodes("a", "e") &&
		!aGraph.ExistsPathBetweenTwoNodes("e", "a") &&
		!aGraph.ExistsPathBetweenTwoNodes("e", "f") &&
		!aGraph.ExistsPathBetweenTwoNodes("f", "a") &&
		!aGraph.ExistsPathBetweenTwoNodes("f", "e") &&
		!aGraph.ExistsPathBetweenTwoNodes("f", "f"));
}

TEST(Graph, exists_path_between_two_nodes_throws_when_graph_does_not_contain_fist_of_given_nodes)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_ANY_THROW(aGraph.ExistsPathBetweenTwoNodes("e", "a"));
}

TEST(Graph, exists_path_between_two_nodes_throws_when_graph_does_not_contain_second_of_given_nodes)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_ANY_THROW(aGraph.ExistsPathBetweenTwoNodes("a", "e"));
}

TEST(Graph, exists_path_between_two_nodes_throws_when_graph_does_not_contain_both_of_given_nodes)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_ANY_THROW(aGraph.ExistsPathBetweenTwoNodes("e", "e"));
}

TEST(Graph, is_graph_connected_returns_false_for_empty_graph)
{
	StringGraph aGraph;
	ASSERT_FALSE(aGraph.IsGraphConnected());
}

TEST(Graph, is_graph_connected_returns_true_for_graph_that_contains_one_node)
{
	// Используется граф 6.
	StringGraph aGraph;
	aGraph.AddNode("a");
	ASSERT_TRUE(aGraph.IsGraphConnected());
}

TEST(Graph, is_graph_connected_returns_true_for_connected_graph)
{
	// Используется граф 5.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d", "e", "f" },
		{ {"a", "b"},{"b", "c"}, {"c", "a"}, {"c", "d"}, {"a", "d"}, {"d", "e"}, {"e", "c"}, {"e", "f"},{"f", "c"} });
	ASSERT_TRUE(aGraph.IsGraphConnected());
}

TEST(Graph, is_graph_connected_returns_false_for_non_connected_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.IsGraphConnected());
}
