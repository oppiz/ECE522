

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QDate, QDateTime, QTime
from datetime import datetime, timedelta
from time import gmtime, strftime

from numpy import arange, sin, pi
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas, NavigationToolbar2QT as NavigationToolbar
import matplotlib.pyplot as plt
import sqlite3 
import os

from matplotlib.figure import Figure

UseNow = True

class Ui_Form(object):
    def setupUi(self, Form):

        Graphs = ["", "Temperature", "Humidity", "Garage Lights", "Path Lights", "HVAC Fan", "HVAC Heat", \
                  "HVAC Heat Pump", "HVAC Reverse", "Vent"]

        Graph_Colors= ["Black", "Blue", "Red", "Cyan", "Yellow"]

        Form.setObjectName("Form")
        Form.setWindowTitle("GraphIt")
        Form.resize(800,440)

        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(Form.sizePolicy().hasHeightForWidth())
        Form.setSizePolicy(sizePolicy)

        self.widget = QtWidgets.QWidget(Form)
        self.widget.setGeometry(QtCore.QRect(50, 340, 687, 89))
        self.widget.setObjectName("widget")

        self.gridLayout = QtWidgets.QGridLayout(self.widget)    
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setHorizontalSpacing(15)
        self.gridLayout.setObjectName("gridLayout")

        self.graphicsView = QtWidgets.QWidget(Form)
        self.graphicsView.setGeometry(QtCore.QRect(5, 11, 791, 341))
        self.graphicsView.setObjectName("graphicsView")


        #figure = Figure()
        #figure = plt.figure()
        self.figure = plt.figure()
        #figure.autofmt_xdate()
        #self.axis = figure.gca()
        self.axis = self.figure.gca()
        self.axis2 = self.axis.twinx()
        self.axis3 = self.axis.twinx()
        self.axis4 = self.axis.twinx()
        
        self.axis.set_title("Plot")
        #self.canvas = FigureCanvas(figure)
        self.canvas = FigureCanvas(self.figure)
        
        self.canvas.setGeometry(0, 0, 800, 440)
        self.mpl_toolbar = NavigationToolbar(self.canvas, self.graphicsView) #toolbar
        self.canvas.mpl_connect('key_press_event', self.on_key_press) #toolbar
        lay = QtWidgets.QVBoxLayout(self.graphicsView)
        lay.addWidget(self.canvas)
        lay.addWidget(self.mpl_toolbar) #toolbar

        self.UseCurrentTime = QtWidgets.QRadioButton("Current Time", Form)
        self.gridLayout.addWidget(self.UseCurrentTime, 0, 7, 1, 2)
        #self.UseCurrentTime.setGeometry(QtCore.QRect(550, 390, 82, 17))
        self.UseCurrentTime.setObjectName("UseCurrentTime")
        self.UseCurrentTime.setChecked(True)
        self.UseCurrentTime.toggled.connect(self.UseCurrentTimeButton)


        self.StartTime = QtWidgets.QDateTimeEdit(self.widget)
        self.StartTime.setCalendarPopup(True)
        self.StartTime.setObjectName("StartTime")
        self.gridLayout.addWidget(self.StartTime, 0, 0, 1, 3)
        self.StartTime.setDate(QDate(datetime.now()-timedelta(days=7)))
        self.StartTime.setTime(QTime.currentTime())
        
        print(self.StartTime.dateTime().toString("dd.MM.yyyy hh:mm:ss.zzz"))
        

        self.EndTime = QtWidgets.QDateTimeEdit(self.widget)
        #self.EndTime = QtWidgets.QDateTimeEdit(self, QDateTime())
        #print (QDate(datetime.now()-timedelta(days=7)))
        self.EndTime.setCalendarPopup(True)
        self.EndTime.setCurrentSectionIndex(0)
        self.EndTime.setObjectName("EndTime")
        self.gridLayout.addWidget(self.EndTime, 0, 3, 1, 4)
        self.EndTime.setDate(QDate.currentDate())
        self.EndTime.setTime(QTime.currentTime())
        self.EndTime.setEnabled(False)
        
        

        #Graph1_Label
        self.Graph1_Label = QtWidgets.QLabel("Graph 1", self.widget)
        self.Graph1_Label.setAlignment(QtCore.Qt.AlignCenter)
        self.Graph1_Label.setObjectName("Graph1_Label")
        self.gridLayout.addWidget(self.Graph1_Label, 1, 0, 1, 1)

        #Graph1_Select
        self.Graph1_Select = QtWidgets.QComboBox(self.widget)
        self.Graph1_Select.setObjectName("Graph1_Select")
        self.Graph1_Select.addItems(Graphs)
        self.gridLayout.addWidget(self.Graph1_Select, 1, 1, 2, 1) 
        self.Graph1_Select.currentIndexChanged[str].connect(self.onActivated) 

        #Graph1_Color
        self.Graph1_Color = QtWidgets.QComboBox(self.widget)
        self.Graph1_Color.setObjectName("Graph1_Color")
        self.Graph1_Color.addItems(Graph_Colors)
        self.gridLayout.addWidget(self.Graph1_Color, 1, 2, 2, 2)
        self.Graph1_Color.currentIndexChanged[str].connect(self.onActivated)

        #Graph2_Label
        self.Graph_Label2 = QtWidgets.QLabel("Graph 2", self.widget)
        self.Graph_Label2.setAlignment(QtCore.Qt.AlignCenter)
        self.Graph_Label2.setObjectName("Graph_Label2")
        self.gridLayout.addWidget(self.Graph_Label2, 3, 0, 2, 1)

        #Graph2_Select
        self.Graph2_Select = QtWidgets.QComboBox(self.widget)
        self.Graph2_Select.setObjectName("Graph2_Select")
        self.Graph2_Select.addItems(Graphs)
        self.gridLayout.addWidget(self.Graph2_Select, 3, 1, 2, 1)
        self.Graph2_Select.currentIndexChanged[str].connect(self.onActivated)

        #Graph2_Color
        self.Graph2_Color = QtWidgets.QComboBox(self.widget)
        self.Graph2_Color.setObjectName("Graph2_Color")
        self.Graph2_Color.addItems(Graph_Colors)
        self.gridLayout.addWidget(self.Graph2_Color, 3, 2, 2, 2)
        self.Graph2_Color.currentIndexChanged[str].connect(self.onActivated)

        #Graph3_Label
        self.Graph3_Label = QtWidgets.QLabel("Graph 3", self.widget)
        self.Graph3_Label.setAlignment(QtCore.Qt.AlignCenter)
        self.Graph3_Label.setObjectName("Graph3_Label")
        self.gridLayout.addWidget(self.Graph3_Label, 2, 5, 2, 1)

        #Graph3_Select
        self.Graph3_Select = QtWidgets.QComboBox(self.widget)
        self.Graph3_Select.setObjectName("Graph3_Select")
        self.Graph3_Select.addItems(Graphs)
        self.gridLayout.addWidget(self.Graph3_Select, 1, 6, 3, 2)
        self.Graph3_Select.currentIndexChanged[str].connect(self.onActivated)

        #Graph3_Color
        self.Graph3_Color = QtWidgets.QComboBox(self.widget)
        self.Graph3_Color.setObjectName("Graph3_Color")
        self.Graph3_Color.addItems(Graph_Colors)
        self.gridLayout.addWidget(self.Graph3_Color, 1, 8, 3, 1)
        self.Graph3_Color.currentIndexChanged[str].connect(self.onActivated)

        #Graph4_Label
        self.Graph4_Label = QtWidgets.QLabel("Graph 4", self.widget)
        self.Graph4_Label.setAlignment(QtCore.Qt.AlignCenter)
        self.Graph4_Label.setObjectName("Graph4_Label")
        self.gridLayout.addWidget(self.Graph4_Label, 4, 5, 1, 1)

        #Graph4_Select
        self.Graph4_Select = QtWidgets.QComboBox(self.widget)
        self.Graph4_Select.setObjectName("Graph4_Select")
        self.Graph4_Select.addItems(Graphs)
        self.gridLayout.addWidget(self.Graph4_Select, 4, 6, 1, 2)
        self.Graph4_Select.currentIndexChanged[str].connect(self.onActivated)

        #Graph4_Color
        self.Graph4_Color = QtWidgets.QComboBox(self.widget)
        self.Graph4_Color.setObjectName("Graph4_Color")
        self.Graph4_Color.addItems(Graph_Colors)
        self.gridLayout.addWidget(self.Graph4_Color, 4, 8, 1, 1)
        self.Graph4_Color.currentIndexChanged[str].connect(self.onActivated)

        self.Close = QtWidgets.QPushButton("Close", self.widget)
        self.Close.setObjectName("Close")
        self.gridLayout.addWidget(self.Close, 4, 9, 1, 1)
        self.Close.clicked.connect(self.closeIt)
        
            
        #self.Integrate = QtWidgets.QPushButton("Integrate", self.widget)
        #self.Integrate.setObjectName("Integrate")
        #self.gridLayout.addWidget(self.Integrate, 2, 4, 3, 1)

        QtCore.QMetaObject.connectSlotsByName(Form)


    def onActivated(self, text):

        
        
        self.axis.clear()
                
            
        con = sqlite3.connect("/home/pi/ECE522/test.db", detect_types=sqlite3.PARSE_DECLTYPES)
        with con:
            cur = con.cursor()

            SqGetString = "SELECT timestamp"
          
            if self.Graph1_Select.currentText():
                SqGetString = SqGetString + self.GraphtoSqlName(self.Graph1_Select.currentText())
          
            if self.Graph2_Select.currentText():
                SqGetString = SqGetString + self.GraphtoSqlName(self.Graph2_Select.currentText())

            if self.Graph3_Select.currentText():
                SqGetString = SqGetString + self.GraphtoSqlName(self.Graph3_Select.currentText())

            if self.Graph4_Select.currentText():
                SqGetString = SqGetString + self.GraphtoSqlName(self.Graph4_Select.currentText())

            ST = self.StartTime.dateTime().toString("yyyy-MM-dd hh:mm:ss")
            #Check and use current time or selected time
            if UseNow:
              ET = strftime("%Y-%m-%d %H:%M:%S", gmtime())
            else:
              ET = self.EndTime.dateTime().toString("yyyy-MM-dd hh:mm:ss")
            
            print(ET)
            SqGetString = SqGetString + " FROM PLCValues where timestamp BETWEEN '" + ST + "' AND '" + ET + "'"
            print(SqGetString)
          
            cur.execute(SqGetString)
            print("execute")
            data = cur.fetchall()
            print("fetchall")
            count = 1

            self.axis.clear()
            self.axis2.clear()
            self.axis3.clear()
            self.axis4.clear()
            
            if self.Graph1_Select.currentText():
                #self.PlotIt(data, count, self.GraphColor(self.Graph1_Color.currentText()))
                PlotInfo = self.PlotIt(data, count)
                #self.axis.clear()
                self.axis.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph1_Color.currentText()))
                count += 1
                
            if self.Graph2_Select.currentText():
                #self.PlotIt(data, count, self.GraphColor(self.Graph2_Color.currentText()))
                PlotInfo = self.PlotIt(data, count)
                if count == 1:
                    #self.axis.clear()
                    self.axis.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph2_Color.currentText()))
                else:
                    #self.axis2 = self.axis.twinx()
                    #self.axis2.clear()
                    self.axis2.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph2_Color.currentText()))
                count += 1                

            if self.Graph3_Select.currentText():
                #self.PlotIt(data, count, self.GraphColor(self.Graph3_Color.currentText()))
                PlotInfo = self.PlotIt(data, count)
                #self.axis.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph3_Color.currentText()))
                if count == 1:
                    #self.axis.clear()
                    self.axis.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph3_Color.currentText()))
                elif count == 2:
                    #self.axis2 = self.axis.twinx()
                    #self.axis2.clear()
                    self.axis2.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph3_Color.currentText()))
                else:
                    #self.axis2 = self.axis.twinx()
                    #self.axis3.clear()
                    self.axis3.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph3_Color.currentText()))
                count += 1 
 

            if self.Graph4_Select.currentText():          
                #self.PlotIt(data, count, self.GraphColor(self.Graph4_Color.currentText()))
                PlotInfo = self.PlotIt(data, count)
                #self.axis.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph4_Color.currentText()))
                if count == 1:
                    #self.axis.clear()
                    self.axis.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph4_Color.currentText()))
                elif count == 2:
                    #self.axis2.clear()
                    self.axis2.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph4_Color.currentText()))
                elif count == 3:
                    #self.axis3.clear()
                    self.axis3.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph4_Color.currentText()))
                else:
                    #self.axis4.clear()
                    self.axis4.plot(PlotInfo[0], PlotInfo[1], self.GraphColor(self.Graph4_Color.currentText()))
                

            self.figure.autofmt_xdate()
            self.canvas.draw()
            
        
        cur.close()
        con.close()

    #Parse data from database dendeding on which row it would be. use count to step through the rows
    #def PlotIt(self,data , count, color):
    def PlotIt(self, data , count):
        dates = []
        info = []
        for row in data:
            dates.append(row[0])
            info.append(row[count])
            #print(*data , sep = "\n")
        print("Done with data")
        return[dates, info]
        #if count == 1:
        #    self.axis.plot(dates, info, color)
        #else:
        #    self.nextaxis = self.axis.twinx() #create second plot
        #    self.nextaxis.plot(dates, info, color) #plot it
        #    self.axis.plot(dates, info, color)
        #   self.axis = self.nextaxis #make new normal plot the combined plot

    def GraphtoSqlName(self, Combo):
        if Combo == "Temperature":
          return ", df1"
        if Combo == "Humidity":
          return ", df2"
        if Combo == "Garage Lights":
          return ", y001"
        if Combo == "Path Lights":
          return ", y002"
        if Combo == "HVAC Fan":
          return ", x201"
        if Combo == "HVAC Heat":
          return ", x202"
        if Combo == "HVAC Heat Pump":
          return ", x203"
        if Combo == "HVAC Reverse":
          return ", x204"
        if Combo == "Vent":
          return ", y005"

    def GraphColor(self, Combo):
        if Combo == "Black":
          return "k-"
        if Combo == "Blue":
          return "b-"
        if Combo == "Red":
          return "r-"
        if Combo == "Cyan":
          return "c-"
        if Combo == "Yellow":
          return "y-"

        return "k-"
      

    def UseCurrentTimeButton(self, enabled):

        if enabled:
            print("enabled")
            self.EndTime.setEnabled(False)
            UseNow = True
            print("Use Now time")
        else:
            print("disabled")
            self.EndTime.setEnabled(True)
            self.EndTime.setDate(QDate.currentDate())
            self.EndTime.setTime(QTime.currentTime())
            UseNow = False
            print("Use Selected Time")

    def on_key_press(self, event):
        print('you pressed', event.key)
        # implement the default mpl key press events described at
        # http://matplotlib.org/users/navigation_toolbar.html#navigation-keyboard-shortcuts
        key_press_handler(event, self.canvas, self.mpl_toolbar)

    def closeIt(self):
        self.close()
        
if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Form = QtWidgets.QWidget()
    ui = Ui_Form()
    ui.setupUi(Form)
    Form.show()
    sys.exit(app.exec_())
