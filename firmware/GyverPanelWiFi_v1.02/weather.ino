
#if (USE_WEATHER == 1)     

bool getWeather() {
  
  if (!wifi_connected) return false;  
  if (!client.connect("yandex.com",443)) return false;                    // Устанавливаем соединение с указанным хостом (Порт 443 для https)

  Serial.println();
  Serial.println(F("Запрос текущей погоды"));
  
  // Отправляем запрос
  client.println(String(F("GET /time/sync.json?geo=")) + String(regionID) + String(F(" HTTP/1.1\r\nHost: yandex.com\r\n\r\n"))); 

  // Проверяем статус запроса
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  // It should be "HTTP/1.0 200 OK" or "HTTP/1.1 200 OK"
  if (strcmp(status + 9, "200 OK") != 0) {
    Serial.print(F("Ошибка сервера погоды: "));
    Serial.println(status);
    return false;
  } 

    // Пропускаем заголовки                                                                
  char endOfHeaders[] = "\r\n\r\n";                                       // Системные заголовки ответа сервера отделяются от остального содержимого двойным переводом строки
  if (!client.find(endOfHeaders)) {                                       // Отбрасываем системные заголовки ответа сервера
    Serial.println(F("Нераспознанный ответ сервера погоды"));             // Если ответ сервера не содержит системных заголовков, значит что-то пошло не так
    return false;                                                         // и пора прекращать всё это дело
  }

  const size_t capacity = 750;                                            // Эта константа определяет размер буфера под содержимое JSON (https://arduinojson.org/v5/assistant/)
  DynamicJsonDocument doc(capacity);

  // {"time":1597989853200,"clocks":{"62":{"id":62,"name":"Krasnoyarsk","offset":25200000,"offsetString":"UTC+7:00","showSunriseSunset":true,"sunrise":"05:31","sunset":"20:10","isNight":false,"skyColor":"#57bbfe","weather":{"temp":25,"icon":"bkn-d","link":"https://yandex.ru/pogoda/krasnoyarsk"},"parents":[{"id":11309,"name":"Krasnoyarsk Krai"},{"id":225,"name":"Russia"}]}}}

  // Parse JSON object
  DeserializationError error = deserializeJson(doc, client);

  if (error) {
    Serial.print(F("JSON не разобран: "));
    Serial.println(error.c_str());
    return false;
  }

  client.stop();

  String regId = String(regionID);
  sunriseTime  = doc["clocks"][regId]["sunrise"].as<String>();          // Достаём время восхода - Третий уровень вложенности пары ключ/значение clocks -> значение RegionID -> sunrise 
  sunsetTime   = doc["clocks"][regId]["sunset"].as<String>();           // Достаём время заката - Третий уровень вложенности пары ключ/значение clocks -> значение RegionID -> sunset
  temperature  = doc["clocks"][regId]["weather"]["temp"].as<int8_t>();  // Достаём время заката - Четвёртый уровень вложенности пары ключ/значение clocks -> значение RegionID -> weather -> temp
  skyColor     = doc["clocks"][regId]["skyColor"].as<String>();         // Рекомендованный цвет фона
  isNight      = doc["clocks"][regId]["isNight"].as<boolean>();
  icon         = doc["clocks"][regId]["weather"]["icon"].as<String>();  // Достаём иконку - Четвёртый уровень вложенности пары ключ/значение clocks -> значение RegionID -> weather -> icon
  
  // #57bbfe
  if (skyColor.length() != 7) {
    Serial.print(F("JSON не содержит данных о погоде"));
    return false;
  }

  decodeWeather();
  
  weather_time = millis();  // запомнить время получения погоды с сервера
  init_weather = true;      // Флаг - погода получена
  refresh_weather = false;
  weather_t = 0; 
  weather_cnt = 0;
  
  Serial.println(F("Погода получена:"));
  Serial.print(F("Сейчас: "));
  Serial.print(weather + ", "); 
  if (temperature > 0) Serial.print("+"); 
  if (temperature < 0) Serial.print("-"); 
  Serial.println(String(temperature) + "ºC"); // '˚' '◦' 'º'
  Serial.println(String(F("Код иконки: '")) + icon + "'");
  Serial.println(String(F("Цвет неба: '")) + skyColor + "'");
  Serial.println(dayTime);
  
  return true;
}

