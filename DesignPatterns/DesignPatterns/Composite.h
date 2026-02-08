#pragma once
#include <iostream>

class CompositeItem {
public:
    virtual ~CompositeItem() = default;
    virtual std::string Operation() = 0;
};

class Leaf : public CompositeItem {
public:
    std::string Operation() override {
        return "Leaf";
    }
};

class Composite : public CompositeItem {
private:
    std::pair<CompositeItem*, CompositeItem*> children {nullptr, nullptr};
public:
    std::string Operation() override {
        return "\nBranch (" + 
            (children.first ?  children.first->Operation(): "null") +
            ", " +
            (children.second? children.second->Operation(): "null") + " )";
    }

    void Add(CompositeItem* item) {
        if (children.first == nullptr)
            children.first = item;
        else if (children.second == nullptr)
            children.second = item;
        else
            std::cout << "full";
    }
};



void performComposite() {
    CompositeItem* leaf_1 = new Leaf, * leaf_2 = new Leaf, * leaf_3 = new Leaf, * leaf_4 = new Leaf;
    CompositeItem* test = leaf_1;
    CompositeItem* tree = new Composite;
    CompositeItem* branch_1 = new Composite, * branch_2 = new Composite;


    ((Composite*)branch_1)->Add(leaf_1);
    ((Composite*)branch_1)->Add(leaf_2);
    ((Composite*)branch_2)->Add(leaf_3);
    ((Composite*)branch_2)->Add(leaf_4);

    ((Composite*)tree)->Add(branch_1);
    ((Composite*)tree)->Add(branch_2);

    std::cout << tree->Operation();


    delete leaf_1; 
    delete leaf_2;
    delete leaf_3; 
    delete leaf_4; 
    delete branch_1;
    delete branch_2;
    delete tree;
}