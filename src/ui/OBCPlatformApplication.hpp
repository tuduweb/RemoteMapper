#pragma once

#include "base/OBCBaseApplication.hpp"

#include "core/settings/SettingsBackend.hpp"

#include <QApplication>

#include "core/handler/BundleHandler.hpp"

class OBCPlatformApplication :public QApplication, public OBCApplicationInterface
{
    Q_OBJECT
    public:
        OBCPlatformApplication(int &argc, char *argv[]) : OBCApplicationInterface(), QApplication(argc, argv){};
        virtual ~OBCPlatformApplication(){};

        virtual OBCExitReason GetExitReason() const final
        {
            return _exitReason;
        }

        virtual bool Initialize() final{

            // inject quit slots
            connect(this, &OBCPlatformApplication::aboutToQuit, this, &OBCPlatformApplication::quitInternal);

            // load configs
            LoadConfiguration();

            // Install a translater. From the OS/DE
            return true;
        };

        virtual OBCExitReason RunOBC() final {
        
            BundleManager = new BundleHandler();

            return runOBCInternal();
        
        }

    protected:
        virtual OBCExitReason runOBCInternal() = 0;
        virtual void terminateUIInternal() = 0;

        virtual void SetExitReason(OBCExitReason r) final
        {
            _exitReason = r;
        }

    private:
        void quitInternal() {

            terminateUIInternal();
        
            delete BundleManager;
            BundleManager = nullptr;
        
        };

    private:
        OBCExitReason _exitReason;
};