#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DarkRatCrypterUI.h"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDataStream>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include "VirtualAES.h"

class DarkRatCrypterUI : public QMainWindow
{
	Q_OBJECT

public:
	DarkRatCrypterUI(QWidget *parent = Q_NULLPTR);

private slots:
	void on_btn_icon_clicked();
	void on_gen_enckey_clicked();
	void on_gen_mutex_clicked();
	void on_build_clicked();



private:
	Ui::DarkRatCrypterUIClass ui;
	struct toCrypt
	{
		char* rawData = nullptr;
		char test;

	};


	std::vector<char> file_data;  // With your current program, make this a global.
	toCrypt data;
	qint64 size;

};
