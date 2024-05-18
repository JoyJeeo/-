#include "tool_00_environment.h"

Environment ve_ev;
Environment::Environment()
{
    make_mysql_db();
}

Environment::~Environment()
{
    if(mysql_db){delete mysql_db; mysql_db = nullptr;}
}

void Environment::make_mysql_db()
{
    mysql_db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    mysql_db->setHostName("localhost");
    mysql_db->setUserName("root");
    mysql_db->setPassword("root");
    mysql_db->setDatabaseName("GraduationProject_CommunityCanteenSys");
    assert(DB->open());
}
