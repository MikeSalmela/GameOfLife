#include <QApplication>
#include <QCommandLineParser>
#include "mwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription({"Play the game of life. Set grid size with --width=m --height=n and time between steps --time=milliseconds"});
    parser.addHelpOption();

    parser.addOption({{"n","width"}, "Set width of board.", "int", "25"});
    parser.addOption({{"m", "height"},"Set height of board.", "int", "25"});
    parser.addOption({{"t", "time"},"Set time between steps.", "milliseconds", "500"});

    parser.process(a);
    int w = parser.value("n").toInt();
    int h = parser.value("m").toInt();
    int t = parser.value("t").toInt();

    if (w <= 0 ) {
        w = 25;
    }
    if (h <= 0) {
        h = 25;
    }
    if (t < 0) {
        t = 500;
    }

    MWindow window(w, h, t);

    window.show();
    return a.exec();
}
