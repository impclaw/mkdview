#include <QtWidgets/QApplication>
#include <QMainWindow>
#include <QTextBrowser>
#include <QWidget>
#include <QLayout>
#include <QKeyEvent>
#include <iostream>
#include <stdio.h>

extern "C" {
	#include <mkdio.h>
}

const QString BASEHTML = "<html><head><style>body{font-size:16px; margin:16px}</style></head><body><p>";
const QString BASEHTMLEND = "</p></body></html>";

class MainWindow : public QMainWindow {
Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	void keyPressEvent(QKeyEvent *ev);
	void setHtml(const char * html);

private:
	QTextBrowser *web;
	QWidget *parent;
};

