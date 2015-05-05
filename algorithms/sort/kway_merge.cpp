#include "common.h"
class Solution {	
	private:
		typedef struct TreeNode{
			int val;
			int index;
			TreeNode(int v, int i):val(v), index(i){}
			TreeNode(){}
		} TreeNode;
		typedef ListNode* ListNodeP;
		void adjustAll(TreeNode* tree, int all){
			int levelLen = all / 2;
			while(levelLen > 1){
				for(int i = levelLen; i < 2*levelLen; i +=2){
					int parent = i / 2;
					int winner = (tree[i].val < tree[i+1].val) ? i: i+1;
					//tree[parent].val = tree[winner].val;
					//tree[parent].index = tree[winner].index;
					tree[parent] = tree[winner];
				}
				levelLen >>= 1;
			}
		}

		void adjust(TreeNode* tree, vector<ListNode*>& curIndex, int leavesL)
		{
			int index = tree[1].index;
			if(curIndex[index] != NULL){
				tree[leavesL + index].index = index;
				tree[leavesL + index].val = curIndex[index]->val;
				//curIndex[index] = curIndex[index]->next;
			}else{
				tree[leavesL + index].index = -1;
				tree[leavesL + index].val = INT_MAX;
			}
			index = leavesL + index;
			while(index > 1){
				int parent = index / 2 ;
				int L = parent * 2; 
				int R = L + 1;
				int winner = (tree[L].val < tree[L+1].val) ? L: L+1;
				tree[parent] = tree[winner];
				index = index / 2;
			}
		}
	public:

		ListNode* mergeKLists(vector<ListNode*>& lists) {
			int length = lists.size();
			if(length == 0) return NULL;
			if(length == 1) return lists[0];
			int leavesL = 1;
			while(leavesL < length) leavesL <<= 1;
			int allL = leavesL << 1;
			TreeNode* Tree = new TreeNode[allL];
			int done = length;
			for(int i =0; i<length; i++){
				if(lists[i] != NULL){
					Tree[leavesL + i].val = lists[i]->val;
					Tree[leavesL + i].index = i;				
				}else{
					Tree[leavesL + i].val =  INT_MAX;
					Tree[leavesL + i].index = -1;
				}

			}
			for(int i = length; i<leavesL; i++){
				Tree[leavesL + i].val = INT_MAX;
				Tree[leavesL + i].index = -1;
			}

			adjustAll(Tree, allL);

			ListNode* mergedList = NULL;
			ListNode** pM = &mergedList;		

			while(Tree[1].index != -1){
				int index = Tree[1].index;
				*pM = lists[index];
				lists[index] = lists[index]->next;

				adjust(Tree, lists, leavesL);
				pM = &((*pM)->next);
			}
			(*pM)  = NULL;
			delete Tree;

			return mergedList;
		}
};

static void test()
{
}
APPEND_TO_TEST(); 
