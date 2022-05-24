#include "OrgChart.hpp"

using namespace std;

namespace ariel
{
    OrgChart::LevelOrderIterator::LevelOrderIterator(OrgChart *ptr)
    {
        if (ptr != nullptr)
        {
            this->pointerIndToCurrNode = 0; //first element is 0
            this->iterVec = new vector<Node*>{ptr->root};

            queue<Node*> tempQ; //init queue to define order of Level Order pass
            tempQ.push(ptr->root); //enter the first (root) element in to the queue

            buildVec(tempQ); //building an appropriate vector of poiters to iterate in the appropriate order
        }
        else
        {
            this->pointerIndToCurrNode = -1; //invalid index, should exit iterator when reached
            this->iterVec = new vector<Node*>{};
        }
    }
    OrgChart::LevelOrderIterator::LevelOrderIterator(const OrgChart::LevelOrderIterator &other) //copy ctor
    {
        this->pointerIndToCurrNode = other.pointerIndToCurrNode;
        this->iterVec = other.iterVec;
    }

    void OrgChart::LevelOrderIterator::buildVec(queue<Node*> tempQ) //construction the vector of passing (recursive)
    {
        if (tempQ.empty()) //stopping when no more nodes
        {
            return;
        }

        Node* tempNode = tempQ.front();
        for(uint i = 0; i < tempNode->getChildren().size(); i++) //for every child of curr node
        {
            tempQ.push(tempNode->getChildren().at(i));
            this->iterVec->push_back(tempNode->getChildren().at(i));
        }
        tempQ.pop();
        buildVec(tempQ);
    }

    OrgChart::LevelOrderIterator::~LevelOrderIterator()
    {
        // for(uint i = 0; i < this->iterVec->size(); i++)
        // {
        //     delete(this->iterVec->at(i));
        // }
        // delete(this->iterVec);
    }

    OrgChart::LevelOrderIterator& OrgChart::LevelOrderIterator::operator=(const LevelOrderIterator& other)
    {
        *this = LevelOrderIterator{other};
        return *this;
    }

    OrgChart::LevelOrderIterator::LevelOrderIterator (OrgChart::LevelOrderIterator && obj) noexcept
    {
        // Move constructor
        // It will simply shift the resources,
        // without creating a copy.
        this->iterVec = obj.iterVec;
        obj.iterVec = nullptr;
        this->pointerIndToCurrNode = obj.pointerIndToCurrNode;
    }

    string& OrgChart::LevelOrderIterator::operator*() const //accessing the name of the node (the only interesting information of the tree)
    {
        string* ret = new string(this->iterVec->at(uint(this->pointerIndToCurrNode))->getName());
        return *ret;
    }

    OrgChart::LevelOrderIterator& OrgChart::LevelOrderIterator::operator=(OrgChart::LevelOrderIterator&& other) noexcept
    {
        return *this;
    }

    string* OrgChart::LevelOrderIterator::operator->() const //accessing the name of the node (the only interesting information of the tree)
    {
        string* ret = new string(this->iterVec->at(uint(this->pointerIndToCurrNode))->getName());
        return ret;
    }

    OrgChart::LevelOrderIterator& OrgChart::LevelOrderIterator::operator++() //++i
    //Increasing the index by 1. When finished iterating the vector, set to -1 (should exit iterator)
    {
        this->pointerIndToCurrNode++;
        if (this->pointerIndToCurrNode == this->iterVec->size())
        {
            this->pointerIndToCurrNode = -1;
        }
        return *this;
    }

    OrgChart::LevelOrderIterator OrgChart::LevelOrderIterator::operator++(int) //i++
    //Increasing the index by 1. When finished iterating the vector, set to -1 (should exit iterator)
    {
        auto temp = *this;
        ++*this;
        return temp;
    }

    bool OrgChart::LevelOrderIterator::operator==(const OrgChart::LevelOrderIterator& iter) const
    // returning true if the names are identical
    {
        return this->pointerIndToCurrNode == iter.pointerIndToCurrNode;
    }

    bool OrgChart::LevelOrderIterator::operator!=(const OrgChart::LevelOrderIterator& iter) const
    {
        return !(*this == iter);
    }

    int OrgChart::LevelOrderIterator::size() //return the length of the name of the current entity
    {
        return this->iterVec->at(uint(this->pointerIndToCurrNode))->getName().size();
    }

    vector<Node*>* OrgChart::LevelOrderIterator::getVec() //return the vector of the iterator. Used only in add_sub function in Orgchart.cpp.
    {
        return this->iterVec;
    }

    ostream& operator<<(ostream& output, const OrgChart::LevelOrderIterator &iterator) //exports the name of the entity into an ostream
    {
        output << iterator.iterVec->at(uint(iterator.pointerIndToCurrNode))->getName();
        return output;
    }
}