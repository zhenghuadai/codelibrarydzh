ext_cflags:=-std=c++11
ext_inc:= ./ ./utils
ALGORITHMS:= \
	tree/pre_order_binary_tree \
	tree/post_order_binary_tree \
	tree/in_order_binary_tree \
	tree/is_balanced \
	tree/arrary_to_binary_tree \
	tree/arrary_to_binary_tree \
	tree/is_same_tree \
	\
	sort/kway_merge \
	sort/twosums \
	\
	combination/climbing_stairs \
	\
    binary_search/kth_element \
	binary_search/median_two_sort_array \
	binary_search/power \
	\
	dp/pascal_triangle \
	dp/longest_valid_parentheses \
	dp/permutation_sequence \
	\
	linkedlist/add_two_numbers \
	\
	graph/islands \
	graph/clone \
	\
	string/longest_nonrepeating_substring \
	string/isIsomorphic \
	string/edit_distance \
	\


TEST_LIST=$(foreach i, ${ALGORITHMS},$(i)_test.cpp)
ALGO_LIST=$(foreach i, ${ALGORITHMS},$(i).cpp)
SOURCEFILE:= main.cpp $(TEST_LIST) $(ALGO_LIST) utils/utils.cpp 


EXECUTABLE:=main
include ../include/makefile.inc
