/*
 * Copyright (C) 2015 ~ 2017 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DBUTTONGRID_H
#define DBUTTONGRID_H

#include <QTableWidget>
#include <QPushButton>
#include <QResizeEvent>

#include "dtkwidget_global.h"
#include "dconstants.h"
#include "dimagebutton.h"

class QButtonGroup;
class QLabel;


DWIDGET_BEGIN_NAMESPACE


class ImageButton: public QPushButton
{
    Q_OBJECT
public:
    ImageButton(const QString& icon, const QString text, bool isNameVisible=true, QWidget *parent = 0);
    ~ImageButton();
    void initUI();
    void initConnect();
    QString getId();
    void updateChildWidgets();
    bool isDeletable();


public Q_SLOTS:
    void setId(QString id);
    void handleChecked(bool checked);
    void handleHover(bool hovered);

    void showCloseButton();
    void hideCloseButton();

    void setDeletable(bool flag);
    void handleClose();

Q_SIGNALS:
    void mouseEnter();
    void mouseLeave();
    void closed(QString url);

protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
    void resizeEvent(QResizeEvent* event);

private:
    QString m_icon;
    QString m_text;
    QString m_id;
    bool m_isNameVisible;
    QLabel* m_iconLabel = NULL;
    QLabel* m_textLabel = NULL;
    DImageButton* m_cloesButton;
    bool m_isDeletable = false;
};

class ItemButton: public QPushButton
{
    Q_OBJECT
public:
    ItemButton(QString text, QWidget *parent=0);
    ~ItemButton();
Q_SIGNALS:
    void mouseEntered(QString buttonId);
    void mouseLeaved(QString buttonId);
    void mouseEntered(int index);
    void mouseLeaved(int index);
protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
private:
    QString m_text;
};
class LIBDTKWIDGETSHARED_EXPORT DButtonGrid : public QTableWidget
{
    Q_OBJECT
public:
    explicit DButtonGrid(QWidget *parent = 0);
    explicit DButtonGrid(int rows, int columns, QWidget *parent = 0);
    ~DButtonGrid();

    void init();
    void initConnect();
    void setItemUnChecked();
    void setItemSize(int width, int height);
    int getCurrentCheckedIndex() const;

public Q_SLOTS:
    void addButton(const QString& label, int index);
    void addButtons(const QStringList& listLabels);
    void addImageButton(const QMap<QString, QString>& imageInfo, int index, bool isNameVisible=true);
    void addImageButtons(const QList<QMap<QString, QString>>& imageInfos, bool isNameVisible=true);
    void addButtonWidget(QPushButton* button, int index);
    void checkButtonByIndex(int index);
    void checkButtonByText(const QString& label);
    void clear();
    void handleClosed(QString url);

private Q_SLOTS:
    void setButtonChecked(int id);
    int getButtonEnteredIndex(QString text);
    int getButtonLeavedIndex(QString text);
Q_SIGNALS:
    void buttonChecked(QString label);
    void buttonCheckedIndexChanged(int index);

    void buttonEnteredIndexChanged(int index);
    void buttonLeavedIndexChanged(int index);

    void buttonMouseEntered(QString label);
    void buttonMouseLeaved(QString label);

    void requestRefreshed(QString url);

private:
    QButtonGroup* m_buttonGroup = NULL;
    QStringList m_buttonLabels;
    QList<QMap<QString, QString>> m_imageButtonInfos;
    int m_rowHeight = 40;
    int m_columnWidth = 100;
    int m_currentCheckedIndex = -1;

    void clearData();
};

DWIDGET_END_NAMESPACE

#endif // DBUTTONGRID_H