#include "MidiRetransmitGUI.h"
#include <qlabel.h>
#include <QtWidgets/qapplication.h>
#include <Windows.h>
#include <thread>

DWORD WINAPI ThreadRun(PVOID pvParam) {
	
	system("MidiRetransmit.exe");
	Sleep(1000);
	keybd_event(VK_RETURN, 0, 0, 0);
	Sleep(50);
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);

	return 0;
}


MidiRetransmitGUI::MidiRetransmitGUI(QWidget *parent)
    : QMainWindow(parent)
{
	/*
	LabelLog = new QLabel("Launched", this);
	LabelLog->resize(381, 20);
	LabelLog->move(10, 520);
	*/
	/*
	LabelIcon = new QLabel("", this);
	LabelIcon->resize(24, 24);
	LabelIcon->move(30, 20);
	*/
	/*
	Edit1 = new QLineEdit(this);
	Edit1->resize(261, 20);
	Edit1->move(130, 360);
	Edit2 = new QLineEdit(this);
	Edit2->resize(261, 20);
	Edit2->move(130, 390);
	Edit3 = new QLineEdit(this);
	Edit3->resize(171, 20);
	Edit3->move(130, 420);
	Edit4 = new QLineEdit(this);
	Edit4->resize(171, 20);
	Edit4->move(130, 450);
	*/
	ui.setupUi(this);
}

void MidiRetransmitGUI:: on_BtnExit_clicked() {
	ui.LabelLog->setText("Stopped.");
	ui.LabelLog->show();
	system("taskkill /f /t /im MidiRetransmit.exe");
}

void MidiRetransmitGUI:: on_BtnRun_clicked() {
	ui.LabelLog->setText("Run.");
	ui.LabelLog->show();
	
	
	
	QString ed1, ed2, ed3, ed4;
	std::string d1, d2, d3, d4;
	
	ed1 = ui.Edit1->text();
	ed2 = ui.Edit2->text();
	ed3 = ui.Edit3->text();
	ed4 = ui.Edit4->text();

	d1 = ed1.toStdString();
	d2 = ed2.toStdString();
	d3 = ed3.toStdString();
	d4 = ed4.toStdString();

	std::string str;

	str += "1 ";
	str += d1;
	str += " ";
	str += d2;
	str += " ";
	str += d3;
	str += " ";
	str += d4;
	
	ui.LabelLog->setText("Writing to config file.");
	ui.LabelLog->show();

	std::ofstream outfile("MRTconfig.ini", std::ios::out);

	outfile << str;
	outfile << std::endl;

	outfile.close();
	
	ui.LabelLog->setText("Launch main program.");
	ui.LabelLog->show();
	
	CreateThread(NULL, 0, ThreadRun, NULL, 0, NULL);

	ui.LabelLog->setText("Done");
	ui.LabelLog->show();
	

	return;
	
}