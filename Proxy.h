// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/16 1:31 下午
// Description:
//

#pragma once

namespace proxy {

class ISubject {
public:
  virtual void process() {}
};

class RealSubject : public ISubject {
public:
  virtual void process() {
    //....
  }
};

class ClientApp {
private:
  ISubject *subject;

public:
  ClientApp() { subject = new RealSubject(); }
  void DoTask() {
    //...
    subject->process();
    //....
  }
};

// Proxy的设计
class SubjectProxy : public ISubject {
public:
  virtual void process() {
    //对RealSubject的一种间接访问
    //....
  }
};

class ClientAppOpt {
private:
  ISubject *subject;

public:
  ClientAppOpt() { subject = new SubjectProxy(); }

  void DoTask() {
    //...
    subject->process();
    //....
  }
};
} // namespace proxy
