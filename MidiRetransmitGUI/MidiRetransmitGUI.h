#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MidiRetransmitGUI.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream> 


class MidiRetransmitGUI : public QMainWindow
{
    Q_OBJECT

public:
    MidiRetransmitGUI(QWidget *parent = Q_NULLPTR);
	QPushButton* BtnRun, *BtnExit, *BtnLink, *BtnRefresh;
	QLabel* LabelLog, *LabelIcon, *LabelDeviceList;
	QLineEdit* Edit1, *Edit2, *Edit3, *Edit4;

public slots :
	void on_BtnExit_clicked();
	void on_BtnRun_clicked();
	void on_BtnLink_clicked();
	void on_BtnRefresh_clicked();
	

public:
    Ui::MidiRetransmitGUIClass ui;
};
