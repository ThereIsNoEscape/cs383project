#include "lettereffectdialog.h"
#include "ui_lettereffectdialog.h"


letterEffectDialog::letterEffectDialog(QColor frame[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS], QWidget *parent) :
	QDialog(parent),
	ui(new Ui::letterEffectDialog),
	offsetX(0),
	offsetY(0),
	effectSelected(false)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/resources/icon.png"));
	
	int i = 0, j = 0;
	m_effect = new effect;
	for (i = 0; i < TAN_DEFAULT_ROWS; i++)
		for (j = 0; j < TAN_DEFAULT_COLS; j++)
			m_effect->pixels[j][i] = QColor(0,0,0,0);
	m_effect->primary = Qt::white;
	m_effect->secondary = QColor(0,0,0,0);

	for (i = 0; i < TAN_DEFAULT_ROWS; i++)
		for (j = 0; j < TAN_DEFAULT_COLS; j++)
			backgroundFrame[j][i] = frame[j][i];

	m_generateFrame(TAN_DEFAULT_ROWS, TAN_DEFAULT_COLS);

	ui->pushButton_up->setEnabled(false);
	ui->pushButton_right->setEnabled(false);
	ui->pushButton_down->setEnabled(false);
	ui->pushButton_left->setEnabled(false);
	ui->pushButton_upright->setEnabled(false);
	ui->pushButton_downright->setEnabled(false);
	ui->pushButton_downleft->setEnabled(false);
	ui->pushButton_upleft->setEnabled(false);
}


letterEffectDialog::~letterEffectDialog()
{
	m_destroyFrame(TAN_DEFAULT_ROWS, TAN_DEFAULT_COLS);

	delete ui;
}


// Create the grid of cell widgets
void letterEffectDialog::m_generateFrame(int rows, int cols)
{
	int i = 0, j = 0;
	QGridLayout *m_FrameLayout = ui->gridLayout;
	QSizePolicy m_cellSizePolicy;
	QSize m_cellSize(20,20);

	// Configure the size policy that every cell widget will use
	m_cellSizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
	m_cellSizePolicy.setHorizontalStretch(1);
	m_cellSizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
	m_cellSizePolicy.setVerticalStretch(1);
	m_cellSizePolicy.setHeightForWidth(true);

	QString qss;

	for (i=0; i<rows; i++)
	{
		for (j=0; j<cols; j++)
		{
			QWidget *m_cellWidget = new QWidget;
			m_cellWidget->setMinimumSize(m_cellSize);
			m_cellWidget->setSizePolicy(m_cellSizePolicy);

			// Assemble the style string, and then set it
			qss = QString(cellStyleBasic + "background-color: " + backgroundFrame[j][i].name() + ";");
			if ( (j > 3 && j < 8) && (i > 4 && i < 15) )
				qss += QString(" " + cellStyleActive);
			else
				qss += QString(" " + cellStyleInactive);
			m_cellWidget->setStyleSheet(qss);

			// Adding cell widget to the frame's gridLayout
			m_FrameLayout->addWidget(m_cellWidget, i, j);
			m_cellWidget->show();
			m_FrameLayout->update();
		}
	}
}


// Destroy the grid of cell widgets
void letterEffectDialog::m_destroyFrame(int rows, int cols)
{
	QWidget* m_cellWidget;
	int i = 0, j = 0;

	for (i=0; i<rows; i++)
	{
		for (j=0; j<cols; j++)
		{
			// Iterate through the grid of cells and delete the widget at each (row,col)
			m_cellWidget = (QWidget*)ui->gridLayout->itemAtPosition(i,j)->widget();
			delete m_cellWidget;
			m_cellWidget = 0;
		}
	}
}


void letterEffectDialog::on_buttonBox_accepted()
{
	if (effectSelected)
	{
		emit accepted(m_effect);
	}
}

void letterEffectDialog::on_buttonBox_rejected()
{
	letterEffectDialog::close();
}


