#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "list.h"

/**
 *@fn list_init
 *@brief Initialize list
 *@param plist - list pointer
 *@param destroy - destructor
 *@ret   NONE
 */
void list_init(list_t *plist, void (*destroy)(void *data))
{
    if ( !plist) {
        return ;
    }

    plist->size = 0;
    plist->head = NULL;
    plist->tail = NULL;

    plist->destroy = ((NULL == destroy) ? NULL : destroy);
}

/**
 *@fn list_destroy
 *@brief Destroy list structure all elements
 *@param plist - pointer to list head
 *@ret   None
 */
void list_destroy(list_t *plist)
{
    void *data = NULL;

    while ( LIST_SIZE(plist) > 0) {
        if ( (0 == list_rem_next(plist, (void **)&data)) && (NULL != plist->destroy)) {
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
