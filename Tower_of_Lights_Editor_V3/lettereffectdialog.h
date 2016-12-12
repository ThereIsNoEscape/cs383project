#ifndef LETTEREFFECTDIALOG_H
#define LETTEREFFECTDIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include "effect.h"
#include "config.h"
#include "letters.h"


namespace Ui {
class letterEffectDialog;
}

class letterEffectDialog : public QDialog
{
	Q_OBJECT

public:
	explicit letterEffectDialog(QColor frame[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS], QWidget *parent = 0);
	~letterEffectDialog();

signals:
	void accepted(const effect*);
	void rejected();

private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
	void on_comboLetter_currentIndexChanged(const QString &text);
	void on_btnLetterColor_clicked();
	void on_pushButton_up_clicked();
	void on_pushButton_right_clicked();
	void on_pushButton_down_clicked();
	void on_pushButton_left_clicked();
	void on_pushButton_upright_clicked();
	void on_pushButton_downright_clicked();
	void on_pushButton_downleft_clicked();
	void on_pushButton_upleft_clicked();

	private:
	Ui::letterEffectDialog *ui;
	effect* m_effect;
	QColor backgroundFrame[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS];
	int offsetX;
	int offsetY;
	bool effectSelected;

	void m_generateFrame(int rows,int cols);
	void m_destroyFrame(int rows,int cols);
	void clearEffect();
	void getEffect(const QChar letter);
	void translate(int dir);
	void translateEffect();
	void updateGUI();

};

#endif // LETTEREFFECTDIALOG_H
