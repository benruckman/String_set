/* This node class is used to build linked lists for the
 * string_set class.  
 *
 * Ben Ruckman
 * February 26, 2021
 */

#include "node.h"
#include <iostream>

// By default, functions are not in a namespace.  They are not in any
// class.  Symbols defined here are globally available.  We need to
// qualify our function names so that you are definining our 
// cs3505::node class functions.  
//
// Note that you can also use the namespace cs3505 { } block, this 
// would eliminate one level of name qualification.  The 
// 'using' statement will not help in this situation.
// 
// Qualify it as shown here for functions: 
//      cs3505::node::functionname, etc.

/*******************************************************
 * node class - member function definitions
 ***************************************************** */

// Students will decide how to implement the constructor, 
// destructor, and any helper methods.

namespace cs3505 
{
  /** Node constructor, resizes nodes and sets data = to the input string
    */
  node::node(const std::string & s, int l)
  {
    data = s;
    nodes.resize(l);
  }

  node::~node() //Nothing to delete in destructor, because nothing is created with the keyword new in node
  {
  }

  /** Sets the next node of this node in vector nodes to the input node pointer
    */
  void node::set_next_node(node* n, int l)
  {
    if(l > nodes.size())
      return;
    nodes[l] = n;
  }

  /** Sets the next node of this node in vector nodes to null
    */
  void node::set_next_node_null(int l)
  {
    if(l > nodes.size() || nodes[l] == NULL)
      return;
    nodes[l] = NULL;
  }
  
  /** Returns the next node of this, in nodes at level l
    */
  node* node::get_next_node(int l) const
  {
    if(nodes[l] != NULL)
      return nodes[l];
    return NULL;
  }


}
