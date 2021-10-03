void loadSettings() {

  // Адреса в EEPROM:
  //    0 - если EEPROM_OK - EEPROM инициализировано, если другое значение - нет                             // EEPROMread(0)                 // EEPROMWrite(0, EEPROM_OK)
  //    1 - максимальная яркость ленты 1-255                                                                 // getMaxBrightness()            // putMaxBrightness(globalBrightness)
  //    2 - автосмена режима в демо: вкл/выкл                                                                // getAutoplay();                // putAutoplay(manualMode)
  //    3 - время автосмены режимов в сек                                                                    // getAutoplayTime()             // putAutoplayTime(autoplayTime / 1000L)     // autoplayTime - мс; в ячейке - в сек
  //    4 - время бездействия до переключения в авторежим в минутах                                          // getIdleTime()                 // putIdleTime(idleTime / 60L / 1000L)       // idleTime - мс; в ячейке - в мин
  //    5 - использовать синхронизацию времени через NTP                                                     // getUseNtp()                   // putUseNtp(useNtp)
  //  6,7 - период синхронизации NTP (int16_t - 2 байта) в минутах                                           // getNtpSyncTime()              // putNtpSyncTime(SYNC_TIME_PERIOD)
  //    8 - time zone UTC+X                                                                                  // getTimeZone();                // putTimeZone(timeZoneOffset)
  //    9 - выключать индикатор часов при выключении лампы true - выключать / false - не выключать           // getTurnOffClockOnLampOff()    // putTurnOffClockOnLampOff(needTurnOffClock)
  //   10 - IP[0]                                                                                            // getStaticIP()                 // putStaticIP(IP_STA[0], IP_STA[1], IP_STA[2], IP_STA[3])
  //   11 - IP[1]                                                                                            // - " -                         // - " -
  //   12 - IP[2]                                                                                            // - " -                         // - " -
  //   13 - IP[3]                                                                                            // - " -                         // - " -
  //   14 - Использовать режим точки доступа                                                                 // getUseSoftAP()                // putUseSoftAP(useSoftAP)
  //   15 - ориентация часов горизонтально / веритикально                                                    // getClockOrientation()         // putClockOrientation(CLOCK_ORIENT)
  //   16 - Отображать с часами текущую дату                                                                 // getShowDateInClock()          // putShowDateInClock(showDateInClock)
  //   17 - Кол-во секунд отображения даты                                                                   // getShowDateDuration()         // putShowDateDuration(showDateDuration)
  //   18 - Отображать дату каждые N секунд                                                                  // getShowDateInterval()         // putShowDateInterval(showDateInterval)
  //   19 - тип часов горизонтальной ориентации 0-авто 1-малые 3х5 2 - большие 5х7                           // getClockSize()                // putClockSize(CLOCK_SIZE)
  //   20 - Будильник, дни недели                                                                            // getAlarmWeekDay()             // putAlarmParams(alarmWeekDay, dawnDuration, alarmEffect, alarmDuration)
  //   21 - Будильник, продолжительность "рассвета"                                                          // getDawnDuration()             // putAlarmParams(alarmWeekDay, dawnDuration, alarmEffect, alarmDuration)
  //   22 - Будильник, эффект "рассвета"                                                                     // getAlarmEffect()              // putAlarmParams(alarmWeekDay, dawnDuration, alarmEffect, alarmDuration)
  //   23 - Будильник, использовать звук                                                                     // getUseAlarmSound()            // putAlarmSounds(useAlarmSound, maxAlarmVolume, alarmSound, dawnSound)
  //   24 - Будильник, играть звук N минут после срабатывания                                                // getAlarmDuration()            // putAlarmParams(alarmWeekDay, dawnDuration, alarmEffect, alarmDuration)
  //   25 - Будильник, Номер мелодии будильника (из папки 01 на SD карте)                                    // getAlarmSound()               // putAlarmSounds(useAlarmSound, maxAlarmVolume, alarmSound, dawnSound)
  //   26 - Будильник, Номер мелодии рассвета (из папки 02 на SD карте)                                      // getDawnSound()                // putAlarmSounds(useAlarmSound, maxAlarmVolume, alarmSound, dawnSound)
  //   27 - Будильник, Максимальная громкость будильника                                                     // getMaxAlarmVolume()           // putAlarmSounds(useAlarmSound, maxAlarmVolume, alarmSound, dawnSound)
  //   28 - Номер последнего активного спец-режима или -1, если были включены обычные эффекты                // getCurrentSpecMode()          // putCurrentSpecMode(xxx)                     
  //   29 - Номер последнего активированного вручную режима                                                  // getCurrentManualMode()        // putCurrentManualMode(xxx)
  //   30 - Отображать часы оверлеем в режимах                                                               // getClockOverlayEnabled()      // putClockOverlayEnabled(clockOverlayEnabled)
  //   31 - Использовать случайную последовательность в демо-режиме                                          // getRandomMode()               // putRandomMode(useRandomSequence)
  //   32 - Отображать с часами текущую температуру                                                          // getShowWeatherInClock()       // putShowWeatherInClock(showWeatherInClock)
  //   33 - Режим 1 по времени - часы                                                                        // getAM1hour()                  // putAM1hour(AM1_hour)
  //   34 - Режим 1 по времени - минуты                                                                      // getAM1minute()                // putAM1minute(AM1_minute) 
  //   35 - Режим 1 по времени - -3 - выкл. (не исп.); -2 - выкл. (черный экран); -1 - ночн.часы, 0 - случ., // getAM1effect()                // putAM1effect(AM1_effect_id)
  //   36 - Режим 2 по времени - часы                                      ^^^ 1,2..N - эффект EFFECT_LIST  // getAM2hour()                  // putAM2hour(AM2_hour) 
  //   37 - Режим 2 по времени - минуты                                                                      // getAM2minute()                // putAM2minute(AM2_minute)
  //   38 - Режим 2 по времени - = " = как для режима 1                                                      // getAM2effect()                // putAM2effect(AM2_effect_id)
  //   39 - Цвет ночных часов:  0 - R; 1 - G; 2 - B; 3 - C; 4 - M; 5 - Y; 6 - W;                             // getNightClockColor()          // putNightClockColor(nightClockColor)          
  //   40 - Будильник, время: понедельник : часы                                                             // getAlarmHour(1)               // putAlarmTime(1, alarmHour[0], alarmMinute[0])  // for (byte i=0; i<7; i++) alarmHour[i] = getAlarmHour(i+1)
  //   41 - Будильник, время: понедельник : минуты                                                           // getAlarmMinute(1)             // putAlarmTime(1, alarmHour[0], alarmMinute[0])  // for (byte i=0; i<7; i++) alarmMinute[i] = getAlarmMinute(i+1)
  //   42 - Будильник, время: вторник : часы                                                                 // getAlarmHour(2)               // putAlarmTime(2, alarmHour[1], alarmMinute[1])  // for (byte i=0; i<7; i++) putAlarmTime(i+1, alarmHour[i], alarmMinute[i])
  //   43 - Будильник, время: вторник : минуты                                                               // getAlarmMinute(2)             // putAlarmTime(2, alarmHour[1], alarmMinute[1])
  //   44 - Будильник, время: среда : часы                                                                   // getAlarmHour(3)               // putAlarmTime(3, alarmHour[2], alarmMinute[2])
  //   45 - Будильник, время: среда : минуты                                                                 // getAlarmMinute(3)             // putAlarmTime(3, alarmHour[2], alarmMinute[2])
  //   46 - Будильник, время: четверг : часы                                                                 // getAlarmHour(4)               // putAlarmTime(4, alarmHour[3], alarmMinute[3])
  //   47 - Будильник, время: четверг : минуты                                                               // getAlarmMinute(4)             // putAlarmTime(4, alarmHour[3], alarmMinute[3])
  //   48 - Будильник, время: пятница : часы                                                                 // getAlarmHour(5)               // putAlarmTime(5, alarmHour[4], alarmMinute[4])
  //   49 - Будильник, время: пятница : минуты                                                               // getAlarmMinute(5)             // putAlarmTime(5, alarmHour[4], alarmMinute[4])
  //   50 - Будильник, время: суббота : часы                                                                 // getAlarmHour(6)               // putAlarmTime(6, alarmHour[5], alarmMinute[5])
  //   51 - Будильник, время: суббота : минуты                                                               // getAlarmMinute(6)             // putAlarmTime(6, alarmHour[5], alarmMinute[5])
  //   52 - Будильник, время: воскресенье : часы                                                             // getAlarmHour(7)               // putAlarmTime(7, alarmHour[6], alarmMinute[6])
  //   53 - Будильник, время: воскресенье : минуты                                                           // getAlarmMinute(7)             // putAlarmTime(7, alarmHour[6], alarmMinute[6])
  //  54-63   - имя точки доступа    - 10 байт                                                               // getSoftAPName().toCharArray(apName, 10)       // putSoftAPName(String(apName))       // char apName[11] = ""
  //  64-79   - пароль точки доступа - 16 байт                                                               // getSoftAPPass().toCharArray(apPass, 17)       // putSoftAPPass(String(apPass))       // char apPass[17] = "" 
  //**80-119  - не используется
  //  120-149 - имя NTP сервера      - 30 байт                                                               // getNtpServer().toCharArray(ntpServerName, 31) // putNtpServer(String(ntpServerName)) // char ntpServerName[31] = ""
  //  150,151 - лимит по току в миллиамперах                                                                 // getPowerLimit()                // putPowerLimit(CURRENT_LIMIT)
  //  152 - globalClockColor.r -  цвет часов в режиме MC_COLOR, режим цвета "Монохром"                       // getGlobalClockColor()          // putGlobalClockColor(globalClockColor)              // uint32_t globalClockColor
  //  153 - globalClockColor.g                                                                               // - " -                          // - " -
  //  154 - globalClockColor.b                                                                               // - " -                          // - " -
  //  155 - globalTextColor.r -  цвет текста в режиме MC_TEXT, режим цвета "Монохром"                        //  getGlobalTextColor()          // putGlobalTextColor(globalTextColor)                // uint32_t globalTextColor 
  //  156 - globalTextColor.g                                                                                // - " -                          // - " -
  //  157 - globalTextColor.b                                                                                // - " -                          // - " -
  //  158 - globalColor.r     -  цвет панели в режиме "лампа"                                                // getGlobalColor()               // putGlobalColor(globalColor)                        // uint32_t globalColor
  //  159 - globalColor.g                                                                                    // - " -                          // - " -
  //  160 - globalColor.b                                                                                    // - " -                          // - " -
  //  161 - Режим 3 по времени - часы                                                                        // getAM3hour()                   // putAM3hour(AM3_hour)
  //  162 - Режим 3 по времени - минуты                                                                      // getAM3minute()                 // putAM3minute(AM3_minute) 
  //  163 - Режим 3 по времени - так же как для режима 1                                                     // getAM3effect()                 // putAM3effect(AM3_effect_id)
  //  164 - Режим 4 по времени - часы                                                                        // getAM4hour()                   // putAM4hour(AM4_hour)
  //  165 - Режим 4 по времени - минуты                                                                      // getAM4minute()                 // putAM4minute(AM4_minute)
  //  166 - Режим 4 по времени - так же как для режима 1                                                     // getAM4effect()                 // putAM4effect(AM4_effect_id)
  //  167,168 - интервал отображения текста бегущей строки                                                   // getTextInterval()              // putTextInterval(TEXT_INTERVAL)
  //  169 - Режим цвета оверлея часов X: 0,1,2,3                                                             // getClockColor()                // putClockColor(COLOR_MODE)
  //  170 - Скорость прокрутки оверлея часов                                                                 // getClockScrollSpeed()          // putClockScrollSpeed(speed_value)  
  //  171 - Режим цвета оверлея текста X: 0,1,2,3                                                            // getTextColor()                 // putTextColor(COLOR_TEXT_MODE)  
  //  172 - Скорость прокрутки оверлея текста                                                                // getTextScrollSpeed()           // putTextScrollSpeed(speed_value)  
  //  173 - Отображать бегущую строку оверлеем в режимах                                                     // getTextOverlayEnabled()        // putTextOverlayEnabled(textOverlayEnabled)
  //  174 - Использовать сервис получения погоды 0- нет, 1 - Yandex; 2 - OpenWeatherMap                      // getUseWeather()                // putUseWeather(useWeather)
  //  175 - Период запроса информации о погоде в минутах                                                     // getWeatherInterval()           // putWeatherInterval(SYNC_WEATHER_PERIOD)
  // 176,177,178,179 - Код региона Yandex для получения погоды (4 байта - uint32_t)                          // getWeatherRegion()             // putWeatherRegion(regionID)
  //  180 - цвет температуры в дневных часах: 0 - цвет часов; 1 - цвет в зависимости от теммпературы         // getUseTemperatureColor()       // putUseTemperatureColor(useTemperatureColor)
  //  181 - цвет температуры в ночных часах:  0 - цвет часов; 1 - цвет в зависимости от теммпературы         // getUseTemperatureColorNight()  // putUseTemperatureColorNight(useTemperatureColorNight)
  // 182-206 - MQTT сервер (24 симв)                                                                         // getMqttServer().toCharArray(mqtt_server, 24)  // putMqttServer(String(mqtt_server))       // char mqtt_server[25] = ""
  // 207-221 - MQTT user (14 симв)                                                                           // getMqttUser().toCharArray(mqtt_user, 14)      // putMqttUser(String(mqtt_user))           // char mqtt_user[15] = ""
  // 222-236 - MQTT pwd (14 симв)                                                                            // getMqttPass().toCharArray(mqtt_pass, 14)      // putMqttPass(String(mqtt_pass))           // char mqtt_pass[15] = ""
  // 237,238 - MQTT порт                                                                                     // getMqttPort()                  // putMqttPort(mqtt_port)
  // 239 - использовать MQTT канал управления: 0 - нет 1 - да                                                // getUseMqtt()                   // putUseMqtt(useMQTT)  
  // 240 - яркость ночных часов                                                                              // getNightClockBrightness()      // putNightClockBrightness(nightClockBrightness)
  //**241 - не используется
  //**242 - не используется
  //  243 - Режим по времени "Рассвет" - так же как для режима 1                                             // getAM5effect()                 // putAM5effect(dawn_effect_id)
  // 244,245,246,247 - Код региона OpenWeatherMap для получения погоды (4 байта - uint32_t)                  // getWeatherRegion2()            // putWeatherRegion2(regionID2)
  //  248 - Режим по времени "Закат" - так же как для режима 1                                               // getAM6effect()                 // putAM6effect(dawn_effect_id)
  //**249 - не используется
  // 250-279 - префикс топика сообщения (30 симв)                                                            // getMqttPrefix()                // putMqttPrefix(mqtt_prefix)
  // 280,281 - интервал отправки значения uptime на MQTT-сервер                                              // getUpTimeSendInterval()        // putUpTimeSendInterval(upTimeSendInterval)
  //**282 - не используется
  //  ...
  //**299 - не используется
  //  300 - 300+(Nэфф*5)   - скорость эффекта
  //  301 - 300+(Nэфф*5)+1 - эффект в авторежиме: 1 - использовать; 0 - не использовать
  //  302 - 300+(Nэфф*5)+2 - специальный параметр эффекта #1
  //  303 - 300+(Nэфф*5)+3 - специальный параметр эффекта #2
  //  304 - 300+(Nэфф*5)+4 - контраст эффекта
  //********
  //  800 - текст строк бегущей строки сплошным массивом, строки разделены символом '\r'                     // loadTexts()                    // saveTexts()
  //********

  // Сначала инициализируем имя сети/точки доступа, пароли и имя NTP-сервера значениями по умолчанию.
  // Ниже, если EEPROM уже инициализирован - из него будут загружены актуальные значения
  strcpy(apName, DEFAULT_AP_NAME);
  strcpy(apPass, DEFAULT_AP_PASS);
  strcpy(ntpServerName, DEFAULT_NTP_SERVER);    
  ssid = NETWORK_SSID;
  pass = NETWORK_PASS;

  #if (USE_MQTT == 1)
  strcpy(mqtt_server, DEFAULT_MQTT_SERVER);
  strcpy(mqtt_user,   DEFAULT_MQTT_USER);
  strcpy(mqtt_pass,   DEFAULT_MQTT_PASS);
  strcpy(mqtt_prefix, DEFAULT_MQTT_PREFIX);
  #endif

  // Инициализировано ли EEPROM
  bool isInitialized = EEPROMread(0) == EEPROM_OK;  
  
  if (isInitialized) {    
    globalBrightness = getMaxBrightness();

    autoplayTime = getAutoplayTime();
    idleTime = getIdleTime();

    useNtp = getUseNtp();
    timeZoneOffset = getTimeZone();
    clockOverlayEnabled = getClockOverlayEnabled();
    textOverlayEnabled = getTextOverlayEnabled();

    SYNC_TIME_PERIOD = getNtpSyncTime();
    manualMode = getAutoplay();
    CLOCK_ORIENT = getClockOrientation();
    COLOR_MODE = getClockColor();
    CLOCK_SIZE = getClockSize();
    COLOR_TEXT_MODE = getTextColor();
    CURRENT_LIMIT = getPowerLimit();
    TEXT_INTERVAL = getTextInterval();
    
    useRandomSequence = getRandomMode();
    nightClockColor = getNightClockColor();
    nightClockBrightness = getNightClockBrightness();
    showDateInClock = getShowDateInClock();  
    showDateDuration = getShowDateDuration();
    showDateInterval = getShowDateInterval();

    alarmWeekDay = getAlarmWeekDay();
    alarmEffect = getAlarmEffect();
    alarmDuration = getAlarmDuration();
    dawnDuration = getDawnDuration();

    needTurnOffClock = getTurnOffClockOnLampOff();

    // Загрузить недельные будильники / часы, минуты /
    for (byte i=0; i<7; i++) {
      alarmHour[i] = getAlarmHour(i+1);
      alarmMinute[i] = getAlarmMinute(i+1);
    }
 
    // Загрузить параметры эффектов #1, #2
    for (byte i=0; i<MAX_EFFECT; i++) {
      effectScaleParam[i] = getScaleForEffect(i); 
      effectScaleParam2[i] = getScaleForEffect2(i);
      effectContrast[i] = getEffectContrast(i);
    }

    #if (USE_MP3 == 1)
      useAlarmSound = getUseAlarmSound();
      alarmSound = getAlarmSound();
      dawnSound = getDawnSound();
      maxAlarmVolume = getMaxAlarmVolume();
    #endif

    globalColor = getGlobalColor();           // цвет лампы, задаваемый пользователем
    globalClockColor = getGlobalClockColor(); // цвет часов в режиме MC_COLOR, режим цвета "Монохром"
    globalTextColor = getGlobalTextColor();   // цвет часов бегущей строки в режиме цвета "Монохром"

    useSoftAP = getUseSoftAP();
    getSoftAPName().toCharArray(apName, 10);        //  54-63   - имя точки доступа    ( 9 байт макс) + 1 байт '\0'
    getSoftAPPass().toCharArray(apPass, 17);        //  64-79   - пароль точки доступа (16 байт макс) + 1 байт '\0'
    getNtpServer().toCharArray(ntpServerName, 31);  //  120-149 - имя NTP сервера      (30 байт макс) + 1 байт '\0'

    ssid = getSsid();                               //          - имя сети WiFi
    pass = getPass();                               //          - пароль сети WiFi
    
    if (strlen(apName) == 0) strcpy(apName, DEFAULT_AP_NAME);
    if (strlen(apPass) == 0) strcpy(apPass, DEFAULT_AP_PASS);
    if (strlen(ntpServerName) == 0) strcpy(ntpServerName, DEFAULT_NTP_SERVER);

    #if (USE_MQTT == 1)
    useMQTT = getUseMqtt();
    getMqttServer().toCharArray(mqtt_server, 25);   //  182-206 - mqtt сервер          (24 байт макс) + 1 байт '\0'
    getMqttUser().toCharArray(mqtt_user, 15);       //  207-221 - mqtt user            (14 байт макс) + 1 байт '\0'
    getMqttPass().toCharArray(mqtt_pass, 15);       //  222-236 - mqtt password        (14 байт макс) + 1 байт '\0'
    getMqttPrefix().toCharArray(mqtt_prefix, 31);   //  250-279 - mqtt password        (30 байт макс) + 1 байт '\0'
    if (strlen(mqtt_server) == 0) strcpy(mqtt_server, DEFAULT_MQTT_SERVER);
    if (strlen(mqtt_user)   == 0) strcpy(mqtt_user,   DEFAULT_MQTT_USER);
    if (strlen(mqtt_pass)   == 0) strcpy(mqtt_pass,   DEFAULT_MQTT_PASS);
    if (strlen(mqtt_prefix) == 0) strcpy(mqtt_prefix, DEFAULT_MQTT_PREFIX);
    mqtt_port = getMqttPort();
    upTimeSendInterval = getUpTimeSendInterval();
    #endif

    AM1_hour       = getAM1hour();
    AM1_minute     = getAM1minute();
    AM1_effect_id  = getAM1effect();
    AM2_hour       = getAM2hour();
    AM2_minute     = getAM2minute();
    AM2_effect_id  = getAM2effect();
    AM3_hour       = getAM3hour();
    AM3_minute     = getAM3minute();
    AM3_effect_id  = getAM3effect();
    AM4_hour       = getAM4hour();
    AM4_minute     = getAM4minute();
    AM4_effect_id  = getAM4effect();
    dawn_effect_id = getAM5effect();
    dusk_effect_id = getAM6effect();

  #if (USE_WEATHER == 1)     
    useWeather = getUseWeather();
    regionID = getWeatherRegion();
    regionID2 = getWeatherRegion2();
    SYNC_WEATHER_PERIOD = getWeatherInterval();
    useTemperatureColor = getUseTemperatureColor();
    useTemperatureColorNight = getUseTemperatureColorNight();
    showWeatherInClock = getShowWeatherInClock();
  #endif  

    loadTexts();
    getStaticIP();
    
  } else {

    DEBUGLN(F("Инициализация EEPROM..."));

    // Значения переменных по умолчанию определяются в месте их объявления - в файле a_def_soft.h
    // Здесь выполняются только инициализация массивов и некоторых специальных параметров
    clearEEPROM();

    for (byte i=0; i<MAX_EFFECT; i++) {
      effectScaleParam[i]  = 50;  // среднее значение для параметра. Конкретное значение зависит от эффекта
      effectScaleParam2[i] = 0;   // второй параметр эффекта по умолчанию равен 0. Конкретное значение зависит от эффекта
      effectContrast[i]    = 192; // контраст эффекта
    }

    // Значения текстовых строк по умолчанию - 
    textLines[0] = "##";
    for (byte i = 1; i<36; i++) textLines[i] = "";

    // После первой инициализации значений - сохранить их принудительно
    saveDefaults();
    saveSettings();
    
    DEBUGLN();
  }  

  #if (USE_MQTT == 1) 
  changed_keys = "";
  #endif
}

