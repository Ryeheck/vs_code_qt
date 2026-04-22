#include "mainwindow.h"
#include "encryption/func.hpp"
#include "Paint/painter.h"

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QString>
#include <QPainter>
#include <QMouseEvent>

#include <iostream>
#include <string>

enum Mode {None, Salat, Vig, Table, Encrypt, Decrypt};

QString encryptionClicked(const QString &text, const QString &key, Mode cipher, Mode action, QString sym="x")
{
    if (text.isEmpty())  return nullptr;

    std::string string = text.toStdString();
    
    switch (cipher)
    {
        case Salat: {
            int k = key.toInt();

            return QString::fromStdString(action == Encrypt ? 
                salat_encryption(&string, k) : salat_decryption(&string, k));
        }
        case Vig: {
            std::string k = key.toStdString();
            if (k.empty())  return text;

            return QString::fromStdString(action == Encrypt ? 
                vig_encryption(&string, &k, alphabet, sz_alphbt) : vig_decryption(&string, &k, alphabet, sz_alphbt));
        }
        case Table: {
            std::string k = key.toStdString();
            if (k.empty())  return text;

            char s = sym.at(0).toLatin1();
            return QString::fromStdString(action == Encrypt ? 
                table_encryption(&string, &k, s) : table_decryption(&string, &k));
        }
    }

    return nullptr;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow wn_main;

    QVBoxLayout *layout = new QVBoxLayout(&wn_main);
    
    QWidget *central = new QWidget(&wn_main);
    central->setLayout(layout);
    wn_main.setCentralWidget(central);

    /*                                                          BUTTONS                                                                             */
    QPushButton *btn_exit = new QPushButton("Exit", &wn_main);
    QPushButton *btn_home = new QPushButton("Main menu", &wn_main);
    QPushButton *btn_back = new QPushButton("Back", &wn_main);
    QPushButton *btn_encrypt = new QPushButton("Encryptions", &wn_main);
    QPushButton *btn_DVD = new QPushButton("???", &wn_main);


    /*                                                          CONNECTIONS                                                                         */
    
    // EXIT
    QObject::connect(btn_exit, &QPushButton::clicked, &wn_main, &QMainWindow::close);

    QObject::connect(btn_DVD, &QPushButton::clicked, [&wn_main] () { 
        DVDScreenSaver *widgetDVD = new DVDScreenSaver(&wn_main);

        widgetDVD->setAttribute(Qt::WA_DeleteOnClose);
        widgetDVD->setWindowFlag(Qt::Window);

        // widgetDVD->setWindowState(Qt::WindowFullScreen);
        widgetDVD->setGeometry(wn_main.rect());
        widgetDVD->show();
    });
    // HOME
    QObject::connect(btn_home, &QPushButton::clicked, [=, &wn_main] () {
        btn_home->hide();
        btn_DVD->hide();

        btn_back->show();
        btn_encrypt->show();
        btn_exit->show();

        wn_main.setWindowTitle("Main");
    });

    // BACK
    QObject::connect(btn_back, &QPushButton::clicked, [=, &wn_main] () {
        btn_back->hide();
        btn_encrypt->hide();
        btn_exit->hide();

        btn_DVD->show();
        btn_home->show();
        
        wn_main.setWindowTitle("Not Main");
    });
    
    // ENCRYPTION
    QObject::connect(btn_encrypt, &QPushButton::clicked, [] () {

        static Mode cipher = None;
        Mode action = None;

        // New widget in Encryption
        QWidget *wid_encrypt = new QWidget();

        wid_encrypt->setWindowTitle("Encryptions");
        wid_encrypt->resize(400, 300);
        wid_encrypt->setAttribute(Qt::WA_DeleteOnClose);

        QVBoxLayout *layout_encrypt = new QVBoxLayout(wid_encrypt);

        QLineEdit *inputText = new QLineEdit(wid_encrypt);
        QLineEdit *inputKey = new QLineEdit(wid_encrypt);
        QLineEdit *outputText = new QLineEdit(wid_encrypt);
        QLineEdit *inputOneSym = new QLineEdit(wid_encrypt);

        inputOneSym->setMaxLength(1);
        inputOneSym->setPlaceholderText("Enter filler... (default: x)");
        outputText->setReadOnly(true);
        outputText->setPlaceholderText("Result...");
        inputText->setPlaceholderText("Enter text... ");
        inputKey->setPlaceholderText("Enter key...");

        // BUTTONS

        QPushButton *ButtonEncryption = new QPushButton("Encryption", wid_encrypt);
        QPushButton *ButtonDecryption = new QPushButton("Decryption", wid_encrypt);
        QPushButton *btn_back = new QPushButton("Back", wid_encrypt);
        QPushButton *btn_salat = new QPushButton("Salat", wid_encrypt);
        QPushButton *btn_vig = new QPushButton("Vig", wid_encrypt);
        QPushButton *btn_table = new QPushButton("Table", wid_encrypt);
        
        auto onModeSelect = [=] (QPushButton *Button) mutable 
        {
            QString placeHolder = "";

            if(Button == btn_salat) {
                cipher = Salat;
                placeHolder = "number";
            }
            else if(Button == btn_vig) {
                cipher = Vig;
                placeHolder = "word";
            }
            else if(Button == btn_table) {
                cipher = Table;
                placeHolder = "numbers";
            }

            inputKey->setPlaceholderText("Enter key (" + placeHolder + ")...");
            
            QString Name = Button->text();
            ButtonEncryption->setText("Encryption: " + Name);
            ButtonDecryption->setText("Decryption: " + Name);
            ButtonDecryption->show();
            ButtonEncryption->show();         
        };

        /* CONNECTIONS */

        // ENCRYPTION
        QObject::connect(ButtonEncryption, &QPushButton::clicked, [=] () mutable {
            action = Encrypt;

            QString Text = inputText->text();
            QString Key = inputKey->text();
            QString oneSym = inputOneSym->text();
            QString Result;

            if (oneSym.isEmpty())  oneSym = "x";

            Result = encryptionClicked(Text, Key, cipher, action, oneSym);

            if(!(Result.isEmpty()))
                outputText->setText(Result);
            else
                outputText->setText("Error..");
        });

        // DECRYPTION
        QObject::connect(ButtonDecryption, &QPushButton::clicked, [=] () mutable {
            action = Decrypt;

            QString Text = inputText->text();
            QString Key = inputKey->text();
            QString oneSym = inputOneSym->text();
            QString Result;

            if (oneSym.isEmpty())  oneSym = "x";

            Result = encryptionClicked(Text, Key, cipher, action, oneSym);

            if(!(Result.isEmpty()))
                outputText->setText(Result);
            else
                outputText->setText("Error..");
        });

        // BACK
        QObject::connect(btn_back, &QPushButton::clicked, wid_encrypt, &QWidget::close);

        // SALAT
        QObject::connect(btn_salat, &QPushButton::clicked, [btn_salat, onModeSelect, inputOneSym] () mutable {
            onModeSelect(btn_salat); 
            inputOneSym->hide();
            
        });

        // VIG
        QObject::connect(btn_vig, &QPushButton::clicked, [btn_vig, onModeSelect, inputOneSym] () mutable {
            onModeSelect(btn_vig);
            inputOneSym->hide();

        });

        // TABLE
        QObject::connect(btn_table, &QPushButton::clicked, [btn_table, onModeSelect, inputOneSym]() mutable {
            onModeSelect(btn_table);
            inputOneSym->show();

        });

        // WIDGETS
        layout_encrypt->addWidget(ButtonEncryption);
        layout_encrypt->addWidget(ButtonDecryption);
        layout_encrypt->addWidget(outputText);
        layout_encrypt->addWidget(btn_table, 0, Qt::AlignCenter);
        layout_encrypt->addWidget(btn_vig, 0, Qt::AlignCenter);
        layout_encrypt->addWidget(btn_salat, 0, Qt::AlignCenter);
        layout_encrypt->addWidget(btn_back, 0, Qt::AlignLeft);

        layout_encrypt->setSpacing(5);

        layout_encrypt->addWidget(inputOneSym);
        layout_encrypt->addWidget(inputText);
        layout_encrypt->addWidget(inputKey);

        inputOneSym->hide();
        ButtonEncryption->hide();
        ButtonDecryption->hide();

        wid_encrypt->show();
    });

    /*                                                          COLORS                                                                              */

    qApp->setStyleSheet(
    "QWidget { background-color: black; color: gray; }"      // All windows
    "QPushButton { "
    "   background-color: gray; "
    "   color: white; "
    "   border: none; "
    "   min-width: 100px; "
    "   max-width: 200px; "
    "   min-height: 25px; "
    "   padding: 5px; "
    "}"                                                     // All buttons
    "QPushButton:hover { background-color: darkgray; }"    // При наведении
    );


    btn_encrypt->hide();
    btn_exit->hide();
    btn_back->hide();

    // widgetDVD->show();

    layout->addWidget(btn_exit, 0, Qt::AlignLeft);
    layout->addWidget(btn_home, 0, Qt::AlignCenter);
    layout->addWidget(btn_back, 0, Qt::AlignCenter);
    layout->addWidget(btn_encrypt);

    wn_main.show();

    return a.exec();
}