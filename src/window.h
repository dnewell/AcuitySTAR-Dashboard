#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>
#include "message.h"
#include <QTextEdit>
#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>

class QTextEdit;

class Window: public QWidget
{
    Q_OBJECT;
public:
    Window();
signals:
    void messageSent(const Message &message);
public slots:
    void setMessage(const Message &message);
private slots:
    void sendMessage();
private:
    Message thisMessage;
    QTextEdit *editor;
};

#endif // WINDOW_H
