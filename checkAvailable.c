#include <sqlite3.h>
#include <stdio.h>

int checkAvailable(sqlite3 *db,int roll){
	char sql[1025];

	memset(sql,0,1025);
	sprintf(sql,"SELECT Roll_NO FROM SCIENCE WHERE Roll_NO=%d",roll);
    	struct sqlite3_stmt *selectstmt;
    	int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);
    	if(result == SQLITE_OK)
    	{
       	if (sqlite3_step(selectstmt) == SQLITE_ROW)
       	{
          // record found
  		  sqlite3_finalize(selectstmt);
	  	  return 1;
       	}
       	else
       	{
          // no record found
    		  sqlite3_finalize(selectstmt);
		  return 0;
       	}
    	}
	return 0;
}

