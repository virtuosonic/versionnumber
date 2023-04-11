/*****************************
Name:		versioning.h
Author:		Gabriel Espinoza <virtuosonic at github.com
Date:		2023-04-10
*/

#ifndef VIRTUOSONIC_VERSIONING_H
#define VIRTUOSONIC_VERSIONING_H


#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <algorithm>

namespace virtuosonic {

//API

struct Version{
	int Major;
	int Minor;
	int Revision;
	Version();
	Version(std::string versionString);
	std::string str() const;
	std::array<int,3> arr() const;
	bool isOK() { return Major || Minor || Revision; }
};


bool operator== (const Version& v1,const Version& v2);

bool operator!= (const Version& v1,const Version& v2);

bool operator< (const Version& v1,const Version& v2);

bool operator> (const Version& v1,const Version& v2);

bool operator<= (const Version& v1,const Version& v2);

bool operator>= (const Version& v1,const Version& v2);

std::ostream& operator<<(std::ostream& os, const Version& v);

//implementation below
Version::Version() : Major(0),
	Minor(0),
	Revision(0)
{
}


void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

std::vector<std::string> split(const char *str, const char c )
{
    std::vector<std::string> result;
    do
    {
        const char *begin = str;
        //increase pointer until c is found
        while(*str != c && *str)
            str++;
		//if both pointer are equal ignore, else add
        if ( begin != str )
            result.push_back(std::string(begin, str));
		//jump the c found
    } while (0 != *str++);

    return result;
}


Version::Version(std::string versionString) : Version()
{
	trim(versionString);
	auto tokens = split(versionString.c_str(),'.');
	for ( unsigned i = 0 ; i < tokens.size() ; ++i )
    {
        switch (i) {
        case 0:
			Major = stoi(tokens[i]);
            break;
        case 1:
			Minor = stoi(tokens[i]);
            break;
        case 2:
			Revision = stoi(tokens[i]);
            break;
        }
    }
}

std::string Version::str() const
{
	std::ostringstream os;
	os << *this;
	return os.str();
}

std::array<int, 3> Version::arr() const
{
	return std::array<int, 3>{Major,Minor,Revision};
}

bool operator==(const Version &v1, const Version &v2)
{
	auto a1 = v1.arr();
	auto a2 = v2.arr();
	return std::equal(a1.begin(),a1.end(),a2.begin());
}

bool operator!=(const Version &v1, const Version &v2)
{
    return !(operator== (v1,v2));
}

bool operator<(const Version &v1, const Version &v2)
{
	auto a1 = v1.arr();
	auto a2 = v2.arr();
	for ( unsigned i = 0 ; i < a1.size(); ++i )
    {
		if( a1[i] > a2[i])
			return false;
        if (a1[i] < a2[i])
            return true;
    }
    return false;
}

bool operator>(const Version &v1, const Version &v2)
{
    return operator< (v2,v1);
}

bool operator<=(const Version &v1, const Version &v2)
{
    return !(operator>(v1,v2));
}

bool operator>=(const Version &v1, const Version &v2)
{
    return !(operator<(v1,v2));
}

std::ostream &operator<<(std::ostream &os, const Version &v)
{
    os << v.Major << '.'
       << v.Minor << '.'
	   << v.Revision ;
    return os;
}

}

#endif // VIRTUOSONIC_VERSIONING_H
