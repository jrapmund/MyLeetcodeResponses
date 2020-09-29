#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

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

    //#594 Longest Harmonious Subsequence
    int findLHS(std::vector<int>& nums) {
        if (nums.size() <= 1)
            return 0;

        std::unordered_map<int, unsigned int> history;

        while (nums.size() > 0)
        {
            if (history.find(nums.back()) != history.end())
                history[nums.back()]++;
            else
                history[nums.back()] = 1;
            nums.pop_back();
        }

        int maxset = 0;

        for (std::unordered_map<int, unsigned int>::iterator place = history.begin(); place != history.end(); place++)
        {
            if (history.find(place->first - 1) != history.end())
            {
                if (maxset < place->second + history[place->first - 1])
                    maxset = place->second + history[place->first - 1];
            }

            if (history.find(place->first + 1) != history.end())
            {
                if (maxset < place->second + history[place->first + 1])
                    maxset = place->second + history[place->first + 1];
            }
        }

        return maxset;
    }
}