void clearEEPROM() {
  for (int addr = 1; addr < EEPROM_MAX; addr++) {
    EEPROM.write(addr, 0);
  }
}

void saveDefaults() {

  putMaxBrightness(globalBrightness);

  putAutoplayTime(autoplayTime / 1000L);
  putIdleTime(constrain(idleTime / 60L / 1000L, 0, 255));

  putUseNtp(useNtp);
  putTimeZone(timeZoneOffset);
  putClockOverlayEnabled(clockOverlayEnabled);
  putTextOverlayEnabled(textOverlayEnabled);

  putNtpSyncTime(SYNC_TIME_PERIOD);
  putAutoplay(manualMode);

  putClockOrientation(CLOCK_ORIENT);
  putPowerLimit(CURRENT_LIMIT);
  putTextInterval(TEXT_INTERVAL);
  
  putRandomMode(useRandomSequence);
  putNightClockColor(nightClockColor);  // Цвет ночных часов: 0 - R; 1 - G; 2 - B; 3 - C; 4 - M; 5 - Y;
  putNightClockBrightness(nightClockBrightness);
  putShowDateInClock(showDateInClock);
  putShowDateDuration(showDateDuration);
  putShowDateInterval(showDateInterval);
  putTurnOffClockOnLampOff(needTurnOffClock);

  putAlarmParams(alarmWeekDay,dawnDuration,alarmEffect,alarmDuration);
  #if (USE_MP3 == 1)
    putAlarmSounds(useAlarmSound, maxAlarmVolume, alarmSound, dawnSound);
  #endif

  for (byte i=0; i<7; i++) {
    putAlarmTime(i+1, alarmHour[i], alarmMinute[i]);
  }

  // Настройки по умолчанию для эффектов
  for (int i = 0; i < MAX_EFFECT; i++) {
    putEffectParams(i, effectSpeed, true, true, true, effectScaleParam[i], effectScaleParam2[i], effectContrast[i]);
  }

  // Специальные настройки отдельных эффектов
  putEffectUsage(MC_CLOCK, false);
  putClockScrollSpeed(255);  
  putEffectTextOverlayUsage(MC_CLOCK, false); 
  putEffectTextOverlayUsage(MC_MAZE, false);
  putEffectTextOverlayUsage(MC_SNAKE, false);
  putEffectTextOverlayUsage(MC_TETRIS, false);
  putEffectTextOverlayUsage(MC_ARKANOID, false);
  putEffectTextOverlayUsage(MC_WEATHER, false);
  putEffectTextOverlayUsage(MC_LIFE, false);
  putEffectClockOverlayUsage(MC_CLOCK, false);
  putEffectClockOverlayUsage(MC_MAZE, false);
  putEffectClockOverlayUsage(MC_SNAKE, false);
  putEffectClockOverlayUsage(MC_TETRIS, false);
  putEffectClockOverlayUsage(MC_ARKANOID, false);
  putEffectClockOverlayUsage(MC_WEATHER, false);
  putEffectClockOverlayUsage(MC_LIFE, false);

  #ifdef MC_IMAGE
  putEffectTextOverlayUsage(MC_IMAGE, false);
  putEffectClockOverlayUsage(MC_IMAGE, false);
  #endif

  putClockScrollSpeed(150);
  putTextScrollSpeed(186);
  
  putScaleForEffect(MC_FIRE, 0);            // Огонь красного цвета
  putScaleForEffect2(MC_PAINTBALL, 1);      // Использовать сегменты для эффекта Пэйнтбол на широких матрицах
  putScaleForEffect2(MC_SWIRL, 1);          // Использовать сегменты для эффекта Водоворот на широких матрицах
  putScaleForEffect2(MC_RAINBOW, 0);        // Использовать рандомный выбор эффекта радуга 0 - random; 1 - диагональная; 2 - горизонтальная; 3 - вертикальная; 4 - вращающаяся  

  byte ball_size = min(WIDTH,HEIGHT) / 4;
  if (ball_size > 5) ball_size = 5;
  putScaleForEffect(MC_BALL, ball_size);    // Размер кубика по умолчанию
  
  putGlobalColor(globalColor);              // Цвет панели в режиме "Лампа"
  putGlobalClockColor(globalClockColor);    // Цвет часов в режиме "Монохром" 
  putGlobalTextColor(globalTextColor);      // Цвет текста в режиме "Монохром"

  putUseSoftAP(useSoftAP);

  strcpy(apName, DEFAULT_AP_NAME);
  strcpy(apPass, DEFAULT_AP_PASS);
  ssid = NETWORK_SSID;
  pass = NETWORK_PASS;

  #if (USE_MQTT == 1)
  strcpy(mqtt_server, DEFAULT_MQTT_SERVER);
  strcpy(mqtt_user, DEFAULT_MQTT_USER);
  strcpy(mqtt_pass, DEFAULT_MQTT_PASS);
  #endif  

  putSoftAPName(String(apName));
  putSoftAPPass(String(apPass));
  putSsid(ssid);
  putPass(pass);

  #if (USE_MQTT == 1)
  putMqttServer(String(mqtt_server));
  putMqttUser(String(mqtt_user));
  putMqttPass(String(mqtt_pass));
  putMqttPrefix(String(mqtt_prefix));
  putMqttPort(mqtt_port);
  putUseMqtt(useMQTT);
  putUpTimeSendInterval(upTimeSendInterval);
  #endif

  strcpy(ntpServerName, DEFAULT_NTP_SERVER);
  putNtpServer(String(ntpServerName));

  putAM1hour(AM1_hour);                 // Режим 1 по времени - часы
  putAM1minute(AM1_minute);             // Режим 1 по времени - минуты
  putAM1effect(AM1_effect_id);          // Режим 1 по времени - действие: -3 - выключено (не используется); -2 - выключить матрицу (черный экран); -1 - огонь, 0 - случайный, 1 и далее - эффект EFFECT_LIST
  putAM2hour(AM2_hour);                 // Режим 2 по времени - часы
  putAM2minute(AM2_minute);             // Режим 2 по времени - минуты
  putAM2effect(AM2_effect_id);          // Режим 2 по времени - действие: -3 - выключено (не используется); -2 - выключить матрицу (черный экран); -1 - огонь, 0 - случайный, 1 и далее - эффект EFFECT_LIST
  putAM3hour(AM3_hour);                 // Режим 3 по времени - часы
  putAM3minute(AM3_minute);             // Режим 3 по времени - минуты
  putAM3effect(AM3_effect_id);          // Режим 3 по времени - действие: -3 - выключено (не используется); -2 - выключить матрицу (черный экран); -1 - огонь, 0 - случайный, 1 и далее - эффект EFFECT_LIST
  putAM4hour(AM4_hour);                 // Режим 4 по времени - часы
  putAM4minute(AM4_minute);             // Режим 4 по времени - минуты
  putAM4effect(AM4_effect_id);          // Режим 4 по времени - действие: -3 - выключено (не используется); -2 - выключить матрицу (черный экран); -1 - огонь, 0 - случайный, 1 и далее - эффект EFFECT_LIST
  putAM5effect(dawn_effect_id);         // Режим по времени "Рассвет" - действие: -3 - выключено (не используется); -2 - выключить матрицу (черный экран); -1 - огонь, 0 - случайный, 1 и далее - эффект EFFECT_LIST
  putAM6effect(dusk_effect_id);         // Режим по времени "Закат"   - действие: -3 - выключено (не используется); -2 - выключить матрицу (черный экран); -1 - огонь, 0 - случайный, 1 и далее - эффект EFFECT_LIST

#if (USE_WEATHER == 1)       
  putUseWeather(useWeather);
  putWeatherRegion(regionID);
  putWeatherRegion2(regionID2);
  putWeatherInterval(SYNC_WEATHER_PERIOD);
  putUseTemperatureColor(useTemperatureColor);
  putShowWeatherInClock(showWeatherInClock);
#endif
       
  putStaticIP(IP_STA[0], IP_STA[1], IP_STA[2], IP_STA[3]);
/*
  textLines[0]  = "##";
  textLines[1]  = "Всё будет хорошо!";
  textLines[2]  = "До {C#00D0FF}Нового года {C#FFFFFF}осталось {C#10FF00}{R01.01.2022#4}{E21}";
  textLines[3]  = "До {C#0019FF}Нового года{C#FFFFFF} {P01.01.****#4}";
  textLines[4]  = "-С {C#00D0FF}Новым {C#0BFF00}{D:yyyy} {C#FFFFFF}годом!{E21}";
  textLines[5]  = "В {C#10FF00}Красноярске {C#FFFFFF}{WS} {WT}°C";
  textLines[6]  = "Show must go on!{C#000002}";
  textLines[7]  = "{C#FF000F}Крибле! {C#000001}Крабле!! {C#00FF00}Бумс!!!{E24}";
  textLines[8]  = "Крепитесь, люди - скоро {C#FF0300}лето!{S01.01.****#10.04.****}";
  textLines[9]  = "Это {C#0081FF}\"ж-ж-ж\"{C#FFFFFF} - неспроста!";
  textLines[10]  = "Элементарно, Ватсон!";
  textLines[11]  = "Дело было вечером, делать было нечего...";
  textLines[12]  = "Ах, какая прелесть!";
  textLines[13]  = "Это нужно обдумать...";
  textLines[14]  = "В этом что-то есть...";
  textLines[15]  = "В {C#10FF00}Красноярске {C#FFFFFF}{WS} {WT}°C";
  textLines[16]  = "Вот оно что, {C#FF0000}Михалыч{C#FFFFFF}!..";
  textLines[17]  = "Сегодня {D:dd MMMM yyyy} года, {D:dddd}";
  textLines[18]  = "Лень - двигатель прогресса";
  textLines[19]  = "Чем бы дитя не тешилось...";
  textLines[20]  = "С Рождеством!{S07.01.****}";
  textLines[21]  = "С днем Победы!{S09.05.**** 7:00#09.05.**** 21:30}";
  textLines[22]  = "Сегодня {D:dddd dd MMMM}, на улице {WS}, {WT}°C{E25}";
  textLines[23]  = "С праздником, соседи!";
  textLines[24]  = "Не скучайте!";
  textLines[25]  = "Счастья всем! И пусть никто не уйдет обиженным.";
  textLines[26]  = "В отсутствии солнца сияйте сами!";
  textLines[27]  = "Почему? Потому!";
  textLines[28]  = "Время принимать решения!";
  textLines[29]  = "Время делать выводы!";
  textLines[30]  = "Лето, ах лето!{S15.05.****#01.09.****}";
  textLines[31]  = "Нет предела совершенству!";
  textLines[32]  = "Чего изволите, ваша светлость?";
  textLines[33]  = "Курочка по зёрнышку, копеечка к копеечке!";  
  textLines[34]  = "Подъем через {P7:30#Z#60#60#12345}!";
  textLines[35]  = "-Доброе утро!";
*/ 
  saveTexts();

  putCurrentSpecMode(-1);               // Текущий спец-режим - это не спец-режим
  putCurrentManualMode(-1);             // Текущий вручную включенный режим
}

