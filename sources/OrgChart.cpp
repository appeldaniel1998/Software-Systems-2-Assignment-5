#include "OrgChart.hpp"

using namespace std;

namespace ariel
{
    OrgChart::OrgChart()
    {
        this->root = new Node{""};
    }

    // OrgChart::~OrgChart()
    // {
    //     delete(this->root);
    // }

    OrgChart OrgChart::add_root(string newRoot)
    {
        this->root->setName(move(newRoot));
        return *this;
    }

    OrgChart OrgChart::add_sub(const string& father, const string& child)
    {
        if(this->root->getName().empty())
        {
            __throw_invalid_argument("can't add sub before root");
        }

        bool flag = false;
        auto it = this->begin_level_order();
        vector<Node*> vec = *(it.getVec());

        for (uint i = 0; i < vec.size(); i++)
        {
            if(vec.at(i)->getName() == father)
            {
                Node* newNode = new Node{child, *vec.at(i)};
                vec.at(i)->addChild(*newNode);
                flag = true;
                break;
            }
        }
        if(!flag)
        {
            __throw_invalid_argument("employer doesn't exist");
        }
        return *this;
    }
    
    ostream& operator<<(ostream& output, const OrgChart &org) //unimplemented
    {
        return output;
    }

    OrgChart::LevelOrderIterator OrgChart::begin_level_order()
    {
        if(this->root->getName().empty())
        {
            __throw_invalid_argument("chart is empty!");
        }
        LevelOrderIterator temp{this};
        return temp;
    }

    OrgChart::LevelOrderIterator OrgChart::end_level_order()
    {
        if(this->root->getName().empty())
        {
            __throw_invalid_argument("chart is empty!");
        }
        LevelOrderIterator temp{nullptr};
        return temp;
    }

    OrgChart::ReverseOrderIterator OrgChart::begin_reverse_order()
    {
        if(this->root->getName().empty())
        {
            __throw_invalid_argument("chart is empty!");
        }
        ReverseOrderIterator temp{this};
        return temp;
    }

    OrgChart::ReverseOrderIterator OrgChart::reverse_order()
    {
        if(this->root->getName().empty())
        {
            __throw_invalid_argument("chart is empty!");
        }
        ReverseOrderIterator temp{nullptr};
        return temp;
    }

    OrgChart::PreOrderIterator OrgChart::begin_preorder()
    {
        if(this->root->getName().empty())
        {
            __throw_invalid_argument("chart is empty!");
        }
        PreOrderIterator temp{this};
        return temp;
    }

    OrgChart::PreOrderIterator OrgChart::end_preorder()
    {
        if(this->root->getName().empty())
        {
            __throw_invalid_argument("chart is empty!");
        }
        PreOrderIterator temp{nullptr};
        return temp;
    }

    OrgChart::LevelOrderIterator OrgChart::begin()
    {
        LevelOrderIterator temp{this};
        return temp;
    }
    OrgChart::LevelOrderIterator OrgChart::end()
    {
        LevelOrderIterator temp{nullptr};
        return temp;
    }
}