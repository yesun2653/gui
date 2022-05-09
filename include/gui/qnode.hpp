/**
 * @file /include/gui/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef gui_QNODE_HPP_
#define gui_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#endif

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace gui {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();

	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);

Q_SIGNALS:
        void loggingUpdated();
         void rosShutdown();

private:
	int init_argc;
	char** init_argv;
	ros::Publisher chatter_publisher;

    // ===== algorithm btn generation based on ros com ===== //
    ros::Publisher al_btn;
    ros::Publisher taskflag;
    ros::Publisher select;
    ros::Publisher des_q;
    ros::Publisher des_p;

    QStringListModel logging_model;
};

}  // namespace gui

#endif /* gui_QNODE_HPP_ */
