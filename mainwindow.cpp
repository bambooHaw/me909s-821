#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(&timerWatchDog, &QTimer::timeout, this, &MainWindow::slotWatchDogHandler, Qt::QueuedConnection);
    timerWatchDog.start(1000);
    ui->lineEdit_version->setText(QString((char*)BOXV3CHECKAPP_VERSION));
    slotDisplayInit(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotDisplayInit(bool defFlag)
{
    Qt::CheckState checkState;
    if(defFlag)
    {
        checkState = Qt::Checked;
    }else
    {
        checkState = Qt::Unchecked;
    }

    ui->checkBox_deviceNode->setCheckState(checkState);
    ui->checkBox_ltemodule->setCheckState(checkState);
    ui->checkBox_simSwitch->setCheckState(checkState);
    ui->checkBox_SIMSlot->setCheckState(checkState);
    ui->checkBox_SIMDataService->setCheckState(checkState);
    ui->checkBox_SIMOperator->setCheckState(checkState);
    ui->checkBox_SIMDialing->setCheckState(checkState);
    ui->checkBox_SIMSignal->setCheckState(checkState);
    ui->checkBox_netAccess->setCheckState(checkState);
    ui->checkBox_temp->setCheckState(checkState);
    ui->checkBox_iccid->setCheckState(checkState);
    ui->checkBox_currentMode->setCheckState(checkState);

    ui->lineEdit_deviceNode->setText(NULL);
    ui->lineEdit_LTEmodule->setText(NULL);
    ui->lineEdit_simSwitch->setText(NULL);
    ui->lineEdit_SIMslot->setText(NULL);
    ui->lineEdit_service->setText(NULL);
    ui->lineEdit_operator->setText(NULL);
    ui->lineEdit_dialing->setText(NULL);
    ui->lineEdit_netaccess->setText(NULL);
    ui->lineEdit_signal->setText(NULL);
    ui->lineEdit_temp->setText(NULL);
    ui->lineEdit_iccid->setText(NULL);
    ui->lineEdit_currentMode->setText(NULL);
}

void MainWindow::slotDisplay(char stage, QString result)
{
    Qt::CheckState checkState;
    if(result.isEmpty())
    {
        checkState = Qt::Unchecked;
    }else
    {
        checkState = Qt::Checked;
    }

    switch(stage)
    {
    case STAGE_NODE:
    {
        slotDisplayInit(false);
        ui->checkBox_deviceNode->setCheckState(checkState);
        ui->lineEdit_deviceNode->setText(result);
        break;
    }
    case STAGE_AT:
    {
        ui->checkBox_ltemodule->setCheckState(checkState);
        ui->lineEdit_LTEmodule->setText(result);
        break;
    }
    case STAGE_ICCID:
    {
        ui->checkBox_iccid->setCheckState(checkState);
        ui->lineEdit_iccid->setText(result);
        break;
    }
    case STAGE_SIMSWITCH:
    {
        ui->checkBox_simSwitch->setCheckState(checkState);
        ui->lineEdit_simSwitch->setText(result);
        break;
    }
    case STAGE_CPIN:
    {
        ui->checkBox_SIMSlot->setCheckState(checkState);
        ui->lineEdit_SIMslot->setText(result);
        break;
    }
    case STAGE_SYSINFOEX:
    {
        ui->checkBox_SIMDataService->setCheckState(checkState);
        ui->lineEdit_service->setText(result);
        break;
    }
    case STAGE_COPS:
    {
        ui->checkBox_SIMOperator->setCheckState(checkState);
        ui->lineEdit_operator->setText(result);
        break;
    }
    case STAGE_CHIPTEMP:
    {
        ui->checkBox_temp->setCheckState(checkState);
        ui->lineEdit_temp->setText(result);
        break;
    }
    case STAGE_NDISDUP:
    case STAGE_NDISSTATQRY:
    {
        ui->checkBox_SIMDialing->setCheckState(checkState);
        ui->lineEdit_dialing->setText(result);
        break;
    }
    case STAGE_CSQ:
    {
        ui->checkBox_SIMSignal->setCheckState(checkState);
        ui->lineEdit_signal->setText(result);
        break;
    }
    case STAGE_CHECK_IP:
    {
        ui->checkBox_netAccess->setCheckState(checkState);
        ui->lineEdit_netaccess->setText(result);
        break;
    }
    case STAGE_DISPLAY_INIT:
    {
        slotDisplayInit(false);
        break;
    }
    case STAGE_DISPLAY_NOTES:
    {
        ui->textEdit_info->append(result);
        break;
    }
    case STAGE_DEFAULT:
    {
        ui->checkBox_currentMode->setCheckState(checkState);
        ui->lineEdit_currentMode->setText(result);
        break;
    }
    default:
    {
        DEBUG_PRINTF();
        break;
    }
    }
}

void MainWindow::slotWatchDogHandler()
{
    //ui->dateTimeEdit_sys->setDateTime(QDateTime::currentDateTime());
    ui->lineEdit_sysTime->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd[HH:mm:ss]"));
}