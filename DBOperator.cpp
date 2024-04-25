#include "DBOperator.h"
#include "deltaTime.h"
#include "Config.h"

#define gotoxy(x,y) printf("\x1b[%d;%dH", (y), (x))

DBOperator TetrisDB;

DBOperator::DBOperator() {
	TDatabase = mysql_init(0);

}

MYSQL_RES* DBOperator::executeCommand(string command) {
	MYSQL_RES* result;
	int qstate = mysql_query(TDatabase, command.c_str());
	if (!qstate) result = mysql_store_result(TDatabase);
	else result = nullptr;
	return result;
}

bool DBOperator::tryConnect() {
	short counter = 0;
	char loading[5] = "\\|-/";
	bool success = false;
	TDatabase = mysql_init(0);
	do {
		counter++;
		deltaTime.resetTime();

		if (mysql_real_connect(TDatabase, IP, USERNAME, PASSWORD, DATABASE_NAME, PORT, NULL, 0)) {
			success = true;
			break;
		}

		while (deltaTime < 1.) {
			deltaTime.updateTime();
			gotoxy(0, 0); cout << "Connecting to Database: " << loading[((int)(deltaTime * 8 + counter)) % 4];
		}
	} while (counter != 15);
	system("cls");
	return success;
}

void DBOperator::disconnect() {
	mysql_close(TDatabase);
}

Table DBOperator::tryGetHigthscores(int limit) {
	MYSQL_RES* result;
	Table hightscores;
	if (tryConnect()) {
		result = executeCommand((string)"CALL getHigthscores(" + to_string(limit) + ");");
		int row_count = result->row_count;
		MYSQL_ROW row;

		hightscores.row_count = row_count;

		hightscores.data = new string*[2];
		hightscores.data[0] = new string[row_count];
		hightscores.data[1] = new string[row_count];

		for (int i = 0; (row = mysql_fetch_row(result)) != NULL; i++) {
			hightscores.data[0][i] = row[0];
			hightscores.data[1][i] = row[1];
		}
		disconnect();
	}
	else hightscores.data = nullptr;
	return hightscores;
}

bool DBOperator::tryAddHigthscore(string name, int score) {
	if (tryConnect()) {
		executeCommand((string)"CALL addScore('" + name + "', " + to_string(score) + ");");
		return true;
	}
	return false;
}