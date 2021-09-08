/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     zhengxiaokang <zhengxiaokang@uniontech.com>
   *
   * Maintainer: zhengxiaokang <zhengxiaokang@uniontech.com>
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
#ifndef BUTTONREST_H
#define BUTTONREST_H

#include <DWidget>

DWIDGET_USE_NAMESPACE

class Buttonrest : public DWidget
{
    Q_OBJECT
public:
    explicit Buttonrest(QWidget *parent = nullptr);
    ~Buttonrest() override;

    void setResult(bool result);

signals:
    void signalButtonRestClicked();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap currentPixmap; //当前图片
    QPixmap winRestNormal; //休息一下正常状态-赢
    QPixmap winRestHover; //休息一下hover状态-赢
    QPixmap winRestPress; //休息一下press状态-赢
    QPixmap failRestNormal; //休息一下正常状态-输
    QPixmap failRestHover; //休息一下hover状态-输
    QPixmap failRestPress; //休息一下press状态-输
    bool mResult; //对局结果,包含赢和输两种情况
    bool buttonPressed = false; //按钮按下标识
};

#endif // BUTTONREST_H
