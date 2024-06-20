#ifndef VARIABLES_CPP
#define VARIABLES_CPP
#include <string>

using namespace std;
const string DB_NAME = "salchicha";
const string DB_TABLE_NAME = "pancitos";
const string DB_USER = "christian";
const string DB_PASSWORD = "Perrosalchicha123";
const string DB_HOST = "localhost";
const string DB_PORT = "5432";
const int STRINGS_ARE_EQUAL = 0;
const string TABLE_SCHEMA = string(" (\n"
                                   "id INT,\n"
                                   "name VARCHAR(64),\n"
                                   "weight  REAL,\n"
                                   "gluten_free  BOOLEAN,\n"
                                   "price  MONEY,\n"
                                   "expiration_date  DATE\n"
                                   ")");
const char *SCHEMA[][2] = {
    {"id", "integer"},
    {"name", "character varying"},
    {"weight", "real"},
    {"gluten_free", "boolean"},
    {"price", "money"},
    {"expiration_date", "date"}};

enum Results
{
  ERROR = 0,
  EXIST,
  NOT_EXIST,
  FOLLOW_SCHEMA,
  NOT_FOLLOW_SCHEMA,
  SUCCESS
};

enum TableDefinitionSchemaColums
{
  TABLE_COLUMN = 0,
  DATA_TYPE_COLUMN = 1
};

enum TableSchemaColums
{
  ID_COLUMN = 0,
  NAME_COLUMN = 1,
  WEIGHT_COLUMN = 2,
  GLUTEN_FREE_COLUMN = 3,
  PRICE_COLUMN = 4,
  EXPIRATION_DATE_COLUMN = 5
};

#endif
