#pragma once
#include <mysql.h>
#include <vector>
#include <iostream>
#include <string> 
using namespace std;

struct Table{
	string** data;
	int row_count = 0;
};

class DBOperator {
private:
	MYSQL* TDatabase;
	MYSQL_RES* executeCommand(string command);
public:
	DBOperator();
	bool tryConnect();
	void disconnect();
	
	Table tryGetHigthscores(int limit);
	bool tryAddHigthscore(string name, int score);
};

extern DBOperator TetrisDB;