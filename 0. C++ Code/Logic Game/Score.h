#ifndef SCORE_H
#define SCORE_H

#include <iostream>

using namespace std;

class Score
{
public:
	// Constructors
	Score() : m_points(0), m_user("") {  };
	Score(int points, string user) : m_points(points), m_user(user) {};
	//Destructor
	~Score() { };

	//Getters
	int getPoints() const { return m_points; };
	string getUser() const { return m_user; };
	// Setters
	void setPoints(int points) { m_points = points; };
	void setUser(string user) { m_user = user; };

	bool operator>(const Score& s) const;
	
private:
	int m_points;
	string m_user;
};

#endif