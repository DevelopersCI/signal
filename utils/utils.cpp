#include "utils.h"
#include <QRegularExpression>
#include <QStandardPaths>
#include <QApplication>
#include <QImageReader>
#include <QStorageInfo>
#include <QFileInfo>
#include <QProcess>
#include <QPixmap>
#include <QDebug>
#include <QFile>
#include <QDir>

#ifdef Q_OS_UNIX
#include <sys/utsname.h>
#endif

#include <memory>
#include <fstream>

Utils::Utils(QObject *parent) : QObject(parent)
{

}

QString Utils::getFileContent(const QString &path)
{
    QFile file(path);

    if (file.open(QIODevice::ReadOnly)) {
        return file.readAll();
    }

    return QString();
}

QPixmap Utils::renderSVG(const QString &path, const QSize &size)
{
    QImageReader reader;
    QPixmap pixmap;
    reader.setFileName(path);

    if (reader.canRead()) {
        const qreal ratio = qApp->devicePixelRatio();
        reader.setScaledSize(size * ratio);
        pixmap = QPixmap::fromImage(reader.read());
        pixmap.setDevicePixelRatio(ratio);
    } else {
        pixmap.load(path);
    }

    return pixmap;
}

QString Utils::getUserName()
{
    std::string user_name = std::getenv("USER");

    if (user_name.empty()) {
        user_name = std::getenv("USERNAME");
    }

    return QString::fromStdString(user_name);
}

QString Utils::getPlatform()
{
    struct utsname u;
    QString kernelType;
    QString cpuArchitecture;

    if (uname(&u) != 0) {
        cpuArchitecture = "i386";
    } else {
        kernelType = QString::fromLatin1(u.sysname);
        cpuArchitecture = QString::fromLatin1(u.machine);
    }

    return QString("%1 %2")
           .arg(kernelType)
           .arg(cpuArchitecture);
}

QString Utils::getDistribution()
{
    return QSysInfo::prettyProductName();
}

QString Utils::getKernelVersion()
{
    struct utsname u;
    QString kernelVersion;

    if (uname(&u) == 0) {
        kernelVersion = QString::fromLatin1(u.release);
    }

    return kernelVersion;
}

QString Utils::getBootTime()
{
    QProcess *process = new QProcess;
    process->start("systemd-analyze");
    process->waitForFinished(-1);

    QString output = process->readLine();
    QRegularExpression reg("\\s=.*s");
    QRegularExpressionMatch match = reg.match(output);
    QString bootTime = match.captured(0).remove(" = ");

    if (QLocale::system().name() == "zh_CN") {
        bootTime = bootTime.replace("min", "分").replace("s", "秒");
    }

    return bootTime;
}

QString Utils::getDebianVersion()
{
    QFile file("/etc/debian_version");

    // e.g. "9.0"
    if (file.open(QIODevice::ReadOnly)) {
        return file.readAll();
    }

    return QString();
}
