#ifndef MAINWIN_H
#define MAINWIN_H

#include <QtGui/QDialog>
#include "ui_mainwin.h"

class mainwin : public QDialog
{
	Q_OBJECT

public:
	mainwin(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mainwin();

private:
	Ui::mainwinClass ui;
};

#endif // MAINWIN_H
