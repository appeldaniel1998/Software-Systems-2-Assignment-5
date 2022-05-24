#include "Node.hpp"
#include <queue>
#include <stack>

namespace ariel
{
    class OrgChart
    {
        private:
            Node* root;

        public:
            OrgChart();
            // ~OrgChart();
            OrgChart add_root(std::string newRoot);
            OrgChart add_sub(const std::string& father, const std::string& child);
            
            friend std::ostream& operator<<(std::ostream& output, const OrgChart &org);

            class LevelOrderIterator
            {
                private:
                    int pointerIndToCurrNode;
                    std::vector<Node*>* iterVec;

                    void buildVec(std::queue<Node*> tempQ);
                public:
                    LevelOrderIterator(OrgChart* ptr = nullptr);
                    LevelOrderIterator(const LevelOrderIterator &other);
                    ~LevelOrderIterator();
                    LevelOrderIterator& operator=(const LevelOrderIterator& other);
                    LevelOrderIterator (LevelOrderIterator && obj) noexcept;
                    LevelOrderIterator& operator=(LevelOrderIterator&& other) noexcept;
                    std::string& operator*() const;
                    std::string* operator->() const;
                    LevelOrderIterator& operator++(); //++i
                    LevelOrderIterator operator++(int);
                    bool operator==(const LevelOrderIterator& iter) const;
                    bool operator!=(const LevelOrderIterator& iter) const;
                    int size();
                    std::vector<Node*>* getVec();
                    friend std::ostream& operator<<(std::ostream& output, const LevelOrderIterator &iterator);
            };
            class ReverseOrderIterator
            {
                private:
                    int pointerIndToCurrNode;
                    std::vector<Node*>* iterVec;

                    std::vector<Node*> buildVec(std::queue<Node*> tempQ, std::vector<Node*> tempVec);
                public:
                    ReverseOrderIterator(OrgChart* ptr = nullptr);
                    ReverseOrderIterator(const ReverseOrderIterator &other);
                    ~ReverseOrderIterator();
                    ReverseOrderIterator& operator=(const ReverseOrderIterator& other);
                    ReverseOrderIterator (ReverseOrderIterator && obj) noexcept;
                    ReverseOrderIterator& operator=(ReverseOrderIterator&& other) noexcept;
                    std::string& operator*() const;
                    std::string* operator->() const;
                    ReverseOrderIterator& operator++(); //++i
                    ReverseOrderIterator operator++(int);
                    bool operator==(const ReverseOrderIterator& iter) const;
                    bool operator!=(const ReverseOrderIterator& iter) const;
                    int size();
                    friend std::ostream& operator<<(std::ostream& output, const ReverseOrderIterator &iterator);
            };
            class PreOrderIterator
            {
                private:
                    int pointerIndToCurrNode;
                    std::vector<Node*>* iterVec;

                    void buildVec(Node& currNode);
                public:
                    PreOrderIterator(OrgChart* ptr = nullptr);
                    PreOrderIterator(const PreOrderIterator &other);
                    ~PreOrderIterator();
                    PreOrderIterator& operator=(const PreOrderIterator& other);
                    PreOrderIterator (PreOrderIterator && obj) noexcept;
                    PreOrderIterator& operator=(PreOrderIterator&& other) noexcept;
                    std::string& operator*() const;
                    std::string* operator->() const;
                    PreOrderIterator& operator++(); //++i
                    PreOrderIterator operator++(int);
                    bool operator==(const PreOrderIterator& iter) const;
                    bool operator!=(const PreOrderIterator& iter) const;
                    int size();
                    friend std::ostream& operator<<(std::ostream& output, const PreOrderIterator &iterator);
            };

            LevelOrderIterator begin_level_order();
            LevelOrderIterator end_level_order();

            ReverseOrderIterator begin_reverse_order();
            ReverseOrderIterator reverse_order();

            PreOrderIterator begin_preorder();
            PreOrderIterator end_preorder();

            LevelOrderIterator begin();
            static LevelOrderIterator end();
    };
};