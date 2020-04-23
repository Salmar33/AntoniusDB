#include "currencydelegate.h"

CurrencyDelegate::CurrencyDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

CurrencyDelegate::~CurrencyDelegate()
{}


QString CurrencyDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    return QString("€ ") + QString::number(value.toDouble(), 'f', 2);
}
