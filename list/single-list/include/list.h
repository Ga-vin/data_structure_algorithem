#ifndef LIST_H_
#define LIST_H_

#include "../../../../include/common.h"

/**
 *@def List element
 */
typedef struct list_element {
    void                *data;
    struct list_element *next;
} list_element_t;

/**
 *@def List structure
 */
typedef struct {
    uint32_t size;
    void (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    list_element_t *head;
    list_element_t *tail;
} list_t;

/**
 *@fn Interface
 */
void 		slist_init(list_t *plist, void (*destroy)(void *data));
void 		slist_destroy(list_t *plist);
int32_t 	slist_insert_next(list_t *plist, list_element_t *element, const void *data);
int32_t 	slist_delete_next(list_t *plist, list_element_t *element void **data);
int32_t 	slist_insert_head(list_t *plist, const void *data);
int32_t 	slist_delete_head(list_t *plist, void **data);
int32_t 	slist_insert_tail(list_t *plist, const void *data);
int32_t 	slist_delete_tail(list_t *plist, void **data);
int32_t         slist_size(list_t *plist);
list_element_t *slist_head(list_t *plist);
list_element_t *slist_tail(list_t *plist);
int32_t         slist_is_head(list_element_t *elem);
int32_t         slist_is_tail(list_element_t *elem);
void           *slist_data(const list_element_t *nodp);
list_element_t *slist_next(const list_element_t *nodp);
int32_t         slist_is_empty(list_t *plist);

#define LIST_SIZE(p)          ((p)->size)
#define LIST_HEAD(p)          ((p)->head)
#define LIST_TAIL(p)          ((p)->tail)

#define LIST_IS_HEAD(p, e)    ((e) == (p)->head ? 1 : 0)
#define LIST_IS_TAIL(e)       ((e)->next == NULL ? 1 : 0)


#define LIST_DATA(e)          ((e)->data)
#define LIST_NEXT(e)          ((e)->next)

#endif /* LIST_H_ */
