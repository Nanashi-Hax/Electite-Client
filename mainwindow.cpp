#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Electite.hpp"

#include <QThread>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), electite()
{
    ui->setupUi(this);

    // ボタンコールバック登録
    connect(ui->pushButtonConnect, &QPushButton::clicked, this, &MainWindow::onConnect);
    connect(ui->pushButtonDisconnect, &QPushButton::clicked, this, &MainWindow::onDisconnect);
    connect(ui->pushButtonSetDataBreakpoint, &QPushButton::clicked, this, &MainWindow::onSetDataBreakpoint);
    connect(ui->pushButtonDataBreakpointClear, &QPushButton::clicked, this, &MainWindow::onDataBreakpointClear);

    // Electiteイベント登録
    connect(this, &MainWindow::requestStart, &electite, &ElectiteViewModel::onStart);
    connect(this, &MainWindow::requestStop, &electite, &ElectiteViewModel::onStop);
    connect(this, &MainWindow::requestConnectServer, &electite, &ElectiteViewModel::onConnectServer);
    connect(this, &MainWindow::requestDisconnectServer, &electite, &ElectiteViewModel::onDisconnectServer);
    connect(this, &MainWindow::requestSetDataBreakpoint, &electite, &ElectiteViewModel::onSetDataBreakpoint);
    connect(this, &MainWindow::requestUnsetDataBreakpoint, &electite, &ElectiteViewModel::onUnsetDataBreakpoint);

    // Electiteコールバック登録
    connect(&electite, &ElectiteViewModel::dataBreakReceived, this, &MainWindow::onDataBreakReceived);

    // コンボボックス登録
    ui->comboBoxDataBreakpointSize->addItem("8-bit",  static_cast<uint32_t>(Electite::BreakpointSize::Bit8));
    ui->comboBoxDataBreakpointSize->addItem("16-bit", static_cast<uint32_t>(Electite::BreakpointSize::Bit16));
    ui->comboBoxDataBreakpointSize->addItem("32-bit", static_cast<uint32_t>(Electite::BreakpointSize::Bit32));
    ui->comboBoxDataBreakpointSize->addItem("64-bit", static_cast<uint32_t>(Electite::BreakpointSize::Bit64));

    // ブレークポイントビュー登録
    ui->tableViewDataBreakpoint->setModel(&dataBreakInfoModel);

    // ヘッダーのレイアウト変更
    QHeaderView* header = ui->tableViewDataBreakpoint->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    emit requestStart();
}

MainWindow::~MainWindow()
{
    emit requestStop();
    delete ui;
}

void MainWindow::onConnect()
{
    emit requestConnectServer(ui->lineEditIPAddress->text());
}

void MainWindow::onDisconnect()
{
    emit requestDisconnectServer();
}

void MainWindow::onSetDataBreakpoint()
{
    bool ok;
    uint32_t address = ui->lineEditDataBreakpointAddress->text().toUInt(&ok, 16);
    if(!ok) return;
    bool enable = ui->checkBoxDataBreakpointEnable->isChecked();
    bool read = ui->checkBoxDataBreakpointRead->isChecked();
    bool write = ui->checkBoxDataBreakpointWrite->isChecked();
    auto size = static_cast<Electite::BreakpointSize>(ui->comboBoxDataBreakpointSize->currentData().toUInt());

    if(enable) emit requestSetDataBreakpoint(address, read, write, size);
    else emit requestUnsetDataBreakpoint();
}

void MainWindow::onDataBreakpointClear()
{
    dataBreakInfoModel.clear();
}

void MainWindow::onDataBreakReceived(uint32_t dAddress, uint32_t iAddress)
{
    DataBreakInfoEntry entry(dAddress, iAddress);
    dataBreakInfoModel.add(entry);
}
