#include "DarkRatCrypterUI.h"
#include "loginUI.h"
#include <QtWidgets/QApplication>
#include <tchar.h>
#include <iostream>
#include <string>
#include <wininet.h>
#include <QtWidgets\QMessageBox>
#include <DarkRequest.h>
#pragma comment (lib, "WinInet.lib")

int main(int argc, char *argv[])
{


	QApplication a(argc, argv);
	//DarkRatCrypterUI w;
	std::ifstream infile("config.ini");

	if (infile.good())
	{
		std::string post;
		getline(infile, post);
		try {
			//Retrieve default http user agent
			std::string szBuffer = postRequest(post);


			if (szBuffer == "access") {
				DarkRatCrypterUI w;
				w.show();
				return a.exec();
			}
			else {

			}
		}
		catch (...) {}
	}

	infile.close();


	login w;
	w.show();
	return a.exec();
}
/*


	ifstream infile("config.ini");

	if (infile.good())
	{
		string sLine;
		getline(infile, sLine);
		if (!sLine.empty()) {
			std::string accessbool = postRequest(sLine);
			if (accessbool == "access") {
				DarkRatCrypterUI* builder;
				builder = new DarkRatCrypterUI(this);
				builder->show();
				this->close();
			}
			else {
				QMessageBox msgBox;
				msgBox.setText("DarkRat License");
				msgBox.setInformativeText("You account Looks not Existing or Banned");
				msgBox.setStandardButtons(QMessageBox::Cancel);
				msgBox.setDefaultButton(QMessageBox::Cancel);
				remove("config.ini");
				int ret = msgBox.exec();

			}
		}
	}

	infile.close();
*/