#include <iostream>
#include "postgresql/libpq-fe.h"

int main(/*int argc, char const *argv[]*/)
{
  // const char *conninfo = "dbname=mydb user=myuser password=mypassword";

  PGconn *conn = PQconnectdb("dbname=salchicha user=christian password=Perrosalchicha123 host=localhost port=5432");
  if (PQstatus(conn) != CONNECTION_OK)
  {
    std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
  }
  else
  {
    std::cout << "Connection to database successful" << std::endl;

    // Use the connection

    PQfinish(conn);
  }

  return 0;
}