void saveSettings() {

  saveSettingsTimer.reset();
  if (!eepromModified) return;
  
  // Поставить отметку, что EEPROM инициализировано параметрами эффектов
  EEPROMwrite(0, EEPROM_OK);
  
  EEPROM.commit();
  DEBUGLN(F("Настройки сохранены в EEPROM"));
  eepromModified = false;
}

void putEffectParams(byte effect, int speed, boolean use, boolean use_text_overlay, boolean use_clock_overlay, byte value1, byte value2, byte contrast) {
  const int addr = EFFECT_EEPROM;  
  byte value = 0;

  if (use)               value |= 0x01;
  if (use_text_overlay)  value |= 0x02;
  if (use_clock_overlay) value |= 0x04;
  
  EEPROMwrite(addr + effect*5, constrain(map(speed, D_EFFECT_SPEED_MIN, D_EFFECT_SPEED_MAX, 0, 255), 0, 255));        // Скорость эффекта  
  EEPROMwrite(addr + effect*5 + 1, value);                                                                            // b0 - Вкл/Выкл эффект в демо-режиме; b1 - Вкл/выкл оверлей текста; ; b1 - Вкл/выкл оверлей часов   
  EEPROMwrite(addr + effect*5 + 2, value1);                                                                           // Параметр эффекта #1 
  EEPROMwrite(addr + effect*5 + 3, value2);                                                                           // Параметр эффекта #2 
  EEPROMwrite(addr + effect*5 + 4, contrast);                                                                         // Контраст эффекта 
  effectScaleParam[effect] = value1;
  effectScaleParam2[effect] = value2;
  effectContrast[effect] = contrast;
}

