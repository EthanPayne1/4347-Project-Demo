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

void query_database(double lon, double lat) {
  const char *connection_info = "dbname=dted_database user=ethan host=localhost";
  PGconn* connection = PQconnectdb(connection_info);
  PGresult* res;
  if (PQstatus(connection) != CONNECTION_OK) {
    fprintf(stderr, "Failed to create connection: %s\n", PQerrorMessage(connection));
    PQfinish(connection);
    exit(1);
  }

  char query[512];
  snprintf(query, sizeof(query),
           "SELECT ST_VALUE(rast, ST_SetSRID(ST_Point(%f, %f), 4326))"
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
  // Would rather not hardcode these values
  
  // n48_w114: Highest point = 3171m @ lon/lat=(-113.848, 48.9249)
  //double lon = -113;
  //double lat = 48;
  
  // n48_115: Highest point = 3060m @ lon/lat=(-114.172,48.944)
  double lon_115 = -144.172;
  double lat_115 = 48.944;
  
  // n48_116: Highest point = 2629m @ lon/lat=(-115.689,48.2229)
  //double lon = -115.689;
  //double lat = 48.2229;
  
  // n48_117: Highest point = 2349m @ lon/lat=(-116.555,48.8457)
  // Elevation: 2337m
  double lon = -116.555;
  double lat = 48.8457;

  // n48_118: Highest point = 2219m @ lon/lat=(-117.46,48.9285)
  // Elevation: 2205m
  double lon_118 = -117.46;
  double lat_118 = 48.9285;

  // n48_119: Highest point = 2172m @ lon/lat=(-118.466,48.7026)
  //double lon = -118.466;
  //double lat = 48.7026;

  query_database(lon_118, lat_118);
  return 0;
}
