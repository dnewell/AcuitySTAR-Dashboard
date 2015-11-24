#include "window.h"
#include <QtGui>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

Window::Window()
{

    editor = new QTextEdit();
        QPushButton *sendButton = new QPushButton(tr("&message"));

        connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addStretch();
        buttonLayout->addWidget(sendButton);
        buttonLayout->addStretch();

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(editor);
        layout->addLayout(buttonLayout);

        setWindowTitle(tr("comments"));
}
void Window::sendMessage()
{
       thisMessage = Message(editor->toPlainText(), thisMessage.headers());
       emit messageSent(thisMessage);
}

void Window::setMessage(const Message &message)
{
       thisMessage = message;
       editor->setPlainText(thisMessage.body());
}

