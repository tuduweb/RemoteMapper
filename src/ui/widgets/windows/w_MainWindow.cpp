#include "w_MainWindow.hpp"

#include "qdebug.h"

#include "ui/widgets/widgets/NormalDisplayWidget.hpp"

#include "ui/widgets/widgets/FrameDisplayWidget.hpp"

#include "base/interface/DeviceInterface.hpp"

#include "core/stream/data/SerialDataStream.hpp"

//Bundle
#include "core/handler/BundleHandler.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    qDebug() << "show show show";

    /** Init GUI **/
    QStringList deviceLists = BundleManager->GetBundleLists();
    remotes_cb->addItems(deviceLists);
    
}

#include "ui/widgets/editors/w_RemoteEditor.hpp"

void MainWindow::on_remotes_btn_clicked()
{
	//RemoteEditor w(QJsonObject{}, this);
	RemoteEditor w(_device, this);
	//RemoteObject object;_device

    QJsonObject conf = w.OpenEditor();//其实没有返回数据的吧..
}

void MainWindow::on_remoteStart_btn_clicked()
{
    //
    //_device->
    // link device to other models
}
