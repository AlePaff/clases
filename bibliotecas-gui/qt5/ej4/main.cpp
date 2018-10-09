#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QBrush>

// Se recomienda ver la documentación oficial sobre pintado básico
// http://doc.qt.io/qt-5/qtwidgets-painting-basicdrawing-example.html

class MyCanvas : public QWidget {
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);;
        QRect rect(10, 20, 80, 60);
        painter.drawLine(rect.bottomLeft(), rect.topRight());
        QPen pen(Qt::green);
        painter.setPen(pen);
        painter.drawLine(rect.topLeft(), rect.bottomRight());
    }
};

int main(int argc, char *argv[]) {
    // Clase que contiene el loop principal
    QApplication app(argc, argv);
    // Instancio un widget
    MyCanvas paintArea;
    // Muestro el elemento
    paintArea.show();
    // Arranca el loop de la UI
    return app.exec();
}
