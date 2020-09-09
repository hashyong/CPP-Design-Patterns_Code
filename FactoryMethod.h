// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/15 8:44 下午
// Description:
//

#pragma once

namespace factory {
class ISplitter {
public:
  ISplitter() = default;
  virtual void split(){};
  virtual ~ISplitter() = default;
};

class BinarySplitter : public ISplitter {};

class TxtSplitter : public ISplitter {};

class PictureSplitter : public ISplitter {};

class VideoSplitter : public ISplitter {};

//工厂基类
class SplitterFactory {
public:
  virtual ISplitter *CreateSplitter() = 0;
  virtual ~SplitterFactory() = default;
};

//具体工厂
class BinarySplitterFactory : public SplitterFactory {
public:
  virtual ISplitter *CreateSplitter() { return new BinarySplitter(); }
};

class TxtSplitterFactory : public SplitterFactory {
public:
  virtual ISplitter *CreateSplitter() { return new TxtSplitter(); }
};

class PictureSplitterFactory : public SplitterFactory {
public:
  virtual ISplitter *CreateSplitter() { return new PictureSplitter(); }
};

class VideoSplitterFactory : public SplitterFactory {
public:
  virtual ISplitter *CreateSplitter() { return new VideoSplitter(); }
};

class MainForm : public Form {
  TextBox *txtFilePath;
  TextBox *txtFileNumber;
  ProgressBar *progressBar;

public:
  void Button1_Click() {
    ISplitter *splitter = new BinarySplitter(); //依赖具体类
    splitter->split();
  }
};
class MainFormOpt : public Form {
private:
  SplitterFactory *factory; //工厂

public:
  MainFormOpt(SplitterFactory *factory) { this->factory = factory; }

  void Button1_Click() {
    ISplitter *splitter = factory->CreateSplitter(); //多态new, 依赖抽象类
    splitter->split();
  }
};

void test() {
  MainFormOpt form(new VideoSplitterFactory());
  form.Button1_Click();
}

} // namespace factory