void putEffectSpeed(byte effect, int speed) {
  if (speed != getEffectSpeed(effect)) {
    const int addr = EFFECT_EEPROM;  
    EEPROMwrite(addr + effect*5, constrain(map(speed, D_EFFECT_SPEED_MIN, D_EFFECT_SPEED_MAX, 0, 255), 0, 255));        // Скорость эффекта    
  }
}

byte getEffectSpeed(byte effect) {
  const int addr = EFFECT_EEPROM;
  return map8(EEPROMread(addr + effect*5),D_EFFECT_SPEED_MIN,D_EFFECT_SPEED_MAX);
}

boolean getEffectUsage(byte effect) {
  if (effect >= MAX_EFFECT) return false;
  const int addr = EFFECT_EEPROM;
  byte value = EEPROMread(addr + effect*5 + 1);
  return (value & 0x01) != 0;                                  // b0 - использовать эффект в демо-режиме
}

void putEffectUsage(byte effect, boolean use) {
  const int addr = EFFECT_EEPROM;
  byte value = EEPROMread(addr + effect*5 + 1);
  byte new_value = use ? (value | 0x01) : (value & ~0x01);
  if (value != new_value) {
    const int addr = EFFECT_EEPROM;  
    EEPROMwrite(addr + effect*5 + 1, new_value);               // b0 - использовать эффект в демо-режиме
  }
}

boolean getEffectTextOverlayUsage(byte effect) {
  const int addr = EFFECT_EEPROM;
  byte value = EEPROMread(addr + effect*5 + 1);
  return (value & 0x02) != 0;                                  // b1 - использовать в эффекте бегущую строку поверх эффекта
}

void putEffectTextOverlayUsage(byte effect, boolean use) {
  const int addr = EFFECT_EEPROM;
  byte value = EEPROMread(addr + effect*5 + 1);
  byte new_value = use ? (value | 0x02) : (value & ~0x02);
  if (value != new_value) {
    const int addr = EFFECT_EEPROM;  
    EEPROMwrite(addr + effect*5 + 1, new_value);               // b1 - использовать в эффекте бегущую строку поверх эффекта
  }
}

boolean getEffectClockOverlayUsage(byte effect) {
  const int addr = EFFECT_EEPROM;
  byte value = EEPROMread(addr + effect*5 + 1);
  return (value & 0x04) != 0;                                  // b2 - использовать в эффекте часы поверх эффекта
}

void putEffectClockOverlayUsage(byte effect, boolean use) {
  const int addr = EFFECT_EEPROM;
  byte value = EEPROMread(addr + effect*5 + 1);
  byte new_value = use ? (value | 0x04) : (value & ~0x04);
  if (value != new_value) {
    const int addr = EFFECT_EEPROM;  
    EEPROMwrite(addr + effect*5 + 1, new_value);               // b2 - использовать в эффекте часы поверх эффекта
  }
}

void putScaleForEffect(byte effect, byte value) {
  if (value != getScaleForEffect(effect)) {
    const int addr = EFFECT_EEPROM;
    EEPROMwrite(addr + effect*5 + 2, value);
    effectScaleParam[effect] = value;
  }  
}

byte getScaleForEffect(byte effect) {
  const int addr = EFFECT_EEPROM;
  byte value = EEPROMread(addr + effect*5 + 2);
  effectScaleParam[effect] = value;
  return value;
}

void putScaleForEffect2(byte effect, byte value) {
  if (value != getScaleForEffect2(effect)) {
    const int addr = EFFECT_EEPROM;
    EEPROMwrite(addr + effect*5 + 3, value);
    effectScaleParam2[effect] = value;
  }  
}

byte getScaleForEffect2(byte effect) {
  const int addr = EFFECT_EEPROM;
  byte value = EEPROMread(addr + effect*5 + 3);
  effectScaleParam2[effect] = value;
  return value;
}

byte getEffectContrast(byte effect) {
  const int addr = EFFECT_EEPROM;
  byte contrast = constrain(EEPROMread(addr + effect*5 + 4),10,255);
  effectContrast[effect] = contrast;
  return contrast;
}

void putEffectContrast(byte effect, byte contrast) {
  if (contrast != getEffectContrast(effect)) {
    const int addr = EFFECT_EEPROM;
    EEPROMwrite(addr + effect*5 + 4, contrast);
    effectContrast[effect] = constrain(contrast,10,255);
  }  
}

byte getMaxBrightness() {
  return EEPROMread(1);
}

void putMaxBrightness(byte brightness) {
  if (brightness != getMaxBrightness()) {
    EEPROMwrite(1, brightness);
  }
}

