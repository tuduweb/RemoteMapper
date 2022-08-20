#include <iostream>

//#include <QCoreApplication>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QDebug>

int main(int argc, char *argv[])
{
    std::cout << "hello world!" << std::endl;
    qDebug() << "hello QT5!";


    QCoreApplication app(argc, argv);
    QCoreApplication::setOrganizationName("tuduweb");
    QCoreApplication::setApplicationName("OBC Application");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);


    QStringList args = QCoreApplication::arguments();
    qDebug() << args;
    
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

    ////cant empty
    //qDebug() << parser.positionalArguments().first();

    qDebug() << "hello end";

    return app.exec();
}
