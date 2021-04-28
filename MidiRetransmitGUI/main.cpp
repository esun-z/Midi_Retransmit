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

	
	w.MidiRetransmitGUI::on_BtnRefresh_clicked();
	
	


    
    return a.exec();
}


