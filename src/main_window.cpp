    /**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include "Eigen/Dense"
#include <iostream>
#include "../include/gui/main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/
using Eigen::MatrixXd;
using Eigen::VectorXd;
namespace gui {
     int ros_topic_data = 0;
     int task_flag = 0;
     int ros_arm_select_flag = 0;
     double LP = 10;
     double LPm = 20;
     double LPd = 30;
     double LK = 40;
     double LA = 50;
     double LF = 60;
     double RP = 10;
     double RPm = 20;
     double RPd = 30;
     double RK = 40;
     double RA = 50; 
     double RF = 60;

     double x_des = 1664;
     double y_des = 5000;
     double z_des = 2000;
    double yaw_des = -0;
     double pitch_des = -90;
     double roll_des = -0;

     bool ros_status_flag = 0;
     bool ros_status_flag1 = 0;

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , qnode(argc,argv)
{
    ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application

    ReadSettings();
    setWindowIcon(QIcon(":/images/icon.png"));
//    ui.tab_manager->setCurrentIndex(0); // ensure the first tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

    /*********************
        ** Logging
        **********************/
//    ui.view_logging->setModel(qnode.loggingModel());
//    QObject::connect(&qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));

    /*********************
    ** Auto Start
    **********************/
    if ( ui.checkbox_remember_settings->isChecked() ) {
        on_button_connect_clicked(true);
    }

    /*******************************
    ** Button test - explicit way
    ********************************/
    QObject::connect(ui.Offsettest, SIGNAL(clicked()), this, SLOT(Offset()));
    QObject::connect(ui.HomePose, SIGNAL(clicked()), this, SLOT(Homepose()));
//    QObject::connect(ui.TaskRun, SIGNAL(clicked()), this, SLOT(Taskrun()));
    QObject::connect(ui.JointRun, SIGNAL(clicked()), this, SLOT(Jointrun()));
    QObject::connect(ui.WaitingPose, SIGNAL(clicked()), this, SLOT(Waitingpose()));


//    if(ui.LeftArmInput->isChecked())
//    {
//        L_Arm_Check = 1;
//         ros_arm_select_flag = 2;
//   }
//    else
//    {
//         ros_arm_select_flag = 1;
//        L_Arm_Check = 0;
//    }

//    if(ui.LeftArmInput->isChecked())
//    {
//       L_Arm_Check = 1;
//         ros_arm_select_flag = 2;
//    }
//    else
//    {
//         ros_arm_select_flag = 1;
//       L_Arm_Check = 0;
//    }

//    if(ui.RightArmInput->isChecked())
//    {
//        R_Arm_Check = 1;
//    }
//    else
//    {
//        R_Arm_Check = 0;
//    }

//     if(L_Arm_Check == 1 && R_Arm_Check == 1)
//     {
//         ros_arm_select_flag = 0;
//     }
//     else if(L_Arm_Check == 1 && R_Arm_Check == 0)
//     {
//         ros_arm_select_flag = 1;
//     }
//     else if(L_Arm_Check == 0 && R_Arm_Check == 1)
//     {
//         ros_arm_select_flag = 2;
//     }

}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::showNoMasterMessage() {
    QMessageBox msgBox;
    msgBox.setText("Couldn't find the ros master.");
    msgBox.exec();
    close();
}


/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void MainWindow::on_button_connect_clicked(bool check )
{
    if ( ui.checkbox_use_environment->isChecked() ) {
        if ( !qnode.init() )
        {
            showNoMasterMessage();
        }
        else
        {
            ui.button_connect->setEnabled(false);
        }
    }
    else
    {
        if ( ! qnode.init(ui.line_edit_master->text().toStdString(), ui.line_edit_host->text().toStdString()) )
        {
            showNoMasterMessage();
        }
        else
        {
            ui.button_connect->setEnabled(false);
            ui.line_edit_master->setReadOnly(true);
            ui.line_edit_host->setReadOnly(true);
            ui.line_edit_topic->setReadOnly(true);
        }
    }
}


void MainWindow::on_checkbox_use_environment_stateChanged(int state) {
    bool enabled;
    if ( state == 0 ) {
        enabled = true;
    } else {
        enabled = false;
    }
    ui.line_edit_master->setEnabled(enabled);
    ui.line_edit_host->setEnabled(enabled);
    //ui.line_edit_topic->setEnabled(enabled);
}

/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/**
 * This function is signalled by the underlying model. When the model changes,
 * this will drop the cursor down to the last line in the QListview to ensure
 * the user can always see the latest log message.
 */
