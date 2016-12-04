#ifndef EFFECT_H
#define EFFECT_H
#include <QColor.h>
#include <config.h>

struct effect
{
    QColor pixels[TAN_DEFAULT_COLS][TAN_DEFAULT_ROWS];  //this is the array of pixels that will
                                                        //override the current frame pixel
    QColor primary;     //used by individual effects as needed
    QColor secondary;   //
};

#endif // EFFECT_H
