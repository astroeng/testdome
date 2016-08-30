//
// Derek Schacht | 2016 08 29
//
// Came across this website tonight, it has some interesting problems on it. I
// found a couple of them particularly interesting. The solution for this one
// enforces a time limit, which made my initial solution choke. The initial
// solution had about as much thought put into it as a intro programming class
// would expect. So I thought about it for a minute and came up with the second
// solution.
//
// Performance: with approx 2 million values in the list...
//   Four (4) sequential runs on a 2.4 GHz Core 2 Duo...
//   these runs were measured using the unix (Mac OS X) time command.
// findTwoSum     : 305m20.060s  ... not going to run that more than the once.
// findTwoSum_Map : 2.160s 2.066s 2.099s 2.056s
//
// Problem Statement and Website:
//
// https://www.testdome.com/Questions/Cpp/TwoSum/4779?testId=36&testDifficulty=Easy
//
// Write a function that, given a vector and a target sum, returns zero-based
// indices of any two distinct elements whose sum is equal to the target sum.
// If there are no such elements, the function should return (-1, -1).
//
// For example, findTwoSum({ 1, 3, 5, 7, 9 }, 12) should return any of the
// following pairs of indices:
//
//    1, 4 (3 + 9 = 12)
//    2, 3 (5 + 7 = 12)
//    3, 2 (7 + 5 = 12)
//    4, 1 (9 + 3 = 12)

#include <stdexcept>
#include <iostream>
#include <vector>
#include <map>
#include <utility>

class TwoSum
{
public:

    // This is the second solution that I came up with. It uses maps and the
    // find function.

    static std::pair<int, int> findTwoSum_Map(const std::vector<int>& list, int sum)
    {
        std::pair<int,int> output; // = {-1,-1};
        output.first = -1;
        output.second = -1;

        std::map<int,int> holder;
        std::map<int,int>::iterator thing;

        // Compute the pair values for each value in the list. This is the value
        // that will give the sum when added to the key.

        for (auto &item_a : list)
        {
            holder[item_a] = sum - item_a;
        }

        // Flip through the map and see if the original list contains the value
        // computed above. If it does figure out the index in the original list
        // of the key and computed value and return. I'm thinking there is a
        // better way to get the index back from the original list... something
        // for another day.

        for (auto &item_a : holder)
        {
            thing = holder.find(item_a.second);
            if (thing != holder.end())
            {
                for (std::vector<int>::size_type index_a = 0; index_a != list.size(); index_a++)
                {
                  if (list[index_a] == item_a.first)
                    output.first = index_a;
                  if (list[index_a] == item_a.second)
                    output.second = index_a;
                }
                return output;
            }
        }
        return output;
    }


    // First solution has an time limit issue when there are lots of values to
    // search through. Yeah... this is pretty much as brute force as it gets.

    static std::pair<int, int> findTwoSum(const std::vector<int>& list, int sum)
    {
        std::pair<int,int> output; // = {-1,-1};
        output.first = -1;
        output.second = -1;

        // Yay nested loops...
        for (std::vector<int>::size_type index_a = 0; index_a != list.size(); index_a++)
        {
            for (std::vector<int>::size_type index_b = 0; index_b != list.size(); index_b++)
            {
                if ((list[index_a] + list[index_b]) == sum)
                {
                    // Only required to find a single solution... save it and bail.
                    output.first = index_a;
                    output.second = index_b;
                    return output; // {index_a, index_b};
                }
            }
        }
        return output;
    }
};

int main()
{
    std::vector<int> list;

    // Make the list huge(ish) and put the solution values in the middle.
    for (int i = 12; i < 1000000; i++)
        list.push_back(i);

    list.push_back(1);
    list.push_back(3);
    list.push_back(5);
    list.push_back(7);
    list.push_back(9);

    for (int i = 12; i < 1000000; i++)
        list.push_back(i);

    std::pair<int, int> indices = TwoSum::findTwoSum(list, 12);
    std::cout << indices.first << ", " << indices.second << std::endl;
}
