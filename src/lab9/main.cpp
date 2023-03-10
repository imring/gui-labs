#include <filesystem>
#include <source_location>

#include <QApplication>
#include <QQmlComponent>
#include <QQuickWindow>
#include <QQmlEngine>

int main(int argc, char *argv[]) {
    QApplication a{argc, argv};

    std::filesystem::path src{std::source_location::current().file_name()};
    std::filesystem::path file = src.parent_path() / "main.qml";

    QQmlEngine   *engine = new QQmlEngine;
    QQmlComponent component(engine, QString::fromStdString(file.string()));
    if (component.status() != QQmlComponent::Ready) {
        qWarning() << "Component error: " << component.errorString();
        return 1;
    }
    QObject::connect(engine, &QQmlEngine::quit, &a, &QCoreApplication::quit);

    QObject *object = component.create();
    if (!object) {
        qWarning() << "Object creation error: " << component.errorString();
        return 1;
    }
    QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);

    QQuickWindow *window = qobject_cast<QQuickWindow *>(object);
    if (!window) {
        qWarning() << "Object is not a window.";
        return 1;
    }
    window->show();

    return a.exec();
}