void putAutoplay(boolean value) {
  if (value != getAutoplay()) {
    EEPROMwrite(2, value ? 1 : 0);
  }  
}

bool getAutoplay() {
  return EEPROMread(2) == 1;
}

void putAutoplayTime(long value) {
  if (value != getAutoplayTime()) {
    EEPROMwrite(3, constrain(value / 1000L, 0, 255));
  }
}

long getAutoplayTime() {
  long time = EEPROMread(3) * 1000L;  
  if (time == 0) time = ((long)AUTOPLAY_PERIOD * 1000L);
  return time;
}

void putIdleTime(long value) {
  if (value != getIdleTime()) {
    EEPROMwrite(4, constrain(value / 60L / 1000L, 0, 255));
  }
}

uint16_t getUpTimeSendInterval() {
  return EEPROM_int_read(280);
}

void putUpTimeSendInterval(uint16_t value) {
  if (value != getUpTimeSendInterval()) {
    EEPROM_int_write(280, value);
  }
}

long getIdleTime() {
  long time = EEPROMread(4) * 60 * 1000L;  
  return time;
}

boolean getClockOverlayEnabled() {
  return (EEPROMread(30) == 1) && (allowVertical || allowHorizontal);
}

void putClockOverlayEnabled(boolean enabled) {
  if (enabled != getClockOverlayEnabled()) {
    EEPROMwrite(30, enabled ? 1 : 0);
  }
}

boolean getTextOverlayEnabled() {
  return (EEPROMread(173) == 1);
}

void putTextOverlayEnabled(boolean enabled) {
  if (enabled != getTextOverlayEnabled()) {
    EEPROMwrite(173, enabled ? 1 : 0);
  }
}

void putUseNtp(boolean value) {
  if (value != getUseNtp()) {
    EEPROMwrite(5, value);
  }
}

bool getUseNtp() {
  return EEPROMread(5) == 1;
}

void putNtpSyncTime(uint16_t value) {
  if (value != getNtpSyncTime()) {
    EEPROM_int_write(6, value);
  }
}

uint16_t getNtpSyncTime() {
  uint16_t time = EEPROM_int_read(6);  
  if (time == 0) time = 60;
  return time;
}

void putTimeZone(int8_t value) {
  if (value != getTimeZone()) {
    EEPROMwrite(8, (byte)value);
  }
}

int8_t getTimeZone() {
  return (int8_t)EEPROMread(8);
}

bool getTurnOffClockOnLampOff() {
  return EEPROMread(9) == 1;
}

void putTurnOffClockOnLampOff(bool flag) {
  if (flag != getTurnOffClockOnLampOff()) {
    EEPROMwrite(9, flag ? 1 : 0);
  }  
}

byte getClockOrientation() {  
  byte val = EEPROMread(15) == 1 ? 1 : 0;
  if (val == 0 && !allowHorizontal) val = 1;
  if (val == 1 && !allowVertical) val = 0;
  return val;
}

void putClockOrientation(byte orientation) {
  if (orientation != getClockOrientation()) {
    EEPROMwrite(15, orientation == 1 ? 1 : 0);
  }
}

bool getShowWeatherInClock() {
  bool val = EEPROMread(32) == 1;
  return val;
}

void putShowWeatherInClock(boolean use) {  
  if (use != getShowWeatherInClock()) {
    EEPROMwrite(32, use ? 1 : 0);
  }
}

bool getShowDateInClock() {
  bool val = EEPROMread(16) == 1;
  return val;
}

void putShowDateInClock(boolean use) {  
  if (use != getShowDateInClock()) {
    EEPROMwrite(16, use ? 1 : 0);
  }
}

byte getShowDateDuration() {
  return EEPROMread(17);
}

void putShowDateDuration(byte Duration) {
  if (Duration != getShowDateDuration()) {
    EEPROMwrite(17, Duration);
  }
}

byte getShowDateInterval() {
  return EEPROMread(18);
}

void putShowDateInterval(byte Interval) {
  if (Interval != getShowDateInterval()) {
    EEPROMwrite(18, Interval);
  }
}

byte getClockSize() {
  return EEPROMread(19);
}

void putClockSize(byte c_size) {
  if (c_size != getClockSize()) {
    EEPROMwrite(19, c_size);
  }
}

void putAlarmParams(byte alarmWeekDay, byte dawnDuration, byte alarmEffect, byte alarmDuration) {  
  if (alarmWeekDay != getAlarmWeekDay()) {
    EEPROMwrite(20, alarmWeekDay);
  }
  if (dawnDuration != getDawnDuration()) {
    EEPROMwrite(21, dawnDuration);
  }
  if (alarmEffect != getAlarmEffect()) {
    EEPROMwrite(22, alarmEffect);
  }
  //   24 - Будильник, длительность звука будильника, минут
  if (alarmDuration != getAlarmDuration()) {
    EEPROMwrite(24, alarmDuration);
  }
}

byte getAlarmHour(byte day) { 
  return constrain(EEPROMread(40 + 2 * (day - 1)), 0, 23);
}

byte getAlarmMinute(byte day) { 
  return constrain(EEPROMread(40 + 2 * (day - 1) + 1), 0, 59);
}

void putAlarmTime(byte day, byte hour, byte minute) { 
  if (hour != getAlarmHour(day)) {
    EEPROMwrite(40 + 2 * (day - 1), constrain(hour, 0, 23));
  }
  if (minute != getAlarmMinute(day)) {
    EEPROMwrite(40 + 2 * (day - 1) + 1, constrain(minute, 0, 59));
  }
}

byte getAlarmWeekDay() { 
  return EEPROMread(20);
}

byte getDawnDuration() { 
  return constrain(EEPROMread(21),1,59);
}

void putAlarmSounds(boolean useSound, byte maxVolume, int8_t alarmSound, int8_t dawnSound) {
  //   23 - Будильник звук: вкл/выкл 1 - вкл; 0 -выкл
  //   25 - Будильник, мелодия будильника
  //   26 - Будильник, мелодия рассвета
  //   27 - Будильник, максимальная громкость
  if (alarmEffect != getAlarmEffect()) {
    EEPROMwrite(22, alarmEffect);
  }
  if (useSound != getUseAlarmSound()) {
    EEPROMwrite(23, useSound ? 1 : 0);
  }
  if (alarmSound != getAlarmSound()) {
    EEPROMwrite(25, (byte)alarmSound);
  }
  if (dawnSound != getDawnSound()) {
    EEPROMwrite(26, (byte)dawnSound);
  }
  if (maxVolume != getMaxAlarmVolume()) {
    EEPROMwrite(27, maxVolume);
  }
}

byte getAlarmEffect() { 
  return EEPROMread(22);
}

bool getUseAlarmSound() { 
  return EEPROMread(23) == 1;
}

byte getAlarmDuration() { 
  return constrain(EEPROMread(24),1,10);
}

byte getMaxAlarmVolume() { 
  return constrain(EEPROMread(27),0,30);
}

int8_t getAlarmSound() { 
  return constrain((int8_t)EEPROMread(25),-1,127);
}

int8_t getDawnSound() { 
  return constrain((int8_t)EEPROMread(26),-1,127);
}

bool getUseSoftAP() {
  return EEPROMread(14) == 1;
}

void putUseSoftAP(boolean use) {  
  if (use != getUseSoftAP()) {
    EEPROMwrite(14, use ? 1 : 0);
  }
}

String getSoftAPName() {
  return EEPROM_string_read(54, 10);
}

void putSoftAPName(String SoftAPName) {
  if (SoftAPName != getSoftAPName()) {
    EEPROM_string_write(54, SoftAPName, 10);
  }
}

String getSoftAPPass() {
  return EEPROM_string_read(64, 16);
}

void putSoftAPPass(String SoftAPPass) {
  if (SoftAPPass != getSoftAPPass()) {
    EEPROM_string_write(64, SoftAPPass, 16);
  }
}

// -----------------------------
// До версии v.1.10.2021.0915 имя сети (SSID) и пароль доступа размещались в ячейках 80-103 и 104-119 соответственно
// Начиная с версии v.1.10.2021.0915 хранение SSID и пароля перенесены в файловую сичтему в файлы ssid и pass соответственно
// Длина имени сети и пароля увеличина до 32 символов
// -----------------------------

// ssid – символьная строка, содержащая SSID точки доступа, к которой мы хотим подключиться (может содержать не более 32 символов).
String getSsid() {
  String ssid;
  File file;
  bool ok = true;
  #if defined(ESP32)
    String fileName = "/ssid";
  #else
    String fileName = "ssid";
  #endif  
  file = LittleFS.open(fileName, "r");
  if (!file) {
    // Файл не найден. Полагаем, что переход на хранение имени сети в файле еще не выполнен - счтываем имя сети с прежнего места хранения в EEPROM из ячеек 80-103
    // после чего сохраняем его в файл в файловой системе МК
    ssid = EEPROM_string_read(80, 24);
    ok = putSsid(ssid);    
  } else {
    // считываем содержимое файла ssid
    char buf[33];
    memset(buf, '\0', 33);
    size_t len = file.read((uint8_t*)buf, 33);
    ok = len > 0;    
    file.close();
    ssid = ok ? String(buf) : "";
  }
  return ssid;
}

bool putSsid(String Ssid) {
  File file;
  bool ok = true;
  #if defined(ESP32)
    String fileName = "/ssid";
  #else
    String fileName = "ssid";
  #endif  
  if (LittleFS.exists(fileName)) {
    ok = LittleFS.remove(fileName);
  }
  if (ok) {
    file = LittleFS.open(fileName, "w");
    if (file) {
      size_t len = Ssid.length()+1, lenw = 0;
      if (len > 32) len = 32;
      char buf[33];
      memset(buf, '\0', 33);
      Ssid.toCharArray(buf, len);
      lenw = file.write((uint8_t*)buf, len);
      ok = lenw == len;       
      file.close();
    } else {
      ok = false;
    }
  }
  if (!ok) {
    DEBUGLN(String(F("Ошибка сохранения SSID")));
  } 
  return ok; 
}

