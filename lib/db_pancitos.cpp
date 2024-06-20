#ifndef DB_PANCITOS_CPP
#define DB_PANCITOS_CPP

#include <iostream>
#include <string>
#include "db_pancitos.hpp"
#include "variables.hpp"
#include "postgresql/libpq-fe.h"

using namespace std;

dbPancitos::dbPancitos(/* args */)
{
  cout << "Conectando con la base de datos con la configuracion por defecto" << endl;
  string connInfo;
  connInfo.append("dbname=").append(DB_NAME).append(" user=").append(DB_USER).append(" password=").append(DB_PASSWORD).append(" host=").append(DB_HOST).append(" port=").append(DB_PORT);
  this->conn = PQconnectdb(connInfo.c_str());
  this->onInit();
}

dbPancitos::dbPancitos(string dbname, string user, string password, string host, string port)
{
  cout << "Conectando con la base de datos" << endl;
  string connInfo;
  connInfo.append("dbname=").append(dbname).append(" user=").append(user).append(" password=").append(password).append(" host=").append(host).append(" port=").append(port);
  this->conn = PQconnectdb(connInfo.c_str());
  this->onInit();
}

void dbPancitos::onInit()
{
  if (PQstatus(this->conn) != CONNECTION_OK)
  {
    std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
  }
  else
  {
    std::cout << "Connection to database successful" << std::endl;
    this->checkDB();
  }
}

Results dbPancitos::checkDB()
{
  std::cout << "Verificando base de datos..." << std::endl;
  if (this->tableExist(DB_TABLE_NAME) == NOT_EXIST)
  {
    this->createTable(DB_TABLE_NAME, TABLE_SCHEMA);
    cout << "Creando tabla" << endl;
    return SUCCESS;
  }
  else
  {
    cout << "La tabla ya existe" << endl;
    if (this->tableFollowsSchema(DB_TABLE_NAME, SCHEMA) == NOT_FOLLOW_SCHEMA)
    {
      cout << "La tabla no sigue el esquema" << endl;
      return NOT_FOLLOW_SCHEMA;
    }
    else
    {
      cout << "La tabla sigue el esquema" << endl;
      return SUCCESS;
    }
  }
}

Results dbPancitos::tableExist(string table)
{
  Results result = NOT_EXIST;
  PGresult *queryResult = PQexec(this->conn, string("SELECT table_name\n"
                                                    "FROM information_schema.tables\n"
                                                    "WHERE table_schema = 'public'\n"
                                                    "AND table_type = 'BASE TABLE';")
                                                 .c_str());
  if (PQresultStatus(queryResult) != PGRES_TUPLES_OK)
  {
    std::cout << "Error al hacer la consulta" << std::endl;
    cout << PQerrorMessage(this->conn) << endl;
    result = ERROR;
  }
  else
  {
    cout << endl;
    this->printTable(queryResult);
    cout << endl;
    std::cout << "Chequeando que exista la tabla " << std::endl;
    const unsigned char TABLE_COLUMN = 0;
    for (int i = 0; i < PQntuples(queryResult); i++)
    {
      const string table = string(PQgetvalue(queryResult, i, TABLE_COLUMN));
      if (table.compare(DB_TABLE_NAME) == STRINGS_ARE_EQUAL)
        result = EXIST;
    }
  }
  PQclear(queryResult);
  return result;
}

Results dbPancitos::tableFollowsSchema(string table, const char *SCHEMA[][2])
{
  Results result = FOLLOW_SCHEMA;
  PGresult *queryResult = PQexec(this->conn, string("SELECT column_name,\n"
                                                    "data_type\n"
                                                    "FROM information_schema.columns\n"
                                                    "WHERE table_name = '")
                                                 .append(table)
                                                 .append("' AND table_schema = 'public';")
                                                 .c_str());
  if (PQresultStatus(queryResult) != PGRES_TUPLES_OK)
  {
    cout << PQerrorMessage(this->conn) << endl;
    result = ERROR;
  }
  else
  {
    bool isModelFine = true;
    for (int i = 0; i < PQntuples(queryResult); i++)
    {
      bool columnExist = (string(PQgetvalue(queryResult, i, TABLE_COLUMN)))
                             .compare(SCHEMA[i][TABLE_COLUMN]) == STRINGS_ARE_EQUAL;
      bool correctDataType = (string(PQgetvalue(queryResult, i, DATA_TYPE_COLUMN))
                                  .compare(SCHEMA[i][DATA_TYPE_COLUMN])) == STRINGS_ARE_EQUAL;
      if (!columnExist || !correctDataType)
        result = NOT_FOLLOW_SCHEMA;
    }
  }
  PQclear(queryResult);
  return result;
}

Results dbPancitos::createTable(string table, string schema)
{
  Results result = SUCCESS;
  PGresult *queryResult = PQexec(this->conn, string("CREATE TABLE ").append(table).append(schema).c_str());
  if (PQresultStatus(queryResult) != PGRES_COMMAND_OK)
  {
    cout << PQerrorMessage(this->conn) << endl;
    result = ERROR;
  }
  PQclear(queryResult);
  return result;
}

dbPancitos::~dbPancitos()
{
  PQfinish(this->conn);
  cout << "Se desconecto" << endl;
}

void dbPancitos::printTable(PGresult *result)
{
  for (int i = 0; i < PQnfields(result); i++)
  {
    cout << PQfname(result, i) << "\t";
  }
  cout << endl;
  for (int i = 0; i < PQntuples(result); i++)
  {
    for (int j = 0; j < PQnfields(result); j++)
    {
      cout << PQgetvalue(result, i, j) << "\t";
    }
    cout << endl;
  }
}

#endif
