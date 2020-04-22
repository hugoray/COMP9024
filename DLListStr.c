/*
 Implementation of doubly-linked list ADT for string values.
 Written by Ashesh Mahidadia Jan 2020, based on code writted by John Shepherd 2015.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "DLListStr.h"

// data structures representing DLListStr

typedef struct DLListNode {
    char *value;  // value of this list item (string)
    struct DLListNode *prev;
    // pointer previous node in list
    struct DLListNode *next;
    // pointer to next node in list
    DLListStr children;
    // get the relation of url and value
    double pagerank;
    int count;
    // for part 3
} DLListNode;

// data structures of DLListStr
// including count first current & last node in DLL
typedef struct DLListRep {
    int nitems;      // count of items in list
    DLListNode *first; // first node in list
    DLListNode *curr;  // current node in list
    DLListNode *last;  // last node in list
} DLListRep;

// create a new DLListNode (private function)
static DLListNode *newDLListNode(char *val) {
    DLListNode *new;
    new = malloc(sizeof(DLListNode));
    assert(new != NULL);

    new->value = malloc((strlen(val) + 1) * sizeof(char));    // reset value
    assert(new->value != NULL);
    strcpy(new->value, val);  // copy the string val to new.value

    new->value[strlen(val)] = '\0'; //set \0
    new->prev = new->next = NULL;
    new->children = NULL;
    return new;
}


// create a new DLListNode for part3
// based on *newDLlistNode
static DLListNode *newDLListNode2(char *val,  double pagerank) {
    DLListNode *new;
    new = malloc(sizeof(DLListNode));
    assert(new != NULL);
    // re set value
    new->value = malloc((strlen(val) + 1) * sizeof(char));
    assert(new->value != NULL);
    // copy
    strcpy(new->value, val);
    // set \0
    new->value[strlen(val)] = '\0';
    new->pagerank = pagerank;
    new->next = NULL;
    new->children = NULL;
    return new;
}

// create a new empty DLListStr
DLListStr newDLListStr() {
    DLListStr L = malloc(sizeof(struct DLListRep));
    assert (L != NULL);
    L->nitems = 0;
    L->first = NULL;
    L->last = NULL;
    //L->curr = NULL;
    return L;
}

// return the existed DLList
DLListNode *existDLList(DLListStr L, char *val) {
    assert(L != NULL);

    DLListNode *curr = L->first;
    while (curr != NULL) {
        if (strcmp(curr->value, val) == 0) {
            break;
        }
        curr = curr->next;
    }
    return curr;
}


/*
   pre-reqisite: L is ordered (increasing) with no duplicates
   post-condition: val is inserted in L, L is ordered (increasing) with no duplicates
*/
// insert the node to the DLL in order
void insertSetOrd(DLListStr L, char *val) {
    /*
       implement this function to
       insert val in L  (in order), no duplicates (set)

    */
    assert(L != NULL);
    DLListNode *existNode = existDLList(L, val);
    if (existNode == NULL) {
        // get the new node
        DLListNode *newNode = newDLListNode(val);

        if (L->last == NULL) {
            L->first = L->last = newNode;
            L->nitems++;
        } else {
            newNode->prev = L->last;
            L->last->next = newNode;
            L->last = L->last->next;
            L->nitems++;
        }
    }
}

