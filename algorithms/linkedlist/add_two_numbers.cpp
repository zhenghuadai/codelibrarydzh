/*
 * =====================================================================================
 *
 *       Filename:  add_two_numbers.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2015 04:02:37 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "common.h"
namespace{
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result;
        ListNode** p = &result;
        int ten = 0;
        while(l1!= NULL && l2 != NULL){
            *p = new ListNode(0);
            (*p)->val = (l1->val + l2->val + ten) % 10;
            ten = (l1->val + l2->val + ten)>=10?1:0;
            p = &((*p)->next);
            l1 = l1->next;
            l2 = l2->next;
        }
        if(l1!=NULL || l2 != NULL){
            ListNode* q = (l1 == NULL?l2:l1);
            while(q != NULL){
              *p = new ListNode(0);
              (*p)->val = (q->val  + ten ) %10;
              ten = (q->val  + ten)>=10?1:0;
               p = &((*p)->next);
              q = q->next;
              
            }
        }
        
        if(ten != 0){
            *p = new ListNode(ten);
        }
        return result;
    }
};
} /// namespace

ListNode* test_addTwoNumbers(ListNode* l1, ListNode* l2){
    Solution s;
    return s.addTwoNumbers(l1,l2);
}
