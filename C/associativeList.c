#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 100
#define MAX_VALUE_LEN 100

typedef struct node{
    int key;
    char str[MAX_VALUE_LEN];
    struct node* next;
} node;

node* add(node* head, int key, const char* str)
{
    node* cur = head;
    while (cur != NULL)
    {
        // CWE-462: Duplicate Key in Associative List (Alist) 
        if (cur->key == key) //if a duplicate is found
        {
            strcpy(cur->str, str);
            return head;
        }
        cur = cur->next;
    }

    //handle regular creation
    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: out of Memory\n");
        exit(1);
    }
    new_node->key = key;
    strncpy(new_node->str, str, MAX_VALUE_LEN);
    new_node->next = head;
    return new_node;
}

const char* node_find(const node* head, const int key)
{
    const node* cur = head;
    while (cur != NULL)
    {
        if(cur->key == key)
        {
            return cur->str;
        }
        cur = cur->next;
    }
    return NULL;
}

void node_free(node* head)
{
    node* cur = head;
    while (cur != NULL)
    {
        node* next = cur->next;
        free(cur);
        cur = next;
    }
}

int main()
{
    node* list = NULL;
    list = add(list, 1, "note1");
    list = add(list, 2, "note2");
    list = add(list, 3, "note3");
    printf("String for key '2': %s\n", node_find(list, 2));
    list = add(list, 2, "new_note2");
    printf("Updated string for key '2': %s\n", node_find(list, 2));
    node_free(list);
}