/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/
#include "Eigen/Dense"
#include <QtGui>
#include <QApplication>
#include "../include/gui/main_window.hpp"

/*****************************************************************************
** Main
*****************************************************************************/
using Eigen::MatrixXd;
using Eigen::VectorXd;
int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
    gui::MainWindow w(argc,argv);
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

	return result;
}
