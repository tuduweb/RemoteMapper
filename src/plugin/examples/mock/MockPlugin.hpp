#include "../../PluginInterface.hpp"

#include <QObject>


//using namespace OBC::Plugin;

class MockPlugin : public QObject, OBC::Plugin::ObInterface
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID ObInterface_IID)
    Q_INTERFACES(OBC::Plugin::ObInterface)

public:
    bool InitializePlugin(const QString &, const QJsonObject &) override;
};