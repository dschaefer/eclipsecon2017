TEMPLATE = app

QT += qml quick
CONFIG += c++11

RESOURCES += CQtDemo.qrc

qml.files = CQtDemo.qml

launch_modeall {
	CONFIG(debug, debug|release) {
	    DESTDIR = debug
	} else {
	    DESTDIR = release
	}
}

SOURCES += CQtDemo.cpp
