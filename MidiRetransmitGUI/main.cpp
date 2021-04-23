#include "MidiRetransmitGUI.h"
#include <QtWidgets/QApplication>
#include <qlabel.h>
#include <qlistview.h>
#include <qicon.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MidiRetransmitGUI w;
	QIcon icon("icon.png");
	w.setWindowIcon(icon);
	w.show();

	QPixmap LIcon("icon.png");
	w.ui.LabelIcon->setPixmap(LIcon);

	QLabel LabelDeviceList;
	LabelDeviceList.setWordWrap(true);
	w.ui.LabelLog->setText("Reading Devices...");
	w.ui.LabelLog->show();
	char DeviceList[128];
	char StrDevice[32];
	ShellExecute(NULL, L"open", L"MidiRetransmit.exe", L"1", NULL, SW_SHOWMINIMIZED);
	Sleep(1000);
	

	std::ifstream  in("MRTdevice.txt");
	std::ostringstream  tmp;
	tmp << in.rdbuf();
	std::string  str = tmp.str();
	LabelDeviceList.setText(QString::fromStdString(str));
	LabelDeviceList.resize(361, 261);
	LabelDeviceList.move(30, 90);
	LabelDeviceList.setParent(&w);
	LabelDeviceList.show();

	w.ui.LabelLog->setText("Devices Loaded.");
	w.ui.LabelLog->show();
	
	
	


    
    return a.exec();
}


