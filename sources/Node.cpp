#include "Node.hpp"

using namespace std;

namespace ariel
{
    uint Node::maxLevel = 0;

    Node::Node()
    {
        this->name = "";
        this->parent = nullptr;
        this->children = vector<Node*>{};
        this->level = 0;
    }

    Node::Node(std::string inName)
    {
        this->name = move(inName);
        this->parent = new Node{};
        this->children = vector<Node*>{};
        this->level = 0;
        Node::maxLevel = 0;
    }

    Node::Node(std::string inName, Node& parent)
    {
        this->name = move(inName);
        this->parent = &parent;
        this->children = vector<Node*>{};
        this->level = parent.level+1;
        if (Node::maxLevel < this->level)
        {
            Node::maxLevel = this->level;
        }
    }

    void Node::addChild(Node& other)
    {
        this->children.push_back(&other);
    }

    Node* Node::getParent()
    {
        return this->parent;
    }

    vector<Node*> Node::getChildren()
    {
        return this->children;
    }

    string Node::getName()
    {
        return this->name;
    }

    void Node::setName(std::string str)
    {
        this->name = move(str);
    }

    uint Node::getLevel() const
    {
        return this->level;
    }
}