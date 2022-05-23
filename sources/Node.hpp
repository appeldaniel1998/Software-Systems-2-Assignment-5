#include <iostream>
#include <string>
#include <vector>

namespace ariel
{
    class Node
    {
        private:
            std::string name;
            Node* parent;
            std::vector<Node*> children;
            uint level;
        
        public:
            static uint maxLevel;
            Node();
            Node(std::string inName);
            Node(std::string inName, Node& parent);
            void addChild(Node& other);
            Node* getParent();
            std::vector<Node*> getChildren();
            std::string getName();
            void setName(std::string str);
            uint getLevel() const;
    };
};