#include <sstream>
#include "doctest.h"
#include "sources/OrgChart.hpp"
#include <vector>

using namespace std;
using namespace ariel;

// string OstreamToString(std::ostream out) // Converting ostream to string and returning the string
// // Adapted from:
// // https://stackoverflow.com/questions/3513173/converting-ostream-into-standard-string
// {
//     stringstream ss;
//     ss << out.rdbuf();
//     string ret = ss.str();
//     return ret;
// }


TEST_CASE("Valid Cases")
{
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("Big Boss Temp"));
    CHECK_NOTHROW(organization.add_root("BigBoss")); //checking that an addition of a root for the 2nd time is acceptable
    CHECK_NOTHROW(organization.add_sub("BigBoss", "Boss")); //Checking the addition of 1 sub
    CHECK_NOTHROW(organization.add_sub("BigBoss", "Boss2")  //checking multiple additions in the same line
                              .add_sub("BigBoss", "Boss3")
                              .add_sub("Boss", "subBoss")
                              .add_sub("Boss2", "subBoss2"));

    vector<string> outputsLevelOrder{"BigBoss", "Boss" ,"Boss2", "Boss3", "subBoss", "subBoss2"};
    auto it = organization.begin_level_order();
    for (uint i = 0; i < outputsLevelOrder.size(); i++)
    {
        CHECK(*it == outputsLevelOrder[i]);
        CHECK_NOTHROW(++it);
    } // outputs and checks: BigBoss Boss Boss2 Boss3 subBoss subBoss2


    vector<string> outputsReverseOrder{"subBoss", "subBoss2", "Boss", "Boss2", "Boss3", "BigBoss"};
    auto it2 = organization.begin_reverse_order();
    for (uint i = 0; i < outputsReverseOrder.size(); i++)
    {
        CHECK(*it2 == outputsReverseOrder[i]);
        CHECK_NOTHROW(++it2);
    } // outputs and checks: subBoss subBoss2 Boss Boss2 Boss3 BigBoss


    vector<string> outputsPreOrder{"BigBoss", "Boss", "subBoss", "Boss2", "subBoss2", "Boss3"};
    auto it3 = organization.begin_preorder();
    for (uint i = 0; i < outputsPreOrder.size(); i++)
    {
        CHECK(*it3 == outputsPreOrder[i]);
        CHECK_NOTHROW(++it3);
    }  // outputs and checks: BigBoss Boss subBoss Boss2 subBoss2 Boss3


    vector<int> lengths{7, 4, 7, 5, 8, 5};
    auto it4 = organization.begin_level_order();
    for (uint i = 0; i < lengths.size(); i++)
    {
        CHECK(it4->size() == lengths[i]);
        CHECK_NOTHROW(++it4);
    }


    uint i = 0;
    for (auto element : organization) // this should work like level order
    {
        CHECK(element == outputsPreOrder[i]);
        i++;
    } // prints: BigBoss Boss Boss2 Boss3 subBoss subBoss2
}

TEST_CASE("Invalid Cases")
{
    OrgChart organization{};
    CHECK_THROWS(organization.add_sub("BigBoss", "Boss")); //adding sub before root
    CHECK_NOTHROW(organization.add_root("BigBoss")); //adding root
    CHECK_NOTHROW(organization.add_sub("BigBoss", "Boss")); //adding sub to root
    CHECK_THROWS(organization.add_sub("BigBoss1", "Boss")); //adding sub to non existent node
}