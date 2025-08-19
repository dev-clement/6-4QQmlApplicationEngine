#include <QDebug>
#include <QQuickItem>
#include <QQuickStyle>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication o_app(argc, argv);

    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine o_engine;
    QObject::connect(
        &o_engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &o_app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    o_engine.loadFromModule("QQmlApplicationEngine", "Main");

    if (o_engine.rootObjects().isEmpty()) {
        QGuiApplication::exit(-1);
    }

    QObject *po_rootObject = o_engine.rootObjects().first();

    // Show item count
    qDebug() << "Show item count: " << po_rootObject->children().count();
    qDebug() << "Object named: " << po_rootObject->objectName();

    // Finding the rectangles
    const auto o_childrens = po_rootObject->findChildren<QQuickItem *>();
    if (o_childrens.count() < 0) {
        QGuiApplication::exit(-1);
    }
    qDebug() << "Rectangle count:";
    for (std::size_t i_idx{0}; i_idx < o_childrens.count(); ++i_idx) {
        QQuickItem *po_item = o_childrens.at(i_idx);
        if (po_item->property("color").toString().isEmpty())
            continue;
        qDebug() << "------------------- ITEM -------------------";
        qDebug() << "The color is: " << po_item->property("color").toString();

        QVariant o_varColor = po_item->property("color");
        const auto o_color = po_item->property("color").value<QColor>();
        const auto o_display = QString("The color component: %1, %2, %3").arg(o_color.red()).arg(o_color.green()).arg(o_color.blue());
        qDebug() << o_display;
        if (o_color.green() > 0) {
            po_item->setProperty("radius", 20);
        }
        if (o_color.blue() > 0) {
            po_item->setProperty("height", 200);
        }
    }

    // Finding the text area
    QQuickItem *po_item = po_rootObject->findChild<QQuickItem *>("myTextArea");
    po_item->setProperty("text", "Text from the C++ !!");
    return o_app.exec();
}
