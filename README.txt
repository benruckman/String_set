The tester I have attached is incomplete, though this code did pass the tests that my class had. 
This is an implementation of a string_set, via a drop list. A drop list is basically a vector of linked lists, starting with a head node. 
A drop list's timing is on average, O(log(n)) for add, remove, and contains functions. The = operator and get_elements of both O(n), because 
it has to iterate through the list at level 0. 