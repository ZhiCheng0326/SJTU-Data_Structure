//Input : 1->2->3->4
//Output: 4->3->2->1
void SinglyLinkedList::reverse()
{
    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;
    while(curr){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}
