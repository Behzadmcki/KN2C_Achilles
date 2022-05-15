#include "gamepad.h"
#include <QBitArray>
#include <QApplication>
#include <QProcess>

Gamepad::Gamepad(QObject *parent) : QObject(parent) , G_gamepad(0)
{
    connect(&updateTimer,SIGNAL(timeout()),this,SLOT(gamepadUpdate()));
    connect(&openTimer,SIGNAL(timeout()),this,SLOT(openGamepad()));

    openTimer.start(2000);


    AchillesNetwork.set_client_IP("192.168.1.10",8585);
    AchillesNetwork.set_server_IP("192.168.1.11",8234);



}
void Gamepad::openGamepad()
{
    if(!system("ls /dev/input/js0"))
    {
        auto gamepads = QGamepadManager::instance()->connectedGamepads();
        G_gamepad = new QGamepad(*gamepads.begin(), this);
        openTimer.stop();
        updateTimer.start(5);
    }
}
void Gamepad::closeGamepad()
{
    updateTimer.stop();

}
void Gamepad::gamepadUpdate()
{

  


    gamepadData[GP_Data::RY_Axis] = -G_gamepad->axisRightY();
    gamepadData[GP_Data::LY_Axis] = -G_gamepad->axisLeftY();
    gamepadData[GP_Data::RX_Axis] = G_gamepad->axisRightX();
    gamepadData[GP_Data::LX_Axis] = G_gamepad->axisLeftX();

    gamepadData[GP_Data::R1_BTN] = G_gamepad->buttonR1();
    gamepadData[GP_Data::R2_BTN] = G_gamepad->buttonR2();
    gamepadData[GP_Data::R3_BTN] = G_gamepad->buttonR3();

    gamepadData[GP_Data::L1_BTN] = G_gamepad->buttonL1();
    gamepadData[GP_Data::L2_BTN] = G_gamepad->buttonL2();
    gamepadData[GP_Data::L3_BTN] = G_gamepad->buttonL3();

    gamepadData[GP_Data::A_BTN] = G_gamepad->buttonA();
    gamepadData[GP_Data::B_BTN] = G_gamepad->buttonB();
    gamepadData[GP_Data::X_BTN] = G_gamepad->buttonX();
    gamepadData[GP_Data::Y_BTN] = G_gamepad->buttonY();
    gamepadData[GP_Data::UP_BTN] = G_gamepad->buttonUp();
    gamepadData[GP_Data::DOWN_BTN] = G_gamepad->buttonDown();
    gamepadData[GP_Data::LEFT_BTN] = G_gamepad->buttonLeft();
    gamepadData[GP_Data::RIGHT_BTN] = G_gamepad->buttonRight();
    gamepadData[GP_Data::GUIDE_BTN] = G_gamepad->buttonGuide();
    gamepadData[GP_Data::SHARE_BTN] = G_gamepad->buttonSelect();
    gamepadData[GP_Data::OPTION_BTN] = G_gamepad->buttonStart();



    // filter L2 and R2
    gamepadData[L2_BTN] = gamepadData[L2_BTN] -0.2;
    if(gamepadData[L2_BTN] < 0)
        gamepadData[L2_BTN] = 0;



    gamepadData[R2_BTN] = gamepadData[R2_BTN] -0.2;
    if(gamepadData[R2_BTN] < 0)
        gamepadData[R2_BTN] = 0;



    if(system("ls /dev/input/js0"))
    {
        closeGamepad();
        qApp->quit();

        QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
    }

     AchillesMakeData();

}

