/***************************************************************************
 *   Copyright (C) 2011~2011 by CSSlayer                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/
#include <QTimer>

#include <KDebug>
#include <KPluginFactory>
#include <KPluginLoader>
#include <KSharedConfig>
#include <KConfigGroup>
#include <KStandardDirs>
#include <KDesktopFile>
#include <KProcess>
#include <KShell>

#include "imlauncher.h"

K_PLUGIN_FACTORY(IMChooserFactory, registerPlugin<IMLauncher>();)
K_EXPORT_PLUGIN(IMChooserFactory("kded_imlauncher"))


IMLauncher::IMLauncher(QObject *parent, const QList<QVariant> &) : KDEDModule(parent)
    ,imProcess(0)
    ,m_failStart(0)
{
    KGlobal::dirs()->addResourceType("inputmethods", "data", "inputmethods");
    startInputMethod();
}

IMLauncher::~IMLauncher()
{
    if (imProcess) {
        imProcess->disconnect(SIGNAL(finished(int,QProcess::ExitStatus)));
        imProcess->kill();
        delete imProcess;
        imProcess = 0;
    }
}

void IMLauncher::startInputMethod()
{
    if (imProcess) {
        imProcess->disconnect(SIGNAL(finished(int,QProcess::ExitStatus)));
        imProcess->kill();
        delete imProcess;
        imProcess = 0;
    }

    KSharedConfig::Ptr config = KSharedConfig::openConfig("imlauncherrc", KConfig::SimpleConfig);
    KConfigGroup group(config, "IMLauncher");
    QString defaultIM = group.readEntry<QString>("DefaultIM", "none");
    qDebug() << defaultIM;

    if (defaultIM == "none")
        return;
    QString desktopFile = KGlobal::dirs()->findResource("inputmethods", defaultIM.append(".desktop"));
    if (desktopFile.isEmpty())
        return;

    KDesktopFile file(desktopFile);
    if (!file.tryExec())
        return;
    QString exec = file.desktopGroup().readEntry<QString>("Exec", QString());
    qDebug() << exec;
    if (exec.isEmpty())
        return;
    imProcess = new KProcess;
    connect(imProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(imFinshed(int,QProcess::ExitStatus)));
    *imProcess << KShell::splitArgs( exec );
    m_startTime = QDateTime::currentDateTimeUtc();
    imProcess->start();
}

void IMLauncher::imFinshed(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    delete imProcess;
    imProcess = 0;
    if (m_startTime.msecsTo(QDateTime::currentDateTimeUtc()) < 5000) {
        m_failStart++;
    }

    if (m_failStart >= 5) {
        return;
    }

    QTimer::singleShot(1000, this, SLOT(startInputMethod()));
}


