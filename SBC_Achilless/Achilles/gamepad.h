#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <QObject>


#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtGamepad/QGamepad>
#include <QLoggingCategory>
#include <QKeyEvent>




#include <xnetwork.h>


#define GamepadDataSize 21



typedef __uint8_t  Byte;

class QGamepad;



class Gamepad : public QObject
{
    Q_OBJECT
public:
    explicit Gamepad(QObject *parent = nullptr);
    ~Gamepad();

    QGamepad *G_gamepad;
    double gamepadData[GamepadDataSize];

    QTimer updateTimer;
    QTimer openTimer;


    void AchillesMakeData();


private:
    void process_gamepad_data();
    QThread *thisThread;

    XNetwork AchillesNetwork;


signals:
    void gamepadDataReady(double *);




public slots:
    void gamepadUpdate();
    void openGamepad();
    void closeGamepad();

};

enum GP_Data{
    LX_Axis,
    LY_Axis,
    RX_Axis,
    RY_Axis,
    R1_BTN,
    R2_BTN,
    R3_BTN,
    L1_BTN,
    L2_BTN,
    L3_BTN,
    A_BTN,
    B_BTN,
    X_BTN,
    Y_BTN,
    UP_BTN,
    DOWN_BTN,
    LEFT_BTN,
    RIGHT_BTN,
    GUIDE_BTN,
    SHARE_BTN,
    OPTION_BTN,

};

#endif // GAMEPAD_H
