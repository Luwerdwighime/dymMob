/**
 * @file main.cpp
 * @brief Прога для комфортного кача с YouTube
 */

#include "Cfg.hpp"    // Для класса Cfg и глобального объекта config типа Cfg
#include "Fs.hpp"     // Для класса Fs
#include "User.hpp"   // Для класса User
#include "Yt.hpp"     // Для класса Yt
#include "config.hpp" // Константы

/**
 * @brief Точка входа в программу
 *
 * @param argc Число параметров командной строки
 * @param argv Массив указателей на строки с параметрами
 *
 * @return Числовые коды ошибок или 0 при успехе
 */
int main(int argc, char* argv[]) {
  // Читаем всю конфигурацию (из ini и командной строки)
  config = new Cfg(argc, argv);

  // Может хэлп?
  if (config->opt.bug) {
    User::help(); // Юзер ошибся с опциями
    return ERR_OPTS; // Критический выход
  }
  if (config->opt.mode == 'h') {
    User::help(); // Юзер хочет хэлп
    return 0; // Просто выход
  }
  
  // Доспрашиваем необходимое, если нужно
  if (!config->opt.mode)     // Юзер не указал режим, спрашиваем
    config->opt.mode = User::menu();   
  if (config->opt.url == "") // Юзер не указал URL, спрашиваем
    config->opt.url  = User::getUrl();

  // Пойдем работать потихонечку
  Fs::initDirs(); // Создаем, если нужно, рабочие папки
  Yt::yt_dlp(config->opt.url, config->opt.mode); // Работаем

  return 0; // Profit!
}

