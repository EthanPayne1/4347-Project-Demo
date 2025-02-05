#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include "/opt/homebrew/Cellar/libpq/17.2/include/libpq-fe.h"

// PGconn encapsulated a connection to the backend 
// PGresult encapsulates the result of a single SQL command (Query) -- A Query string given to PQsendQuery can conain multiple commands and thus return multiple PGresult objects)
// PGfinish closes the current connection and frees the PG conn data structure
void check_query(PGresult *results, PGconn *connection) {
  // Error: Incompatible integer to pointer conversion passing 'int' to type const PGresults
  if (PQresultStatus((results) != PGRES_TUPLES_OK)) {
    fprintf(stderr, "Line 7: Failed to Query: %s\n", PQerrorMessage(connection));
    PQclear(results);
    PQfinish(connection);
    exit(1);
  }
}

int main() {  
  const char *connection_info = "dbname=dted_db user=systemUser password=systemPassword host=localhost";
  PGconn *connection = PQconnectdb(connection_info);
  
  if (PQstatus(connection) != CONNECTION_OK) {
    // Print error
  }
  double lon = -122.42;
  double lat = 37.77;

  char query[512];
  snprintf(query, sizeof(query),
           "SELECT ST_VALUE(rast, ST_SRID(ST_Point(%f, $f), 4326))"
           "FROM dted_table "
           "WHERE ST_Intersects(rast, ST_SetSRID(ST_Point(%f, %f), -4326));",
           lon, lat, lon, lat);

  // Error: Incompatible integer to pointer conversion passing 'int' to type const PGresults * 
  PGresult *results = PGexec(connection, query);
  check_query(results, connection);

  if (PQntuples(results) > 0) {
    printf("Elevation: %s meters\n", PGgetvalue(results, 0, 0));
  }
  else {
    printf("No elevation data found at this location. \n"); // Not possible but checking
  }

  // Error: call to undeclared function
  PGclear(results);
  PQfinish(connection);
  return 0;
}
