#include "DarkRatCrypterUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DarkRatCrypterUI w;
	w.show();
	return a.exec();
}
