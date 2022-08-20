#include "MockPlugin.hpp"

#include "MockKernel.hpp"

#include "MockGUI.hpp"

bool MockPlugin::InitializePlugin(const QString &, const QJsonObject &)
{

    // MockKernelInterface* pluginIns = new MockKernelInterface;
    // auto kernel = pluginIns->CreateKernel();

    // qDebug() << kernel->GetKernelName();


    kernelInterface = std::make_shared<MockKernelInterface>();

    guiInterface = new MockGuiInterface();

    qDebug() << "hello Initalize Mock Plugin";

    qDebug() << "gui interface:" << guiInterface;

    return true;
}
