#ifndef LIST_H_
#define LIST_H_

/**
 *@brief Type redefine
 */
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

/**
 *@def List element
 */
typedef struct list_element {
    void   *data;
    struct *list_element;
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
void 	list_init(list_t *plist, void (*destroy)(void *data));
void 	list_destroy(list_t *plist);
int32_t list_ins_next(list_t *plist, list_element_t *element, const void *data);
int32_t list_rem_next(list_t *plist, list_element_t *element void **data);

#define LIST_SIZE(p)          ((p)->size)
#define LIST_HEAD(p)          ((p)->head)
#define LIST_TAIL(p)          ((p)->tail)

#define LIST_IS_HEAD(p, e)    ((e) == (p)->head ? 1 : 0)
#define LIST_IS_TAIL(e)       ((e)->next == NULL ? 1 : 0)


#define LIST_DATA(e)          ((e)->data)
#define LIST_NEXT(e)          ((e)->next)

#endif /* LIST_H_ */
