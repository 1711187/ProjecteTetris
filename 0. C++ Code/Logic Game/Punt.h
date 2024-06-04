#ifndef PUNT_H
#define PUNT_H



class Punt
{
public:
	// Constructors
	Punt() : m_x(0), m_y(0) {  };
	Punt(int x, int y) : m_x(x), m_y(y) {};
	//Destructor
	~Punt() { };

	//Getters
	int getX() const { return m_x; };
	int getY() const { return m_y; };
	// Setters
	void setX(int x) { m_x = x; };
	void setY(int y) { m_y = y; };
	
	//Incrementators & decrementators
	void incX() { m_x++; };
	void incY() { m_y++; };
	void decX() { m_x--; };
	void decY() { m_y--; };
private:
	int m_x;
	int m_y;
};

#endif