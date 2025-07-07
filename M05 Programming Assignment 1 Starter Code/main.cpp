#include <iostream>
#include <string>
#include "sqlite3.h"

// Callback function to process query results
int callback(void* data, int argc, char** argv, char** azColName) {
    // data contains the last album title printed
    std::string* lastAlbumTitle = static_cast<std::string*>(data);
    
    // argv[0] is Album Title, argv[1] is Track Name
    std::string currentAlbumTitle = argv[0];
    std::string trackName = argv[1];

    // If the album title is new, print it
    if (*lastAlbumTitle != currentAlbumTitle) {
        *lastAlbumTitle = currentAlbumTitle;
        std::cout << "\nAlbum: " << currentAlbumTitle << std::endl;
    }

    // Print the track name
    std::cout << "\t" << trackName << std::endl;
    
    return 0;
}

int main(int argc, char* argv[])
{
	sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("chinook.db", &db);

    if (rc) {
        fprintf(stderr, "Error in connection: unable to open database file\n");
        sqlite3_close(db);
        return 1;
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    // Create SQL statement
    const char* sql = "SELECT a.Title, t.Name "
                      "FROM albums a "
                      "JOIN tracks t ON a.AlbumId = t.AlbumId "
                      "ORDER BY a.Title, t.TrackId;";

    std::string lastAlbum = "";
    
    // Execute SQL statement
    rc = sqlite3_exec(db, sql, callback, &lastAlbum, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    // Close database
    sqlite3_close(db);

	return 0;
}