void Gamepad::AchillesMakeData()
{




    QByteArray sendData;
    sendData.resize(35);
    sendData.fill(0);

    sendData[0] = 'P';
    sendData[1] = 'W';
    sendData[2] = 'M';


    /*
     * Right -->3 Direction  , 4 PWM
     * Left  -->9 Direction  , 10 PWM

    */
        for (int i =3; i<15; i++) {
            sendData[i] = 0;

        }

    if(gamepadData[GP_Data::RY_Axis] >= 0.2)
    {
        if(gamepadData[GP_Data::LX_Axis] >=0.2)
        {
            sendData[3] = 60;
            sendData[4] = gamepadData[GP_Data::LX_Axis] * 126;

            sendData[9] = 59;
            sendData[10] = gamepadData[GP_Data::RY_Axis] * 126;
        }
        else if(gamepadData[GP_Data::LX_Axis] <= -0.2){
            sendData[3] = 59;
            sendData[4] = gamepadData[GP_Data::RY_Axis] * 126;

            sendData[9] = 60;
            sendData[10] = (-gamepadData[GP_Data::LX_Axis]) * 126;
        }
        else {
            sendData[3] = 59;
            sendData[4] = gamepadData[GP_Data::RY_Axis] * 126;

            sendData[9] = 59;
            sendData[10] = gamepadData[GP_Data::RY_Axis] * 126;
        }


    }
    else if(gamepadData[GP_Data::RY_Axis] <= -0.2)
    {
        if(gamepadData[GP_Data::LX_Axis] >=0.2)
        {
            sendData[3] = 59;
            sendData[4] = gamepadData[GP_Data::LX_Axis] * 126;

            sendData[9] = 60;
            sendData[10] = gamepadData[GP_Data::RY_Axis] * 126;
        }
        else if(gamepadData[GP_Data::LX_Axis] <= -0.2){
            sendData[3] = 60;
            sendData[4] = gamepadData[GP_Data::RY_Axis] * 126;

            sendData[9] = 59;
            sendData[10] = (-gamepadData[GP_Data::LX_Axis]) * 126;
        }
        else {
            sendData[3] = 60;
            sendData[4] = -gamepadData[GP_Data::RY_Axis] * 126;

            sendData[9] = 60;
            sendData[10] = -gamepadData[GP_Data::RY_Axis] * 126;
        }
    }
    else {
        sendData[3] = 58;
        sendData[4] = 0;

        sendData[9] = 58;
        sendData[10] = 0;
    }



    //Front Flipper Right
    if(gamepadData[GP_Data::UP_BTN] == 1)
    {
        sendData[5] = 59;
        sendData[6] = 126;
    }
    else  if(gamepadData[GP_Data::DOWN_BTN] == 1){
        sendData[5] = 60;
        sendData[6] = 126;
    }
    else {
        sendData[5] = 58;
        sendData[6] = 0;
    }



    //Front Flipper Left
    if(gamepadData[GP_Data::X_BTN] == 1)
    {
        sendData[7] = 59;
        sendData[8] = 126;
    }
    else  if(gamepadData[GP_Data::A_BTN] == 1){
        sendData[7] = 60;
        sendData[8] = 126;
    }
    else {
        sendData[7] = 58;
        sendData[8] = 0;
    }





    //Back Flipper Right
    if(gamepadData[GP_Data::L1_BTN] == 1)
    {
        sendData[11] = 59;
        sendData[12] = 126;
    }
    else  if(gamepadData[GP_Data::L2_BTN] >= 0.5){
        sendData[11] = 60;
        sendData[12] = 126;
    }
    else {
        sendData[11] = 58;
        sendData[12] = 0;
    }



    //Back Flipper Left
    if(gamepadData[GP_Data::R1_BTN] == 1)
    {
        sendData[13] = 59;
        sendData[14] = 126;
    }
    else  if(gamepadData[GP_Data::R2_BTN] >= 0.5){
        sendData[13] = 60;
        sendData[14] = 126;
    }
    else {
        sendData[13] = 58;
        sendData[14] = 0;
    }




    int chechsum = 0;
    for(int i =3 ; i<15;i++)
    {
        chechsum += sendData[i];
        chechsum = chechsum %256;
    }


    sendData[38] = 0;
    sendData[39] = '\r';


    AchillesNetwork.send(sendData);



}


Gamepad::~Gamepad()
{
    delete G_gamepad;
}
