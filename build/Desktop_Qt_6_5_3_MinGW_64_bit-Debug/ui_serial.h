/********************************************************************************
** Form generated from reading UI file 'serial.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIAL_H
#define UI_SERIAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serial
{
public:
    QAction *actOpen_serial;
    QAction *actOpen_can;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *pressure;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_16;
    QGroupBox *groupBox_5;
    QPushButton *pushButton_7;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_17;
    QRadioButton *study_after_3;
    QRadioButton *study_after_4;
    QRadioButton *study_after_5;
    QRadioButton *study_front_3;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_18;
    QRadioButton *study_after;
    QRadioButton *study_front;
    QGroupBox *groupBox;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_4;
    QCheckBox *filter;
    QLineEdit *filter_2;
    QTextBrowser *textBrowser;
    QGridLayout *gridLayout_5;
    QLabel *label_2;
    QLabel *label_9;
    QLabel *label_13;
    QLabel *label_5;
    QLabel *lf;
    QLabel *rr;
    QLabel *rf;
    QLabel *label;
    QLabel *label_11;
    QLabel *lr;
    QLabel *rr_Receive;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *lf_Receive;
    QLabel *lr_Receive;
    QLineEdit *lineEdit2;
    QLineEdit *lineEdit3;
    QLineEdit *lineEdit4;
    QLineEdit *lineEdit1;
    QLabel *label_23;
    QLabel *rf_Receive;
    QLineEdit *ID;
    QLabel *label_3;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_14;
    QLabel *frames;
    QLabel *label_15;
    QLabel *label_19;
    QLabel *label_16;
    QGridLayout *gridLayout;
    QComboBox *portBox;
    QPushButton *clearuart;
    QGridLayout *gridLayout_3;
    QTextBrowser *receiveData;
    QLabel *label_6;
    QWidget *tab_2;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_11;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_36;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *horizontalSpacer_27;
    QHBoxLayout *horizontalLayout_37;
    QLabel *label_35;
    QComboBox *btl;
    QHBoxLayout *horizontalLayout_38;
    QLabel *label_36;
    QComboBox *sjw;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_37;
    QComboBox *xy;
    QHBoxLayout *horizontalLayout_40;
    QLabel *label_38;
    QComboBox *tz;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_41;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *horizontalSpacer_28;
    QHBoxLayout *horizontalLayout_42;
    QLabel *label_39;
    QComboBox *can_btl;
    QHBoxLayout *horizontalLayout_43;
    QLabel *label_40;
    QComboBox *pressure_number_id;
    QHBoxLayout *horizontalLayout_44;
    QSpacerItem *horizontalSpacer_30;
    QSpacerItem *horizontalSpacer_31;
    QHBoxLayout *horizontalLayout_45;
    QSpacerItem *horizontalSpacer_32;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_46;
    QSpacerItem *horizontalSpacer_33;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_34;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *serial)
    {
        if (serial->objectName().isEmpty())
            serial->setObjectName("serial");
        serial->resize(861, 722);
        actOpen_serial = new QAction(serial);
        actOpen_serial->setObjectName("actOpen_serial");
        actOpen_serial->setCheckable(true);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(11);
        actOpen_serial->setFont(font);
        actOpen_can = new QAction(serial);
        actOpen_can->setObjectName("actOpen_can");
        actOpen_can->setCheckable(true);
        actOpen_can->setFont(font);
        centralWidget = new QWidget(serial);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(true);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        font1.setPointSize(10);
        tabWidget->setFont(font1);
        pressure = new QWidget();
        pressure->setObjectName("pressure");
        gridLayout_2 = new QGridLayout(pressure);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_16 = new QGridLayout();
        gridLayout_16->setSpacing(6);
        gridLayout_16->setObjectName("gridLayout_16");
        groupBox_5 = new QGroupBox(pressure);
        groupBox_5->setObjectName("groupBox_5");
        pushButton_7 = new QPushButton(groupBox_5);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(0, 260, 93, 28));
        layoutWidget = new QWidget(groupBox_5);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 29, 233, 79));
        gridLayout_17 = new QGridLayout(layoutWidget);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName("gridLayout_17");
        gridLayout_17->setContentsMargins(0, 0, 0, 0);
        study_after_3 = new QRadioButton(layoutWidget);
        study_after_3->setObjectName("study_after_3");
        study_after_3->setCheckable(true);
        study_after_3->setChecked(false);
        study_after_3->setAutoRepeat(false);

        gridLayout_17->addWidget(study_after_3, 0, 1, 1, 1);

        study_after_4 = new QRadioButton(layoutWidget);
        study_after_4->setObjectName("study_after_4");
        study_after_4->setCheckable(true);
        study_after_4->setChecked(false);
        study_after_4->setAutoRepeat(false);

        gridLayout_17->addWidget(study_after_4, 1, 1, 1, 1);

        study_after_5 = new QRadioButton(layoutWidget);
        study_after_5->setObjectName("study_after_5");
        study_after_5->setCheckable(true);
        study_after_5->setChecked(false);
        study_after_5->setAutoRepeat(false);

        gridLayout_17->addWidget(study_after_5, 1, 0, 1, 1);

        study_front_3 = new QRadioButton(layoutWidget);
        study_front_3->setObjectName("study_front_3");
        study_front_3->setChecked(false);

        gridLayout_17->addWidget(study_front_3, 0, 0, 1, 1);

        layoutWidget1->raise();
        pushButton_7->raise();

        gridLayout_16->addWidget(groupBox_5, 0, 0, 1, 1);

        groupBox_6 = new QGroupBox(pressure);
        groupBox_6->setObjectName("groupBox_6");

        gridLayout_16->addWidget(groupBox_6, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_16, 1, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName("gridLayout_7");
        groupBox_2 = new QGroupBox(pressure);
        groupBox_2->setObjectName("groupBox_2");
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(0, 260, 93, 28));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(10, 30, 216, 31));
        gridLayout_18 = new QGridLayout(layoutWidget1);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName("gridLayout_18");
        gridLayout_18->setContentsMargins(0, 0, 0, 0);
        study_after = new QRadioButton(layoutWidget1);
        study_after->setObjectName("study_after");
        study_after->setCheckable(true);
        study_after->setChecked(false);
        study_after->setAutoRepeat(false);

        gridLayout_18->addWidget(study_after, 0, 1, 1, 1);

        study_front = new QRadioButton(layoutWidget1);
        study_front->setObjectName("study_front");
        study_front->setChecked(false);

        gridLayout_18->addWidget(study_front, 0, 0, 1, 1);

        layoutWidget1->raise();
        pushButton_2->raise();

        gridLayout_7->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(pressure);
        groupBox->setObjectName("groupBox");

        gridLayout_7->addWidget(groupBox, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_7, 0, 0, 1, 1);

        tabWidget->addTab(pressure, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName("gridLayout_4");
        filter = new QCheckBox(tab);
        filter->setObjectName("filter");

        gridLayout_4->addWidget(filter, 0, 0, 1, 1);

        filter_2 = new QLineEdit(tab);
        filter_2->setObjectName("filter_2");

        gridLayout_4->addWidget(filter_2, 0, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 2, 1, 1, 1);

        textBrowser = new QTextBrowser(tab);
        textBrowser->setObjectName("textBrowser");

        gridLayout_6->addWidget(textBrowser, 3, 0, 1, 2);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName("gridLayout_5");
        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_2, 7, 0, 1, 1);

        label_9 = new QLabel(tab);
        label_9->setObjectName("label_9");
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_9, 7, 1, 1, 1);

        label_13 = new QLabel(tab);
        label_13->setObjectName("label_13");
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_13, 9, 1, 1, 1);

        label_5 = new QLabel(tab);
        label_5->setObjectName("label_5");

        gridLayout_5->addWidget(label_5, 3, 1, 1, 1);

        lf = new QLabel(tab);
        lf->setObjectName("lf");
        lf->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lf, 4, 1, 1, 1);

        rr = new QLabel(tab);
        rr->setObjectName("rr");
        rr->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(rr, 10, 1, 1, 1);

        rf = new QLabel(tab);
        rf->setObjectName("rf");
        rf->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(rf, 8, 1, 1, 1);

        label = new QLabel(tab);
        label->setObjectName("label");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(12);
        label->setFont(font2);

        gridLayout_5->addWidget(label, 0, 0, 1, 4);

        label_11 = new QLabel(tab);
        label_11->setObjectName("label_11");
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_11, 9, 0, 1, 1);

        lr = new QLabel(tab);
        lr->setObjectName("lr");
        lr->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lr, 6, 1, 1, 1);

        rr_Receive = new QLabel(tab);
        rr_Receive->setObjectName("rr_Receive");
        rr_Receive->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(rr_Receive, 10, 2, 1, 2);

        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_4, 3, 0, 1, 1);

        label_7 = new QLabel(tab);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_7, 5, 0, 1, 1);

        label_8 = new QLabel(tab);
        label_8->setObjectName("label_8");
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_8, 5, 1, 1, 1);

        lf_Receive = new QLabel(tab);
        lf_Receive->setObjectName("lf_Receive");
        lf_Receive->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lf_Receive, 4, 2, 1, 2);

        lr_Receive = new QLabel(tab);
        lr_Receive->setObjectName("lr_Receive");
        lr_Receive->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lr_Receive, 6, 2, 1, 2);

        lineEdit2 = new QLineEdit(tab);
        lineEdit2->setObjectName("lineEdit2");

        gridLayout_5->addWidget(lineEdit2, 6, 0, 1, 1);

        lineEdit3 = new QLineEdit(tab);
        lineEdit3->setObjectName("lineEdit3");

        gridLayout_5->addWidget(lineEdit3, 8, 0, 1, 1);

        lineEdit4 = new QLineEdit(tab);
        lineEdit4->setObjectName("lineEdit4");

        gridLayout_5->addWidget(lineEdit4, 10, 0, 1, 1);

        lineEdit1 = new QLineEdit(tab);
        lineEdit1->setObjectName("lineEdit1");

        gridLayout_5->addWidget(lineEdit1, 4, 0, 1, 1);

        label_23 = new QLabel(tab);
        label_23->setObjectName("label_23");
        label_23->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_23, 1, 0, 1, 1);

        rf_Receive = new QLabel(tab);
        rf_Receive->setObjectName("rf_Receive");
        rf_Receive->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(rf_Receive, 8, 2, 1, 2);

        ID = new QLineEdit(tab);
        ID->setObjectName("ID");

        gridLayout_5->addWidget(ID, 2, 0, 1, 1);

        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");

        gridLayout_5->addWidget(label_3, 3, 2, 1, 2);

        label_10 = new QLabel(tab);
        label_10->setObjectName("label_10");

        gridLayout_5->addWidget(label_10, 5, 2, 1, 2);

        label_12 = new QLabel(tab);
        label_12->setObjectName("label_12");

        gridLayout_5->addWidget(label_12, 7, 2, 1, 2);

        label_14 = new QLabel(tab);
        label_14->setObjectName("label_14");

        gridLayout_5->addWidget(label_14, 9, 2, 1, 2);

        frames = new QLabel(tab);
        frames->setObjectName("frames");
        frames->setContextMenuPolicy(Qt::DefaultContextMenu);
        frames->setLayoutDirection(Qt::LeftToRight);
        frames->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(frames, 2, 1, 1, 1);

        label_15 = new QLabel(tab);
        label_15->setObjectName("label_15");

        gridLayout_5->addWidget(label_15, 2, 2, 1, 2);

        label_19 = new QLabel(tab);
        label_19->setObjectName("label_19");
        label_19->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_19, 1, 1, 1, 1);

        label_16 = new QLabel(tab);
        label_16->setObjectName("label_16");
        label_16->setLayoutDirection(Qt::LeftToRight);

        gridLayout_5->addWidget(label_16, 1, 2, 1, 2);


        gridLayout_6->addLayout(gridLayout_5, 0, 1, 2, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        portBox = new QComboBox(tab);
        portBox->setObjectName("portBox");

        gridLayout->addWidget(portBox, 0, 0, 1, 1);

        clearuart = new QPushButton(tab);
        clearuart->setObjectName("clearuart");

        gridLayout->addWidget(clearuart, 0, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout, 1, 0, 2, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName("gridLayout_3");
        receiveData = new QTextBrowser(tab);
        receiveData->setObjectName("receiveData");

        gridLayout_3->addWidget(receiveData, 1, 0, 1, 1);

        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");
        label_6->setFont(font2);

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_3, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_6);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        layoutWidget_2 = new QWidget(tab_2);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(12, 32, 453, 223));
        gridLayout_11 = new QGridLayout(layoutWidget_2);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName("gridLayout_11");
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        groupBox_7 = new QGroupBox(layoutWidget_2);
        groupBox_7->setObjectName("groupBox_7");
        horizontalLayout_36 = new QHBoxLayout(groupBox_7);
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_36->setObjectName("horizontalLayout_36");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_7->addItem(horizontalSpacer_27);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setObjectName("horizontalLayout_37");
        label_35 = new QLabel(groupBox_7);
        label_35->setObjectName("label_35");

        horizontalLayout_37->addWidget(label_35);

        btl = new QComboBox(groupBox_7);
        btl->setObjectName("btl");

        horizontalLayout_37->addWidget(btl);


        verticalLayout_7->addLayout(horizontalLayout_37);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(6);
        horizontalLayout_38->setObjectName("horizontalLayout_38");
        label_36 = new QLabel(groupBox_7);
        label_36->setObjectName("label_36");

        horizontalLayout_38->addWidget(label_36);

        sjw = new QComboBox(groupBox_7);
        sjw->setObjectName("sjw");

        horizontalLayout_38->addWidget(sjw);


        verticalLayout_7->addLayout(horizontalLayout_38);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(6);
        horizontalLayout_39->setObjectName("horizontalLayout_39");
        label_37 = new QLabel(groupBox_7);
        label_37->setObjectName("label_37");

        horizontalLayout_39->addWidget(label_37);

        xy = new QComboBox(groupBox_7);
        xy->setObjectName("xy");

        horizontalLayout_39->addWidget(xy);


        verticalLayout_7->addLayout(horizontalLayout_39);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setSpacing(6);
        horizontalLayout_40->setObjectName("horizontalLayout_40");
        label_38 = new QLabel(groupBox_7);
        label_38->setObjectName("label_38");

        horizontalLayout_40->addWidget(label_38);

        tz = new QComboBox(groupBox_7);
        tz->setObjectName("tz");

        horizontalLayout_40->addWidget(tz);


        verticalLayout_7->addLayout(horizontalLayout_40);


        horizontalLayout_36->addLayout(verticalLayout_7);


        gridLayout_11->addWidget(groupBox_7, 0, 0, 1, 1);

        groupBox_8 = new QGroupBox(layoutWidget_2);
        groupBox_8->setObjectName("groupBox_8");
        horizontalLayout_41 = new QHBoxLayout(groupBox_8);
        horizontalLayout_41->setSpacing(6);
        horizontalLayout_41->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_41->setObjectName("horizontalLayout_41");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName("verticalLayout_8");
        horizontalSpacer_28 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_8->addItem(horizontalSpacer_28);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setSpacing(6);
        horizontalLayout_42->setObjectName("horizontalLayout_42");
        label_39 = new QLabel(groupBox_8);
        label_39->setObjectName("label_39");

        horizontalLayout_42->addWidget(label_39);

        can_btl = new QComboBox(groupBox_8);
        can_btl->setObjectName("can_btl");

        horizontalLayout_42->addWidget(can_btl);


        verticalLayout_8->addLayout(horizontalLayout_42);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(6);
        horizontalLayout_43->setObjectName("horizontalLayout_43");
        label_40 = new QLabel(groupBox_8);
        label_40->setObjectName("label_40");

        horizontalLayout_43->addWidget(label_40);

        pressure_number_id = new QComboBox(groupBox_8);
        pressure_number_id->setObjectName("pressure_number_id");

        horizontalLayout_43->addWidget(pressure_number_id);


        verticalLayout_8->addLayout(horizontalLayout_43);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setSpacing(6);
        horizontalLayout_44->setObjectName("horizontalLayout_44");
        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_44->addItem(horizontalSpacer_30);


        verticalLayout_8->addLayout(horizontalLayout_44);

        horizontalSpacer_31 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_8->addItem(horizontalSpacer_31);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setObjectName("horizontalLayout_45");
        horizontalSpacer_32 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_45->addItem(horizontalSpacer_32);


        verticalLayout_8->addLayout(horizontalLayout_45);


        horizontalLayout_41->addLayout(verticalLayout_8);


        gridLayout_11->addWidget(groupBox_8, 0, 1, 1, 1);

        layoutWidget_3 = new QWidget(tab_2);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(20, 300, 181, 34));
        horizontalLayout_46 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_46->setSpacing(6);
        horizontalLayout_46->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_46->setObjectName("horizontalLayout_46");
        horizontalLayout_46->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_33 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_46->addItem(horizontalSpacer_33);

        pushButton_5 = new QPushButton(layoutWidget_3);
        pushButton_5->setObjectName("pushButton_5");

        horizontalLayout_46->addWidget(pushButton_5);

        horizontalSpacer_34 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_46->addItem(horizontalSpacer_34);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        serial->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(serial);
        statusBar->setObjectName("statusBar");
        serial->setStatusBar(statusBar);
        mainToolBar = new QToolBar(serial);
        mainToolBar->setObjectName("mainToolBar");
        serial->addToolBar(Qt::TopToolBarArea, mainToolBar);

        mainToolBar->addAction(actOpen_serial);
        mainToolBar->addAction(actOpen_can);

        retranslateUi(serial);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(serial);
    } // setupUi

    void retranslateUi(QMainWindow *serial)
    {
        serial->setWindowTitle(QCoreApplication::translate("serial", "serial", nullptr));
        actOpen_serial->setText(QCoreApplication::translate("serial", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        actOpen_can->setText(QCoreApplication::translate("serial", "\346\211\223\345\274\200CAN", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("serial", "\345\233\233\350\275\256\350\203\216\345\216\213", nullptr));
        pushButton_7->setText(QCoreApplication::translate("serial", "\345\217\221\351\200\201\345\221\275\344\273\244", nullptr));
        study_after_3->setText(QCoreApplication::translate("serial", "\345\255\246\344\271\240\345\217\263\345\211\215\350\275\256", nullptr));
        study_after_4->setText(QCoreApplication::translate("serial", "\345\255\246\344\271\240\345\217\263\345\220\216\350\275\256", nullptr));
        study_after_5->setText(QCoreApplication::translate("serial", "\345\255\246\344\271\240\345\217\263\345\211\215\350\275\256", nullptr));
        study_front_3->setText(QCoreApplication::translate("serial", "\345\255\246\344\271\240\345\267\246\345\211\215\350\275\256", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("serial", "\345\233\233\350\275\256\350\203\216\345\216\213\347\212\266\346\200\201", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("serial", "\344\270\244\350\275\256\350\203\216\345\216\213", nullptr));
        pushButton_2->setText(QCoreApplication::translate("serial", "\345\217\221\351\200\201\345\221\275\344\273\244", nullptr));
        study_after->setText(QCoreApplication::translate("serial", "\345\255\246\344\271\240\345\220\216\350\275\256", nullptr));
        study_front->setText(QCoreApplication::translate("serial", "\345\255\246\344\271\240\345\211\215\350\275\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("serial", "\344\270\244\350\275\256\350\203\216\345\216\213\347\212\266\346\200\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(pressure), QCoreApplication::translate("serial", "\350\203\216\345\216\213\345\267\245\345\205\267\347\256\261", nullptr));
        filter->setText(QCoreApplication::translate("serial", "\345\220\257\345\212\250ID\350\277\207\346\273\244", nullptr));
        filter_2->setText(QString());
        textBrowser->setHtml(QCoreApplication::translate("serial", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\344\275\277\347\224\250\346\226\271\346\263\225:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">1\343\200\201\346\211\223\345\274\200\344\270\262\345\217\243\343\200\201\346\211\223\345\274\200CAN\350\256\276\345\244\207</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"
                        "\"><span style=\" font-family:'SimSun'; font-size:9pt;\">2\343\200\201\350\276\223\345\205\245\347\233\270\345\272\224\346\265\213\350\257\225\350\275\256\350\203\216\347\232\204\345\210\235\345\247\213\345\200\274\357\274\210\346\212\212\346\234\200\345\274\200\345\247\213\347\232\204\346\234\200\347\273\210\345\200\274\344\275\234\344\270\272\345\210\235\345\247\213\345\200\274\357\274\211</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">3\343\200\201\351\230\262\346\255\242\345\205\266\344\273\226\350\203\216\345\216\213\345\271\262\346\211\260\357\274\214\350\276\223\345\205\245\345\275\223\345\211\215\350\203\216\345\216\213ID\350\277\233\350\241\214\350\277\207\346\273\244\357\274\214\345\217\252\346\216\245\346\224\266\345\275\223\345\211\215\350\203\216\345\216\213\347\232\204\346\225\260\346\215\256</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; ma"
                        "rgin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\346\240\274\345\274\217XX XX XX XX\347\251\272\346\240\274\345\210\206\345\274\200</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">4\343\200\201\350\203\216\345\216\213\346\216\245\346\224\266\347\216\207\350\256\241\347\256\227\345\205\254\345\274\217\344\270\272\357\274\232CAN\345\267\256\345\200\274/\344\270\262\345\217\243\345\270\247\346\225\260</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("serial", "\345\217\263\345\211\215\350\275\256\345\210\235\345\247\213\345\200\274", nullptr));
        label_9->setText(QCoreApplication::translate("serial", "\345\217\263\345\211\215\350\275\256\346\234\200\347\273\210\345\200\274", nullptr));
        label_13->setText(QCoreApplication::translate("serial", "\345\217\263\345\211\215\350\275\256\346\234\200\347\273\210\345\200\274:", nullptr));
        label_5->setText(QCoreApplication::translate("serial", "\345\267\246\345\211\215\350\275\256\346\234\200\347\273\210\345\200\274", nullptr));
        lf->setText(QCoreApplication::translate("serial", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
        rr->setText(QCoreApplication::translate("serial", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
        rf->setText(QCoreApplication::translate("serial", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
        label->setText(QCoreApplication::translate("serial", "                \350\203\216\345\216\213\346\216\245\346\224\266\346\225\260\346\215\256\345\244\204\347\220\206", nullptr));
        label_11->setText(QCoreApplication::translate("serial", "\345\217\263\345\220\216\350\275\256\345\210\235\345\247\213\345\200\274", nullptr));
        lr->setText(QCoreApplication::translate("serial", "\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224\342\200\224", nullptr));
        rr_Receive->setText(QString());
        label_4->setText(QCoreApplication::translate("serial", "\345\267\246\345\211\215\350\275\256\345\210\235\345\247\213\345\200\274", nullptr));
        label_7->setText(QCoreApplication::translate("serial", "\345\267\246\345\220\216\350\275\256\345\210\235\345\247\213\345\200\274", nullptr));
        label_8->setText(QCoreApplication::translate("serial", "\345\267\246\345\220\216\350\275\256\346\234\200\347\273\210\345\200\274", nullptr));
        lf_Receive->setText(QString());
        lr_Receive->setText(QString());
        label_23->setText(QCoreApplication::translate("serial", "\350\203\216\345\216\213ID", nullptr));
        rf_Receive->setText(QString());
        label_3->setText(QCoreApplication::translate("serial", "\345\267\246\345\211\215\350\275\256\350\203\216\345\216\213\346\216\245\346\224\266\347\216\207", nullptr));
        label_10->setText(QCoreApplication::translate("serial", "\345\267\246\345\220\216\350\275\256\350\203\216\345\216\213\346\216\245\346\224\266\347\216\207", nullptr));
        label_12->setText(QCoreApplication::translate("serial", "\345\217\263\345\211\215\350\275\256\350\203\216\345\216\213\346\216\245\346\224\266\347\216\207", nullptr));
        label_14->setText(QCoreApplication::translate("serial", "\345\217\263\345\211\215\350\275\256\350\203\216\345\216\213\346\216\245\346\224\266\347\216\207", nullptr));
        frames->setText(QString());
        label_15->setText(QString());
        label_19->setText(QCoreApplication::translate("serial", "\344\270\262\345\217\243\345\270\247\346\225\260", nullptr));
        label_16->setText(QCoreApplication::translate("serial", "\350\203\216\345\216\213\347\224\265\351\207\217", nullptr));
        clearuart->setText(QCoreApplication::translate("serial", "\346\270\205\351\231\244", nullptr));
        label_6->setText(QCoreApplication::translate("serial", "                 \344\270\262\345\217\243\344\277\241\346\201\257\346\216\245\346\224\266\347\252\227\345\217\243", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("serial", "\350\203\216\345\216\213\346\240\207\345\256\232", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("serial", "      \344\270\262\345\217\243\351\205\215\347\275\256", nullptr));
        label_35->setText(QCoreApplication::translate("serial", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        label_36->setText(QCoreApplication::translate("serial", "\346\225\260\346\215\256\344\275\215\357\274\232", nullptr));
        label_37->setText(QCoreApplication::translate("serial", "\346\240\241\351\252\214\357\274\232", nullptr));
        label_38->setText(QCoreApplication::translate("serial", "\345\201\234\346\255\242\344\275\215\357\274\232", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("serial", "          CAN\351\205\215\347\275\256", nullptr));
        label_39->setText(QCoreApplication::translate("serial", "CAN\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        label_40->setText(QCoreApplication::translate("serial", "\350\203\216\345\216\213\350\256\241\346\225\260ID\357\274\232", nullptr));
        pushButton_5->setText(QCoreApplication::translate("serial", "\344\277\235\345\255\230\351\205\215\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("serial", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serial: public Ui_serial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIAL_H
