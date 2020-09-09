// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/16 1:44 下午
// Description:
//

#pragma once

#include <map>
using namespace std;

namespace mediator {

class Mediator;

class Colleague{
public:
  virtual ~Colleague()= default;

  virtual void sendmsg(int toWho,string str) = 0;
  virtual void receivemsg(string str) = 0;
  virtual void setMediator(Mediator* self) = 0;
};
class ConcreteColleagueA : public Colleague
{
public:
  ConcreteColleagueA()= default;
  ~ConcreteColleagueA() override= default;

  void sendmsg(int toWho,string str) override{}
  void receivemsg(string str) override{}

};

class Mediator{
public:
  virtual ~Mediator()= default;

  virtual void operation(int nWho,string str) = 0;
  virtual void registered(int nWho, Colleague * aColleague) = 0;

};

class ConcreteMediator : public Mediator
{

public:
  ConcreteMediator()= default;
  ~ConcreteMediator() override{}

  void operation(int nWho,string str) override{
    map<int,Colleague*>::const_iterator itr = m_mpColleague.find(nWho);
    if(itr == m_mpColleague.end())
    {
      cout << "not found this colleague!" << endl;
      return;
    }

    Colleague* pc = itr->second;
    pc->receivemsg(str);
  }

  void registered(int nWho, Colleague * aColleague) override{
    map<int,Colleague*>::const_iterator itr = m_mpColleague.find(nWho);
    if(itr == m_mpColleague.end())
    {
      m_mpColleague.insert(make_pair(nWho,aColleague));
      //同时将中介类暴露给colleague
      aColleague->setMediator(this);
    }
  }
private:
  map<int,Colleague*> m_mpColleague;
};

}