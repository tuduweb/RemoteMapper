#pragma once
#include "ui/OBCPlatformApplication.hpp"

//class MainWindow;
#include "ui/widgets/windows/w_MainWindow.hpp"

namespace OBC
{
    class OBCWidgetApplication : public OBCPlatformApplication
    {
        Q_OBJECT
        public:
            explicit OBCWidgetApplication(int &argc, char *argv[]) : OBCPlatformApplication(argc, argv) {};

        private:
            OBCExitReason runOBCInternal() override {

                //setQuitOnLastWindowClosed(false);


                // debug mode

                /*************** normal ***************/
                // show window : normal window
                mainWindow = new MainWindow();
	            mainWindow->show();


                return (OBCExitReason) exec();
            };
            void terminateUIInternal() override {
                delete mainWindow;
                //    StringToFile(JsonToString(UIStates), QV2RAY_CONFIG_DIR + QV2RAY_WIDGETUI_STATE_FILENAME);
            };

        private:
            MainWindow* mainWindow;

    };
};

#ifdef OBCApplication
#undef OBCApplication
#endif
#define OBCApplication OBCWidgetApplication

#define ObWidgetApplication static_cast<OBCWidgetApplication *>(qApp)
