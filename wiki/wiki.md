# Пошаговая инструкция подготовки среды для проекта
## Шаг 1
Перейдите на сайт разработчиков [Arduino](https://www.arduino.cc/en/Main/Software) и скачайте среду разработки.

![Среда разработки Arduino IDE](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_01.png)

![Среда разработки Arduino IDE](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_01_1.png)

Установите среду разработки на ваш компьютер. После завершения установки, запустите Arduino IDE.

## Шаг 2
В Arduino IDE в меню "Файл" выберите пункт "Настройки".

![Настройки среды разработки ArduinoIDE](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_02_1.png)

В открывшемся окне нажмите на кнопку справа от поля "Дополнительные ссылки для менеджера плат"

![Дополнительные ссылки для менеджера плат](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_02_2.png)

В открывшемся окне добавьте в поле ввода следующие строки:
`http://arduino.esp8266.com/stable/package_esp8266com_index.json` - для поддержки микроконтроллеров ESP8266 (NodeMCU, Wemos d1 mini)
`https://raw.githubuserconteenumnt.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` - для поддержки микроконтроллера ESP32

![Ссылка на плату ESP8266](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_02_3.png)

Примените изменения

## Шаг 3

В Arduino IDE в меню "Инструменты" выберите пункт "Менеджер плат".

![Менеджер плат](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_03_1.png)

В строке фильтра введите "ESP8266", найдите блок esp8266 by ESP8266 Commumity
Нажмите кнопку "Установка", дождитесь завершения установки.

![Менеджер плат - установка](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_03_2.png)

В строке фильтра введите "ESP32", найдите блок esp23 by Espressif System
Нажмите кнопку "Установка", дождитесь завершения установки.

![Менеджер плат - установка](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_03_3.png)

Закройте Arduino IDE

## Шаг 4

Перейдите в [репозиторий](https://github.com/vvip-68/GyverPanelWiFi) проекта
Нажмите зеленую кнопку "Clone or download" выберите "Download ZIP"

![Загрузка проекта из репозитория](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_04_1.png)

Сохраните архив на диск, распакуйте его в отдельную папку.

Для тех, кто пользуется утилитами работы с хранилищем GitHub (например, [SmartGit](https://www.syntevo.com/smartgit/download/)) - зарегистрируйте в нем ссылку на репозиторий
https://github.com/vvip-68/GyverPanelWiFi

## Шаг 5
Скопируйте содержимое папки "libraries" из папки проекта, в папку "libraries" установленной среды разработки Arduino
C:\Program Files (x86)\Arduino\libraries

![Копирование библиотек](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_05_1.png)

## Шаг 6

Запустите Arduino IDE
В меню "Инструменты" выберите пункт "Управлять библиотеками"

![Менеджер библиотек](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_06_1.png)

A строке поиска наберите "FastLED"
Выберите блок "FastLED by Daniel Garcia", нажмите кнопку "Установка".

![Менеджер библиотек](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_06_2.png)

Дождитесь завершения установки. Закройте Arduino IDE

## Шаг 7

В проводнике откройте папку с проектом, перейдите в папку "firmware" и далее в папку "GyverPanelWiFi_v1.10"

![Проводник - папка проекта](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_07_1.png)

Дважды щелкните на файле "GyverPanelWiFi_v1.10.ino"
Откроется Arduino IDE с загруженным проектом. Файлы проекта располагаются в разных вкладках. Их несколько.

![Редактор кода](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_07_2.png)

В меню "Инструменты" в пункте "Плата" в выпадающем списке выберите плату, соответствующую вашему микроконтроллеру.
В данном проекте используется плата микроконтроллера NodeMCU v1.0 или Wemos D1 pro mini.
В обоих случаях рекомендуется установить настройки как показано на рисунке.

![Параметры сборки](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_07_3.png)

Подключите плату микроконтроллера кабелем micro-USB к компьютеру.
Установите драйверы, соответствующие вашей плате (CH340G или CP2101) если они не установились автоматически при подключении контроллера.

Откройте менеджер устройств, найдите в группе "Диспетчер устройств" ветку дерева "Порты COM и LPT"

![Управление компьютером](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_07_4.png)

<a id="com-port"></a>
Найдите COM-порт, соответствующей вашей подключенной плате.

![Менеджер устройств](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_07_5.png)

Укажите данный порт в настройках - в меню "Инструменты", пункт "Порт"

## Шаг 8

Измените в скетче [параметры](https://github.com/vvip-68/GyverPanelWiFi/wiki/%D0%9D%D0%B0%D1%81%D1%82%D1%80%D0%BE%D0%B9%D0%BA%D0%B0-%D1%81%D0%BA%D0%B5%D1%82%D1%87%D0%B0-%D0%B4%D0%BB%D1%8F-%D0%B2%D0%B0%D1%88%D0%B5%D0%B3%D0%BE-%D1%83%D1%81%D1%82%D1%80%D0%BE%D0%B9%D1%81%D1%82%D0%B2%D0%B0),
соответствующие вашему проекту - высоту, ширину матрицы, угол подключения, направление ленты и другие, которые требуется изменить для вашего проекта.
Проверьте, что проект компилируется без ошибок. Для этого нажмите на кнопку "Проверить" в панели инструментов Arduino IDE.

![Проверка скетча](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_08_1.png)

Дождитесь окончания сборки проекта компилятором. Об успешном окончании сборки свидетельствуют белые буквы на черном фоне внизу окна редактора. 

Если белые буквы появились, обращать внимание на расположенные выше них оранжевые не нужно. Это диагностические сообщения библиотек. 

Если белых букв не появилось, вместо этого напечаталось сообщение об ошибке - читайте его внимательно, включая весь текст выше и устраняйте причину ошибки.

## Шаг 9

Если сборка проекта завершилась без ошибок - можно скетч загружать в микроконтроллер.
Подключите контроллер к USB кабелем micro-USB, выберите порт к которому подключена плата микроконтроллера, откройте монитор порта, нажав на кнопку в правом верхнем углу окна Arduino IDE.

При необходимости перед присоединением кабеля USB к контроллеру, подключите дополнительное питание к компонентам вашего собранного проекта. 

![Загрузка скетча](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_09_1.png)

Нажмите на кнопку "Загрузка" для загрузки скетча в микроконтроллер. Дождитесь завершения операции загрузки. 

![Загрузка скетча](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_09_2.png)

В черном поле редактора будут отображаться служебные сообщения, а так же прогресс загрузки в процентах.
После завершения операции появится надпись "Leaving... Hard resetting via RTS pin..."

Микроконтроллер автоматически перезагрузится и начнет выполнение скетча.
В мониторе порта отобразится журнал работы приложения, подтверждающий успешное завершение операции и выполнение скетча

![Загрузка скетча](https://github.com/vvip-68/GyverPanelWiFi/blob/master/wiki/Step_09_3.png)

Для завершения процесса сборки устройства установите Android-приложение и [выполните настройку](https://github.com/vvip-68/GyverPanelWiFi/wiki/%D0%9D%D0%B0%D1%81%D1%82%D1%80%D0%BE%D0%B9%D0%BA%D0%B0-%D0%BF%D0%B0%D1%80%D0%B0%D0%BC%D0%B5%D1%82%D1%80%D0%BE%D0%B2-%D0%B2-%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B8)
подключения устройства к сети и параметов режимов работы.


