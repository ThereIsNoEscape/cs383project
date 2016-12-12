#include "letters.h"


void getLetterA(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterB(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterC(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterD(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterE(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterF(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterG(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			pixels[7][10].setAlpha(m_colorAlphaMax);
			pixels[4][11].setAlpha(m_colorAlphaMax);
			pixels[5][11].setAlpha(m_colorAlphaMax);
			pixels[6][11].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterH(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterI(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[5][6].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterJ(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[4][10].setAlpha(m_colorAlphaMax);
			pixels[6][10].setAlpha(m_colorAlphaMax);
			pixels[5][11].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[6][6].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterK(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[6][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterL(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[5][6].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterM(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[5][6].setAlpha(m_colorAlphaMax);
			pixels[6][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterN(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[5][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterO(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterP(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[4][10].setAlpha(m_colorAlphaMax);
			pixels[4][11].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterQ(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			pixels[7][10].setAlpha(m_colorAlphaMax);
			pixels[7][11].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterR(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterS(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterT(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[5][6].setAlpha(m_colorAlphaMax);
			pixels[6][6].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[5][6].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterU(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterV(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterW(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[7][6].setAlpha(m_colorAlphaMax);
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterX(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[5][6].setAlpha(m_colorAlphaMax);
			pixels[6][6].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[7][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterY(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[7][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[5][10].setAlpha(m_colorAlphaMax);
			pixels[4][11].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[4][6].setAlpha(m_colorAlphaMax);
			pixels[6][6].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			break;
	}
}

void getLetterZ(unsigned short c, QColor (&pixels)[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS])
{
	switch (c)
	{
		case 1:
			pixels[4][7].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[6][7].setAlpha(m_colorAlphaMax);
			pixels[5][8].setAlpha(m_colorAlphaMax);
			pixels[6][8].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
		default:
			pixels[4][5].setAlpha(m_colorAlphaMax);
			pixels[5][5].setAlpha(m_colorAlphaMax);
			pixels[6][5].setAlpha(m_colorAlphaMax);
			pixels[7][5].setAlpha(m_colorAlphaMax);
			pixels[6][6].setAlpha(m_colorAlphaMax);
			pixels[5][7].setAlpha(m_colorAlphaMax);
			pixels[4][8].setAlpha(m_colorAlphaMax);
			pixels[4][9].setAlpha(m_colorAlphaMax);
			pixels[5][9].setAlpha(m_colorAlphaMax);
			pixels[6][9].setAlpha(m_colorAlphaMax);
			pixels[7][9].setAlpha(m_colorAlphaMax);
			break;
	}
}
