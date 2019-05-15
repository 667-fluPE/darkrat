#include "DarkRatCrypterUI.h"
#include "loginUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//DarkRatCrypterUI w;
	login w;
	w.show();
	return a.exec();
}
