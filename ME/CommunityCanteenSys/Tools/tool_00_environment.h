#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QSqlDatabase>

#define DELETE(ptr) if(ptr != nullptr) delete ptr

class Environment
{
public:
    Environment();
    ~Environment();

private:
    void make_mysql_db();
public:
    QSqlDatabase *mysql_db;
};

extern Environment ev;
#define EV ev
#define DB EV.mysql_db

#endif // ENVIRONMENT_H