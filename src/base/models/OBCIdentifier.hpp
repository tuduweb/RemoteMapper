#pragma once

#include "3rdparty/QJsonStruct/QJsonStruct.hpp"

#include <QHash>
#include <QHashFunctions>
#include <QString>
#include <QtCore>

namespace OBC::base{

    template<typename T>
    class IDType
    {
      public:
        explicit IDType() : m_id("null"){};
        explicit IDType(const QString &id) : m_id(id){};
        friend bool operator==(const IDType<T> &lhs, const IDType<T> &rhs)
        {
            return lhs.m_id == rhs.m_id;
        }
        friend bool operator!=(const IDType<T> &lhs, const IDType<T> &rhs)
        {
            return lhs.m_id != rhs.m_id;
        }
        const QString toString() const
        {
            return m_id;
        }
        void loadJson(const QJsonValue &d)
        {
            m_id = d.toString("null");
        }
        QJsonValue toJson() const
        {
            return m_id;
        }

      private:
        QString m_id;
    };


    #define DECL_IDTYPE(type)                                                                                                                            \
    class __##type;                                                                                                                                  \
    typedef IDType<__##type> type

    DECL_IDTYPE(GroupId);
    DECL_IDTYPE(ConnectionId);
    DECL_IDTYPE(GroupRoutingId);

    inline const static ConnectionId NullConnectionId;
    inline const static GroupId NullGroupId;
    inline const static GroupRoutingId NullRoutingId;

    //new things
    DECL_IDTYPE(BundleId);
    inline const static BundleId NullBundleId;

    DECL_IDTYPE(StreamId);
    inline const static StreamId NullStreamId;

    DECL_IDTYPE(CommId);
    inline const static CommId NullCommId;

    using namespace std::chrono;
    struct __OBCConfigObjectBase
    {
        QString displayName;
        qint64 creationDate = system_clock::to_time_t(system_clock::now());
        qint64 lastUpdatedDate = system_clock::to_time_t(system_clock::now());
        JSONSTRUCT_REGISTER(__OBCConfigObjectBase, F(displayName, creationDate, lastUpdatedDate))
    };

    struct BundleObject : __OBCConfigObjectBase
    {
        bool isSubscription = false;
        QList<ConnectionId> connections;
        GroupRoutingId routeConfigId;
        //SubscriptionConfigObject subscriptionOption;
        BundleObject() : __OBCConfigObjectBase(){};
        JSONSTRUCT_COMPARE(BundleObject, isSubscription, connections, routeConfigId)
        JSONSTRUCT_REGISTER(BundleObject, F(connections, isSubscription, routeConfigId), B(__OBCConfigObjectBase))
    };

    struct CommObject : __OBCConfigObjectBase
    {
        QString type = "none";
        int __obLinkRefCount = 0;

        // bool isSubscription = false;
        // QList<ConnectionId> connections;
        // GroupRoutingId routeConfigId;

        QJsonObject settings;

        //SubscriptionConfigObject subscriptionOption;
        CommObject() : __OBCConfigObjectBase(){};
        JSONSTRUCT_COMPARE(CommObject, type, settings)
        JSONSTRUCT_REGISTER(CommObject, F(type, settings), B(__OBCConfigObjectBase))
    };

    template<typename T>
    inline uint qHash(IDType<T> key)
    {
        return ::qHash(key.toString());
    }
    // inline uint qHash(const OBC::base::ConnectionGroupPair &pair)
    // {
    //     return ::qHash(pair.connectionId.toString() + pair.groupId.toString());
    // }

};

using namespace OBC::base;

Q_DECLARE_METATYPE(BundleId)
Q_DECLARE_METATYPE(BundleObject)

Q_DECLARE_METATYPE(CommId)