void letterEffectDialog:: on_comboLetter_currentIndexChanged(const QString &text)
{
	clearEffect();

	if (text.at(0).toLatin1() != '.')
		getEffect(text.at(0));

	updateGUI();

	if (text.at(0).toLatin1() == '.')
	{
		effectSelected = false;
		ui->pushButton_up->setEnabled(false);
		ui->pushButton_right->setEnabled(false);
		ui->pushButton_down->setEnabled(false);
		ui->pushButton_left->setEnabled(false);
		ui->pushButton_upright->setEnabled(false);
		ui->pushButton_downright->setEnabled(false);
		ui->pushButton_downleft->setEnabled(false);
		ui->pushButton_upleft->setEnabled(false);
	}
	else
	{
		effectSelected = true;
		ui->pushButton_up->setEnabled(true);
		ui->pushButton_right->setEnabled(true);
		ui->pushButton_down->setEnabled(true);
		ui->pushButton_left->setEnabled(true);
		ui->pushButton_upright->setEnabled(true);
		ui->pushButton_downright->setEnabled(true);
		ui->pushButton_downleft->setEnabled(true);
		ui->pushButton_upleft->setEnabled(true);
	}
}


void letterEffectDialog::on_btnLetterColor_clicked()
{
	int i = 0, j = 0;
	QColor color = QColorDialog::getColor(m_effect->primary, this);

	if(color.isValid())
	{
		m_effect->primary = color;

		for (i=0; i < TAN_DEFAULT_ROWS; i++)
		{
			for (j= 0; j < TAN_DEFAULT_COLS; j++)
			{
				if (m_effect->pixels[j][i].alpha() == 255)
					m_effect->pixels[j][i] = m_effect->primary;
			}
		}

		ui->btnLetterColor->setStyleSheet("background-color: " + m_effect->primary.name());
		updateGUI();
	}
}


void letterEffectDialog::clearEffect()
{
	int i = 0, j = 0;
	QColor empty = QColor(0,0,0,0);

	for (i=0; i < TAN_DEFAULT_ROWS; i++)
	 for (j=0; j < TAN_DEFAULT_COLS; j++)
		 m_effect->pixels[j][i] = empty;
}


void letterEffectDialog::getEffect(const QChar letter)
{
	int i = 0, j = 0;

	switch (static_cast<char>(letter.unicode()))
	{
		case 'A':
			getLetterA(0, m_effect->pixels);
			break;
		case 'B':
			getLetterB(0, m_effect->pixels);
			break;
		case 'C':
			getLetterC(0, m_effect->pixels);
			break;
		case 'D':
			getLetterD(0, m_effect->pixels);
			break;
		case 'E':
			getLetterE(0, m_effect->pixels);
			break;
		case 'F':
			getLetterF(0, m_effect->pixels);
			break;
		case 'G':
			getLetterG(0, m_effect->pixels);
			break;
		case 'H':
			getLetterH(0, m_effect->pixels);
			break;
		case 'I':
			getLetterI(0, m_effect->pixels);
			break;
		case 'J':
			getLetterJ(0, m_effect->pixels);
			break;
		case 'K':
			getLetterK(0, m_effect->pixels);
			break;
		case 'L':
			getLetterL(0, m_effect->pixels);
			break;
		case 'M':
			getLetterM(0, m_effect->pixels);
			break;
		case 'N':
			getLetterN(0, m_effect->pixels);
			break;
		case 'O':
			getLetterO(0, m_effect->pixels);
			break;
		case 'P':
			getLetterP(0, m_effect->pixels);
			break;
		case 'Q':
			getLetterQ(0, m_effect->pixels);
			break;
		case 'R':
			getLetterR(0, m_effect->pixels);
			break;
		case 'S':
			getLetterS(0, m_effect->pixels);
			break;
		case 'T':
			getLetterT(0, m_effect->pixels);
			break;
		case 'U':
			getLetterU(0, m_effect->pixels);
			break;
		case 'V':
			getLetterV(0, m_effect->pixels);
			break;
		case 'W':
			getLetterW(0, m_effect->pixels);
			break;
		case 'X':
			getLetterX(0, m_effect->pixels);
			break;
		case 'Y':
			getLetterY(0, m_effect->pixels);
			break;
		case 'Z':
			getLetterZ(0, m_effect->pixels);
			break;
		case 'a':
			getLetterA(1, m_effect->pixels);
			break;
		case 'b':
			getLetterB(1, m_effect->pixels);
			break;
		case 'c':
			getLetterC(1, m_effect->pixels);
			break;
		case 'd':
			getLetterD(1, m_effect->pixels);
			break;
		case 'e':
			getLetterE(1, m_effect->pixels);
			break;
		case 'f':
			getLetterF(1, m_effect->pixels);
			break;
		case 'g':
			getLetterG(1, m_effect->pixels);
			break;
		case 'h':
			getLetterH(1, m_effect->pixels);
			break;
		case 'i':
			getLetterI(1, m_effect->pixels);
			break;
		case 'j':
			getLetterJ(1, m_effect->pixels);
			break;
		case 'k':
			getLetterK(1, m_effect->pixels);
			break;
		case 'l':
			getLetterL(1, m_effect->pixels);
			break;
		case 'm':
			getLetterM(1, m_effect->pixels);
			break;
		case 'n':
			getLetterN(1, m_effect->pixels);
			break;
		case 'o':
			getLetterO(1, m_effect->pixels);
			break;
		case 'p':
			getLetterP(1, m_effect->pixels);
			break;
		case 'q':
			getLetterQ(1, m_effect->pixels);
			break;
		case 'r':
			getLetterR(1, m_effect->pixels);
			break;
		case 's':
			getLetterS(1, m_effect->pixels);
			break;
		case 't':
			getLetterT(1, m_effect->pixels);
			break;
		case 'u':
			getLetterU(1, m_effect->pixels);
			break;
		case 'v':
			getLetterV(1, m_effect->pixels);
			break;
		case 'w':
			getLetterW(1, m_effect->pixels);
			break;
		case 'x':
			getLetterX(1, m_effect->pixels);
			break;
		case 'y':
			getLetterY(1, m_effect->pixels);
			break;
		case 'z':
			getLetterZ(1, m_effect->pixels);
			break;
		default:
			break;
	}

	for (i=0; i < TAN_DEFAULT_ROWS; i++)
	 for (j=0; j < TAN_DEFAULT_COLS; j++)
		if (m_effect->pixels[j][i].alpha() == 255)
		 m_effect->pixels[j][i] = m_effect->primary;
}


