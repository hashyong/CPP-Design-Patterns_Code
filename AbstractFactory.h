// -*- coding: utf-8-unix; -*-
//
// Date: 2020/7/15 8:59 下午
// Description:
//

#pragma once

namespace abstract {

class EmployeeDO {};
class SqlConnection {
 public:
  string ConnectionString;
};

class SqlDataReader {
 public:
  bool Read() {}
};

class SqlCommand {
 public:
  string CommandText;
  void SetConnection(SqlConnection *conn) {}
  SqlDataReader *ExecuteReader() {}
};

class EmployeeDAO {
 public:
  vector<EmployeeDO> GetEmployees() {
    SqlConnection *connection = new SqlConnection();
    connection->ConnectionString = "...";

    SqlCommand *command = new SqlCommand();
    command->CommandText = "...";
    command->SetConnection(connection);

    SqlDataReader *reader = command->ExecuteReader();
    while (reader->Read()) {
    }
  }
};

//数据库访问有关的基类
class IDBConnection {
 public:
  virtual void ConnectionString(string test) {}
};
class IDBConnectionFactory {
 public:
  virtual IDBConnection *CreateDBConnection() = 0;
};

class IDBDataReader {
 public:
  virtual bool Read() {}
};
class IDataReaderFactory {
 public:
  virtual IDBDataReader *CreateDataReader() = 0;
};

class IDBCommand {
 public:
  virtual void CommandText(string test) {}
  virtual void SetConnection(IDBConnection *conn) {}
  IDBDataReader *ExecuteReader() {}
};
class IDBCommandFactory {
 public:
  virtual IDBCommand *CreateDBCommand() = 0;
};

//支持SQL Server
class SqlConnectionServer : public IDBConnection {};
class SqlConnectionFactory : public IDBConnectionFactory {};

class SqlCommandServer : public IDBCommand {};
class SqlCommandFactory : public IDBCommandFactory {};

class SqlDataReaderServer : public IDBDataReader {};
class SqlDataReaderFactory : public IDataReaderFactory {};

//支持Oracle
class OracleConnection : public IDBConnection {};
class OracleCommand : public IDBCommand {};
class OracleDataReader : public IDBDataReader {};

class EmployeeDAOOpt {
  IDBConnectionFactory *dbConnectionFactory;
  IDBCommandFactory *dbCommandFactory;
  IDataReaderFactory *dataReaderFactory;

 public:
  vector<EmployeeDO> GetEmployees() {
    IDBConnection *connection = dbConnectionFactory->CreateDBConnection();
    connection->ConnectionString("...");

    IDBCommand *command = dbCommandFactory->CreateDBCommand();
    command->CommandText("...");
    command->SetConnection(connection);  //关联性

    IDBDataReader *reader = command->ExecuteReader();  //关联性
    while (reader->Read()) {
    }
  }
};

//数据库访问有关的基类
class IDBConnectionOpt {
 public:
  virtual void ConnectionString(string test) {}
};
class IDataReaderOpt {
 public:
  virtual bool Read() {}
};

class IDBCommandOpt {
 public:
  virtual void CommandText(string test) {}
  virtual void SetConnection(IDBConnectionOpt *conn) {}
  virtual IDataReaderOpt *ExecuteReader() {}
};

class IDBFactoryOpt {
 public:
  virtual IDBConnectionOpt *CreateDBConnection() = 0;
  virtual IDBCommandOpt *CreateDBCommand() = 0;
  virtual IDataReaderOpt *CreateDataReader() = 0;
};

//支持SQL Server
class SqlConnectionOpt : public IDBConnectionOpt {};
class SqlCommandOpt : public IDBCommandOpt {};
class SqlDataReaderOpt : public IDataReaderOpt {};

class SqlDBFactory : public IDBFactoryOpt {
 public:
  IDBConnectionOpt *CreateDBConnection() override{};
  IDBCommandOpt *CreateDBCommand() override{};
  IDataReaderOpt *CreateDataReader() override{};
};

//支持Oracle
class OracleConnectionOpt : public IDBConnectionOpt {};
class OracleCommandOpt : public IDBCommandOpt {};
class OracleDataReaderOpt : public IDataReaderOpt {};

class EmployeeDAOOptFinal {
  IDBFactoryOpt *dbFactory;

 public:
  vector<EmployeeDO> GetEmployees() {
    auto *connection = dbFactory->CreateDBConnection();
    connection->ConnectionString("...");

    auto *command = dbFactory->CreateDBCommand();
    command->CommandText("...");
    command->SetConnection(connection);  //关联性

    auto *reader = command->ExecuteReader();  //关联性
    while (reader->Read()) {
    }
  }
};

}  // namespace abstract
