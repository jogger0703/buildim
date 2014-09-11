#ifndef LOGIN_WIN_H
#define LOGIN_WIN_H

#include <QtGui/QDialog>
#include "ui_login_win.h"

class login_win : public QDialog
{
	Q_OBJECT

public:
	login_win(QWidget *parent = 0, Qt::WFlags flags = 0);
	~login_win();

private:
	Ui::Dialog ui;
};

#endif // 
