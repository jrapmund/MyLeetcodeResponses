#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace Leetcode
{
    //#697 Degree of an Array (decent speed and memory usage)=========================================================================================================================
     //struct to record frequency and locations (by me)
    struct value
    {
        unsigned int freq;
        std::size_t indexl;
        std::size_t indexr;
    };

    //Function
    int findShortestSubArray(std::vector<int>& nums) {

        //base case
        if (nums.size() <= 1)
            return nums.size();

        //map of instances of specific integer values and their frequency and starting and ending locations
        std::unordered_map<int, value> occurences;

        //map occurences
        for (std::size_t i = 0; i < nums.size(); i++)
        {
            if (occurences.find(nums[i]) != occurences.end())
            {
                occurences[nums[i]].freq++;
                occurences[nums[i]].indexr = i;
            }
            else
                occurences[nums[i]] = { 1, i, i };
        }

        //keeps track largest frequency
        unsigned int largestVal = 0;

        //keeps track of values that share the largest frequency
        std::vector<int> possibilities;

        //get values with largest frequency
        for (std::unordered_map<int, value>::iterator it = occurences.begin(); it != occurences.end(); it++)
        {
            if (it->second.freq > largestVal)
            {
                possibilities.clear();
                largestVal = it->second.freq;
                possibilities.push_back(it->first);
            }
            else if (it->second.freq == largestVal)
                possibilities.push_back(it->first);
        }

        //now looking for smallest subset size among possiblities (largestVal is now used as smallest val)
        largestVal = nums.size();

        //iterate through possiblities
        for (int pos : possibilities)
        {
            if (largestVal > occurences[pos].indexr - occurences[pos].indexl + 1)
                largestVal = occurences[pos].indexr - occurences[pos].indexl + 1;
        }

        return largestVal;
    }

    //#203 Remove Linked List Elements (mine is super slow and poopy) =====================================================================================================
    struct ListNode { //struct provided by leetcode
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}

    };

    //function
    ListNode* removeElements(ListNode* head, int val) {

        //base case
        if (!head)
            return nullptr;

        ListNode* curr = head;
        ListNode* prev = nullptr;

        //first check
        while (curr == head && curr)
        {
            if (curr->val == val)
            {
                if (curr->next)
                {
                    head = curr->next;
                    curr->next = nullptr;
                }
                else
                    head = nullptr;

                delete curr;
                curr = nullptr;

                curr = head;
            }
            else
            {
                prev = curr;
                if (curr->next)
                    curr = curr->next;
                else
                    curr = nullptr;
            }
        }

        //remaining checks
        while (curr)
        {
            if (curr->val == val)
            {
                if (curr->next)
                {
                    prev->next = curr->next;
                    curr->next = nullptr;
                }
                else
                    prev->next = nullptr;

                delete curr;

                if (prev->next)
                    curr = prev->next;
                else
                    curr = nullptr;
            }
            else
            {
                prev = curr;
                if (curr->next)
                    curr = curr->next;
                else
                    curr = nullptr;
            }
        }

        return head;
    }

	//#38 Count and Say ===================================================================================================================================================
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

    //#594 Longest Harmonious Subsequence =======================================================================================================================================================
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