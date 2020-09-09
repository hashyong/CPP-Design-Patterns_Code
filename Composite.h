// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/17 1:45 下午
// Description:
//

#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <string>

namespace composite {

class Component {
public:
  virtual void process() = 0;
  virtual ~Component() {}
};

//树节点
class Composite : public Component {
  string name;
  list<Component *> elements;

public:
  Composite(const string &s) : name(s) {}

  void add(Component *element) { elements.push_back(element); }
  void remove(Component *element) { elements.remove(element); }

  void process() {
    // 1. process current node
    // 2. process leaf nodes
    for (auto &e : elements)
      e->process(); //多态调用
  }
};

//叶子节点
class Leaf : public Component {
  string name;
public:
  Leaf(string s) : name(s) {}
  void process() {
    // process current node
  }
};

void Invoke(Component &c) {
  //...
  c.process();
  //...
}

int main() {

  Composite root("root");
  Composite treeNode1("treeNode1");
  Composite treeNode2("treeNode2");
  Composite treeNode3("treeNode3");
  Composite treeNode4("treeNode4");
  Leaf leaf1("left1");
  Leaf leaf2("left2");

  root.add(&treeNode1);
  treeNode1.add(&treeNode2);
  treeNode2.add(&leaf1);

  root.add(&treeNode3);
  treeNode3.add(&treeNode4);
  treeNode4.add(&leaf2);

  Invoke(root);
  Invoke(leaf2);
  Invoke(treeNode3);
}
} // namespace composite