/*
Код расшифровки иконки. Возможные значения:
  bkn-minus-ra-d — облачно с прояснениями, небольшой дождь (день)
  bkn-minus-sn-d — облачно с прояснениями, небольшой снег (день)
  bkn-minus-sn-n — облачно с прояснениями, небольшой снег (ночь)
  bkn-d — переменная облачность (день)
  bkn-n — переменная облачность (ночь)
  bkn-ra-d — переменная облачность, дождь (день)
  bkn-ra-n — переменная облачность, дождь (ночь)
  bkn-sn-d — переменная облачность, снег (день)
  bkn-sn-n — переменная облачность, снег (ночь)
  bl — метель
  fg-d — туман
  ovc — пасмурно
  ovc-minus-ra — пасмурно, временами дождь
  ovc-minus-sn — пасмурно, временами снег
  ovc-ra — пасмурно, дождь
  ovc-sn — пасмурно, снег
  ovc-ts-ra — пасмурно, дождь, гроза
  skc-d — ясно (день)
  skc-n — ясно (ночь)
*/

void decodeWeather(){  
  bool hasDay   = icon.endsWith("-d");
  bool hasNight = icon.endsWith("-n");
  String ico = icon;
  
  if (hasDay)
    dayTime = F("Светлое время суток");  // Сейчас день
  else if (hasNight)           
    dayTime = F("Темное время суток");   // Сейчас ночь

  if (hasDay || hasNight) {
    ico = icon.substring(0, icon.length() - 2);
  }

  if      (ico == F("bkn-minus-ra"))  weather = F("облачно с прояснениями, небольшой дождь");
  else if (ico == F("bkn-minus-sn"))  weather = F("облачно с прояснениями, небольшой снег");
  else if (ico == F("bkn"))           weather = F("переменная облачность");
  else if (ico == F("bkn-ra"))        weather = F("переменная облачность, дождь");
  else if (ico == F("bkn-sn"))        weather = F("переменная облачность, снег");
  else if (ico == F("bl"))            weather = F("метель");
  else if (ico == F("fg"))            weather = F("туман");
  else if (ico == F("ovc"))           weather = F("пасмурно");
  else if (ico == F("ovc-minus-ra"))  weather = F("пасмурно, временами дождь");
  else if (ico == F("ovc-minus-sn"))  weather = F("пасмурно, временами снег");
  else if (ico == F("ovc-ra"))        weather = F("пасмурно, дождь");
  else if (ico == F("ovc-sn"))        weather = F("пасмурно, снег");
  else if (ico == F("ovc-ts-ra"))     weather = F("пасмурно, дождь, гроза");
  else if (ico == F("skc"))           weather = F("ясно");  
}

#else

bool getWeather() {
  return false;
}

#endif

// Строка цвета, соответствующая температуре
String getTemperatureColor(int8_t temp) {
  String s_color;
  if      (temp <= -30)
    s_color = cold_less_30;
  else if (temp <= -20)
    s_color = cold_29_20;
  else if (temp <= -10)
    s_color = cold_19_10;
  else if (temp <= -4)
    s_color = cold_9_4;
  else if (temp <=  3)
    s_color = zero_3_3;
  else if (temp <=  9)
    s_color = hot_4_9;
  else if (temp <= 19)
    s_color = hot_10_19;
  else if (temp <= 29)
    s_color = hot_20_29;
  else
    s_color = hot_30_great;
  return s_color;
}

