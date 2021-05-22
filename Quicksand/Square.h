#pragma once

class Square {
private:
	//Square holds coordinates relative to the map,
	int row = -1, col = -1, color = 0;
	float width = 0;
public:
	Square();
	Square(int r, int c, float size, int col = 0);
	Square(const Square& target);
	~Square();

	float getWidth() const;
	int getColor() const;
	int getRow() const;
	int getCol() const;

	void setSize(float newS);
	void setColor(int newColor);
	void setCoOrd(int newRow, int newCol);

	Square& operator= (const Square& target);
};

