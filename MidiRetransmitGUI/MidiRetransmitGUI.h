#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MidiRetransmitGUI.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include "qcheckbox.h"


class MidiRetransmitGUI : public QMainWindow
{
    Q_OBJECT

public:
    MidiRetransmitGUI(QWidget *parent = Q_NULLPTR);
	QPushButton* BtnRun, *BtnExit, *BtnLink, *BtnRefresh, *BtnCreateDevice;
	QLabel* LabelLog, *LabelIcon, *LabelDeviceList;
	QLineEdit* Edit1, *Edit2, *Edit3, *Edit4, *Edit5;
	QCheckBox* CheckBoxPedalCopy;

public slots :
	void on_BtnExit_clicked();
	void on_BtnRun_clicked();
	void on_BtnLink_clicked();
	void on_BtnRefresh_clicked();
	//void on_BtnCreateDevice_clicked();
	

public:
    Ui::MidiRetransmitGUIClass ui;
};
