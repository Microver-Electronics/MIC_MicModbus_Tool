#ifndef SERIALSETTINGSWIDGET_H
#define SERIALSETTINGSWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "imodbus.h"
#include "modbus.h"

namespace Ui {
class SerialSettingsWidget;
}


class SerialSettingsWidget : public QWidget, public IModbus
{
	Q_OBJECT

public:
	SerialSettingsWidget(QWidget *parent = 0);
	virtual ~SerialSettingsWidget();

	virtual modbus_t*  modbus() { return m_serialModbus; }

	virtual int setupModbusPort();

    QSerialPort *serialUSB= nullptr;

    bool activeListen = false;

protected:
	virtual void changeModbusInterface(const QString &port, char parity) = 0;
	void releaseSerialModbus();
	void enableGuiItems(bool checked);

    Ui::SerialSettingsWidget *ui;
    modbus_t *                m_serialModbus;

signals:
	void serialPortActive(bool active);
	void connectionError(const QString &msg);

private slots:
	void on_checkBox_clicked(bool checked);

    void on_setButton_clicked();

    void on_checkListen_clicked(bool checked);

private:

};

#endif // SERIALSETTINGSWIDGET_H
