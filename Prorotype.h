// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/15 9:22 下午
// Description:
//

#pragma once

namespace prototype {

//抽象类
class ISplitter {
public:
  virtual void split(){};
  virtual ISplitter *clone() = 0; //通过克隆自己来创建对象

  virtual ~ISplitter() {}
};

class MainForm : public Form {
  ISplitter *prototype; //原型对象

public:
  MainForm(ISplitter *prototype) { this->prototype = prototype; }

  void Button1_Click() {
    ISplitter *splitter = prototype->clone(); //克隆原型
    splitter->split();
  }
};

//具体类
class BinarySplitter : public ISplitter {
public:
  virtual ISplitter *clone() { return new BinarySplitter(*this); }
};

class TxtSplitter : public ISplitter {
public:
  virtual ISplitter *clone() { return new TxtSplitter(*this); }
};

class PictureSplitter : public ISplitter {
public:
  virtual ISplitter *clone() { return new PictureSplitter(*this); }
};

class VideoSplitter : public ISplitter {
public:
  virtual ISplitter *clone() { return new VideoSplitter(*this); }
};

void test(){
 MainForm obj(new BinarySplitter());
 obj.Button1_Click();
}

} // namespace prototype
