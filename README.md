# :loudspeaker: Измеритель уровня CO2 на M5Stack
### **Версия:** 1.0
![M5Stack](https://img.shields.io/badge/M5Stack-Core_1-blue?style=flat-square&logo=appveyor) ![Arduino IDE 2.0.1](https://img.shields.io/badge/Arduino_IDE-2.0.1-blue?style=flat-square&logo=appveyor)

![Иллюстрация к проекту](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEhSvEzpZwDhYHhC3y6IvePiCfcNg_gnjNYyL4M8MeDZLSSgycLCsR7K3tPALoCoyGmDsH0IJ9PsKJh7volbyj28nqEVSqgVc5a9Dn0vvt_FYhaz60pELMfC-C8Dln1mew7ne-VP5qvGZIbgAOF4zxmhS4XwRioIrFJpNLrR2cvkzSUCiR-70-cX2kVhnA/w640-h381/logo-m5stack.jpg)

:tv: [Смотреть видео на YouTube](https://www.youtube.com/shorts/iWTrOM322Z4)
## Описание программы
Данное устройство позволяет определять уровень CO2 в воздухе и построено на базе платформы M5Stack (ESP32) и датчика CO2 MHZ19-B. Программа написана в среде Arduino IDE (C++).
В программе реализована функция отправки данных на сервер, в моем случае это Nginx+Flask+InfuxDB+Grafana. В файлах ``` prepare.psd``` и ``` set-inf.psd``` исходники картинок для Adobe Photoshop CC.

Нажатие кнопки **A** откроет меню (статус сети, заряд), для отключения звука нажать **B**, **С** - выход.

В целом устройство оказалось полезным, замеры на улице и в квартире показывают +/- реальные значения. Отмечается резкий рост СО2 в квартире при закрытых окнах, в машине значения достигают 1200-1300 ppm при включенном кондиционере менее чем за час. Автономность от родного АкБ порядка 25-30 минут. 

## Настройки
Укажите данные вашей WiFi сети:
```cpp
const char *ssid = "WIFI";
const char *password = "PASS"
```
## Комплектующие
- M5Stack
- MicroSD Card (Для хранения картинок)
- 2x2 Pin
- Кабель МГТФ 1х0.07 мм2
- MHZ19-B CO2 Датчик


P.S. Пример мониторинга данных в Grafana.

![Иллюстрация к проекту](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEgp2rqTa1MfSwwdLbC2MzQy3idwq9jpzDH3VSvDbB9CG_wNJ0LX7TUd1shJiaPqKKz6-iW410FHdbsG75W4ioGwlsXHVDABDgqOc9LyK_MYdnD_oAABkx0TCjbTgcwqwa8hvT7n9MlnVNRsRVfh0ai1Gdi6MuW48AOqDjWY05nFlXG6xrde10dNd2tNiA/w640-h253/2023-06-15_15-11-08.png)