// password – это пароль к точке доступа в виде символьной строки, которая может содержать от 8 до 64 символов
String getPass() {
  String pass;
  File file;
  bool ok = true;
  #if defined(ESP32)
    String fileName = "/pass";
  #else
    String fileName = "pass";
  #endif  
  file = LittleFS.open(fileName, "r");
  if (!file) {
    // Файл не найден. Полагаем, что переход на хранение имени сети в файле еще не выполнен - счтываем пароль с прежнего места хранения в EEPROM из ячеек 104-119
    // после чего сохраняем его в файл в файловой системе МК
    pass = EEPROM_string_read(104, 16);
    ok = putPass(pass);    
  } else {
    // считываем содержимое файла pass
    char buf[65];
    memset(buf, '\0', 65);
    size_t len = file.read((uint8_t*)buf, 65);
    ok = len > 0; 
    file.close();
    pass = ok ? String(buf) : "";
  }
  return pass;
}

bool putPass(String Pass) {
  File file;
  bool ok = true;
  #if defined(ESP32)
    String fileName = "/pass";
  #else
    String fileName = "pass";
  #endif  
  if (LittleFS.exists(fileName)) {
    ok = LittleFS.remove(fileName);
  }
  if (ok) {
    file = LittleFS.open(fileName, "w");
    if (file) {
      size_t len = Pass.length()+1, lenw = 0;
      if (len > 64) len = 64;
      char buf[65];
      memset(buf, '\0', 65);
      Pass.toCharArray(buf, len);
      lenw = file.write((uint8_t*)buf, len);
      ok = lenw == len;
      file.close();
    } else {
      ok = false;
    }
  }
  if (!ok) {
    DEBUGLN(String(F("Ошибка сохранения пароля")));
  } 
  return ok; 
}

// -----------------------------

String getNtpServer() {
  return EEPROM_string_read(120, 30);
}

void putNtpServer(String server) {
  if (server != getNtpServer()) {
    EEPROM_string_write(120, server, 30);
  }
}

void putAM1params(byte hour, byte minute, int8_t effect) { 
  putAM1hour(hour);
  putAM1minute(minute);
  putAM1effect(effect);
}

byte getAM1hour() { 
  byte hour = EEPROMread(33);
  if (hour>23) hour = 0;
  return hour;
}

void putAM1hour(byte hour) {
  if (hour != getAM1hour()) {
    EEPROMwrite(33, hour);
  }
}

byte getAM1minute() {
  byte minute = EEPROMread(34);
  if (minute > 59) minute = 0;
  return minute;
}

void putAM1minute(byte minute) {
  if (minute != getAM1minute()) {
    EEPROMwrite(34, minute);
  }
}

int8_t getAM1effect() {
  int8_t value = (int8_t)EEPROMread(35);
  if (value < -3) value = -3;
  return value;
}

void putAM1effect(int8_t effect) {
  if (effect != getAM1effect()) {
    EEPROMwrite(35, (byte)effect);
  }
}

void putAM2params(byte hour, byte minute, int8_t effect) { 
  putAM2hour(hour);
  putAM2minute(minute);
  putAM2effect(effect);
}

byte getAM2hour() { 
  byte hour = EEPROMread(36);
  if (hour>23) hour = 0;
  return hour;
}

void putAM2hour(byte hour) {
  if (hour != getAM2hour()) {
    EEPROMwrite(36, hour);
  }
}

byte getAM2minute() {
  byte minute = EEPROMread(37);
  if (minute > 59) minute = 0;
  return minute;
}

void putAM2minute(byte minute) {
  if (minute != getAM2minute()) {
    EEPROMwrite(37, minute);
  }
}

int8_t getAM2effect() {
  int8_t value = (int8_t)EEPROMread(38);
  if (value < -3) value = -3;
  return value;
}

void putAM2effect(int8_t effect) {
  if (effect != getAM2effect()) {
    EEPROMwrite(38, (byte)effect);
  }
}

void putAM3params(byte hour, byte minute, int8_t effect) { 
  putAM3hour(hour);
  putAM3minute(minute);
  putAM3effect(effect);
}

byte getAM3hour() { 
  byte hour = EEPROMread(161);
  if (hour>23) hour = 0;
  return hour;
}

void putAM3hour(byte hour) {
  if (hour != getAM3hour()) {
    EEPROMwrite(161, hour);
  }
}

byte getAM3minute() {
  byte minute = EEPROMread(162);
  if (minute > 59) minute = 0;
  return minute;
}

void putAM3minute(byte minute) {
  if (minute != getAM3minute()) {
    EEPROMwrite(162, minute);
  }
}

int8_t getAM3effect() {
  int8_t value = (int8_t)EEPROMread(163);
  if (value < -3) value = -3;
  return value;
}

void putAM3effect(int8_t effect) {
  if (effect != getAM3effect()) {
    EEPROMwrite(163, (byte)effect);
  }
}

void putAM4params(byte hour, byte minute, int8_t effect) { 
  putAM4hour(hour);
  putAM4minute(minute);
  putAM4effect(effect);
}

byte getAM4hour() { 
  byte hour = EEPROMread(164);
  if (hour>23) hour = 0;
  return hour;
}

void putAM4hour(byte hour) {
  if (hour != getAM4hour()) {
    EEPROMwrite(164, hour);
  }
}

byte getAM4minute() {
  byte minute = EEPROMread(165);
  if (minute > 59) minute = 0;
  return minute;
}

void putAM4minute(byte minute) {
  if (minute != getAM4minute()) {
    EEPROMwrite(165, minute);
  }
}

int8_t getAM4effect() {
  int8_t value = (int8_t)EEPROMread(166);
  if (value < -3) value = -3;
  return value;
}

void putAM4effect(int8_t effect) {
  if (effect != getAM4effect()) {
    EEPROMwrite(166, (byte)effect);
  }
}

int8_t getAM5effect() {
  int8_t value = (int8_t)EEPROMread(243);
  if (value < -3) value = -3;
  return value;
}

void putAM5effect(int8_t effect) {
  if (effect != getAM5effect()) {
    EEPROMwrite(243, (byte)effect);
  }
}

int8_t getAM6effect() {
  int8_t value = (int8_t)EEPROMread(248);
  if (value < -3) value = -3;
  return value;
}

void putAM6effect(int8_t effect) {
  if (effect != getAM6effect()) {
    EEPROMwrite(248, (byte)effect);
  }
}

int8_t getCurrentManualMode() {
  return (int8_t)EEPROMread(29);
}

void putCurrentManualMode(int8_t mode) {
  if (mode != getCurrentManualMode()) {
    EEPROMwrite(29, (byte)mode);
  }
}

void getStaticIP() {
  IP_STA[0] = EEPROMread(10);
  IP_STA[1] = EEPROMread(11);
  IP_STA[2] = EEPROMread(12);
  IP_STA[3] = EEPROMread(13);
}

void putStaticIP(byte p1, byte p2, byte p3, byte p4) {
  EEPROMwrite(10, p1);
  EEPROMwrite(11, p2);
  EEPROMwrite(12, p3);
  EEPROMwrite(13, p4);
}

uint32_t getGlobalColor() {
  byte r,g,b;
  r = EEPROMread(158);
  g = EEPROMread(159);
  b = EEPROMread(160);
  return (uint32_t)r<<16 | (uint32_t)g<<8 | (uint32_t)b;
}

void putGlobalColor(uint32_t color) {
  if (color != getGlobalColor()) {
    CRGB cl = CRGB(color);
    EEPROMwrite(158, cl.r); // R
    EEPROMwrite(159, cl.g); // G
    EEPROMwrite(160, cl.b); // B
  }
}

uint32_t getGlobalClockColor() {
  byte r,g,b;
  r = EEPROMread(152);
  g = EEPROMread(153);
  b = EEPROMread(154);
  return (uint32_t)r<<16 | (uint32_t)g<<8 | (uint32_t)b;
}

void putGlobalClockColor(uint32_t color) {
  if (color != getGlobalClockColor()) {
    CRGB cl = CRGB(color);
    EEPROMwrite(152, cl.r); // R
    EEPROMwrite(153, cl.g); // G
    EEPROMwrite(154, cl.b); // B
  }
}

uint32_t getGlobalTextColor() {
  byte r,g,b;
  r = EEPROMread(155);
  g = EEPROMread(156);
  b = EEPROMread(157);
  return (uint32_t)r<<16 | (uint32_t)g<<8 | (uint32_t)b;
}

void putGlobalTextColor(uint32_t color) {
  if (color != getGlobalTextColor()) {
    CRGB cl = CRGB(color);
    EEPROMwrite(155, cl.r); // R 
    EEPROMwrite(156, cl.g); // G
    EEPROMwrite(157, cl.b); // B
  }
}

int8_t getCurrentSpecMode() {
  return (int8_t)EEPROMread(28);
}

void putCurrentSpecMode(int8_t mode) {
  if (mode != getCurrentSpecMode()) {
    EEPROMwrite(28, (byte)mode);
  }
}

void putRandomMode(bool randomMode) {
  if (randomMode != getRandomMode()) {
    EEPROMwrite(31, randomMode ? 1 : 0);
  }  
}

bool getRandomMode() {
 return EEPROMread(31) != 0;
}

void putPowerLimit(uint16_t limit) {
  if (limit != getPowerLimit()) {
    EEPROM_int_write(150, limit);
  }
}

uint16_t getPowerLimit() {
  uint16_t val = (uint16_t)EEPROM_int_read(150);
  if (val !=0 && val < 1000) val = 1000;
  return val;
}

void putNightClockColor(byte clr) {
  if (clr != getNightClockColor()) {
    EEPROMwrite(39, clr);
  }  
}

byte getNightClockColor() {
  byte clr = EEPROMread(39);
  if (clr > 6) clr=0;
  return clr;
}

// Интервал включения режима бегущей строки
uint16_t getTextInterval() {
  uint16_t val = (uint16_t)EEPROM_int_read(167);
  return val;
}

void putTextInterval(uint16_t interval) {
  if (interval != getTextInterval()) {
    EEPROM_int_write(167, interval);
  }  
}

