#include "bascula.h"

#include <QSerialPort>

#include <QTime>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QException>
Bascula::Bascula(QObject *parent) :
    QThread(parent)
{
}

//! [0]
Bascula::~Bascula()
{
    m_mutex.lock();
    m_quit = true;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}
void Bascula::transaction(const QString &portName, int waitTimeout, const QString &request)
{
    const QMutexLocker locker(&m_mutex);
    m_portName = portName;
    m_waitTimeout = waitTimeout;
    m_request = request;
    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
}

void Bascula::stopReading(){
    m_quit = true;
    /*m_mutex.lock();
    m_cond.wait(&m_mutex);
    QString currentPortName;
    bool currentPortNameChanged = false;
    int currentWaitTimeout = m_waitTimeout;
    QString currentRequest = m_request;
    if (currentPortName != m_portName) {
        currentPortName = m_portName;
        currentPortNameChanged = true;
    } else {
        currentPortNameChanged = false;
    }
    currentWaitTimeout = m_waitTimeout;
    currentRequest = m_request;
    m_mutex.unlock();*/
}

void Bascula::run()
{
    m_quit = false;
    bool currentPortNameChanged = false;

    QString currentPortName;
    if (currentPortName != m_portName) {
        currentPortName = m_portName;
        currentPortNameChanged = true;
    }

    int currentWaitTimeout = m_waitTimeout;
    QString currentRequest = m_request;
    QSerialPort serial;

    if (currentPortName.isEmpty()) {
        emit error(tr("No port name specified"));
        return;
    }

    try  {

        while (!m_quit) {
            // qDebug() << "in whilte";
            //![6] //! [7]
            if (currentPortNameChanged) {
                serial.close();
                serial.setPortName(currentPortName);

                if (!serial.open(QIODevice::ReadWrite)) {
                    emit error(tr("Can't open %1, error code %2")
                               .arg(m_portName).arg(serial.error()));
                    return;
                }
            }
            //! [7] //! [8]
            // write request
            const QByteArray requestData = currentRequest.toUtf8();
            serial.write(requestData);
            if (serial.waitForBytesWritten(m_waitTimeout)) {
                //! [8] //! [10]
                // read response
                if (serial.waitForReadyRead(currentWaitTimeout)) {
                    QByteArray responseData = serial.readAll();
                    while (serial.waitForReadyRead(10))
                        responseData += serial.readAll();

                    const QString response = QString::fromUtf8(responseData);
                    //! [12]
                   // qDebug() << "valor antes de formatear "<< response.simplified();

                    if (response.simplified()!="NEG."){
                        const QString removespace = response.simplified();
                        QJsonObject stats_obj;
                        stats_obj["quantity"]=removespace.split(" ")[0];
                        stats_obj["type"]=removespace.split(" ")[1];
                        QJsonDocument doc(stats_obj);
                        //qDebug() << doc.toJson();
                        emit this->response(doc.toJson());
                    }
                    //! [10] //! [11] //! [12]
                } else {
                    emit timeout(tr("Wait read response timeout %1")
                                 .arg(QTime::currentTime().toString()));
                }
                //! [9] //! [11]
            } else {
                emit timeout(tr("Wait write request timeout %1")
                             .arg(QTime::currentTime().toString()));
            }

        }

    } catch (QException &e) {
        qDebug() << e.what();
        // handle exception
    }
}
