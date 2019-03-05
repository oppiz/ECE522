
from PyQt5 import QtCore, QtGui, QtWidgets

from PyQt5.QtCore import QTime, QTimer
from time import strftime
import sys
import sqlite3

import subprocess

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(800, 460)
        Form.setWindowTitle("Form")

        self.timer = QTimer()
        self.timer.timeout.connect(self.showTime)
        self.timer.start(1000)

        self.timer2 = QTimer()
        self.timer2.timeout.connect(self.TempHumidUpdate)
        self.timer2.start(30000)
        
        self.Clock = QtWidgets.QLCDNumber(Form)
        self.Clock.setGeometry(QtCore.QRect(180, 20, 451, 201))
        self.Clock.setObjectName("Clock")


        self.lcdTemp = QtWidgets.QLCDNumber(Form)
        self.lcdTemp.setGeometry(QtCore.QRect(70, 250, 250, 125))
        self.lcdTemp.setObjectName("lcdTemp")

        self.lcdHumid = QtWidgets.QLCDNumber(Form)
        self.lcdHumid.setGeometry(QtCore.QRect(470, 250, 250, 125))
        self.lcdHumid.setObjectName("lcdHumid")

        

        self.Graph_It_Button = QtWidgets.QPushButton("Graph It", Form)
        self.Graph_It_Button.setGeometry(QtCore.QRect(670, 20, 100, 45))
        self.Graph_It_Button.setObjectName("Graph It")
        self.Graph_It_Button.clicked.connect(self.CallGraphIt)

        self.Close_Button = QtWidgets.QPushButton("Close", Form)
        self.Close_Button.setGeometry(QtCore.QRect(710, 440, 75, 23))
        self.Close_Button.setObjectName("Close")

        self.label = QtWidgets.QLabel("Temperature", Form)
        self.label.setGeometry(QtCore.QRect(120, 370, 131, 41))

        font = QtGui.QFont()
        font.setPointSize(14)
        self.label.setFont(font)
        self.label.setFrameShadow(QtWidgets.QFrame.Raised)
        self.label.setScaledContents(False)
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setTextInteractionFlags(QtCore.Qt.NoTextInteraction)
        self.label.setObjectName("label")

        self.label_2 = QtWidgets.QLabel("Humidity", Form)
        self.label_2.setGeometry(QtCore.QRect(550, 370, 101, 41))
        self.label_2.setFont(font)
        self.label_2.setAlignment(QtCore.Qt.AlignCenter)
        self.label_2.setTextInteractionFlags(QtCore.Qt.NoTextInteraction)
        self.label_2.setObjectName("label_2")

        QtCore.QMetaObject.connectSlotsByName(Form)

        self.TempHumidUpdate()


    def showTime(self):
        #Blink the middle? This code does that
        #time = QTime.currentTime()
        #text = time.toString('hh:mm')
        #if (time.second() % 2) == 0:
        #    text = text[:2] + ' ' + text[3:]

        #self.Clock.display(text)
        self.Clock.display(strftime("%H"+":"+"%M"))

    def TempHumidUpdate(self):
        con = sqlite3.connect("/home/pi/ECE522/test.db", detect_types=sqlite3.PARSE_DECLTYPES)
        with con:    
    
            cur = con.cursor()    
            cur.execute("SELECT df1, df2 FROM PLCValues")
            data = cur.fetchall()

            print(data[-1][1])
            self.lcdTemp.display(data[-1][0])
            self.lcdHumid.display(data[-1][1])
            
            cur.close()
        con.close()

    def CallGraphIt(self):
        subprocess.call("python3 ./FinalProduct.py", shell=True)
    
if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Form = QtWidgets.QWidget()
    ui = Ui_Form()
    ui.setupUi(Form)
    Form.show()
    sys.exit(app.exec_())

