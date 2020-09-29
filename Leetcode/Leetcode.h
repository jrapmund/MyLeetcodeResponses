#pragma once

#include <iostream>
#include <string>

namespace Leetcode
{
	//#38 Count and Say
    std::string countAndSay(int& n) {
        //default state
        if (n == 1) return "1";

        //recursive call
        n--;
        std::string state = countAndSay(n);
        std::string newState = "";

        //iterators
        std::string::iterator post, prev, curr;
        post = prev = curr = state.begin();

        //starting position
        curr++;

        //creation of new string
        while (curr != state.end())
        {
            //comparing values
            if (*prev != *curr)
            {
                newState += std::to_string(curr - post) + *prev;
                post = prev = curr;
            }
            else
                prev = curr;

            //increment
            curr++;
        }

        //final catch
        newState += std::to_string(curr - post) + *prev;

        return newState;
    }
}