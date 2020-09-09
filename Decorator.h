// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/15 7:54 下午
// Description:
//

#pragma once
//业务操作
class Stream {
public:
  virtual char Read(int number) = 0;
  virtual void Seek(int position) = 0;
  virtual void Write(char data) = 0;

  virtual ~Stream() {}
};

//主体类
class FileStream : public Stream {
public:
  virtual char Read(int number) {
    //读文件流
  }
  virtual void Seek(int position) {
    //定位文件流
  }
  virtual void Write(char data) {
    //写文件流
  }
};

class NetworkStream : public Stream {
public:
  virtual char Read(int number) {
    //读网络流
  }
  virtual void Seek(int position) {
    //定位网络流
  }
  virtual void Write(char data) {
    //写网络流
  }
};

class MemoryStream : public Stream {
public:
  virtual char Read(int number) {
    //读内存流
  }
  virtual void Seek(int position) {
    //定位内存流
  }
  virtual void Write(char data) {
    //写内存流
  }
};

//扩展操作
class CryptoFileStream : public FileStream {
public:
  virtual char Read(int number) {

    //额外的加密操作...
    FileStream::Read(number); //读文件流
  }
  virtual void Seek(int position) {
    //额外的加密操作...
    FileStream::Seek(position); //定位文件流
    //额外的加密操作...
  }
  virtual void Write(char data) {
    //额外的加密操作...
    FileStream::Write(data); //写文件流
    //额外的加密操作...
  }
};

class CryptoNetworkStream : public NetworkStream {
public:
  virtual char Read(int number) {

    //额外的加密操作...
    NetworkStream::Read(number); //读网络流
  }
  virtual void Seek(int position) {
    //额外的加密操作...
    NetworkStream::Seek(position); //定位网络流
    //额外的加密操作...
  }
  virtual void Write(char data) {
    //额外的加密操作...
    NetworkStream::Write(data); //写网络流
    //额外的加密操作...
  }
};

class CryptoMemoryStream : public MemoryStream {
public:
  virtual char Read(int number) {

    //额外的加密操作...
    MemoryStream::Read(number); //读内存流
  }
  virtual void Seek(int position) {
    //额外的加密操作...
    MemoryStream::Seek(position); //定位内存流
    //额外的加密操作...
  }
  virtual void Write(char data) {
    //额外的加密操作...
    MemoryStream::Write(data); //写内存流
    //额外的加密操作...
  }
};

class BufferedFileStream : public FileStream {
  //...
};

class BufferedNetworkStream : public NetworkStream {
  //...
};

class BufferedMemoryStream : public MemoryStream {
  //...
};

class CryptoBufferedFileStream : public FileStream {
public:
  virtual char Read(int number) {

    //额外的加密操作...
    //额外的缓冲操作...
    FileStream::Read(number); //读文件流
  }
  virtual void Seek(int position) {
    //额外的加密操作...
    //额外的缓冲操作...
    FileStream::Seek(position); //定位文件流
    //额外的加密操作...
    //额外的缓冲操作...
  }
  virtual void Write(char data) {
    //额外的加密操作...
    //额外的缓冲操作...
    FileStream::Write(data); //写文件流
    //额外的加密操作...
    //额外的缓冲操作...
  }
};

void Dec_Process() {

  // 最开始为流，包括文件流，内存流，网络流
  // 然后开始整加密，使用继承实现，这必然是不好的
  // 加了缓存，这再一继承，不久傻逼了
  // 加密+缓存，崩了，指数级膨胀

  // 此时其实是为原来流加了新功能，走装饰模式好一点
  //编译时装配
  CryptoFileStream *fs1 = new CryptoFileStream();

  BufferedFileStream *fs2 = new BufferedFileStream();

  CryptoBufferedFileStream *fs3 = new CryptoBufferedFileStream();
}

//-----------------

//扩展操作, 使用组合来实现
class CryptoStream : public Stream {
private:
  Stream *stream; //...

public:
  CryptoStream(Stream *stm) : stream(stm) {}

  virtual char Read(int number) {
    //额外的加密操作...
    stream->Read(number); //读文件流
  }
  virtual void Seek(int position) {
    //额外的加密操作...
    stream->Seek(position); //定位文件流
    //额外的加密操作...
  }
  virtual void Write(char data) {
    //额外的加密操作...
    stream->Write(data); //写文件流
    //额外的加密操作...
  }
};

class BufferedStream : public Stream {
private:
  Stream *stream; //...

public:
  BufferedStream(Stream *stm) : stream(stm) {}
  //...

  virtual char Read(int number) {
    //额外的操作...
    stream->Read(number); //读文件流
  }
  virtual void Seek(int position) {
    //额外的操作...
    stream->Seek(position); //定位文件流
    //额外的加密操作...
  }
  virtual void Write(char data) {
    //额外的操作...
    stream->Write(data); //写文件流
    //额外的加密操作...
  }
};

//----------------------
// 再隔离的彻底一点

//扩展操作

class DecoratorStream : public Stream {
protected:
  Stream *stream; //...

  DecoratorStream(Stream *stm) : stream(stm) {}
};

class CryptoStreamOpt : public DecoratorStream {

public:
  CryptoStreamOpt(Stream *stm) : DecoratorStream(stm) {}

  virtual char Read(int number) {
    //额外的加密操作...
    stream->Read(number); //读文件流
  }
  virtual void Seek(int position) {
    //额外的加密操作...
    stream->Seek(position); //定位文件流
    //额外的加密操作...
  }
  virtual void Write(char data) {
    //额外的加密操作...
    stream->Write(data); //写文件流
    //额外的加密操作...
  }
};

class BufferedStreamOpt : public DecoratorStream {
public:
  BufferedStreamOpt(Stream *stm) : DecoratorStream(stm) {}
  //...
  virtual char Read(int number) {
    //额外的加密操作...
    stream->Read(number); //读文件流
  }
  virtual void Seek(int position) {
    //额外的加密操作...
    stream->Seek(position); //定位文件流
    //额外的加密操作...
  }
  virtual void Write(char data) {
    //额外的加密操作...
    stream->Write(data); //写文件流
    //额外的加密操作...
  }
};

void ProcessOpt() {
  //运行时装配, 叼的一批，很舒服，支持动态扩展功能，还能套娃, 扩展性极强
  auto *s1 = new FileStream();
  auto *s2 = new CryptoStream(s1);
  auto *s3 = new BufferedStream(s1);
  auto *s4 = new BufferedStream(s2);

  // 太骚了, c++有点意思啊， 设计模式有意思，装饰模式可以的，古人诚不我欺
  // 怪不得归并到单一职责模式里边去了，很有道理，类的职责要单一和清晰，给类动态加功能用装饰模式棒棒的
  auto* s5 = new CryptoStreamOpt(s1);
  auto* s6 = new BufferedStreamOpt(s5);
}