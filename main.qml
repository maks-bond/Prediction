import QtQuick 1.0

Rectangle {
    width: 300
    height: 300
    anchors.fill: parent

    //Кнопка
    Rectangle {
        id: button //Имя кнопки

        //Размещаем в центре
        x: parent.width / 2 - button.width / 2;
        y: parent.height / 2 - button.height / 2;

        //Размеры кнопки
        width: 100
        height: 30

        //Цвет кнопки
        color: "gray"

        //Текст кнопки
        Text {
            id: buttonLabel
            text: "Пуск"
            anchors.centerIn: parent;
        }

        //Действие мыши
        MouseArea {
            anchors.fill: parent
            id: mouseArea
            //При нажатии вызвать фугкцию window.FunctionC()
            onClicked: window.FunctionC()
        }
    }

    //Строка ввода
        Rectangle {
            id: textinputRect //Имя строки ввода

            //Размещаем ниже
            x: parent.width / 2 - button.width / 2;
            y: parent.height / 2 - button.height / 2+40;

            //Размеры строки ввода
            width: 100
            height: 18

            //цвет строки ввода
            color: "gray"

            TextInput {
                id: textinput
                objectName: "textinput"
                color: "#151515";
                selectionColor: "blue"
                font.pixelSize: 12;
                width: parent.width-4
                anchors.centerIn: parent
                focus: true
                text:"1"
                }
        }

        //Поле вывода
        Rectangle {
            id: memoRect //Имя поля вывода

            //Размещаем ниже
            x: parent.width / 2 - button.width / 2;
            y: parent.height / 2 - button.height / 2+70;

            //Размеры поле вывода
            width: 100
            height: 35

            //Цвет поля вывода
            color: "gray"

            TextEdit{
                id: memo
                objectName: "memo"
                wrapMode: TextEdit.Wrap
                width:parent.width;
                readOnly:true
            }
        }
}