// Получить индекс иконки в мвссиве иконок погоды
uint8_t getWeatherFrame(String icon) {
  if (icon == "skc-d") return 0;
  if (icon == "skc-n") return 1;
  if (icon == "bkn-d") return 2;
  if (icon == "bkn-n") return 3;
  if (icon == "bkn-minus-ra-d") return 4;
  if (icon == "bkn-minus-ra-n") return 5;
  if (icon == "bkn-minus-sn-d") return 6;
  if (icon == "bkn-minus-sn-n") return 7;
  if (icon == "bkn-ra-d") return 8;
  if (icon == "bkn-ra-n") return 9;
  if (icon == "bkn-sn-d") return 10;
  if (icon == "bkn-sn-n") return 11;
  if (icon == "bl") return 12;
  if (icon == "fg-d") return 13;
  if (icon == "ovc") return 14;
  if (icon == "ovc-minus-ra") return 15;
  if (icon == "ovc-minus-sn") return 16;
  if (icon == "ovc-ra") return 17;
  if (icon == "ovc-sn") return 18;
  if (icon == "ovc-ts-ra") return 19;
  return random8(0,19);
}

uint8_t fade_weather_phase = 0;        // Плавная смена картинок: 0 - плавное появление; 1 - отображение; 2 - затухание
uint8_t fade_step = 0;
uint8_t weather_frame_num = 0;
int8_t  weather_text_x, weather_text_y;

