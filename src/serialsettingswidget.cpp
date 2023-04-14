#include <QSettings>
#include "serialsettingswidget.h"
#include "ui_serialsettingswidget.h"

SerialSettingsWidget::SerialSettingsWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SerialSettingsWidget),
	m_serialModbus( NULL )
{
	ui->setupUi(this);
    enableGuiItems(false);
}

SerialSettingsWidget::~SerialSettingsWidget()
{
	delete ui;
}

int SerialSettingsWidget::setupModbusPort()
{
	QSettings s;

	int i = 0;
    ui->serialPort->disconnect();
    ui->serialPort->clear();

	ui->baud->setCurrentIndex( ui->baud->findText( s.value( "serialbaudrate" ).toString() ) );
	ui->parity->setCurrentIndex( ui->parity->findText( s.value( "serialparity" ).toString() ) );
	ui->stopBits->setCurrentIndex( ui->stopBits->findText( s.value( "serialstopbits" ).toString() ) );
	ui->dataBits->setCurrentIndex( ui->dataBits->findText( s.value( "serialdatabits" ).toString() ) );

	connect( ui->serialPort, SIGNAL( currentIndexChanged( int ) ),
			this, SLOT( changeSerialPort( int ) ) );
	connect( ui->baud, SIGNAL( currentIndexChanged( int ) ),
			this, SLOT( changeSerialPort( int ) ) );
	connect( ui->dataBits, SIGNAL( currentIndexChanged( int ) ),
			this, SLOT( changeSerialPort( int ) ) );
	connect( ui->stopBits, SIGNAL( currentIndexChanged( int ) ),
			this, SLOT( changeSerialPort( int ) ) );
	connect( ui->parity, SIGNAL( currentIndexChanged( int ) ),
			this, SLOT( changeSerialPort( int ) ) );

}

void SerialSettingsWidget::releaseSerialModbus()
{
	if( m_serialModbus )
	{
		modbus_close( m_serialModbus );
		modbus_free( m_serialModbus );
		m_serialModbus = NULL;
	}
}

static inline QString embracedString( const QString & s )
{
    return s.section( '(', 1 ).section( ')', 0, 0 );
}

void SerialSettingsWidget::enableGuiItems(bool checked)
{
	ui->serialPort->setEnabled(checked);
	ui->baud->setEnabled(checked);
	ui->dataBits->setEnabled(checked);
	ui->stopBits->setEnabled(checked);
	ui->parity->setEnabled(checked);
}

void SerialSettingsWidget::on_checkBox_clicked(bool checked)
{
	if (checked) {
        ui->setButton->setEnabled(true);
        ui->checkListen->setEnabled(true);
		setupModbusPort();
	}
	else {
        ui->setButton->setEnabled(false);
        ui->checkListen->setEnabled(false);
        ui->checkListen->setChecked(false);
        ui->listenPort->setEnabled(false);
        activeListen = false;
		releaseSerialModbus();
	}
	enableGuiItems(checked);
	emit serialPortActive(checked);
}

void SerialSettingsWidget::on_setButton_clicked()
{
    QSettings settings;
    settings.setValue( "serialinterface", ui->serialPort->text() );
    settings.setValue( "serialbaudrate", ui->baud->currentText() );
    settings.setValue( "serialparity", ui->parity->currentText() );
    settings.setValue( "serialdatabits", ui->dataBits->currentText() );
    settings.setValue( "serialstopbits", ui->stopBits->currentText() );

    const QString port = ui->serialPort->text();

    char parity;
    switch( ui->parity->currentIndex() )
    {
        case 1: parity = 'O'; break;
        case 2: parity = 'E'; break;
        default:
        case 0: parity = 'N'; break;
    }

    if(ui->checkListen->isChecked())
    {
        serialUSB = new QSerialPort;
        serialUSB->setPortName(ui->listenPort->text());
        serialUSB->setBaudRate(QSerialPort::Baud115200);
        serialUSB->setDataBits(QSerialPort::Data8);
        serialUSB->setParity(QSerialPort::NoParity);
        serialUSB->setStopBits(QSerialPort::OneStop);
        serialUSB->setFlowControl(QSerialPort::NoFlowControl);
        if (!serialUSB->open(QIODevice::WriteOnly))
        {
            qDebug() << "Failed to open portS4";

        }
    }
    changeModbusInterface(port, parity);

    emit serialPortActive(true);
}

void SerialSettingsWidget::on_checkListen_clicked(bool checked)
{
    if (checked) {
        ui->listenPort->setEnabled(true);
        activeListen = true;
    }
    else {
        ui->listenPort->setEnabled(false);
        activeListen = false;
    }
}