//void MainWindow::updateLoggingView() {
//    ui.view_logging->scrollToBottom();
//}

void MainWindow::Offset(){
    ros_topic_data = 1;
    task_flag = 0;
    ros_status_flag = true;
    ros_status_flag1 = true;
}
void MainWindow::Homepose()
{
    //ros_topic_data = 3;//2;
    //task_flag = 1;//0;
//    ui.X->setText("Ready");
//    ui.Y->setText("Ready");
//    ui.Z->setText("Ready");
//    ui.Yaw->setText("Ready");
//    ui.Roll->setText("Ready");
//    ui.Pitch->setText("Ready");
    ui.LP->setText("Ready");
    ui.LPm->setText("Ready");
    ui.LPd->setText("Ready");
    ui.LK->setText("Ready");
    ui.LA->setText("Ready");
    ui.LF->setText("Ready");
    ui.RP->setText("Ready");
    ui.RPm->setText("Ready");
    ui.RPd->setText("Ready");
    ui.RK->setText("Ready");
    ui.RA->setText("Ready");
    ui.RF->setText("Ready");

}
//void MainWindow::Taskrun(){

//    ros_topic_data = 3;
//    task_flag = 1;

//    x_des = ui.X->text().toDouble();
//    y_des = ui.Y->text().toDouble();
//    z_des = ui.Z->text().toDouble();
//    yaw_des = ui.Yaw->text().toDouble();
//    pitch_des = ui.Pitch->text().toDouble();
//    roll_des = ui.Roll->text().toDouble();

//    ros_status_flag = true;
//}
void MainWindow::Jointrun(){

    ros_topic_data = 3;
    task_flag = 1;

    LP = ui.LP->text().toDouble();
    LPm = ui.LPm->text().toDouble();
    LPd = ui.LPd->text().toDouble();
    LK = ui.LK->text().toDouble();
    LA = ui.LA->text().toDouble();
    LF = ui.LF->text().toDouble();
    RP = ui.RP->text().toDouble();
    RPm = ui.RPm->text().toDouble();
    RPd = ui.RPd->text().toDouble();
    RK = ui.RK->text().toDouble();
    RA = ui.RA->text().toDouble();
    RF = ui.RF->text().toDouble();
    

    ros_status_flag1 = true;
}
void MainWindow::Waitingpose(){

//    ui.X->setText(" ");
//    ui.Y->setText(" ");
//    ui.Z->setText(" ");
//    ui.Yaw->setText(" ");
//    ui.Roll->setText(" ");
//    ui.Pitch->setText(" ");

    ui.LP->setText(" ");
    ui.LPm->setText(" ");
    ui.LPd->setText(" ");
    ui.LK->setText(" ");
    ui.LA->setText(" ");
    ui.LF->setText(" ");
    ui.RP->setText(" ");
    ui.RPm->setText(" ");
    ui.RPd->setText(" ");
    ui.RK->setText(" ");
    ui.RA->setText(" ");
    ui.RF->setText(" ");
}


/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "gui");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://localhost:11311/")).toString();
    QString host_url = settings.value("host_url", QString("localhost")).toString();
    //QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
    ui.line_edit_master->setText(master_url);
    //ui.line_edit_host->setText(host_url);
    //ui.line_edit_topic->setText(topic_name);

    bool remember = settings.value("remember_settings", false).toBool();
    ui.checkbox_remember_settings->setChecked(remember);
    bool checked = settings.value("use_environment_variables", false).toBool();
    ui.checkbox_use_environment->setChecked(checked); // checkbox 체크확인
    if ( checked ) {
        ui.line_edit_master->setEnabled(false); //check 되어있으면, 마스터 부분비활성
        ui.line_edit_host->setEnabled(false); //check 되어있으면, 호스트 부분비활성
        //ui.line_edit_topic->setEnabled(false);
    }


}

void MainWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", "gui");
    settings.setValue("master_url",ui.line_edit_master->text());
    //settings.setValue("X",ui.X->text());
    settings.setValue("host_url",ui.line_edit_host->text());
    //settings.setValue("topic_name",ui.line_edit_topic->text());
    settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));

//    settings.setValue("Left_Arm",QVariant(ui.LeftArmInput->isChecked()));


}

void MainWindow::closeEvent(QCloseEvent *event)
{
    WriteSettings();
    QMainWindow::closeEvent(event);
}

}  // namespace gui


void gui::MainWindow::on_LeftArmInput_clicked()
{

}
void gui::MainWindow::on_RightArmInput_clicked()
{

}
