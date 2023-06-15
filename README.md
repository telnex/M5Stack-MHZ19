# :loudspeaker: Измеритель уровня CO2 на M5Stack
### **Версия:** 1.0
![M5Stack](https://img.shields.io/badge/M5Stack-Core_1-blue?style=flat-square&logo=appveyor) ![Arduino IDE 2.0.1](https://img.shields.io/badge/Arduino_IDE-2.0.1-blue?style=flat-square&logo=appveyor)
![Иллюстрация к проекту](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEhSvEzpZwDhYHhC3y6IvePiCfcNg_gnjNYyL4M8MeDZLSSgycLCsR7K3tPALoCoyGmDsH0IJ9PsKJh7volbyj28nqEVSqgVc5a9Dn0vvt_FYhaz60pELMfC-C8Dln1mew7ne-VP5qvGZIbgAOF4zxmhS4XwRioIrFJpNLrR2cvkzSUCiR-70-cX2kVhnA/w640-h381/logo-m5stack.jpg)

:tv: [Смотреть видео на YouTube](https://www.youtube.com/shorts/iWTrOM322Z4)
## Описание программы
Данное устройство определять уровень CO2 в воздухе и построено на базе платформы M5Stack (ESP32) и датчика CO2 MHZ19-B. Программа написана в среде Arduino IDE (C++).
В программе реализована функция отправки данных на сервер, в моем случае это Nginx+Flask+InfuxDB+Grafana. В файлах ``` prepare.psd``` и ``` set-inf.psd``` исходники картинок для Adobe Photoshop CC.

Нажатие кнопки **A** откроет меню (статус сети, заряд), для отключения звука нажать **B**, **С** - выход. 

## Настройки
Укажите данные вашей WiFi сети:
```cpp
const char *ssid = "WIFI";
const char *password = "PASS"
```
