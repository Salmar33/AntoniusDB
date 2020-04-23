#ifndef CURRENCYDELEGATE_H
#define CURRENCYDELEGATE_H

#include <QStyledItemDelegate>
#include <QString>

class CurrencyDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    CurrencyDelegate(QObject *parent = nullptr);
    ~CurrencyDelegate();

    QString displayText(const QVariant &value, const QLocale &locale) const;
};

#endif // CURRENCYDELEGATE_H
