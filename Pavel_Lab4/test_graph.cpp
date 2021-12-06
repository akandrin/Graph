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

// Тест: Может создать граф
TEST(Graph, can_create_graph)
{
	ASSERT_NO_THROW(IntGraph());
}

// Тест: может построить корректный граф
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

// Тест: Кидает исключение при попытке построения некорректного графа
TEST(Graph, throws_when_build_incorrect_graph)
{
	StringGraph aGraph;
	ASSERT_ANY_THROW(aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "e"}, {"b", "d"}, {"d", "a"} }));
	// Граф не содержит узел "e", но "e" содержится в списке дуг.
}

// Тест: может добавить узел в пустой граф
TEST(Graph, can_add_node_to_empty_graph)
{
	StringGraph aGraph;
	aGraph.AddNode("a");
	ASSERT_EQ(aGraph.GetAdjacencyMap(), StringGraph::GraphMap(
		{
			{"a", {}}
		}));
}

// Тест: Добавление узла в пустой граф возвращает истину
TEST(Graph, adding_node_to_empty_graph_returns_true)
{
	StringGraph aGraph;
	ASSERT_TRUE(aGraph.AddNode("a"));
}

// Тест: Может добавить узел, которого нет в графе
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

// Тест: Добавление узла, которого нет в графе, возвращает истину
TEST(Graph, adding_node_to_graph_that_does_not_have_this_node_returns_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.AddNode("e"));
}

// Тест: Не может добавить узел, который есть в графе
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

// Тест: Добавление узла, которого нет в графе, возвращает ложь.
TEST(Graph, adding_node_to_graph_that_contains_this_node_returns_false)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.AddNode("a"));
}

// Тест: Может добавить дугу к узлу, который не имеет смежных узлов.
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

// Тест: Добавление дуги к узлу, который не имеет смежных узлов, возвращает истину.
TEST(Graph, adding_edge_to_node_that_does_not_have_adjacent_nodes_returns_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.AddEdge({"c", "a"}));
}

// Тест: Может добавить дугу к узлу, который уже имеет смежные узлы.
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

// Тест: Добавление дуги к графу, который не содержит эту дугу, возвращает истину.
TEST(Graph, adding_edge_to_graph_that_does_not_have_this_edge_returns_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.AddEdge({ "b", "a" }));
}

// Тест: Не может добавить дугу, если она уже есть в графе.
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

// Тест: Добавление дуги, если она уже есть в графе, возвращает ложь.
TEST(Graph, adding_edge_that_is_already_in_the_graph_returns_false)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.AddEdge({ "a", "b" }));
}

// Тест: Кидает исключение при добавлении некорректной дуги.
TEST(Graph, throws_when_add_incorrect_edge)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_ANY_THROW(aGraph.AddEdge({ "a", "e" }));
}

// Тест: Графы, построенные разными способами, одинаковы.
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

// Тест: Может очистить граф.
TEST(Graph, can_clear_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	aGraph.Clear();
	ASSERT_EQ(aGraph, StringGraph());
}

// Тест: Может удалить узел, который не имеет смежных узлов.
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

// Тест: Может удалить узел, который имеет входящие связи.
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

// Тест: Может удалить узел, который имеет исходящие связи.
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

// Тест: Может удалить узел, который имеет входящие и исходящие связи.
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

// Тест: Удаление узла, у которого нет смежных узлов, возвращает истину.
TEST(Graph, removal_node_that_has_no_adjacent_nodes_returns_true)
{
	// Используется граф 2.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d", "e" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.RemoveNode("e"));
}

// Тест: Удаление узла, который имеет входящие связи, возвращает истину.
TEST(Graph, removal_of_node_that_has_incomming_connections_returs_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.RemoveNode("c"));
}

// Тест: Удаление узла, который имеет исходящие связи, возвращает истину.
TEST(Graph, removal_of_node_that_has_outgoing_connections_returns_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.RemoveNode("a"));
}

// Тест: Удаление узла, который имеет входящие и исходящие связи, возвращает истину.
TEST(Graph, removal_of_node_that_has_incomming_and_outgoing_connections_returns_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.RemoveNode("b"));
}

// Тест: Не может удалить узел, которого нет в графе.
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

// Тест: Удаление узла, которого нет в графе, возвращает ложь.
TEST(Graph, removal_of_node_that_is_not_contained_in_graph_returns_false)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.RemoveNode("e"));
}

// Тест: Может удалить дугу, которая содержится в графе.
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

// Тест: Не может удалить дугу, которая не содержится в графе.
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

// Тест: Не может удалить некорректную дугу.
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

// Тест: Удаление дуги, которая есть в графе, возвращает истину.
TEST(Graph, removal_of_edge_that_is_contained_in_graph_returns_true)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.RemoveEdge({ "b", "c" }));
}

// Тест: Удаление дуги, которой нет в графе, возвращает ложь.
TEST(Graph, removal_of_edge_that_is_not_contained_in_graph_retunrs_false)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.RemoveEdge({ "a", "d" }));
}

// Тест: Удаление некорректной дуги возвращает ложь.
TEST(Graph, removal_of_incorrect_edge_returns_false)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.RemoveEdge({ "a", "e" }));
}

