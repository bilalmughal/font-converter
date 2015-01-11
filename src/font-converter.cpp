/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Test Project for CXXTest
 *
 *        Version:  1.0
 *        Created:  01/09/2015 12:16:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mirza Bilal
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

using namespace std;
int main()
{
	cout<<"Hello CMake and CXXTest"<<endl;
	std::vector<char> v;
	if (FILE *file = fopen("main.cpp", "r")) {
	  char buf[1024];
	  while (size_t len = fread(buf, 1, sizeof(buf), file))
	    v.insert(v.end(), buf, buf + len);
	  fclose(file);
	  std::cout << v.size()<< endl;
	  for (std::vector<char>::const_iterator i = v.begin(); i != v.end(); ++i) {
	    std::cout << *i << endl;
	  }
	  
	}
	
	return 0;
}

