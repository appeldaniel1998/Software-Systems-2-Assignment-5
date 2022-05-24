#include "OrgChart.hpp"

using namespace std;

namespace ariel
{
    OrgChart::ReverseOrderIterator::ReverseOrderIterator(OrgChart *ptr)
    {
        if (ptr != nullptr)
        {
            this->pointerIndToCurrNode = 0; //first element is 0
            this->iterVec = new vector<Node*>{};

            queue<Node*> tempQ; //init queue to define order of Reverse Level Order pass
            tempQ.push(ptr->root); //enter the first (root) element in to the queue

            vector<Node*> tempVec;

            tempVec = buildVec(tempQ, tempVec); //building an appropriate vector of poiters to iterate in the appropriate order

            uint currLevel = Node::maxLevel;
            while(this->iterVec->size() != tempVec.size())
            {
                for (uint i = 0; i < tempVec.size(); i++)
                {
                    if (tempVec.at(i)->getLevel() == currLevel)
                    {
                        this->iterVec->push_back(tempVec.at(i));
                    }
                }
                currLevel--;
            }
        }
        else
        {
            this->pointerIndToCurrNode = -1; //invalid index, should exit iterator when reached
            this->iterVec = new vector<Node*>{};
        }
    }
    OrgChart::ReverseOrderIterator::ReverseOrderIterator(const OrgChart::ReverseOrderIterator &other) //copy ctor
    {
        this->pointerIndToCurrNode = other.pointerIndToCurrNode;
        this->iterVec = other.iterVec;
    }

    vector<Node*> OrgChart::ReverseOrderIterator::buildVec(queue<Node*> tempQ, vector<Node*> tempVec) //construction the vector of passing (recursive)
    {
        if (tempQ.empty()) //stopping when no more nodes
        {
            return tempVec;
        }

        Node* tempNode = tempQ.front();
        for(uint i = 0; i < tempNode->getChildren().size(); i++) //for every child of curr node
        {
            tempQ.push(tempNode->getChildren().at(i));
        }
        tempVec.push_back(tempQ.front());
        tempQ.pop();

        return buildVec(tempQ, tempVec);
    }

    OrgChart::ReverseOrderIterator::~ReverseOrderIterator()
    {
        // for(uint i = 0; i < this->iterVec->size(); i++)
        // {
        //     delete(this->iterVec->at(i));
        // }
        // delete(this->iterVec);
    }

    OrgChart::ReverseOrderIterator& OrgChart::ReverseOrderIterator::operator=(const ReverseOrderIterator& other)
    {
        *this = ReverseOrderIterator{other};
        return *this;
    }

    OrgChart::ReverseOrderIterator::ReverseOrderIterator (OrgChart::ReverseOrderIterator && obj) noexcept
    {
        // Move constructor
        // It will simply shift the resources,
        // without creating a copy.
        this->iterVec = obj.iterVec;
        obj.iterVec = nullptr;
        this->pointerIndToCurrNode = obj.pointerIndToCurrNode;
    }

    OrgChart::ReverseOrderIterator& OrgChart::ReverseOrderIterator::operator=(OrgChart::ReverseOrderIterator&& other) noexcept
    {
        return *this;
    }

    string& OrgChart::ReverseOrderIterator::operator*() const //accessing the name of the node (the only interesting information of the tree)
    {
        string* ret = new string(this->iterVec->at(uint(this->pointerIndToCurrNode))->getName());
        return *ret;
    }

    string* OrgChart::ReverseOrderIterator::operator->() const //accessing the name of the node (the only interesting information of the tree)
    {
        string* ret = new string(this->iterVec->at(uint(this->pointerIndToCurrNode))->getName());
        return ret;
    }

    OrgChart::ReverseOrderIterator& OrgChart::ReverseOrderIterator::operator++() //++i
    //Increasing the index by 1. When finished iterating the vector, set to -1 (should exit iterator)
    {
        this->pointerIndToCurrNode++;
        if (this->pointerIndToCurrNode == this->iterVec->size())
        {
            this->pointerIndToCurrNode = -1;
        }
        return *this;
    }

    OrgChart::ReverseOrderIterator OrgChart::ReverseOrderIterator::operator++(int) //i++
    //Increasing the index by 1. When finished iterating the vector, set to -1 (should exit iterator)
    {
        auto temp = *this;
        ++*this;
        return temp;
    }

    bool OrgChart::ReverseOrderIterator::operator==(const OrgChart::ReverseOrderIterator& iter) const
    // returning true if the names are identical
    {
        return this->pointerIndToCurrNode == iter.pointerIndToCurrNode;
    }

    bool OrgChart::ReverseOrderIterator::operator!=(const OrgChart::ReverseOrderIterator& iter) const
    {
        return !(*this == iter);
    }

    int OrgChart::ReverseOrderIterator::size() //return the length of the name of the current entity
    {
        return this->iterVec->at(uint(this->pointerIndToCurrNode))->getName().size();
    }

    ostream& operator<<(ostream& output, const OrgChart::ReverseOrderIterator &iterator) //exports the name of the entity into an ostream
    {
        output << iterator.iterVec->at(uint(iterator.pointerIndToCurrNode))->getName();
        return output;
    }
}