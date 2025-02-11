#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include "/opt/homebrew/include/libpq-fe.h"
// PGconn encapsulated a connection to the backend 
// PGresult encapsulates the result of a single SQL command (Query) -- A Query string given to PQsendQuery can conain multiple commands and thus return multiple PGresult objects)
// PGfinish closes the current connection and frees the PG conn data structure
void check_query(PGresult *results, PGconn *connection) {
  if (PQresultStatus(results) != PGRES_TUPLES_OK) {
    fprintf(stderr, "Line 7: Failed to Query: %s\n", PQerrorMessage(connection));
    PQclear(results);
    PQfinish(connection);
    exit(1);
  }
}

void query_database() {
  const char *connection_info = "dbname=dted_db user=ethan host=localhost";
  PGconn* connection = PQconnectdb(connection_info);
  PGresult* res;
  if (PQstatus(connection) != CONNECTION_OK) {
    fprintf(stderr, "Failed to create connection: %s\n", PQerrorMessage(connection));
    PQfinish(connection);
    exit(1);
  }

  // Would rather not hardcode these values
  double lon = -122.42;
  double lat = 37.77;

  char query[512];
  snprintf(query, sizeof(query),
           "SELECT ST_VALUE(rast, ST_SRID(ST_Point(%f, %f), 4326))"
           "FROM dted_table "
           "WHERE ST_Intersects(rast, ST_SetSRID(ST_Point(%f, %f), 4326));",
           lon, lat, lon, lat);
 
  res = PQexec(connection, query);
  check_query(res, connection);

  if (PQntuples(res) > 0) {
    printf("Elevation: %s meters\n", PQgetvalue(res, 0, 0));
  } 
  else {
    printf("No elevation data found at this location.\n");
  }

  PQclear(res);
  PQfinish(connection);
}

int main() {  
  query_database();
  return 0;
}
