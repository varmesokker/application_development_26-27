#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName("app.db");

    if (!database.open())
    {
        qDebug() << "Could not open database";
        qDebug() << database.lastError().text();
    }
    else{
        qDebug() << "Database successfully opened";
    }

    QSqlQuery query;
    if(query.exec(
        "CREATE TABLE IF NOT EXISTS users ( "
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT, "
        "password TEXT "
        " )"
            )){
        qDebug() << "Table creation query executed";
    }
    else{
        qDebug() << "Table creation failed";
    }

    QSqlQuery query_;
    query_.exec(
        "INSERT INTO users (username, password) "
        "VALUES ('admin', 'admin123')"
        );

    QSqlQuery query__;
    query__.exec("SELECT * FROM users");
    while(query__.next()){
        int id = query__.value("id").toInt();
        QString username = query__.value("username").toString();
        QString password = query__.value("password").toString();

        qDebug() << id << " " << username << " " << password;
    }



    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("database_integration", "Main");

    return QGuiApplication::exec();
}
