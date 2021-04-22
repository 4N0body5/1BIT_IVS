//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Natalia Bubakova <xbubak01@stud.fit.vutbr.cz>
// $Date:       $2021-03-10
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Natalia Bubakova
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//


class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        int values[] = { 13, 5, 69, 25, 74, 22, 88, 21, 45, 5, 55, 4, 202 };

        for(int key : values)
            tree.InsertNode(key);
    }

    BinaryTree tree;
};


class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        int values[] = { 13, 5, 69, 25, 74, 22, 45, 36, 50, 65, 88, 21, 45, 5, 55 };

        for(int key : values)
            tree.InsertNode(key);
    }

    BinaryTree tree;
};




TEST_F (EmptyTree, InsertNode)
{
    auto node1 = tree.InsertNode(0);
    EXPECT_TRUE(node1.first);
    EXPECT_EQ(node1.second->key, 0);

    auto node2 = tree.InsertNode(45);
    EXPECT_TRUE(node2.first);
    EXPECT_EQ(node2.second->key, 45);

    auto node3 = tree.InsertNode(0);
    EXPECT_FALSE(node3.first);       // it is already there
    EXPECT_EQ(node1.second->key, node3.second->key);

}

TEST_F (EmptyTree, DeleteNode)
{
    EXPECT_FALSE(tree.DeleteNode(32));
    EXPECT_FALSE(tree.DeleteNode(-2));
    EXPECT_FALSE(tree.DeleteNode(42));
    EXPECT_FALSE(tree.DeleteNode(0));

    tree.InsertNode(0);
    EXPECT_TRUE(tree.DeleteNode(0));
}

TEST_F (EmptyTree, FindNode)
{
    EXPECT_TRUE(tree.FindNode(9) == NULL);
    EXPECT_TRUE(tree.FindNode(-9) == NULL);
    EXPECT_TRUE(tree.FindNode(100) == NULL);

    tree.InsertNode(100);
    EXPECT_FALSE(tree.FindNode(100) == NULL);

    auto node = tree.InsertNode(10);
    EXPECT_TRUE(node.first);

    auto node_p = tree.FindNode(10);
    ASSERT_TRUE(node_p != NULL);
    EXPECT_EQ(node.second, node_p);
}


TEST_F (NonEmptyTree, InsertNode)
{
    auto node1 = tree.InsertNode(5);
    EXPECT_FALSE(node1.first); // was already there

    auto node2 = tree.InsertNode(0);
    EXPECT_TRUE(node2.first); // is first in the tree

    auto node3 = tree.InsertNode(69);
    EXPECT_FALSE(node3.first);
}


TEST_F (NonEmptyTree, DeleteNode)
{
    EXPECT_TRUE(tree.DeleteNode(88));
    EXPECT_FALSE(tree.DeleteNode(8));   //is not there
    EXPECT_TRUE(tree.DeleteNode(55));
    EXPECT_FALSE(tree.DeleteNode(55));  //already deleted
    EXPECT_TRUE(tree.DeleteNode(202));
}


TEST_F (NonEmptyTree, FindNode)
{
    EXPECT_FALSE(tree.FindNode(13) == NULL);
    EXPECT_FALSE(tree.FindNode(5) == NULL);
    EXPECT_TRUE(tree.FindNode(96) == NULL); //is not there
    EXPECT_TRUE(tree.FindNode(2) == NULL);  //not there

    //BinaryTree::Node_t *node;
    auto node_p = tree.FindNode(74);
    ASSERT_TRUE(node_p != NULL);
    EXPECT_EQ(node_p->key, 74);
}


TEST_F (TreeAxioms, Axiom1)
{
    std::vector<BinaryTree::Node_t *> leaf_nodes;
    tree.GetLeafNodes(leaf_nodes);

    for (auto leaf_node : leaf_nodes)
    {
        ASSERT_EQ(leaf_node->color, BinaryTree::BLACK);
    }
}

TEST_F (TreeAxioms, Axiom2)
{
    std::vector<BinaryTree::Node_t *> nodes;
    tree.GetNonLeafNodes(nodes);

    for(auto node : nodes)
    {
        if(node->color == BinaryTree::RED)
        {
            ASSERT_EQ(node->pLeft->color, BinaryTree::BLACK);
            ASSERT_EQ(node->pRight->color, BinaryTree::BLACK);
        }
    }
}

TEST_F (TreeAxioms, Axiom3)
{
    std::vector<BinaryTree::Node_t *> leaf_nodes;
    tree.GetLeafNodes(leaf_nodes);

    int black_nodes = 0;
    int path = -1;
    int ln_array[sizeof(leaf_nodes)];

    for(auto leaf_node : leaf_nodes)
    {
        path ++;
        while(leaf_node != tree.GetRoot())
        {
            if(leaf_node->color == BinaryTree::BLACK)
            {
                black_nodes ++;
            }
            leaf_node = leaf_node->pParent;
        }
        ln_array[path] = black_nodes;
        black_nodes = 0;
    }

    for(int i = 0; i < path; i++)
    {
        ASSERT_EQ(ln_array[i], ln_array[i+1]);
    }
}


/*** Konec souboru black_box_tests.cpp ***/
