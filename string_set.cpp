/* A 'string set' is defined as a set of strings stored
 * in sorted order in a drop list.  See the class video
 * for details.
 *
 * For lists that do not exceed 2 ^ (max_width + 1)
 * elements, the add, remove, and contains functions are 
 * O(lg size) on average.  The operator= and get_elements 
 * functions are O(size).   
 * 
 * Peter Jensen
 * February 12, 2021
 */

#include "string_set.h"
#include <iostream>  // For debugging, if needed.
#include <stdlib.h>
#include <cassert>

namespace cs3505
{
  /*******************************************************
   * string_set member function definitions
   ***************************************************** */
  
  /** Constructor:  The parameter indicates the maximum
    * width of the next pointers in drop list nodes.
    */
  string_set::string_set(int max_w)
  {
    size = 0;
    max_width = max_w;
    head = new node("", max_w);
  }

  
  /** Copy constructor:  Initialize this set
    * to contain exactly the same elements
    * as another set.
    */
  string_set::string_set (const string_set &other)
  {
    set_string_set_to(other);
  }


  /** Destructor:  Release any memory allocated
    * for this object.
    */
  string_set::~string_set()
  {
    int times = size;
    for(int i = 0; i < times; i++)
      {
	node *temp = head->get_next_node(0);
	remove(temp->data); 
      }
    delete head;    
    size = 0;
    max_width = 0;
    
  }
  
  /** Add method: Adds the object stored at pointer 
    * &data to this (the object string_set). 
    */
  void string_set::add(const std::string &data)
  {
    if(contains(data))
      {
	return;
      }

    int level = 0;
    int random = 0;
    do
      {
	level++;
	random = rand() % 2;
      }
    while(random == 0 && level <= max_width); //Coin flipping

    node* n = new node(data, level);
    
    std::vector<node*> prior = get_prior(data); //Create prior array

    level--;

    for(level; level >= 0; level--) //For all levels, starting at level
      {
	if(prior[level] == NULL) //If prior array is NULL, then has to set the head node's next instead of prior
	  {
	    n->set_next_node(head->nodes[level], level);

	    head->set_next_node(n, level);
	  }
	else
	  {
	    n->set_next_node((prior[level]->get_next_node(level)), level); //Sets the next node of n to 
	                                                                   //the prior's next node on level
	    prior[level]->set_next_node(n, level); //Set the prior node's, next node, to be this node
	  }
      }
    //Update size after succesfully adding an object to the string_set
    size++;
  }

  /** Remove method: Removes the object stored at pointer &data from this (the object string_set). 
    */
  void string_set::remove(const std::string &data)
  {
    if(!contains(data))
      {
	return;
      }
    std::vector<node*> prior = get_prior(data);

    node* to_remove;
    if(prior[0] != NULL)
      to_remove = prior[0]->get_next_node(0);
    else 
      to_remove = head->nodes[0];
      

    int level = to_remove->nodes.size() - 1; //Set the level to the length of the width of the node to be 
                                             //removed, via the nodes' vector's size. 
    for(level; level >= 0; level--)
      {
	if(prior[level] != NULL)
	//Set the next node of the prior node to the next node of the node being removed
	  prior[level]->nodes[level] = to_remove->nodes[level];  
	else 
	  head->nodes[level] = to_remove->nodes[level]; 
      }
    delete to_remove; //Deallocate memory, after removing from drop list
    
    //Update size after succesfully removing an object from the string_set
    size--;
  }

  
  /** Contains method: Returns if the object stored at pointer &data is contained in this 
    * (the object string_set). 
    */
  bool string_set::contains(const std::string &data) const
  {
    std::vector<node*> prior;
    prior = get_prior(data);

    if((prior[0] != NULL) && (prior[0]->nodes[0] != NULL) && (prior[0]->nodes[0]->data.compare(data) == 0))
      return true;
    else if((prior[0] == NULL) && (size > 0) && (head->nodes[0]->data.compare(data) == 0))
      return true;

    return false;
  }


  /** Returns the number of objects stored in this (the object string_set)
    */
  int string_set::get_size() const
  {
    return size;
  }

  
  /** Overloading operator = 
    * 
    * Sets this string_set object equal to the string_set object on the right hand side of =
    */
  string_set & string_set::operator= (const string_set &rhs)
  {
    if(&rhs == this)
      return *this;

    set_string_set_to(rhs);

    return *this;
  }

  /** The recursive method, that builds the prior array for the method get_prior
    */
  void string_set::recursive_prior(std::vector<node*> &prior, const std::string &data, int level, node* current) const
  {
    if(current == NULL)
      {
	if(level <= 0)
	  return; 
	level--;
	if(prior[level] == NULL)
	  current = head->nodes[level];
	else
	  current = prior[level];
	recursive_prior(prior, data, level, current);
      }
    else if(current->data.compare(data) < 0)
      {
        if(level < 0)
          return; 
	for(int i = level; i >= 0; i--) //Updates all of prior, so prior doesn't have to start at head
	  prior[i] = current;
	current = current->get_next_node(level);
	recursive_prior(prior, data, level, current);
      }
    else if(current->data.compare(data) >= 0) //This entire body is the same as the first if, but for code readability, I left it like this
      {
	if(level <= 0)
	  return; 
	level--;
	if(prior[level] == NULL)
	  current = head->nodes[level];
	else
	  current = prior[level];
	recursive_prior(prior, data, level, current);
      }
    else //Should never get here
      {
	assert(false);
      }
  }


  /** Returns the prior vector, of the input string in the set
    */
  std::vector<node*> string_set::get_prior(const std::string &data) const
  {
    node* current = head->nodes[max_width - 1];

    std::vector<node*> prior (max_width);

    recursive_prior(prior, data, max_width, current);

    return prior;
  }

    
  /** Helper method for the equals operator, and the copy constructor 
    */
  void string_set::set_string_set_to(const string_set &other)
  {
    int times = size;
    for(int i = 0; i < times; i++)
      {
	node *temp = head->get_next_node(0);
	remove(temp->data);
      }
    this->size = 0; //Update the size to 0, because add increases the size
    this->max_width = other.max_width; //Update the max_width of this string_set
    this->head = new node("", max_width); //Set our head node to a new headnode, with the new max_width

    node* current = other.head->get_next_node(0); //The other head node is set to current, so we can loop 
                                                  //through the other set

    for(int i = other.size; i > 0; i--) //For all nodes in drop list
      {
	add(current->data);
	current = current->get_next_node(0);
      } 
    delete current;
  }

  /** Get elements method, returns the elements of the string_set in a vector
    */
  std::vector<std::string> string_set::get_elements()
  {
    std::vector<std::string> vec;
    vec.resize(size);
    node* current = head->nodes[0];
    for(int i = 0; i < size; i++)
      {
	vec[i] = current->data;
	current = current->get_next_node(0);
      }
    return vec;
  }
}
