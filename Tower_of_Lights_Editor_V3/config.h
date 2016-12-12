#ifndef CONFIG_H
#define CONFIG_H

#include <QString>


const int TAN_DEFAULT_ROWS = 20;
const int TAN_DEFAULT_COLS = 12;
const int TAN_DEFAULT_COLORPRESETS = 16;

const QString cellStyleBasic = QString("margin: 0px; border-radius: 2px;");
const QString cellStyleActive = QString("border: 1px solid rgb(127,127,127);");
const QString cellStyleInactive = QString("border: 1px solid rgb(0,0,0);");

const int m_colorAlphaMax = 255;

#endif // CONFIG_H