// Загрузка массива строк "Бегущей строки"
void loadTexts() {

  int addr = TEXT_EEPROM;  
  int size = sizeof(textLines) / sizeof(String);   // Размер массива текста бегущих строк
  int max_text_size = sizeof(incomeBuffer);        // Размер приемного буфера формирования текста загружаемой из EEPROM строки
  int idx = 0;                           
  bool finished = false;

  memoryAvail = (EEPROM_MAX - TEXT_EEPROM) / 2;    // UTF8 кирилицы - один символ 2 байта

  while (addr < EEPROM_MAX && idx < size && !finished) {
   
    memset(incomeBuffer, '\0', max_text_size);
    int16_t i = 0;
   
    while (i < max_text_size) {
      byte c = EEPROMread(addr++);
      finished = c == '\0' || addr == EEPROM_MAX - 1;
      if (finished || c == '\r') break;
      incomeBuffer[i++] = c;
    }

    // Сформировать строку из загруженного буфера
    textLines[idx] = String(incomeBuffer);

    idx++;
  }

  memoryAvail = (EEPROM_MAX - addr) / 2;  // UTF8 кирилицы - один символ 2 байта
  if (memoryAvail < 0) memoryAvail = 0;

  if (addr == TEXT_EEPROM + 1) {
    DEBUGLN(F("Нет сохраненных строк"));
  } else {
    DEBUG(F("Загрузка строк выполнена.\nИспользованы адреса EEPROM "));
    DEBUGLN(String(TEXT_EEPROM) + " - " + String(addr - 1));
  }
  if (addr >= EEPROM_MAX) {
    DEBUGLN(F("Память заполнена."));
  }
  DEBUG(F("Свободно ячеек "));
  DEBUGLN(String(EEPROM_MAX - addr));

  // Заполнить оставшиеся строки массивва пустой строкой
  for (byte i=idx; i<size; i++) {
     textLines[i] = "";
  }

  /*
  // Контрольная печать загруженных строк
  for (byte i=0; i<size; i++) {
     DEBUGLN("Строка " + String(i) + " = '" + textLines[i] + "'");
  }
  */
  
  // Подсчитать контрольную сумму строк в массиве. Это позволит определить были ли изменения, нужно ли сохранять массив в EEPROM,
  // если флаг eepromModified == true
  crc = 0;
  for (byte i=0; i<size; i++) {
    String text = textLines[i];
    uint16_t len = text.length();
    if (len > BUF_MAX_SIZE) len = BUF_MAX_SIZE;
    if (len>0) {
      text.toCharArray(incomeBuffer, len);
      crc ^= getCrc16((uint8_t*)incomeBuffer, len);
    }
  }

  if (textLines[0] == "#") textLines[0] = "##";
  
  /*
  // Это пример макросов в строках, использовались для отладки режимов замены макросов в тексте бегущей строки
  //
  textLines[0]  = "#123456789ABDCEFGHI";
  textLines[1]  = "-Это просто строка";
  textLines[2]  = "-Эту строку не отображать";
  textLines[3]  = "";
  textLines[4]  = "Эту строку не {-} отображать";
  textLines[5]  = "-Эта желтая строка на красном фоне{C#FFFF00}{B#FF0000}";
  textLines[6]  = "-Эта строка разнобуквица{C#000002}";
  textLines[7]  = "-Эта строка на фоне эффекта {E5}'Огонь'";
  textLines[8]  = "-Эта строка на фоне эффекта 'Палитра'{E29}";
  textLines[9]  = "-Эта строка на фоне эффекта {E28}'Тетрис'";
  textLines[10] = "-Эта строка на 40 секунд {T40}";  
  textLines[11] = "-Эта строка на 4 раза {N4}";
  textLines[12] = "-После этой строки (1) - строка 19 на фоне Analyzer{#19}";
  textLines[13] = "-После этой строки (2) - строка 19 на фоне Analyzer{#J}";
  textLines[14] = "-Текущее время: {D}";
  textLines[15] = "-Время: {D:HH:mm:ss}";
  textLines[16] = "-Дата: {D:D MMMM YYYY года}";
  textLines[17] = "-Дата и время: {D:DD.MM.YY hh:mm tt}";
  textLines[18] = "До Нового года осталось {R01.01.2021#20}";
  textLines[19] = "Это строка 19 на фоне {E30}Analyzer";
  textLines[20] = "С Новым годом!{-}";  // отоброжение должно быть отключено, иначе строка будет отображаться как обычная, а не только как заместитель при наступлении события
  */

  /*
  textLines[0]  = "#56789A";
  textLines[5]  = "Это зеленая строка на красном фоне{C#00FF00}{B#FF0000}";
  textLines[6]  = "Это строка c {C#000002}разноцветными {C#FFFFFF}буквами";
  textLines[7]  = "Это зеленая строка{C#00FF00}";
  textLines[8]  = "{C#0000FF}Это синяя строка";
  textLines[9]  = "Белый, {C#0000FF}Синий, {C#FF0000}Красный, {C#00FF00}Зеленый";
  textLines[10] = "До {C#0000FF}Нового года {C#FFFFFF}осталось {C#00FF00}{R23.08.2020#11}";
  textLines[11] = "-С Новым годом!";  // отображение должно быть отключено, иначе строка будет отображаться как обычная, а не только как заместитель при наступлении события
  textLines[12] = "До начала {P23.08.2020 20:00#13#60#60}";
  textLines[13] = "-Дождались!";  // отображение должно быть отключено, иначе строка будет отображаться как обычная, а не только как заместитель при наступлении события
  textLines[14] = "Подъем через {P07:00#13#60#60#12345}";
  textLines[15] = "-Доброе утро!";  // отображение должно быть отключено, иначе строка будет отображаться как обычная, а не только как заместитель при наступлении события
  */

  // Если строка 0 - управляющая - установить индекс последовательности отображения на 1-й символ (т.к. нулевой - это '#')
  sequenceIdx = isFirstLineControl() ? 1 : -1;
}

// Сохранения массива строк "Бегущей строки"
// Весть текст (все строки массива) сохраняются сплошным потоком, начиная с адреса TEXT_EEPROM до EEPROM_MAX, то есть примерно доступно 3K байта под строки.
// UTF8 для кириллицы имеет преимущественно два байта на символ - можно всего сохранить порядка 1500 букв
// Строки массива разделяются символом '\r'; Последний символ сохранения данных - '\0'

bool saveTexts() {
  int addr = TEXT_EEPROM;  
  int size = sizeof(textLines) / sizeof(String);

  set_memoryAvail((EEPROM_MAX - TEXT_EEPROM) / 2);  // UTF8 кирилицы - один символ 2 байта

  // Подсчитать контрольную сумму строк в массиве. Это позволит определить были ли изменения, нужно ли сохранять массив в EEPROM,
  uint16_t new_crc = 0; 
  for (byte i=0; i<size; i++) {
    String text = textLines[i];
    uint16_t len = text.length();
    if (len > BUF_MAX_SIZE) len = BUF_MAX_SIZE;
    text.toCharArray(incomeBuffer, len);
    new_crc ^= getCrc16((uint8_t*)incomeBuffer, len);
  }

  // CRC совпадает - массив строк не изменен - сохранять нечего
  if (crc == new_crc) return true;

  bool completed = true;
  
  for (byte i=0; i<size; i++) {
        
    uint16_t len = textLines[i].length();
    uint16_t j = 0;
  
    // Сохранить новое значение
    while (j < len) {
      EEPROMwrite(addr++, textLines[i][j++]);
      if (addr == EEPROM_MAX - 1) break;
    }

    if (addr == EEPROM_MAX - 1) {
      completed = false;
      break;
    }

    if (completed) EEPROMwrite(addr++, '\r');
    
    if (addr == EEPROM_MAX - 1) {
      completed = false;
      break;
    }
  }

  // Символ завершение данных после того, как все строки записаны
  if (addr < EEPROM_MAX - 1) {  
    EEPROMwrite(addr, '\0');
  }

  set_memoryAvail((EEPROM_MAX - addr) / 2);  // UTF8 кирилицы - один символ 2 байта
  if (memoryAvail < 0) set_memoryAvail(0);
  
  DEBUG(F("Сохранение строк выполнено.\nИпользованы адреса EEPROM "));
  DEBUGLN(String(TEXT_EEPROM) + " - " + String(addr - 1));
  if (addr >= EEPROM_MAX - 1) {
    DEBUGLN(F("Память заполнена."));
  }
  DEBUG(F("Свободно ячеек "));
  DEBUGLN(String(EEPROM_MAX - addr));
  if (!completed) {
    DEBUGLN(F("Не все строки были загружены."));
  }

  return addr < EEPROM_MAX;
}

// Режим цвета часов оверлея X: 0,1,2,3
void putClockColor(byte clr) {
  if (clr != getClockColor()) {
    EEPROMwrite(169, clr);
  }  
}

byte getClockColor() {
  byte clr = EEPROMread(169);
  if (clr > 3) clr=0;
  return clr;
}

// Скорость прокрутки часов
void putClockScrollSpeed(byte clr) {
  if (clr != getClockScrollSpeed()) {
    EEPROMwrite(170, clr);
  }  
}

byte getClockScrollSpeed() {
  byte clr = EEPROMread(170);
  return clr;
}

// Режим цвета оверлея бегущей строки X: 0,1,2,3
void putTextColor(byte clr) {
  if (clr != getTextColor()) {
    EEPROMwrite(171, clr);
  }  
}

byte getTextColor() {
  byte clr = EEPROMread(171);
  if (clr > 2) clr=0;
  return clr;
}

// Скорость прокрутки бегущей строки
void putTextScrollSpeed(byte clr) {
  if (clr != getTextScrollSpeed()) {
    EEPROMwrite(172, clr);
  }  
}

byte getTextScrollSpeed() {
  byte clr = EEPROMread(172);
  return clr;
}

uint8_t getUseWeather() {
  return EEPROMread(174);
}

void putUseWeather(uint8_t id) {
  if (id != getUseWeather()) {
    EEPROMwrite(174, id);
  }
}

