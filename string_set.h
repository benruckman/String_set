/* A 'string set' is defined as a set of strings stored
 * in sorted order in a drop list.  See the class video
 * for details.
 *
 * For lists that do not exceed 2 ^ (max_width + 1)
 * elements, the add, remove, and contains functions are 
 * O(lg size) on average.  The operator= and get_elements 
 * functions are O(size).   
 * 
 * Ben Ruckman
 * February 26, 2021
 */

#ifndef STRING_SET_H
#define STRING_SET_H

#include "node.h"  

namespace cs3505
{
  class string_set
    {
      //  Default visibility is private.  Except for debugging, you MUST 
      //  NOT add any additional instance variables to string_set objects.
      //  (Object variables should only hold object state.  You should 
      //  never communicate between functions with object variables - 
      //  use parameters and return values.)

      int max_width;  // The maximum width of of a drop list in each node

      node *head;     // The head of the list will sit in a sentinal node
                      // (without any data in it).  This sentinal node
                      // will have a maximum width next list.  The head
                      // sentinal node should be in heap memory.

      int size;       // The number of elements in the set

    public:
      string_set(int max_next_width = 12);   // Constructor.  Notice the default parameter value.
      string_set(const string_set &other);   // Copy constructor
      ~string_set();                         // Destructor

      void add      (const std::string &data);          // Not const - modifies the object
      void remove   (const std::string &data);          // Not const - modifies the object
      bool contains (const std::string &data) const;    // Const - does not change the object
      int  get_size () const;                           // Const - does not change object

      string_set & operator= (const string_set &rhs);   // Not const - modifies this object   

      std::vector<std::string> get_elements();          // Returns all the elements in this string_set,
                                                        // in ascending order.
    private:

      void set_string_set_to(const string_set &other);

      std::vector<node*> get_prior(const std::string &data) const;

      void recursive_prior(std::vector<node*> &prior, const std::string &data, int level, node* current) const;

  };

}

#endif
