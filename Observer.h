// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/15 7:35 下午
// Description:
//

#pragma once

#include <list>

class ProgressBar {
public:
  void setValue(int value) {}
};

class FileSplitter {
  string m_filePath;
  int m_fileNumber;
  ProgressBar *m_progressBar;

public:
  FileSplitter(const string &filePath, int fileNumber, ProgressBar *progressBar)
      : m_filePath(filePath), m_fileNumber(fileNumber),
        m_progressBar(progressBar) {}

  void split() {

    // 1.读取大文件

    // 2.分批次向小文件中写入
    for (int i = 0; i < m_fileNumber; i++) {
      //...
      float progressValue = m_fileNumber;
      progressValue = (i + 1) / progressValue;
      // 只能通知给这一个processbar
      m_progressBar->setValue(progressValue);
    }
  }
};

class Form {};
class TextBox {
public:
  string getText() { return string(); }
};
class MainForm : public Form {
  TextBox *txtFilePath;
  TextBox *txtFileNumber;

  // 这里相当于展示相关的逻辑和form强绑定在一起了
  ProgressBar *progressBar;

public:
  void Button1_Click() {

    string filePath = txtFilePath->getText();
    int number = atoi(txtFileNumber->getText().c_str());

    FileSplitter splitter(filePath, number, progressBar);

    splitter.split();
  }
};

class IProgress {
public:
  virtual void DoProgress(float value) = 0;
  virtual ~IProgress() {}
};

class FileSplitterOpt {
  string m_filePath;
  int m_fileNumber;

  std::list<IProgress *> m_iprogressList; // 抽象通知机制，支持多个观察者

public:
  FileSplitterOpt(const string &filePath, int fileNumber)
      : m_filePath(filePath), m_fileNumber(fileNumber) {}

  void split() {

    // 1.读取大文件

    // 2.分批次向小文件中写入
    for (int i = 0; i < m_fileNumber; i++) {
      //...

      float progressValue = m_fileNumber;
      progressValue = (i + 1) / progressValue;
      onProgress(progressValue); //发送通知
    }
  }

  void addIProgress(IProgress *iprogress) {
    m_iprogressList.push_back(iprogress);
  }

  void removeIProgress(IProgress *iprogress) {
    m_iprogressList.remove(iprogress);
  }

protected:
  virtual void onProgress(float value) {
    auto itor = m_iprogressList.begin();
    while (itor != m_iprogressList.end())
      (*itor)->DoProgress(value); //更新进度条
    itor++;
  }
};

class ConsoleNotifier : public IProgress {
public:
  virtual void DoProgress(float value) { cout << "."; }
};

class MainFormOpt : public Form, public IProgress {
private:
  TextBox *txtFilePath;
  TextBox *txtFileNumber;
  ProgressBar *progressBar;

public:
  void Button1_Click() {

    string filePath = txtFilePath->getText();
    int number = atoi(txtFileNumber->getText().c_str());

    ConsoleNotifier cn;

    FileSplitterOpt splitter(filePath, number);

    splitter.addIProgress(this); //订阅通知
    splitter.addIProgress(&cn);  //订阅通知

    splitter.split();

    splitter.removeIProgress(this);
  }

  virtual void DoProgress(float value) { progressBar->setValue(value); }
};