// Тест: "ContainsNode" возвращает истну, если узел есть в графе.
TEST(Graph, contains_node_returns_true_if_graph_contains_node)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.ContainsNode("a") && aGraph.ContainsNode("b") && aGraph.ContainsNode("c") && aGraph.ContainsNode("d"));
}

// Тест: "ContainsNode" возвращает ложь, если узла нет в графе.
TEST(Graph, contains_node_returns_false_if_graph_does_not_contain_node)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.ContainsNode("e"));
}

// Тест: "ContainsEdge" возвращает истну, если дуга есть в графе.
TEST(Graph, contains_edge_returns_true_if_graph_contains_edge)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_TRUE(aGraph.ContainsEdge(std::make_pair("a", "b")) &&
		aGraph.ContainsEdge(std::make_pair("b", "c")) &&
		aGraph.ContainsEdge(std::make_pair("b", "d")) &&
		aGraph.ContainsEdge(std::make_pair("d", "a")));
}

// Тест: "ContainsEdge" возвращает ложь, если дуги нет в графе.
TEST(Graph, contains_edge_returns_false_if_graph_does_not_contain_edge)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.ContainsEdge(std::make_pair("a", "d")) ||
		aGraph.ContainsEdge(std::make_pair("x", "y")) ||
		aGraph.ContainsEdge(std::make_pair("a", "x")) ||
		aGraph.ContainsEdge(std::make_pair("x", "a")) ||
		aGraph.ContainsEdge(std::make_pair("c", "a")));
}

// Тест: Может вывести граф.
TEST(Graph, can_output_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_EQ(GetInfo(aGraph), "a : { b }\nb : { c, d }\nc : { }\nd : { a }\n");
}

// Тест: Сравнение равных графов возвращает истину.
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

// Тест: Сравнение разных графов возвращает ложь.
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

// Тест: ExistsPathBetweenTwoNodes возвращает истину для смежных узлов, если существует дуга между ними.
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

// Тест: ExistsPathBetweenTwoNodes возвращает истину для несмежных узлов, если существует путь между ними.
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

// Тест: ExistsPathBetweenTwoNodes возвращает истину для петли.
TEST(Graph, exists_path_between_two_nodes_returns_true_for_loop)
{
	// Используется граф 3.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d", "e" }, { {"a", "a"}, {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"}, { "e", "e"} });
	ASSERT_TRUE(aGraph.ExistsPathBetweenTwoNodes("a", "a") &&
		aGraph.ExistsPathBetweenTwoNodes("e", "e"));
}

// Тест: ExistsPathBetweenTwoNodes возвращает ложь, если пути не существует.
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

// Тест: ExistsPathBetweenTwoNodes кидает исключение, если граф не содержит первый из переданных узлов.
TEST(Graph, exists_path_between_two_nodes_throws_when_graph_does_not_contain_first_of_given_nodes)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_ANY_THROW(aGraph.ExistsPathBetweenTwoNodes("e", "a"));
}

// Тест: ExistsPathBetweenTwoNodes кидает исключение, если граф не содержит второй из переданных узлов.
TEST(Graph, exists_path_between_two_nodes_throws_when_graph_does_not_contain_second_of_given_nodes)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_ANY_THROW(aGraph.ExistsPathBetweenTwoNodes("a", "e"));
}

// Тест: ExistsPathBetweenTwoNodes кидает исключение, если граф не содержит оба переданных узла.
TEST(Graph, exists_path_between_two_nodes_throws_when_graph_does_not_contain_both_of_given_nodes)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_ANY_THROW(aGraph.ExistsPathBetweenTwoNodes("e", "e"));
}

// Тест: IsGraphConnected возвращает ложь для пустых графов.
TEST(Graph, is_graph_connected_returns_false_for_empty_graph)
{
	StringGraph aGraph;
	ASSERT_FALSE(aGraph.IsGraphConnected());
}

// Тест: IsGraphConnected возвращает истину для графов, состоящих из одного узла.
TEST(Graph, is_graph_connected_returns_true_for_graph_that_contains_one_node)
{
	// Используется граф 6.
	StringGraph aGraph;
	aGraph.AddNode("a");
	ASSERT_TRUE(aGraph.IsGraphConnected());
}

// Тест: IsGraphConnected возвращаетистину для связных графов.
TEST(Graph, is_graph_connected_returns_true_for_connected_graph)
{
	// Используется граф 5.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d", "e", "f" },
		{ {"a", "b"},{"b", "c"}, {"c", "a"}, {"c", "d"}, {"a", "d"}, {"d", "e"}, {"e", "c"}, {"e", "f"},{"f", "c"} });
	ASSERT_TRUE(aGraph.IsGraphConnected());
}

// Тест: IsGraphConnected возвращает ложь для несвязных графов.
TEST(Graph, is_graph_connected_returns_false_for_non_connected_graph)
{
	// Используется граф 1.
	StringGraph aGraph;
	aGraph.Build({ "a", "b", "c", "d" }, { {"a", "b"}, {"b", "c"}, {"b", "d"}, {"d", "a"} });
	ASSERT_FALSE(aGraph.IsGraphConnected());
}
