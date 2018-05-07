#include "mkdview.h"

MainWindow::MainWindow(QWidget *parent) {
	this->parent = parent;
	web = new QTextBrowser();
	setCentralWidget(web);
}

MainWindow::~MainWindow() {
	delete web;
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
	if (ev->key() == Qt::Key_Q || ev->key() == Qt::Key_Escape)
		exit(0);
}

void MainWindow::setHtml(const char *html) {
	web->setHtml(BASEHTML + html + BASEHTMLEND);
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	char * buffer;
	size_t len;
	FILE *infile;
	FILE *outfile;
	MMIOT *doc;

	if (argc != 2) {
		std::cerr << argv[0] << " <filename>\n";
		exit(1);
	}

	infile = fopen(argv[1], "r");
	if (infile == NULL) {
		std::cerr << argv[1] << " does not exist\n";
		exit(1);
	}
	doc = mkd_in(infile, 0);

	outfile = open_memstream(&buffer, &len);
	markdown(doc, outfile, 0);
	mkd_cleanup(doc);

	fclose(infile);
	fclose(outfile);
	
	MainWindow mw;
	mw.setHtml(buffer);
	mw.show();
	app.exec();
	return 0;
}

