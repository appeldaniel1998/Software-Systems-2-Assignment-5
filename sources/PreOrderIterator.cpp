#include "OrgChart.hpp"

using namespace std;

namespace ariel
{
    OrgChart::PreOrderIterator::PreOrderIterator(OrgChart *ptr)
    {
        if (ptr != nullptr)
        {
            this->pointerIndToCurrNode = 0; //first element is 0
            this->iterVec = new vector<Node*>{ptr->root};

            buildVec(*ptr->root); //building an appropriate vector of poiters to iterate in the appropriate order
        }
        else
        {
            this->pointerIndToCurrNode = -1; //invalid index, should exit iterator when reached
            this->iterVec = new vector<Node*>{};
        }
    }
    OrgChart::PreOrderIterator::PreOrderIterator(const OrgChart::PreOrderIterator &other) //copy ctor
    {
        this->pointerIndToCurrNode = other.pointerIndToCurrNode;
        this->iterVec = other.iterVec;
    }

    void OrgChart::PreOrderIterator::buildVec(Node& currNode) //construction the vector of passing (recursive)
    {
        if (currNode.getChildren().empty()) //stopping when no more nodes
        {
            return;
        }

        for(uint i = 0; i < currNode.getChildren().size(); i++) //for every child of curr node
        {
            this->iterVec->push_back(currNode.getChildren().at(i));
            this->buildVec(*currNode.getChildren().at(i));
        }
    }

    OrgChart::PreOrderIterator::~PreOrderIterator()
    {
    //     for(uint i = 0; i < this->iterVec->size(); i++)
    //     {
    //         delete(this->iterVec->at(i));
    //     }
    //     delete(this->iterVec);
    }

    OrgChart::PreOrderIterator& OrgChart::PreOrderIterator::operator=(const PreOrderIterator& other)
    {
        *this = PreOrderIterator{other};
        return *this;
    }

    OrgChart::PreOrderIterator::PreOrderIterator (OrgChart::PreOrderIterator && obj) noexcept
    {
        // Move constructor
        // It will simply shift the resources,
        // without creating a copy.
        this->iterVec = obj.iterVec;
        obj.iterVec = nullptr;
        this->pointerIndToCurrNode = obj.pointerIndToCurrNode;
    }

    OrgChart::PreOrderIterator& OrgChart::PreOrderIterator::operator=(OrgChart::PreOrderIterator&& other) noexcept
    {
        return *this;
    }

    string& OrgChart::PreOrderIterator::operator*() const //accessing the name of the node (the only interesting information of the tree)
    {
        string* ret = new string(this->iterVec->at(uint(this->pointerIndToCurrNode))->getName());
        return *ret;
    }

    string* OrgChart::PreOrderIterator::operator->() const //accessing the name of the node (the only interesting information of the tree)
    {
        string* ret = new string(this->iterVec->at(uint(this->pointerIndToCurrNode))->getName());
        return ret;
    }

    OrgChart::PreOrderIterator& OrgChart::PreOrderIterator::operator++() //++i
    //Increasing the index by 1. When finished iterating the vector, set to -1 (should exit iterator)
    {
        this->pointerIndToCurrNode++;
        if (this->pointerIndToCurrNode == this->iterVec->size())
        {
            this->pointerIndToCurrNode = -1;
        }
        return *this;
    }

    OrgChart::PreOrderIterator OrgChart::PreOrderIterator::operator++(int) //i++
    //Increasing the index by 1. When finished iterating the vector, set to -1 (should exit iterator)
    {
        auto temp = *this;
        ++*this;
        return temp;
    }

    bool OrgChart::PreOrderIterator::operator==(const OrgChart::PreOrderIterator& iter) const
    // returning true if the names are identical
    {
        return this->pointerIndToCurrNode == iter.pointerIndToCurrNode;
    }

    bool OrgChart::PreOrderIterator::operator!=(const OrgChart::PreOrderIterator& iter) const
    {
        return !(*this == iter);
    }

    int OrgChart::PreOrderIterator::size() //return the length of the name of the current entity
    {
        return this->iterVec->at(uint(this->pointerIndToCurrNode))->getName().size();
    }

    ostream& operator<<(ostream& output, const OrgChart::PreOrderIterator &iterator) //exports the name of the entity into an ostream
    {
        output << iterator.iterVec->at(uint(iterator.pointerIndToCurrNode))->getName();
        return output;
    }
}