void weatherRoutine() {

  boolean need_fade_image = false;     // Если отображение значения температуры наслаивается на картинку и задано использовать цвета для отображения значения -
                                       // яркость картинки нужно немного приглушать, чтобы цифры температуры не сливались с картинкой
  if (loadingFlag) {
    loadingFlag = false;
    // modeCode = MC_WEATHER;
    
    FastLED.clear();                   // очистить экран

    // Загрузить описатель массива изображений погоды
    loadDescriptor(&animation_weather);
    frames_in_image = sizeof(weather_array) / sizeof(weather_array[0]);

    // Координаты вывода изображения - центрировать
    image_desc.options = 1+2+4+16;             // Центрировать по вертикали/горизонтали, есть прозрачные пиксели, перед отрисовкой кадра - заливать цветом
    image_desc.transparent_color = 0x000000;   // Ролзоачные пиксели - черные
    image_desc.background_color = 0x000000;    // Заливка - черная (?)
    image_desc.draw_frame_interval = 2500;     // Интервал перехода к следующей картинке
    image_desc.draw_row_interval = 0;          // Рисовка - картинка целиком
    image_desc.move_type = 0;                  // Нет движения картинки

    flip_x = false;
    flip_y = false;

    if (init_weather) {
      
      // Если режим c отображением температуры - по максимуму картинка погоды - в левом верхнем углу, температура не перекрывая - в правом нижнем
      // Общая площадь - размер картинки плюс размер отображения погоды
      // Если полученный размер выходит за границы - сдвигаем позицию погоды вверх/влево, пока она не поместится в размер.
      // Полученную скорректированную площадь отрисовки размещаем по центру матирицы
      pos_x = 0;
      pos_y = HEIGHT - image_desc.frame_height;
      weather_text_x = image_desc.frame_width - 3; // знак +/- пусть залазит на картинку  
      weather_text_y = pos_y - 5;                  // отступ от низа картинки; 5 - высота шрифта

      uint8_t text_w = 12;   // +15 - 3 знака шрифта 3x5 + по пробелу между знаками = 9 + 3 = 12;
      
      while(weather_text_x > 0 && weather_text_x + text_w - 1 > WIDTH) weather_text_x--;
      while(weather_text_y < 0) weather_text_y++;

      // Ширина картинки + text = oт "pos_x" до "weather_text_x + 15"; - если матрица шире - центрировать конгломерат по матрице
      // Высота картинки + text = oт "weather_text_x" до "pos_y + image_desc.frame_height"; - если матрица выше - центрировать конгломерат по матрице
      uint8_t offset_x = (WIDTH - (weather_text_x + text_w - pos_x)) / 2;
      uint8_t offset_y = (HEIGHT - ((pos_y + image_desc.frame_height) - (weather_text_y + 5))) / 2;

      pos_x += offset_x;
      pos_y += offset_y;
      weather_text_x += offset_x;
      weather_text_y += offset_y;

      #if (USE_WEATHER == 1)     
        need_fade_image = useTemperatureColor && (pos_x + image_desc.frame_width < weather_text_x) && (pos_y < weather_text_y + 5);
      #endif   
      
    } else {
      // Если режим без отображения температуры - рисовать картинки погоды по центру матрицы
      pos_x = (WIDTH - image_desc.frame_width) / 2;
      pos_y = (HEIGHT - image_desc.frame_height) / 2;
    }

    // Если погода отключена или еще не получена - просто рисуем картинки по кругу
    // Если погода получена - находим индекс отрисовываемой картинки в соответствии с полученной иконкой погоды
    #if (USE_WEATHER == 1)
      weather_frame_num = init_weather ? getWeatherFrame(icon) : 0;
    #else
      weather_frame_num =  0;      
    #endif
    fade_weather_phase = init_weather ? 1 : 0;                         // плавное появление картинки
  }  

  // Нарисовать картинку
  loadImageFrame(weather_array[weather_frame_num]);
  
  byte spd = map8(255-effectSpeed, 2, 24);   

  // Если находимся в фазе 0 - плавное появление картинки - затенить только что отрисованную картинку, постепенно уменьшая затенение
  if (fade_weather_phase == 0) {
    fade_step += spd;
    if ((uint16_t)fade_step + spd >= 255) {
      fade_weather_phase = 1;
      last_draw_frame = millis();
    } else {  
      fader(255 - fade_step);
    }
  } else

  // Если находимся в фазе 1 - отображение - считаем сколько времени уже отображается, не пора ли переходить к фазе затухания и следующему кадру
  if (fade_weather_phase == 1) {
    if (need_fade_image) {
      fader(64);
    }
    if (!init_weather) {
      if (millis() - last_draw_frame > image_desc.draw_frame_interval) {
        fade_weather_phase = 2;
        fade_step = 0;
      }
    } else {
      // Чтобы картинка при известной погоде не выглядела статично - придаем ей некоторое "дыхание"
      uint8_t beat = beatsin8(10, 25, 155);
      fader(beat);
    }
  } else
  
  // Если находимся в фазе 2 - плавное затухание картинки - затенить только что отрисованную картинку, постепенно увеличивая затенение
  if (fade_weather_phase == 2) {
    fade_step += spd;
    if ((uint16_t)fade_step + spd >= 255) {
      fillAll(CRGB(image_desc.background_color));
      fade_step = 0;
      fade_weather_phase = 0;
      weather_frame_num++;
      if (weather_frame_num >= frames_in_image) {
        weather_frame_num = 0;
      }      
    } else {  
      fader(fade_step);
    }
  }

  #if (USE_WEATHER == 1)     

  // Если температура известна - нарисовать температуру
  if (init_weather) {
    
    // Получить цвет отображения значения температуры
    CRGB color = useTemperatureColor ? CRGB(HEXtoInt(getTemperatureColor(temperature))) : CRGB::White;
    
    // Если температура - однозначная - сместиться на одно знакоместо
    byte text_x = weather_text_x;
    byte text_y = weather_text_y;
    
    if (abs(temperature) < 10) text_x += 4;
    
    // Нарисовать '+' или '-' если температура не 0
    if (temperature != 0) {
      // Горизонтальная черта - общая для '-' и '+'
      for(int i = 0; i < 3; i++) {
        drawPixelXY(text_x + i, text_y + 2, color);      
      }
      
      // Для плюcа - вертикальная черта
      if (temperature > 0) {
        drawPixelXY(text_x + 1, text_y + 1, color);
        drawPixelXY(text_x + 1, text_y + 3, color);
      }
    }
    text_x += 4;

    // Десятки температуры
    if (abs(temperature) >= 10) {
      drawDigit3x5(abs(temperature) / 10, text_x, text_y, color);
      text_x += 4;
    }

    // Единицы температуры
    drawDigit3x5(abs(temperature) % 10, text_x, text_y, color);
    text_x += 4;

    /*
    // Буква 'C'
    for(int i = 0; i < 3; i++) {
      drawPixelXY(text_x, text_y + 1 + i, color);      
    }

    for(int i = 0; i < 2; i++) {
      drawPixelXY(text_x + 1 + i, text_y, color);      
      drawPixelXY(text_x + 1 + i, text_y + 4, color);      
    }
    */
  }
  
  #endif
  
}