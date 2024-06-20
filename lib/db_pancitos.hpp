#ifndef DB_PANCITOS_HPP
#define DB_PANCITOS_HPP
#include "postgresql/libpq-fe.h"
#include <string>
#include "variables.hpp"

using namespace std;

class dbPancitos
{
private:
  PGconn *conn;
  /* data */
  void onInit();
  Results tableExist(string table);
  Results tableFollowsSchema(string table, const char *SCHEMA[][2]);
  Results createTable(string table, string schema);
  Results checkDB();
  void printTable(PGresult *result);

public:
  dbPancitos();
  dbPancitos(string dbname, string user, string password, string host, string port);
  ~dbPancitos();
};

#endif
