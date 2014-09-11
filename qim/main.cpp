#include "mainwin.h"
#include "login_win.h"
#include "libim/core.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	g_im_core.init();

	login_win d;
	d.show();

// 	mainwin w;
// 	w.show();

	return a.exec();
}