byte getWeatherInterval() {
  byte value = EEPROMread(175);
  if (value < 10) value = 10;
  return value;
}

// Интервал обновления погоды
void putWeatherInterval(byte interval) {
  if (interval != getWeatherInterval()) {
    EEPROMwrite(175, interval);
  }  
}

uint32_t getWeatherRegion() {
  uint32_t region = EEPROM_long_read(176);  
  return region;
}

void putWeatherRegion(uint32_t value) {
  if (value != getWeatherRegion()) {
    EEPROM_long_write(176, value);
  }
}

uint32_t getWeatherRegion2() {
  uint32_t region = EEPROM_long_read(244);  
  return region;
}

void putWeatherRegion2(uint32_t value) {
  if (value != getWeatherRegion2()) {
    EEPROM_long_write(244, value);
  }
}

boolean getUseTemperatureColor() {
  return EEPROMread(180) == 1;
}

void putUseTemperatureColor(boolean use) {
  if (use != getUseTemperatureColor()) {
    EEPROMwrite(180, use ? 1 : 0);
  }
}

boolean getUseTemperatureColorNight() {
  return EEPROMread(181) == 1;
}

void putUseTemperatureColorNight(boolean use) {
  if (use != getUseTemperatureColorNight()) {
    EEPROMwrite(181, use ? 1 : 0);
  }
}

#if (USE_MQTT == 1)

bool getUseMqtt() {
  return EEPROMread(239) == 1;
}

void putUseMqtt(boolean use) {  
  if (use != getUseMqtt()) {
    EEPROMwrite(239, use ? 1 : 0);
  }
}

uint16_t getMqttPort() {
  uint16_t val = (uint16_t)EEPROM_int_read(237);
  return val;
}

void putMqttPort(uint16_t port) {
  if (port != getMqttPort()) {
    EEPROM_int_write(237, port);
  }  
}

String getMqttServer() {
  return EEPROM_string_read(182, 24);
}

void putMqttServer(String server) {
  if (server != getMqttServer()) {
    EEPROM_string_write(182, server, 24);
  }
}

String getMqttUser() {
  return EEPROM_string_read(207, 24);
}

void putMqttUser(String user) {
  if (user != getMqttUser()) {
    EEPROM_string_write(207, user, 14);
  }
}

String getMqttPass() {
  return EEPROM_string_read(222, 24);
}

void putMqttPass(String pass) {
  if (pass != getMqttPass()) {
    EEPROM_string_write(222, pass, 14);
  }
}

String getMqttPrefix() {
  return EEPROM_string_read(250, 30);
}

void putMqttPrefix(String prefix) {  
  if (prefix != getMqttPrefix()) {
    EEPROM_string_write(250, prefix, 30);
  }
}

#endif

byte getNightClockBrightness()   {
  byte br = EEPROMread(240);
  if (br <= 1) br = 2;
  return br;
}

void putNightClockBrightness(byte brightness) {
  if (brightness <= 1) brightness = 2;
  if (brightness != getNightClockBrightness()) {
    EEPROMwrite(240, brightness);
  }  
}

// ----------------------------------------------------------

byte EEPROMread(uint16_t addr) {    
  return EEPROM.read(addr);
}

void EEPROMwrite(uint16_t addr, byte value) {    
  EEPROM.write(addr, value);
  eepromModified = true;
  saveSettingsTimer.reset();
}

// чтение uint16_t
uint16_t EEPROM_int_read(uint16_t addr) {    
  byte raw[2];
  for (byte i = 0; i < 2; i++) raw[i] = EEPROMread(addr+i);
  uint16_t &num = (uint16_t&)raw;
  return num;
}

// запись uint16_t
void EEPROM_int_write(uint16_t addr, uint16_t num) {
  byte raw[2];
  (uint16_t&)raw = num;
  for (byte i = 0; i < 2; i++) EEPROMwrite(addr+i, raw[i]);
}

// чтение uint32_t
uint32_t EEPROM_long_read(uint16_t addr) {    
  byte raw[4];
  for (byte i = 0; i < 4; i++) raw[i] = EEPROMread(addr+i);
  uint32_t &num = (uint32_t&)raw;
  return num;
}

// запись uint32_t
void EEPROM_long_write(uint16_t addr, uint32_t num) {
  byte raw[4];
  (uint32_t&)raw = num;
  for (byte i = 0; i < 4; i++) EEPROMwrite(addr+i, raw[i]);
}

String EEPROM_string_read(uint16_t addr, int16_t len) {
   char buffer[len+1];
   memset(buffer,'\0',len+1);
   int16_t i = 0;
   while (i < len) {
     byte c = EEPROMread(addr+i);
     if (c == 0) break;
     buffer[i++] = c;
   }
   return String(buffer);
}

void EEPROM_string_write(uint16_t addr, String buffer, uint16_t max_len) {
  uint16_t len = buffer.length();
  uint16_t i = 0;

  // Принудительно очистить "хвосты от прежнего значения"
  while (i < max_len) {
    EEPROMwrite(addr+i, 0x00);
    i++;
  }
  
  // Обрезать строку, если ее длина больше доступного места
  if (len > max_len) len = max_len;

  // Сохранить новое значение
  i = 0;
  while (i < len) {
    EEPROMwrite(addr+i, buffer[i]);
    i++;
  }
}

// Проверка наличия сохраненной резервной копии
// Возврат: 0 - не найден; 1 - найден в FS микроконтроллера; 2 - найден на SD-карте; 3 - найден в FS и на SD
uint8_t checkEepromBackup() {
  File file;
  String  fileName = F("/eeprom.bin");
  uint8_t existsFS = 0; 
  uint8_t existsSD = 0; 
  
  file = LittleFS.open(fileName, "r");
  if (file) {
    if (file.size() == EEPROM_MAX) {
      existsFS = 1;
    }
    file.close();
  }

  #if (USE_SD == 1)
    file = SD.open(fileName);
    if (file) {
      if (file.size() == EEPROM_MAX) {
        existsSD = 2;
      }
      file.close();
    }
  #endif
  
  return existsFS + existsSD;
}

// Сохранить eeprom в файл
// storage = "FS" - внутренняя файловая система
// storage = "SD" - на SD-карту
// возврат: true - успех; false - ошибка
bool saveEepromToFile(String storage) {

  const uint8_t part_size = 128;
  bool ok = true;
  uint8_t buf[part_size];
  String message = "", fileName = F("/eeprom.bin");
  size_t len = 0;
  uint16_t cnt = 0, idx = 0;  
  File file;

  saveSettings();
  if (USE_SD == 0) storage = "FS";

  DEBUG(F("Сохранение файла: "));
  DEBUGLN(storage + String(F(":/")) + fileName);

  memset(buf, 0, part_size);

  if (storage == "FS") {

    // Если файл с таким именем уже есть - удалить (перезапись файла новым)
    if (LittleFS.exists(fileName)) {
      ok = LittleFS.remove(fileName);
      if (!ok) {
        message = String(F("Ошибка создания файла '")) + fileName + "'";
        DEBUGLN(message);
        return false;
      }
    }
  
    file = LittleFS.open(fileName, "w");
  }

  #if (USE_SD == 1) 
  if (storage == "SD") {

    // Если файл с таким именем уже есть - удалить (перезапись файла новым)
    if (SD.exists(fileName)) {
      ok = SD.remove(fileName);
      if (!ok) {
        message = String(F("Ошибка создания файла '")) + fileName + "'";
        DEBUGLN(message);
        return false;
      }
    }

    file = SD.open(fileName, FILE_WRITE);
  }
  #endif

  if (!file) {
    message = String(F("Ошибка создания файла '")) + fileName + "'";
    DEBUGLN(message);
    return false;
  }

  while (idx < EEPROM_MAX) {
    delay(0);
    if (cnt >= part_size) {
      len = file.write(buf, cnt);
      ok = len == cnt;
      if (!ok) break;
      cnt = 0;
      memset(buf, 0, part_size);
    }
    buf[cnt++] = EEPROMread(idx++);
  }

  // Дописываем остаток
  if (ok && cnt > 0) {
    len = file.write(buf, cnt);
    ok = len == cnt;
  }
  
  if (!ok) {
    message = String(F("Ошибка записи в файл '")) + fileName + "'";
    DEBUGLN(message);
    file.close();
    return false;
  }          
  
  file.close();
  DEBUGLN(F("Файл сохранен."));

  eeprom_backup = checkEepromBackup();
  
  return true;
}

// Загрузить eeprom из файла
// storage = "FS" - внутренняя файловая система
// storage = "SD" - на SD-карту
// возврат: true - успех; false - ошибка
bool loadEepromFromFile(String storage) {

  const uint8_t part_size = 128;
  bool ok = true;
  uint8_t buf[part_size];
  String message = "", fileName = F("/eeprom.bin");
  size_t len = 0;
  uint16_t idx = 0;  
  File file;

  if (USE_SD == 0) storage = "FS";

  DEBUG(F("Загрузка файла: "));
  DEBUGLN(storage + String(F(":/")) + fileName);

  if (storage == "FS") {
    file = LittleFS.open(fileName, "r");
  }

  #if (USE_SD == 1) 
  if (storage == "SD") {
    file = SD.open(fileName, FILE_READ);
  }
  #endif

  if (!file) {
    message = String(F("Файл '")) + fileName + String(F("' не найден."));
    DEBUGLN(message);
    return false;
  }
  
  clearEEPROM();
  
  while (idx < EEPROM_MAX) {
    delay(0);
    memset(buf, 0, part_size);
    len = file.read(buf, part_size);
    for (uint8_t i=0; i<len; i++) {
      EEPROMwrite(idx++, buf[i]);
    }
  }
  file.close();

  ok = idx == EEPROM_MAX;

  if (!ok) {
    message = String(F("Ошибка чтения файла '")) + fileName + "'";
    DEBUGLN(message);
    return false;
  }          

  // Записать в 0 текущее значение EEPROM_OK, иначе при несовпадении версии
  // после перезагрузки будут восстановлены значения по-умолчанию
  EEPROMwrite(0, EEPROM_OK);
  
  saveSettings();
  
  return true;
}

// ----------------------------------------------------------
