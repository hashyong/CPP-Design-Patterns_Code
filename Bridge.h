// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/15 8:19 下午
// Description:
//

#pragma once

class Image {};
class Messager {
public:
  virtual void Login(string username, string password) = 0;
  virtual void SendMessage(string message) = 0;
  virtual void SendPicture(Image image) = 0;

  virtual void PlaySound() = 0;
  virtual void DrawShape() = 0;
  virtual void WriteText() = 0;
  virtual void Connect() = 0;

  virtual ~Messager() {}
};

//平台实现
class PCMessagerBase : public Messager {
public:
  virtual void PlaySound() {
    //**********
  }
  virtual void DrawShape() {
    //**********
  }
  virtual void WriteText() {
    //**********
  }
  virtual void Connect() {
    //**********
  }
};

class MobileMessagerBase : public Messager {
public:
  virtual void PlaySound() {
    //==========
  }
  virtual void DrawShape() {
    //==========
  }
  virtual void WriteText() {
    //==========
  }
  virtual void Connect() {
    //==========
  }
};

//业务抽象
class PCMessagerLite : public PCMessagerBase {
public:
  virtual void Login(string username, string password) {

    PCMessagerBase::Connect();
    //........
  }
  virtual void SendMessage(string message) {

    PCMessagerBase::WriteText();
    //........
  }
  virtual void SendPicture(Image image) {

    PCMessagerBase::DrawShape();
    //........
  }
};

class PCMessagerPerfect : public PCMessagerBase {
public:
  virtual void Login(string username, string password) {

    PCMessagerBase::PlaySound();
    //********
    PCMessagerBase::Connect();
    //........
  }
  virtual void SendMessage(string message) {

    PCMessagerBase::PlaySound();
    //********
    PCMessagerBase::WriteText();
    //........
  }
  virtual void SendPicture(Image image) {

    PCMessagerBase::PlaySound();
    //********
    PCMessagerBase::DrawShape();
    //........
  }
};

class MobileMessagerLite : public MobileMessagerBase {
public:
  virtual void Login(string username, string password) {

    MobileMessagerBase::Connect();
    //........
  }
  virtual void SendMessage(string message) {

    MobileMessagerBase::WriteText();
    //........
  }
  virtual void SendPicture(Image image) {

    MobileMessagerBase::DrawShape();
    //........
  }
};

class MobileMessagerPerfect : public MobileMessagerBase {
public:
  virtual void Login(string username, string password) {

    MobileMessagerBase::PlaySound();
    //********
    MobileMessagerBase::Connect();
    //........
  }
  virtual void SendMessage(string message) {

    MobileMessagerBase::PlaySound();
    //********
    MobileMessagerBase::WriteText();
    //........
  }
  virtual void SendPicture(Image image) {

    MobileMessagerBase::PlaySound();
    //********
    MobileMessagerBase::DrawShape();
    //........
  }
};

void Bridge_Process() {
  // 编译时装配
  // 两个方向的能力耦合在一起导致的, login和其余的 播放和画图等等
  Messager *m = new MobileMessagerPerfect();
}
//------期待这里看看具体咋优化呢，期望两个部分独立的变化

class MessagerImp {
public:
  virtual void PlaySound() = 0;
  virtual void DrawShape() = 0;
  virtual void WriteText() = 0;
  virtual void Connect() = 0;

  MessagerImp() = default;
};

class MessagerOpt {
protected:
  MessagerImp *messagerImp; //...
public:
  explicit MessagerOpt(MessagerImp *imp) : messagerImp(imp) {}
  virtual void Login(string username, string password) = 0;
  virtual void SendMessage(string message) = 0;
  virtual void SendPicture(Image image) = 0;

  virtual ~MessagerOpt() = default;
};

//平台实现 n
class PCMessagerImp : public MessagerImp {
public:
  virtual void PlaySound() {
    //**********
  }
  virtual void DrawShape() {
    //**********
  }
  virtual void WriteText() {
    //**********
  }
  virtual void Connect() {
    //**********
  }
};

class MobileMessagerImp : public MessagerImp {
public:
  virtual void PlaySound() {
    //==========
  }
  virtual void DrawShape() {
    //==========
  }
  virtual void WriteText() {
    //==========
  }
  virtual void Connect() {
    //==========
  }
};

//业务抽象 m

//类的数目：1+n+m

class MessagerLite : public MessagerOpt {
public:
  void Login(string username, string password) override {
    messagerImp->Connect();
    //........
  }
  void SendMessage(string message) override {
    messagerImp->WriteText();
    //........
  }
  void SendPicture(Image image) override {
    messagerImp->DrawShape();
    //........
  }
};

class MessagerPerfectOpt : public MessagerOpt {
public:
  explicit MessagerPerfectOpt(MessagerImp* imp) : MessagerOpt(imp){}
  void Login(string username, string password) override {
    messagerImp->PlaySound();
    //********
    messagerImp->Connect();
    //........
  }
  void SendMessage(string message) override {
    messagerImp->PlaySound();
    //********
    messagerImp->WriteText();
    //........
  }
  void SendPicture(Image image) override {
    messagerImp->PlaySound();
    //********
    messagerImp->DrawShape();
    //........
  }
};

void Process() {
  //运行时装配, 舒服了，两个类可以独立的变化，互相不影响，以组合的形态，棒棒的
  MessagerImp* mImp = new PCMessagerImp();
  MessagerOpt *m = new MessagerPerfectOpt(mImp);
}
