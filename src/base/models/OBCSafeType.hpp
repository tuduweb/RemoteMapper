#pragma once

#include "3rdparty/QJsonStruct/QJsonStruct.hpp"

#include <QJsonObject>
#include <QJsonArray>

template<typename placeholder, typename BASETYPE_T>
class SAFETYPE_IMPL : public BASETYPE_T
{
  public:
    template<class... Args>
    explicit SAFETYPE_IMPL(Args... args) : BASETYPE_T(args...){};
    const BASETYPE_T &raw() const
    {
        return *this;
    }
};

#define SAFE_TYPEDEF(BASE, CLASS)                                                                                                                    \
    class __##CLASS##__;                                                                                                                             \
    typedef SAFETYPE_IMPL<__##CLASS##__, BASE> CLASS;

namespace OBC::base::safetype
{
    // To prevent anonying QJsonObject misuse
    SAFE_TYPEDEF(QJsonObject, INBOUNDSETTING);

    SAFE_TYPEDEF(QJsonArray, OUTBOUNDS);

    //data struct
    template<typename T1, typename T2 = T1>
    struct ObPair
    {
        T1 value1;
        T2 value2;
        friend bool operator==(const ObPair<T1, T2> &one, const ObPair<T1, T2> &another)
        {
            return another.value1 == one.value1 && another.value2 == one.value2;
        }
        JSONSTRUCT_REGISTER(___obcpair_t, F(value1, value2)) private : typedef ObPair<T1, T2> ___obcpair_t;
    };

    template<typename enumKey, typename TValue, typename = typename std::enable_if_t<std::is_enum_v<enumKey>>>
    struct ObEnumMap : QMap<enumKey, TValue>
    {
        // WARN: Changing this will break all existing JSON.
        static constexpr auto ENUM_JSON_KEY_PREFIX = "$";
        void loadJson(const QJsonValue &json_object)
        {
            QMap<QString, TValue> data;
            JsonStructHelper::Deserialize(data, json_object);
            this->clear();
            for (QString k_str : data.keys())
            {
                auto k = (enumKey) k_str.remove(ENUM_JSON_KEY_PREFIX).toInt();
                this->insert(k, data[ENUM_JSON_KEY_PREFIX + k_str]);
            }
        }
        [[nodiscard]] static auto fromJson(const QJsonValue &json)
        {
            ObEnumMap t;
            t.loadJson(json);
            return t;
        }
        [[nodiscard]] const QJsonObject toJson() const
        {
            QMap<QString, TValue> data;
            for (const auto &k : this->keys())
            {
                data[ENUM_JSON_KEY_PREFIX + QString::number(k)] = this->value(k);
            }
            return JsonStructHelper::Serialize(data).toObject();
        }
    };

};