void letterEffectDialog::translateEffect()
{
	if (effectSelected)
	{
		int i = 0, j = 0;
		QColor m_temp[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS];

		for (i=0; i < TAN_DEFAULT_ROWS; i++)
		 for (j=0; j < TAN_DEFAULT_COLS; j++)
			 m_temp[j][i] = m_effect->pixels[j][i];
		for (i=0; i < TAN_DEFAULT_ROWS; i++)
		 for (j=0; j < TAN_DEFAULT_COLS; j++)
			 m_effect->pixels[j][i] = m_temp[(j-offsetX)%TAN_DEFAULT_COLS][(i-offsetY)%TAN_DEFAULT_ROWS];
	}
}


// dir == direction
// 1 == up, 2 == right, 3 == down, 4 == left
// diagonals are the sum of their cardinals: 3, 6, 9, 12
void letterEffectDialog::translate(int dir)
{
	if (effectSelected)
	{
		if (dir == 1 || dir == 3 || dir == 9)
			--offsetY;
		if (dir == 2 || dir == 3 || dir == 6)
			offsetX -= TAN_DEFAULT_COLS - 1;
		if (dir == 4 || dir == 6 || dir == 12)
			offsetY -= TAN_DEFAULT_ROWS - 1;
		if (dir == 8 || dir == 12 || dir == 9)
			--offsetX;

		translateEffect();
		updateGUI();

		offsetX = 0;
		offsetY = 0;
	}
}


void letterEffectDialog::on_pushButton_up_clicked()
{
	translate(1);
}

void letterEffectDialog::on_pushButton_right_clicked()
{
	translate(2);
}

void letterEffectDialog::on_pushButton_down_clicked()
{
	translate(4);
}

void letterEffectDialog::on_pushButton_left_clicked()
{
	translate(8);
}

void letterEffectDialog::on_pushButton_upright_clicked()
{
	translate(3);
}

void letterEffectDialog::on_pushButton_downright_clicked()
{
	translate(6);
}

void letterEffectDialog::on_pushButton_downleft_clicked()
{
	translate(12);
}

void letterEffectDialog::on_pushButton_upleft_clicked()
{
	translate(9);
}

void letterEffectDialog::updateGUI()
{
	int i = 0, j = 0;
	QString qss;

	for (i=0; i<TAN_DEFAULT_ROWS; i++)
	{
		for (j=0; j<TAN_DEFAULT_COLS; j++)
		{
			// Assemble the style string, and then set it
			qss = QString(cellStyleBasic);
			if (m_effect->pixels[j][i].alpha() == 255)
				qss += QString(" background-color: " + m_effect->pixels[j][i].name() + ";");
			else
				qss += QString(" background-color: " + backgroundFrame[j][i].name() + ";");
			if ( (j > 3 && j < 8) && (i > 4 && i < 15) )
				qss += QString(" " + cellStyleActive);
			else
				qss += QString(" " + cellStyleInactive);
			ui->gridLayout->itemAtPosition(i,j)->widget()->setStyleSheet(qss);
		}
	}
}
