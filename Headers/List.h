/**
 * This file is created to realize a linked list with a simulation of template in C.
 * The main usage of this linked list is to stock points and triangles in the final project NF06.
 */

#ifndef _LIST_H_
#define _LIST_H_

/**
 * Using stdlib.h for memory allocation.
 */
#include "stdlib.h"

/**
 * Implementation of the list by macro.
 * 
 * Define the node of the list with his content and his next node.
 * Define the list with his head node and his tail node.
 * 
 * following some basic fontions with the list.
 *****************************************************************************************************************************************
 * void List_T_push_back(List_T_ *list, T data)
 * 
 * this List_Push_back fonction is to add a element at the end of the list.
 * 
 * @param list a pointer who point to the list operated.
 * @param data the element we want to add.
 *****************************************************************************************************************************************
 * void List_T_erase(List_T_ *list,List_T_Node** iter)
 * this List_erase fonction is to delete a element in the position we want.
 * 
 * @param list a pointer who point to the list operated.
 * @param iter a pointer who point at the node that we want to delete.
 * !!! Please atention that here we need a pointer who point at the (iterator pointer).!!!
 * !!! in raison that sometimes we need to set the iterator to NULL. !!!
 *****************************************************************************************************************************************
 * void List_T_clear(List_T_ *list)
 * this function delete all the elements in the list.
 * @param list the list that we want to clear.
 */

#define List_IMPL(T) \
    typedef struct Node_##T##_struct {T data; struct Node_##T##_struct* next;} List_##T##_Node; \
    typedef struct List_##T##_struct {struct Node_##T##_struct *head, *tail;} List_##T##_; \
    \
    void List_##T##_push_back(List_##T##_ *list, T data){ \
        if(list->tail == NULL){ \
            list->head->data = data; \
            list->tail = list -> head;} \
        else{ \
            List_##T##_Node* newNode = (List_##T##_Node*)malloc(sizeof(List_##T##_Node)); \
            newNode -> data = data; \
            newNode -> next = NULL; \
            List_##T##_Node* tailNode = list->tail; \
            tailNode -> next = newNode; \
            list -> tail = newNode;}} \
    \
    void List_##T##_erase(List_##T##_ *list,List_##T##_Node** iter){ \
        if(list->head == list->tail){ \
            list->head -> next = NULL; \
            list->tail = NULL; \
            return;} \
        else if((*iter) == list->tail){ \
            List_##T##_Node* iterTemp = list->head; \
            while(iterTemp->next != (*iter)){ \
                iterTemp = iterTemp->next;} \
            iterTemp->next = NULL; \
            list->tail = iterTemp; \
            free((*iter)); \
            (*iter) = NULL;} \
        else{ \
            List_##T##_Node* iterTemp = (*iter)->next; \
            (*iter)->data = iterTemp->data; \
            (*iter)->next = iterTemp->next; \
            if(iterTemp == list->tail) \
                list->tail = (*iter); \
            free(iterTemp);}} \
    \
    void List_##T##_clear(List_##T##_ *list){ \
        if(list->tail == NULL) return; \
        List_##T##_Node* iter; \
        while (list->head != NULL){ \
        iter = list->head; \
        list->head = list->head->next; \
        free(iter);}} \

        
/**
 * A simulated constructor of the list by macro.
 * 
 * @param T Type wanted to use. example : List_int_
 * @param LIST name of the list.
 * @param DATA data of the first node.
 */


#define List(T,LIST,DATA) \
        T LIST;\
        LIST.head = (T##Node*)malloc(sizeof(T##Node)); \
        LIST.head -> data = DATA; \
        LIST.head -> next = NULL; \
        LIST.tail  = LIST.head; \
/* we assume that if tail node = NULL, then it is a empty list. */
#define ListEmpty(T,LIST) \
        T LIST;\
        LIST.head = (T##Node*)malloc(sizeof(T##Node)); \
        LIST.head -> next = NULL; \
        LIST.tail = NULL; \

#endif /* _LIST_H_ */