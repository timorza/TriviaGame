#pragma once
#include "IDatabase.h"
#include "Structs.h"


class SqliteDataBase : public IDatabase
{
private:
	static  SqliteDataBase* m_ptr;
	SqliteDataBase();  // no one else can create one
	~SqliteDataBase();
	sqlite3* db;//The database
	std::queue<User> users;//Queue to hold users
	std::vector<Question> questions;//Vector of questions


	/*
	* Function that sends the sql statment instead
	* of reapting the same lines everytime, also
	* uses the callback funtion.
	*/
	void sendSQLStatment(std::string statement, int(*callBack)(void*, int, char**, char**), std::queue<User>* userQueue);

	//Clears the user queue
	void clearUsers();

	//Clears the questions vector
	void clearQuestions();

	/*
	* This fucntion gets a statment
	* and return the sqlite3_stmt as a pointer
	* of that statment
	*/
	sqlite3_stmt* getStmt(std::string statment);

	/*
	* Function that creates a database if it doesn't exist
	* and opens it if it exists
	*/
	void openDataBase();

	/*
	* User callback used to retrive
	* the information after selecting it
	* from the database
	*/
	void userCallBack(sqlite3_stmt* stmt);

	UserStatistics userStatisticsCallBack(sqlite3_stmt* stmt);

	void questionCallBack(sqlite3_stmt* stmt);

	sqlite3_stmt* getUserStatisticsStmt(std::string username);
public:
	static IDatabase* get_instance();
	static void reset_instance();
	bool doesUserExist(std::string username) override;
	bool doesPasswordMatch(std::string password, std::string username)  override;
	void addNewUser(std::string username, std::string password, std::string email)  override;

	std::vector<Question> getQuestions(string difficulty, unsigned int numOfQuestuions);
	float getPlayerAverageAnswerTime(std::string username);
	int getNumOfCorrectAnswer(std::string username);
	int getNumOfTotalAnswers(std::string username);
	int getNumOfPlayerGames(std::string username);

	bool isAnswerCorrect(string answer, string question);
	void addToCorrectAnswers(string username);
	void addToPlayerGames(string username);
	void addToWrongAnswers(string username);
	void setPlayerAverageAnswerTime(string username, float averageAnswerTime);
};
