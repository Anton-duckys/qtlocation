#ifndef QDECLARATIVEPLACE_P_H
#define QDECLARATIVEPLACE_P_H

#include <QObject>
#include <QDeclarativeListProperty>
#include <qgeoplace.h>
#include "qdeclarativegeolocation_p.h"
#include "qdeclarativebusinessinformation_p.h"
#include "qdeclarativecategory_p.h"
#include "qdeclarativesupplier_p.h"
#include "qdeclarativecontact_p.h"
#include "qdeclarativerating_p.h"
#include "qdeclarativedescription_p.h"
#include "qdeclarativereviewmodel_p.h"
#include "qdeclarativemediamodel_p.h"

QT_BEGIN_NAMESPACE

class QDeclarativePlace : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantHash additionalData READ additionalData WRITE setAdditionalData NOTIFY additionalDataChanged);
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeCategory> categories READ categories NOTIFY categoriesChanged)
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeContact> contacts READ contacts NOTIFY contactsChanged)
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeDescription> descriptions READ descriptions NOTIFY descriptionsChanged)
    Q_PROPERTY(QDeclarativeGeoLocation* location READ location WRITE setLocation NOTIFY locationChanged);
    Q_PROPERTY(QDeclarativeBusinessInformation* businessInformation READ businessInformation WRITE setBusinessInformation NOTIFY businessInformationChanged);
    Q_PROPERTY(QDeclarativeRating* rating READ rating WRITE setRating NOTIFY ratingChanged);
    Q_PROPERTY(QDeclarativeListProperty<QDeclarativeSupplier> suppliers READ suppliers NOTIFY suppliersChanged)
    Q_PROPERTY(QStringList feeds READ feeds WRITE setFeeds NOTIFY feedsChanged);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(QString placeId READ placeId WRITE setPlaceId NOTIFY placeIdChanged);
    Q_PROPERTY(QString shortDescription READ shortDescription WRITE setShortDescription NOTIFY shortDescriptionChanged);
    Q_PROPERTY(QStringList tags READ tags WRITE setTags NOTIFY tagsChanged);
    Q_PROPERTY(bool detailsFetched READ detailsFetched WRITE setDetailsFetched NOTIFY detailsFetchedChanged);
    Q_PROPERTY(QDeclarativeReviewModel *reviewModel READ reviewModel NOTIFY reviewModelChanged)
    Q_PROPERTY(QDeclarativeMediaModel *mediaModel READ mediaModel NOTIFY mediaModelChanged)

public:
    explicit QDeclarativePlace(QObject* parent = 0);
    explicit QDeclarativePlace(const QGeoPlace &src, QObject* parent = 0);
    ~QDeclarativePlace();

    QDeclarativeReviewModel *reviewModel();
    QDeclarativeMediaModel *mediaModel();

    QGeoPlace place();
    void setPlace(const QGeoPlace &src);

    QVariantHash additionalData() const;
    void setAdditionalData(const QVariantHash &data);
    QDeclarativeListProperty<QDeclarativeCategory> categories();
    static void category_append(QDeclarativeListProperty<QDeclarativeCategory> *prop,
                                  QDeclarativeCategory* value);
    static int category_count(QDeclarativeListProperty<QDeclarativeCategory> *prop);
    static QDeclarativeCategory* category_at(QDeclarativeListProperty<QDeclarativeCategory> *prop, int index);
    static void category_clear(QDeclarativeListProperty<QDeclarativeCategory> *prop);
    QDeclarativeListProperty<QDeclarativeContact> contacts();
    static void contact_append(QDeclarativeListProperty<QDeclarativeContact> *prop,
                                  QDeclarativeContact* value);
    static int contact_count(QDeclarativeListProperty<QDeclarativeContact> *prop);
    static QDeclarativeContact* contact_at(QDeclarativeListProperty<QDeclarativeContact> *prop, int index);
    static void contact_clear(QDeclarativeListProperty<QDeclarativeContact> *prop);
    QDeclarativeListProperty<QDeclarativeDescription> descriptions();
    static void descriptions_append(QDeclarativeListProperty<QDeclarativeDescription> *prop,
                                  QDeclarativeDescription* value);
    static int descriptions_count(QDeclarativeListProperty<QDeclarativeDescription> *prop);
    static QDeclarativeDescription* descriptions_at(QDeclarativeListProperty<QDeclarativeDescription> *prop, int index);
    static void descriptions_clear(QDeclarativeListProperty<QDeclarativeDescription> *prop);
    QDeclarativeGeoLocation *location();
    void setLocation(QDeclarativeGeoLocation *location);
    QDeclarativeRating *rating();
    void setRating(QDeclarativeRating *rating);
    QDeclarativeListProperty<QDeclarativeSupplier> suppliers();
    static void suppliers_append(QDeclarativeListProperty<QDeclarativeSupplier> *prop,
                                  QDeclarativeSupplier* value);
    static int suppliers_count(QDeclarativeListProperty<QDeclarativeSupplier> *prop);
    static QDeclarativeSupplier* suppliers_at(QDeclarativeListProperty<QDeclarativeSupplier> *prop, int index);
    static void suppliers_clear(QDeclarativeListProperty<QDeclarativeSupplier> *prop);
    QStringList feeds() const;
    void setFeeds(const QStringList &feeds);
    QString name() const;
    void setName(const QString &name);
    QString placeId() const;
    void setPlaceId(const QString &placeId);
    QDeclarativeBusinessInformation *businessInformation();
    void setBusinessInformation(QDeclarativeBusinessInformation *business);
    QString shortDescription() const;
    void setShortDescription(const QString &description);
    QStringList tags() const;
    void setTags(const QStringList &tags);
    bool detailsFetched() const;
    void setDetailsFetched(bool fetched);

signals:
    void additionalDataChanged();
    void categoriesChanged();
    void contactsChanged();
    void descriptionsChanged();
    void locationChanged();
    void ratingChanged();
    void suppliersChanged();
    void feedsChanged();
    void nameChanged();
    void placeIdChanged();
    void businessInformationChanged();
    void shortDescriptionChanged();
    void tagsChanged();
    void detailsFetchedChanged();
    void reviewModelChanged();
    void mediaModelChanged();

private:
    void synchronizeCategories();
    void synchronizeContacts();
    void synchronizeDescriptions();
    void synchronizeSuppliers();

private:
    QList<QDeclarativeCategory*> m_categories;
    QList<QDeclarativeContact*> m_contacts;
    QList<QDeclarativeDescription*> m_descriptions;
    QDeclarativeGeoLocation m_location;
    QDeclarativeRating m_rating;
    QList<QDeclarativeSupplier*> m_suppliers;
    QDeclarativeBusinessInformation m_businessInformation;
    QDeclarativeReviewModel *m_reviewModel;
    QDeclarativeMediaModel *m_mediaModel;

    QGeoPlace m_src;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QT_PREPEND_NAMESPACE(QDeclarativePlace));

#endif // QDECLARATIVEPLACE_P_H
