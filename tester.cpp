#include <iostream>
#include "string_set.h"
#include <string>

//Delcaration of unit test methods, before main method
bool test_constructor();
bool test_copy_constructor();
bool test_add();
bool test_remove();
bool test_contains();
bool test_get_size();
bool test_equals_operator();
bool test_get_elements();

int main()
{
  //if(test_constructor())
    {
      //std::cout << "Error in constructor" << std::endl;
    }
  if(test_copy_constructor())
    {
       std::cout << "Error in copy constructor" << std::endl;
    }
  else if(test_add())
    {
       std::cout << "Error in copy constructor" << std::endl;
    }
  else if(test_remove())
    {
       std::cout << "Error in copy constructor" << std::endl;
    }
  else if(test_contains())
    {
       std::cout << "Error in copy constructor" << std::endl;
    }
  else if(test_get_size())
    {
       std::cout << "Error in copy constructor" << std::endl;
    }
  else if(test_equals_operator())
    {
       std::cout << "Error in copy constructor" << std::endl;
    }
  else if(test_get_elements())
    {
       std::cout << "Error in copy constructor" << std::endl;
    }
  else
    std::cout << "No errors found" << std::endl;
  
  return 0;
};

bool test_constructor()
{
  //std::cout << "Starting new test level 8" << std::endl;
  //cs3505::string_set s = cs3505::string_set(8);
  //std::cout << "Starting new test level 7" << std::endl;
  //cs3505::string_set a = cs3505::string_set(7);
   std::cout << "Starting new test level 10000" << std::endl;
   cs3505::string_set b = cs3505::string_set(10000); // Weird error
  //cs3505::string_set c = cs3505::string_set(0);
   //if(s.get_size() != 0 || a.get_size() != 0/* || b.get_size() != 0*/)
   //return true;

   std::cout << "Deleting objects" << std::endl;
   //delete &s;
   //delete &a;
   delete &b;
   //~c;
   
  return false;

  
}

bool test_copy_constructor()
{
  std::cout << "Starting new test level 5, then adding words" << std::endl;
  cs3505::string_set s = cs3505::string_set(5);
  s.add("hello");
  s.add("darkness");
  s.add("my");
  s.add("old");
  s.add("friend");

  cs3505::string_set copy = cs3505::string_set(s);

  std::vector<std::string> elements = copy.get_elements();
  if(elements[0].compare("darkness") != 0)
    return true;
  if(elements[1].compare("friend") != 0)
    return true;
  if(elements[2].compare("hello") != 0)
    return true;
  if(elements[3].compare("my") != 0)
    return true;
  if(elements[4].compare("friend") != 0)
    return true;
  delete &s;
  delete &copy;

  return false;
}

bool test_add()
{
  return false;
}

bool test_remove()
{
  return false;
}

bool test_contains()
{
  return false;
}

bool test_get_size()
{
  return false;
}

bool test_equals_operator()
{
  return false;
}

bool test_get_elements()
{
  return false;
}

