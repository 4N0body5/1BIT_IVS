//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Natalia Bubakova <xbubak01@stud.fit.vutbr.cz>
// $Date:       $2021-03-10
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Natalia Bubakova
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
    Element_t* item = GetHead();
    Element_t* next_item;
    while (item != NULL)
    {
        next_item = item->pNext;
        delete item;
        item = next_item;
    }
}

void PriorityQueue::Insert(int value)
{
    Element_t* item = GetHead();
    Element_t* new_item = new Element_t();
    new_item->pNext = NULL;
    new_item->value = value;

    if (m_pHead == NULL || m_pHead->value <= value)
    {
        new_item->pNext = m_pHead;
        m_pHead = new_item;
    }
    else
    {
        while (item->pNext != NULL && item->pNext->value > value)
        {
            item = item->pNext;
        }
        new_item->pNext = item->pNext;
        item->pNext = new_item;
    }

}

bool PriorityQueue::Remove(int value)
{
    Element_t* item = GetHead();
    Element_t* found_item = Find(value);
    if (found_item != NULL && item != NULL)
    {
        if (m_pHead == found_item)
            m_pHead = found_item->pNext;
        else
        {
            while (item->pNext != found_item)
            {
                item = item->pNext;
            }
            item->pNext = found_item->pNext;
        }
        delete found_item;
        return true;
    }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t* item = GetHead();
    while (item != NULL)
    {
        if (item->value == value)
        {
            return item;
        }
        item = item->pNext;
    }
    return NULL;
}

size_t PriorityQueue::Length()
{
    size_t count = 0;
    Element_t* item = GetHead();
    while (item != NULL)
    {
        count++;
        item = item->pNext;
    }
    return count;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
