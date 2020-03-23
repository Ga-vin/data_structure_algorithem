/** ********************************************************************************
 **
 ** @file    single-list.c
 **
 ** @author  Gavin.Bai
 **
 ** @date    2020.02.26
 **
 ** @brief   Implementation for single list which do all operations
 ** *******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../include/list.h"

/**
 *@see    slist_init
 *@brief  Initialize list
 *@param  plist - list pointer
 *@param  destroy - destructor
 *@return NONE
 */
void slist_init(list_t *plist, void (*destroy)(void *data))
{
    if ( !plist) {
        return ;
    }

    plist->size    = 0;
    plist->head    = NULL;
    plist->tail    = NULL;
    plist->destroy = destroy;
}

/**
 *@see    slist_destroy
 *@brief  Destroy list structure all elements
 *@param  plist - pointer to list head
 *@return None
 */
void slist_destroy(list_t *plist)
{
    void *data = NULL;

    while ( slist_size(plist) > 0) {
        if ( (0 == list_delete_next(plist, NULL, (void **)&data)) && (NULL != plist->destroy)) {
            plist->destroy(data);
        }
    }

    memset(plist, 0, sizeof(list_t));
}

/**
 *@see    slist_insert_next
 *@brief  Insert element at specific location
 *@param  plist    - pointer to list head
 *@param  pelement - specific location
 *@param  data     - data to be inserted
 *@return 0 will be returned when it is inserted success, or else -1
 */
int32_t list_insert_next(list_t *plist, list_element_t *pelement, const void *data)
{
    list_element_t *new_element = NULL;

    if ( !plist || !pelement || !data) {
        return (-1);
    }

    new_element = (list_element_t *)malloc(sizeof(list_element_t));
    if ( NULL == new_element) {
        return (-1);
    }
    new_element->data = (void *)data;

    if ( NULL == pelement) {
        if ( 0 == LIST_SIZE(plist)) {
	    plist->tail = new_element;
        }

	new_element->next = plist->head;
	plist->head       = new_element;
    } else {
        if ( NULL == pelement->next) {
	    plist->tail = new_element;
        }

      	new_element->next = pelement->next;
      	pelement->next = new_element;
    }

    plist->size++;

    return (0);
}

/**
 *@see    slist_delete_next
 *@brief  Delete element at specific location
 *@param  plist    - pointer to list head
 *@param  pelement - specific location
 *@param  data     - data to be deleted
 *@return 0 will be returned when it is deleted success, or else -1
 */
int32_t slist_delete_next(list_t *plist, list_element_t *element, void **data)
{
    list_element_t *odata;
    
    if ( !plist || !element || !data) {
	return (-1);
    }

    if ( 0 == list_size(plist)) {
	return (-1);
    }

    if ( NULL == element) {
	*data 	    = plist->head->data;
	odata 	    = plist->head;
	plist->head = plist->head->next;

	if ( 1 == list_size(plist)) {
	    plist->tail = NULL;
	}
    } else {
	if ( NULL == element->next) {
	    return (-1);
	}

	*data 	      = element->next->data;
	odata 	      = element->next;
	element->next = element->next->next;

	if ( NULL == element->next) {
	    plist->tail = element;
	}
    }

    free(odata);

    plist->size--;

    return (0);
}

/**
 *@see    slist_size
 *@brief  Get size of single list
 *@param  plist    - pointer to list head
 *@return The length of list
 */
int32_t slist_size(list_t *plist)
{
    return ((NULL == plist) ? (-1) : ((int32_t)plist->size));
}

/**
 *@see    slist_head
 *@brief  Get head of single list
 *@param  plist    - pointer to list head
 *@return The header pointer of list
 */
list_element_t *slist_head(list_t *plist)
{
    return ((NULL == plist) ? (NULL) : (plist->head));    
}

/**
 *@see    slist_tail
 *@brief  Get tail of single list
 *@param  plist    - pointer to list head
 *@return The tail pointer of list
 */
list_element_t *slist_tail(list_t *plist)
{
    return ((NULL == plist) ? (NULL) : (plist->tail));
}

/**
 *@see    slist_is_head
 *@brief  Check whether the specific element which it is header of single list with match to compare
 *@param  plist    - pointer to list head
 *@param  elem     - specific element node
 *@param  match    - specific compare method
 *@return 0 will be returned when it is, or else -1
 */
int32_t slist_is_head(list_t *plist, list_element_t *elem, int32_t (*match)(void *key1, void *key2))
{
    if ( (NULL == plist) || (NULL == elem) || (NULL == match)) {
	return (-1);
    }

    return ((0 == match((void *)plist->head->data, (void *)elem->data)) ? (0) : (-1));
}

/**
 *@see    slist_is_tail
 *@brief  Check whether the specific element which it is tail of single list with match to compare
 *@param  plist    - pointer to list head
 *@param  elem     - specific element node
 *@param  match    - specific compare method
 *@return 0 will be returned when it is, or else -1
 */
int32_t slist_is_tail(list_t *plist, list_element_t *elem, int32_t (*match)(void *key1, void *key2))
{
    if ( (NULL == plist) || (elem == NULL) || (NULL == match)) {
	return (-1);
    }

    return ((0 == match((void *)plist->tail->data, (void *)elem->data)) ? (0) : (-1));
}

/**
 *@see    slist_data
 *@brief  Data area of the element node to be returned
 *@param  elem     - specific element node
 *@return Data of the element node will be returned
 */
void *slist_data(const list_element_t *nodp)
{
    return ((NULL == nodp) ? (NULL) : (nodp->data));
}

/**
 *@see    slist_next
 *@brief  Next area of the element node to be returned
 *@param  elem     - specific element node
 *@return Next of the element node will be returned
 */
list_element_t *slist_next(const list_element_t *nodp)
{
    return ((NULL == nodp) ? (NULL) : (nodp->next));
}

/**
 *@see    slist_is_empty
 *@brief  Check whether the single list which it is empty
 *@param  plist - the specific list
 *@return 0 will be returned when it empty, or else -1
 */
int32_t slist_is_empty(list_t *plist)
{
    return ((NULL == plist) ? (0) : ((0 == plist->size) ? (0) : (-1)));
}
