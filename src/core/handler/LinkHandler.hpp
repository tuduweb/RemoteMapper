#pragma once

#include <QObject>

namespace OBC::core::handler
{
    
    class LinkHandler : public QObject
    {
        Q_OBJECT
    
    public:
        LinkHandler(QObject* parent = nullptr) {}
        ~LinkHandler() {}
    };

};