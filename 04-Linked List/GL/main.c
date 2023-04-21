#include <stdio.h>
#include <stdlib.h>



enum Tag_ {data,link};
typedef enum Tag_ Tag;

union Tuple{
    int data;
    struct GNode* sublist;
};
typedef union Tuple tuple;

struct GNode{
    Tag tag;
    tuple t;
    struct GNode* next;
};
typedef struct GNode Node;

void printList(Node*);

void setNodeData(Node* node,int d){
    node->next=NULL;
    node->tag = data;
    node->t.data = d;
}
void setNodeSub(Node* node,Node* list){
    node->next=NULL;
    node->tag = link;
    node->t.sublist = list;
}

void insertKeyBack(Node** first, int newkey){
    Node* current = *first;
    Node* newNode =(Node*)malloc(sizeof(Node));
    setNodeData(newNode,newkey);

    if(*first == NULL){ *first = newNode; }
    else{
        while(current->next){current = current->next;}
        current->next = newNode;
    }
}

void insertListBack(Node** first, Node* list){
    Node* current = *first;
    Node* newNode =(Node*)malloc(sizeof(Node));
    setNodeSub(newNode,list);

    if(*first == NULL){ *first = newNode; }
    else{
        while(current->next){current = current->next;}
        current->next = newNode;
    }
}

void printList(Node* current){
    if(current == NULL) return;
    else{
        if(current->tag == data)
            printf("(%d),",current->t.data);
        else{
            printf("[");
            printList(current->t.sublist);
            printf("]");
        }  
        printList(current->next);  
    }
}

Node* copyList(Node* current){
    if(current == NULL) return 0;
    else{
        Node* newNode = (Node*)malloc(sizeof(Node));
        // 先複製 tag
        newNode->tag = current->tag;
        
        // 若 Tuple 是 data：複製 data
        if(current->tag == data){
            newNode->t.data = current->t.data;
        }
        // 若 Tuple 是 sublist：往下 遞回複製 sublist
        else 
            newNode->t.sublist = copyList(current->t.sublist);
        // cuurent Node 複製完成，往下 遞回複製 next
        newNode->next = copyList(current->next);
        return newNode;  
    }
}

int equal(Node* la, Node* lb){
    int res = 0;    // 預設「不相等」
    if(la == 0 && lb == 0) return 1;
    else if(la!=0 && lb != 0){   
        if(la->tag == lb->tag){
            if(la->tag == data){
                if(la->t.data == lb->t.data) res = 1;
                else res = 0;
            }
            else res = equal(la->t.sublist,lb->t.sublist);

            // 若到目前止 兩者都相等，再繼續往下比較
            if(res == 1)
                res = equal(la->next,lb->next);
        }
    }
    return res;
}

int depth(Node* current){
    int cnt = 0;
    int temp = 0;
    if(current == NULL) return 0;
    else{
        while(current){
            // 若有 Node 是 sublist -> 層數+1
            if(current->tag == link){
                temp = depth(current->t.sublist); // 比較
                if(temp > cnt) cnt = temp;
            }
            current = current->next;
        }
        return cnt+1;
    }
}

int main(void){
    Node* list_a=0;
    Node* list_b=0;
    Node* list_c=0;

    insertKeyBack(&list_a,1);
    insertKeyBack(&list_a,2);
    insertKeyBack(&list_a,3);
    insertKeyBack(&list_b,11);
    insertKeyBack(&list_b,12);
    insertListBack(&list_a,list_b);
    insertKeyBack(&list_a,5);

    printList(list_a);
    puts("");
    list_c = copyList(list_a);
    printList(list_c);
    puts("");

    insertListBack(&list_a,list_c);
    printList(list_a);
    puts("");

    printf("%d,%d\n",equal(list_a,list_b),equal(list_a,list_c));

    printf("%d\n",depth(list_a));

}