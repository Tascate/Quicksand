#include "Square.h"

Square::Square():row(-1), col(-1), color(0), width(0){}

Square::Square(int r, int c, float size, int col) : row(r), col(c), color(col), width(size){}

Square::Square(const Square& target) {
	row = target.getRow();
	col = target.getCol();
	color = target.getColor();
	width = target.getWidth();
}

Square::~Square(){}

float Square::getWidth() const { return width; }
int Square::getColor() const { return color; }
int Square::getRow() const { return row; }
int Square::getCol() const { return col; }

void Square::setSize(float newS) { width = newS; }
void Square::setColor(int newColor) { color = newColor; }
void Square::setCoOrd(int newRow, int newCol) {
	row = newRow;
	col = newCol;
}

Square& Square::operator= (const Square& target) {
	row = target.getRow();
	col = target.getCol();
	color = target.getColor();
	width = target.getWidth();
	return *this;
}