// display items to the text file for part 2
void display(DLListStr L) {
    assert(L != NULL);
    DLListNode *curr;
    DLListNode *child;
    FILE *fp;
    // open file
    if ((fp = fopen("invertedIndex.txt", "w")) != NULL) {
        for (curr = L->first; curr != NULL; curr = curr->next) {
            fprintf(fp, "%s", curr->value);
            if (curr->children != NULL) {
                for (child = curr->children->first; child != NULL; child = child->next) {
                    fprintf(fp, " %s", child->value);
                }
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
}

// display items from a DLListStr, comma separated
void showDLListStr(DLListStr L) {
    assert(L != NULL);
    DLListNode *curr;
    DLListNode *child;
    for (curr = L->first; curr != NULL; curr = curr->next) {
        fprintf(stdout, "%s", curr->value);
        if (curr->children != NULL) {
            for (child = curr->children->first; child != NULL; child = child->next) {
                fprintf(stdout, " %s", child->value);
            }
        }
        fprintf(stdout, "\n");
    }
}

// free up all space associated with list
void freeDLListStr(DLListStr L) {
    assert(L != NULL);
    DLListNode *curr, *prev;
    curr = L->first;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;

        // free value and current node
        if (prev->children != NULL) {
            freeDLListStr(prev->children);
        }
        free((prev->value));
        free(prev);
    }
    free(L);
}

int lengthDLListStr(DLListStr L) {
    if (L != NULL) {
        return L->nitems;
    } else {
        return 0;
    }
}

void convertDLLtoArray(DLListStr L, char **array) {
    assert(L != NULL);
    int index = 0;

    for (L->curr = L->first; L->curr != NULL; L->curr = L->curr->next) {
        array[index] = malloc(sizeof(strlen(L->curr->value) + 1));
        strcpy(array[index], L->curr->value);
        array[index][strlen(L->curr->value) + 1] = '\0';
        index++;
    }
}

// for inverted part
void insertChild(DLListStr L, char *val, char *child) {
    /*
      based on insertSetOrd
    */
    assert(L != NULL);

    DLListNode *existNode = existDLList(L, val);

    if (existNode == NULL) {
        // get the new node
        insertSetOrd(L, val);
        existNode = L->last;
    }

    // when node has no children, add a DLL
    if (existNode->children == NULL) {
        existNode->children = newDLListStr();
    }

    // add node
    insertSetOrd(existNode->children, child);
}

DLListNode *SelectSortNode(DLListNode *head) {
    DLListNode *p, *q;//遍历的两个指针
    DLListNode *pMin;//记录最小的数据
    char *temp;
    DLListStr child;


    if (head->next == NULL) {
        return head;
    }

    for (p = head; p->next != NULL; p = p->next)//遍历的次数
    {
        pMin = p;//记录最小的数值
        for (q = p->next; q; q = q->next)//从排好的小值部分开始向后遍历
        {
            if (strcmp(q->value, pMin->value) < 0)//发现比最小值更小的
            {
                pMin = q;//记录最小值

            }
        }
        if (pMin != p)//不相等说明已经发现最小值
        {
            temp = pMin->value;
            child = pMin->children;

            pMin->value = p->value;
            pMin->children = p->children;
            p->value = temp;
            p->children = child;


        }
    }

    return head;
}

void sortDLLBySelection(DLListStr L) {
    // sort insertion
    L->first = SelectSortNode(L->first);
}

// sort the collectionurl for part 2
DLListNode *SelectSortNodeurl(DLListNode *head) {
    DLListNode *p, *q;//遍历的两个指针
    DLListNode *pMin;//记录最小的数据
    char *temp;

    if (head->next == NULL) {
        return head;
    }

    for (p = head; p->next != NULL; p = p->next)//遍历的次数
    {
        pMin = p;//记录最小的数值
        for (q = p->next; q; q = q->next)//从排好的小值部分开始向后遍历
        {
            if (strcmp(q->value, pMin->value) < 0)//发现比最小值更小的
            {
                pMin = q;//记录最小值
            }
        }
        if (pMin != p)//不相等说明已经发现最小值
        {
            temp = pMin->value;
            pMin->value = p->value;
            p->value = temp;


        }
    }

    return head;
}

void sortDLLBySelectionurl(DLListStr L) {
    // sort insertion
    L->first = SelectSortNode(L->first);
}




void insertDLListPageRank(DLListStr L, char *val, double rankValue) {
    /*
       implement this function to
       insert val in L  (in order), no duplicates (set)
    */
    assert(L != NULL);
    DLListNode *existNode = existDLList(L, val);
    if (existNode == NULL) {
        // get the new node
        DLListNode *newNode = newDLListNode2(val, rankValue);

        if (L->last == NULL) {
            L->first = L->last = newNode;
            L->nitems++;
        } else {
            L->last->next = newNode;
            L->last = L->last->next;
            L->nitems++;
        }
    }
}
DLListNode *SelectSortNode2(DLListNode *head) {
    DLListNode *p, *q;//遍历的两个指针
    DLListNode *pMax;//记录最小的数据
    char *temp;
    int cnt;
    double pgrk;
    DLListStr child;


    if (head->next == NULL) {
        return head;
    }

    for (p = head; p->next != NULL; p = p->next)//遍历的次数
    {
        pMax = p;//记录最小的数值
        for (q = p->next; q; q = q->next)//从排好的小值部分开始向后遍历
        {
            int flag = 0;
            if (q->count == pMax->count){
                if (q->pagerank < pMax->pagerank) {
                    flag = 0;
                } else {
                    flag = 1;
                }
            } else if (q->count > pMax->count) {
                flag = 1;
            }
            if (flag > 0)//发现比最小值更小的
            {
                pMax = q;//记录最小值
            }
        }
        if (pMax != p)//不相等说明已经发现最小值
        {
            temp = pMax->value;
            child = pMax->children;
            cnt = pMax->count;
            pgrk = pMax->pagerank;

            pMax->value = p->value;
            pMax->children = p->children;
            pMax->count = p->count;
            pMax->pagerank =p->pagerank;

            p->value = temp;
            p->children = child;
            p->count =cnt;
            p->pagerank = pgrk;

        }
    }

    return head;
}

void sortDLLBySelection2(DLListStr L) {
    // sort insertion
    L->first = SelectSortNode2(L->first);
}
void searchpgrnk(DLListStr paramsList, DLListStr pageRankList, DLListStr invertedIndexList,
                          DLListStr searchResultList) {

    DLListNode *paramFirst = paramsList->first;
    DLListNode *invertedIndexFirst;
    DLListNode *existNode;

    while (paramFirst != NULL) {
        // next
        invertedIndexFirst = invertedIndexList->first;
        while (invertedIndexFirst != NULL) {
            // compare
            if (strcmp(paramFirst->value, invertedIndexFirst->value) == 0) {
                // url的列表
                if (invertedIndexFirst->children != NULL) {
                    // url node
                    DLListNode *urlNode = invertedIndexFirst->children->first;
                    DLListNode *rankNode;
                    while (urlNode != NULL) {
                        rankNode = pageRankList->first;
                        while (rankNode != NULL) {
                            if (strcmp(urlNode->value, rankNode->value) == 0) {
                                // 统计个数
                                existNode = existDLList(searchResultList, urlNode->value);
                                if (existNode == NULL) {
                                    insertSetOrd(searchResultList, urlNode->value);
                                    existNode = existDLList(searchResultList, urlNode->value);
                                }
                                existNode->count++;
                                existNode->pagerank = rankNode->pagerank;
                                break;
                            }
                            rankNode = rankNode->next;
                        }
                        urlNode = urlNode->next;
                    }

                }
            }
            invertedIndexFirst = invertedIndexFirst->next;
        }
        paramFirst = paramFirst->next;
    }

    // sort
    sortDLLBySelection2(searchResultList);

}
