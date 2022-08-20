#pragma once

#define OBC_PLUGIN_INTERFACE_VERSION 1
#include "PluginBase.hpp"

#include <QJsonObject>

namespace OBC::Plugin
{

    class PluginKernelInterface;
    class PluginGUIInterface;
    class ObInterface;

    /**
     * @name 插件核心
     * @brief 所有类型的插件放到这里 并遵循这个规范? 然后在插件系统里面就能统一识别这些插件了
     * 需要抽象出来常用插件的类型 比如系统中需要核心插件，界面插件等
     * 
     * 还比如配置信息等是通用的
     * 
     */
    class ObInterface
    {
    public:
        //当前版本
        const int ObPluginInterfaceVersion = OBC_PLUGIN_INTERFACE_VERSION;
        virtual ~ObInterface() = default;
        //virtual const QvPluginMetadata GetMetadata() const = 0;
        virtual bool InitializePlugin(const QString &, const QJsonObject &) = 0;
    
        virtual std::shared_ptr<PluginKernelInterface> GetKernel() const final
        {
            return kernelInterface;
        }

        virtual PluginGUIInterface *GetGUIInterface() const final
        {
            return guiInterface;
        }

        virtual const QJsonObject GetSettngs() const final
        {
            return settings;
        }

    protected:
        explicit ObInterface() {};
        QJsonObject settings;
        std::shared_ptr<PluginKernelInterface> kernelInterface;
        PluginGUIInterface* guiInterface;
    
    };
};


#define DECLARE_PLUGIN_INSTANCE(CLASS) inline CLASS *CLASS##Instance

QT_BEGIN_NAMESPACE
#define ObInterface_IID "com.github.tuduweb.ObPluginInterface"
//This macro associates the given Identifier (a string literal) to the interface class called ClassName. The Identifier must be unique.
Q_DECLARE_INTERFACE(OBC::Plugin::ObInterface, ObInterface_IID)
QT_END_NAMESPACE