/****************************
Name:       versionnumber/usage.cpp
Author:     Gabriel Espinoza <virtuosonic at github.com>
Date:       2023-04-11
License:    MIT
*/

#include "versioning.h"
#include <iostream>

using virtuosonic::Version;
using namespace std;

int main()
{
    Version v1("1.0");
    Version v2;
    v2.Major = 1;
    v2.Minor = 2;
    v2.Revision = 3;
    if (v1 > v2)
    {
        cout << v1 << " is newest" << endl;
    }
    else if(v1 == v2)
    {
        cout << v1 <<" == " << v2;
    }
    else
    {
        cout << v2 << " > " << v1;
    }

    return 0;
}