#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QObject>
#include <QByteArray>
#include <QMetaObject>
#include <QHash>
#include <QDebug>
#include <QDomElement>
#include <QMetaProperty>

class CObjectFactory
{
public:
    CObjectFactory();

    template<typename T>
    static int registerClass()
    {
        return qRegisterMetaType<T>();
    }

    static QObject* createObject(const QByteArray& className, QObject* parent = NULL)
    {
        int type = QMetaType::type(className);
        if(QMetaType::UnknownType == type)
        {
            qCritical() << className << " is QMetaType::UnknownType";
            return nullptr;
        }
        QObject *obj = (QObject*)QMetaType::create(type);
        if(nullptr == obj)
        {
            qCritical() << "QMetaType::create fail: " << type;
            return nullptr;
        }
        //const QMetaObject* metaObj = QMetaType::metaObjectForType(type);
        //QObject *obj = metaObj->newInstance(Q_ARG(QObject*, parent));
        return obj;
    }

    static int LoadSettings(const QDomElement &e, QObject* pThis)
    {
        int nRet = 0;
        const QMetaObject* pObj = pThis->metaObject();
        if("class" != e.tagName())
        {
            qCritical() << pObj->className() << "::LoadSettings faile: tagName:"
                        << e.tagName() << " name:" << e.attribute("name");
            return -1;
        }
        
        QDomElement de = e.firstChildElement();
        while(!de.isNull())
        {
            QString szName = de.nodeName();
            QString szValue = de.attribute("value");
            pThis->setProperty(szName.toStdString().c_str(), szValue);
            /*int nIndex = pObj->indexOfProperty(szName.toStdString().c_str());
            QMetaProperty property = pObj->property(nIndex);
            QVariant v(szValue);
            if(!property.write(pThis, szValue))
                qCritical() << "Write propery fail: " << pObj->className() << szName;
            */
            de = de.nextSiblingElement();
        }
        return nRet;
    }
    
    static int SaveSettings(QDomElement &e, QObject* pThis)
    {
        int nRet = 0;
        const QMetaObject* pObj = pThis->metaObject();
        QDomDocument doc;

        if(e.isNull())
        {
            qCritical() << "CObjectFactory::SaveSettings e is null";
            return -1;  
        }
        
        int nAttr = pObj->propertyCount();
        for(int i = 0; i < nAttr; i++)
        {
            QMetaProperty p = pObj->property(i);
            if(!(p.isReadable() && p.isWritable()))
                continue;
            QString szName = p.name();
            QVariant value = p.read(pThis);
            //qDebug() << "propery name: " << szName << " value: " << value.toString();
            QDomElement domProperty = doc.createElement(szName);
            domProperty.setAttribute("value", value.toString());
            e.appendChild(domProperty);
        } 
        return nRet;
    }
    
};

#endif // OBJECTFACTORY_H
