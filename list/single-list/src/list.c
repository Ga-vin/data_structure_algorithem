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

int32_t list_ins_next(list_t *plist, list_element_t *pelement, const void *data)
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
