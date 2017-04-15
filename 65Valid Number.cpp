//
//  main.cpp
//  GoLeet
//
//  Created by frankan on 2017/4/15.
//  Copyright © 2017年 frankan. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;


bool IsMinus(char c)
{
    return c=='-' || c=='+';
}

bool IsNum(char c)
{
    return c>='0' && c<='9';
}

bool ContainValue(const string& s)
{
    for (auto it:s) {
        if(IsNum(it))
        {
            return true;
        }
    }
    return false;
}

bool IsInt(const string& s, bool emptyCase, bool minusCase, bool singleMinus)
{
    if(s.empty())
    {
        return emptyCase;
    }
    
    for (int i=0; i<s.size(); i++) {
        const char c = s[i];
        if(IsMinus(c))
        {
            if(i!=0 || minusCase==false)
            {
                return false;
            }
            else if(s.size()==1 && singleMinus==false)
            {
                return false;
            }
            else
            {
                continue;
            }
        }
        
        if(!IsNum(c))
        {
            return false;
        }
    }
    
    return true;
}

bool IsNumValid(const string& s, bool emptyCase)
{
    if(s.empty()||(s.size()==1 && IsMinus(s[0])))
    {
        return emptyCase;
    }
    
    auto pointPos = s.find_first_of('.');
    
    if(pointPos==string::npos)
    {
        return IsInt(s,false,true,true);
    }
    else if(s.size()==1)
    {
        return false;
    }
    else
    {
        string prePoint = s.substr(0, pointPos);
        string postPoint = s.substr(pointPos+1, s.size()-pointPos-1);

        if(!ContainValue(prePoint) && !ContainValue(postPoint))
        {
            return false;
        }
        return IsInt(prePoint,true,true,true) && IsInt(postPoint,true,false,false);
    }
}



class Solution {
public:
    bool isNumber(string s) {
        if(s.empty())
        {
            return false;
        }
        
        //remove space in the beginning and end
        int nonSpaceStart = (int)s.find_first_not_of(' ');
        int nonSpaceLast = (int)s.find_last_not_of(' ');
        int startPos = nonSpaceStart == string::npos ? 0 : nonSpaceStart;
        int len = nonSpaceLast==string::npos?(int)(s.length()-startPos):nonSpaceLast-startPos+1;
        s = s.substr(startPos, len);
        
        string result;
        int epos = -1;
        for (auto it=s.begin(); it!=s.end(); it++) {
            const char c = *it;
            //ecase
            if(c == ' ')
            {
                return false;
            }
            else if(c=='e' || c=='E')
            {
                if(epos!=-1)
                {
                    return false;
                }
                else{
                    epos = (int)result.size();
                    result.push_back(*it);
                }
            }
            else if(!IsNum(c) && !IsMinus(c) && c!='.')
            {
                return false;
            }
            else
            {
                result.push_back(c);
            }
        }
        
        //e case
        if(epos!=-1)
        {
            string preE = result.substr(0, epos);
            string postE = result.substr(epos+1, result.size()-epos-1);
            return IsNumValid(preE,false) && IsInt(postE,false,true,false);
        }
        else
        {
            return IsNumValid(result,false);
        }
    }
};

void p(const string& v)
{
    Solution s;
    cout<<v<<" : "<<s.isNumber(v)<<endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Solution s;
    cout<<1e10<<endl;
    std::cout<<s.isNumber("asdf")<<endl;
    std::cout<<s.isNumber("10")<<endl;
    std::cout<<s.isNumber("1.1")<<endl;
    cout<<s.isNumber("1.1f")<<endl;
    cout<<s.isNumber("1e10")<<endl;
    cout<<s.isNumber("1.1e10")<<endl;
    cout<<s.isNumber("1e1.1")<<endl;
    cout<<s.isNumber("e")<<endl;
    cout<<s.isNumber("1. 2")<<endl;
    p("1e+");
    p(".-4");
    p("+.8");
    p("+-.");
    return 0;
}

