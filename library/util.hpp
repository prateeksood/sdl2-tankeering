#pragma once
#include <iostream>
#include <cstring>

#define _DEBUG 1

#define extends :public
#define of :

#define readonly(type, identifier) private: type _ ## identifier;\
  public: const type &identifier = _ ## identifier;

#if _DEBUG == 1
  #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
  #define log(text) std::cout << __FILENAME__ << " [" << __LINE__ << "]: " << text << std::endl
  #define log_as(variable) std::cout << __FILENAME__ << " [" << __LINE__ << "]: " << #variable << " = " << variable << std::endl;
#else
  #define log(text)
  #define log_as(variable)
#endif