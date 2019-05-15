#include <QtWidgets/QMainWindow>
#include "ui_login.h"
#include <QMainWindow>
class login : public QMainWindow
{
	Q_OBJECT

public:
	login(QWidget* parent = 0);
//	~login();

	Ui::MainWindow ui;

public slots:
	void on_btn_login_clicked();



};