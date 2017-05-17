#!/usr/bin/python
# -*- coding: utf-8 -*-

"""**LICENSE********************************************************************
**
** Copyright © 2013, Roman Inflianskas.
** All rights reserved.
** Contact: infroma@gmail.com
**
** You may use this source code under the terms of GPLv3 license with following
** additions:
**
** "Redistribution and use only for educational purposes are permitted provided
** that the redistributions of source code must retain the above copyright
** notice, this list of conditions and the following disclaimer.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
** LIABLE FOR NOT DEFEND LABORATORY WORKS, WHICH USE METHODS FROM THIS PROGRAM,
** BAD MARKS ON CONTROL WORK AND IN STUDENT'S RECORD-BOOK."
*****************************************************************************"""

from math import *
from random import *
import os
import sys

os.chdir(sys.path[0])

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

import matplotlib.pyplot as plt

from algorithm import Approximator

os.system("pyuic5 mainwindow.ui > mainwindow.py")
import mainwindow


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = mainwindow.Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.tblPoints.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.on_spnPointCount_valueChanged(self.ui.spnPointCount.value())
        self.ui.btnGeneratePoints.setDefaultAction(self.ui.actGeneratePoints)
        self.ui.btnPlot.setDefaultAction(self.ui.actPlot)
        self.plotScene = QGraphicsScene()
        self.plotScene.setBackgroundBrush(QBrush(QColor('white')))
        self.ui.plotView.setScene(self.plotScene)

    @pyqtSlot()
    def on_actGeneratePoints_triggered(self):
        x_from = float(self.ui.edtXRangeStart.text())
        x_to = float(self.ui.edtXRangeFinish.text())
        point_count = self.ui.spnPointCount.value()
        function = self.ui.edtFunction.text()
        step = (x_to - x_from) / (point_count - 1)
        x = x_from
        for i in range(point_count):
            self.set_point(i, 0, x)
            self.set_point(i, 1, eval(function))
            x += step

    @pyqtSlot()
    def on_actPlot_triggered(self):
        xs, ys, ros = self.xs_ys_ros()
        polynomial_degree = self.ui.spnPolynomialDegree.value()
        plot_point_count = self.ui.spnPlotPointCount.value()
        approximator = Approximator(xs, ys, ros, polynomial_degree)
        approximation = approximator.linear_least_squares(plot_point_count)
        plt.clf()
        plt.grid(True)
        plt.xlabel('x')
        plt.ylabel('y')
        plt.plot(xs, ys, color='red', linestyle='', marker='.')
        plt.plot(approximation[0], approximation[1])
        plot_filename = 'plot.png'
        plt.savefig(plot_filename, dpi=128)
        self.plotScene.clear()
        pixmap = QGraphicsPixmapItem(QPixmap(plot_filename))
        self.plotScene.addItem(pixmap)
        self.plotScene.setSceneRect(self.plotScene.itemsBoundingRect())
        self.ui.plotView.centerOn(pixmap)

    def set_point(self, row, column, value):
        self.ui.tblPoints.setItem(row, column, QTableWidgetItem(str(value)))

    def point(self, row, column):
        return float(self.ui.tblPoints.item(row, column).text())

    def xs_ys_ros(self):
        xs, ys, ros = [], [], []
        for row in range(self.ui.tblPoints.rowCount()):
            xs += [self.point(row, 0)]
            ys += [self.point(row, 1)]
            ros += [self.point(row, 2)]
        return (xs, ys, ros)

    @pyqtSlot(int)
    def on_spnPointCount_valueChanged(self, count):
        old_row_count = self.ui.tblPoints.rowCount()
        self.ui.tblPoints.setRowCount(count)
        for row in range(old_row_count, count):
            for column in range(self.ui.tblPoints.columnCount()):
                self.set_point(row, column, 0 if column != 2 else 1)


app = QApplication(sys.argv)

my_mainWindow = MainWindow()
my_mainWindow.show()

sys.exit(app.exec_())
