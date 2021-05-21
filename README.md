﻿# HTTP-сервер
При запуске приложение принимает два аргумента командной строки. Первый - прослушиваемый порт, второй - путь к HTML-файлу. Приложение начинает бесконечный цикл "ожидание подключения - ответ". Под ожиданием подключения имеется ввиду прослушивание порта, указанного первым аргументов командной строки. После нового подключения приложение пишет в сокет сообщение следующего типа:

  
```html
HTTP/1.1 200 OK

Content-Type: text/html; charset=utf-8

Content-Length: <размер HTML-страницы>

Connection: close

<пустая строка>

<текст HTML-страницы>
```
  

Текст HTML-страницы берется из файла, указанного вторым аргументом командной строки, а размер рассчитывается программой. Ответ в кодировке UTF-8.
