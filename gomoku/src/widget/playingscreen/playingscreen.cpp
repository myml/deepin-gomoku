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
#include "playingscreen.h"
#include "constants.h"

#include <QPainter>
#include <QDebug>

PlayingScreen::PlayingScreen(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , currentPlayer(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/currentplayer.svg"))
    , aiPlaying(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/ai_playing.svg"))
    , userPlaying(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/user_playing.svg"))
    , chessBlack(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/chess_black.svg"))
    , chessWhite(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/chess_white.svg"))
    , anotherPlayer(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/anotherplayer.svg"))
    , userNotPlay(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/user_notplay.svg"))
    , aiNotPlay(DHiDPIHelper::loadNxPixmap(":/resources/playingscreen/ai_notplay.svg"))
{

}

PlayingScreen::~PlayingScreen()
{

}

//棋子颜色
void PlayingScreen::setCurrentChessColor(bool AIPlaying, int chesscolor)
{
    //当时是否为AI下棋
    AIPlayer = AIPlaying;
    //转换棋子的颜色
    currentChessColro = chesscolor;
    gameOverStatus = false;
    update();
}

/**
 * @brief PlayingScreen::setGameOverStatus 设置游戏结束标志
 */
void PlayingScreen::setGameOverStatus()
{
    gameOverStatus = true;
}

QRectF PlayingScreen::boundingRect() const
{
    //对局详情所在rect大小
    return QRectF(0, 0, 300, 200);
}

void PlayingScreen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal rectWidth = this->boundingRect().width();
    qreal rectHeight = this->boundingRect().height();

    painter->setRenderHint(QPainter::Antialiasing);

    if (gamePlaying && !gameOverStatus) {
        //游戏开始后
        painter->save();
        QFont font;
        font.setPointSize(16);
        painter->setFont(font);
        painter->setPen(QColor("#ffdb9e"));
        if (AIPlayer) {
            painter->drawText(QPointF(rectWidth * chessPlayingTextPosWidth, rectHeight * chessPlayingTextPosHeight),
                              tr("I'm thinking ..."));
        } else {
            painter->drawText(QPointF(rectWidth * chessPlayingTextPosWidth, rectHeight * chessPlayingTextPosHeight),
                              tr("Place your chess piece..."));
        }
        painter->restore();

        painter->save();
        painter->setPen(Qt::NoPen);
        //当前旗手
        painter->drawPixmap(QPointF(rectWidth * currentPlayerPosWidth, rectHeight * currentPlayerPosHeight), currentPlayer);
        if (AIPlayer) {
            painter->drawPixmap(QPointF(rectWidth * aiPlayingPosWidth, rectHeight * aiPlayingPosHeight), aiPlaying);
        } else {
            painter->drawPixmap(QPointF(rectWidth * userPlayingPosWidth, rectHeight * userPlayingPosHeight), userPlaying);
        }
        if (currentChessColro == chess_black) {
            painter->drawPixmap(QPointF(rectWidth * currentPlayerChessPosWidth, rectHeight * currentPlayerchessPosHeight), chessBlack);
        } else {
            painter->drawPixmap(QPointF(rectWidth * currentPlayerChessPosWidth, rectHeight * currentPlayerchessPosHeight), chessWhite);
        }
        //另一方旗手
        painter->drawPixmap(QPointF(rectWidth * anotherPlayerPosWidth, rectHeight * anotherPlayerPosHeight), anotherPlayer);
        if (AIPlayer) {
            painter->drawPixmap(QPointF(rectWidth * userNotPlayPosWidth, rectHeight * userNotPlayPosHeight), userNotPlay);
        } else {
            painter->drawPixmap(QPointF(rectWidth * aiNotPlayPosWidth, rectHeight * aiNotPlayPosHeight), aiNotPlay);
        }
        if (currentChessColro == chess_black) {
            painter->drawPixmap(QPointF(rectWidth * anotherPlayerChessPosWidth, rectHeight * anotherPlayerChessPosHeight), chessWhite);
        } else {
            painter->drawPixmap(QPointF(rectWidth * anotherPlayerChessPosWidth, rectHeight * anotherPlayerChessPosHeight), chessBlack);
        }

        painter->restore();
    } else if (!gamePlaying) {
        //游戏还未开始
        painter->save();
        QFont welcomeFont;
        welcomeFont.setPointSize(20);
        welcomeFont.setBold(true);
        painter->setFont(welcomeFont);
        painter->setPen(QColor("#ffdb9e"));
        painter->drawText(QPointF(rectWidth * sWelcomePosWidth1, rectHeight * sWelcomePosHeight1),
                          tr("Welcome to Gomoku!"));
        painter->restore();

        painter->save();
        QFont startFont1;
        startFont1.setPointSize(16);
        startFont1.setBold(true);
        painter->setFont(startFont1);
        painter->setPen(QColor("#ffffff"));
        painter->drawText(QPointF(rectWidth * sWelcomePosWidth2, rectHeight * sWelcomePosHeight2),
                          tr("Click the start button below"));
        painter->restore();

        painter->save();
        QFont startFont2;
        startFont2.setPointSize(16);
        startFont2.setBold(true);
        painter->setFont(startFont2);
        painter->setPen(QColor("#ffffff"));
        painter->drawText(QPointF(rectWidth * sWelcomePosWidth3, rectHeight * sWelcomePosHeight3),
                          tr("to play chess~"));
        painter->restore();
    } else if (gameOverStatus) {
        painter->save();
        QFont gameOverFont;
        gameOverFont.setPointSize(20);
        gameOverFont.setBold(true);
        painter->setFont(gameOverFont);
        painter->setPen(QColor("#ffdb9e"));
        painter->drawText(QPointF(rectWidth * sWelcomePosWidth1, rectHeight * sWelcomePosHeight1),
                          tr("Game Over!"));
        painter->restore();
    }
}

//游戏是否开始
void PlayingScreen::slotStartGame()
{
    gamePlaying = true;
    update();
}
