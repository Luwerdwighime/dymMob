/**
 * @file Cfg.hpp
 * @brief Класс Cfg и глобальная переменная config
 */

#pragma once
#include <cstdlib>     // Для std::exit()
#include <iostream>    // Для std::cerr
#include <getopt.h>    // Для getopt_long(), optarg, optind
#include <string>      // Для std::string
#include "config.hpp"  // Константы
#include "INIReader.h" // Анализатор ini-шек

/**
 * @brief Класс конфигурации
 */
class Cfg {
 public:
  /**
   * @brief Структура для опций командной строки
   *
   * Это C-like описание куска памяти для типа Options, память ещё не выделена
   */
  struct Options {
    /// Флаг встречи бага при анализе
    bool        bug;
    /// Путь до ini конфига
    std::string config;
    /// Режим работы
    char        mode;
    /// URL
    std::string url;
  };

  /// Память под опции командной строки в формате Options
  Options opt = {false, INI_CFG, 0, ""};

  /**
   * @brief Структура для конфигурации рабочих каталогов вычитанной из config.ini
   *
   * Это C-like описание куска памяти для типа Fs, память ещё не выделена
   */
  struct Fs {
    /// Права доступа к создаваемым папкам, 9 бит
    int         dir_rights;
    /// Путь к папке для видео
    std::string video_dir;
    /// Путь к папке для аудио
    std::string audio_dir;
    /// Путь к папке для Дмитрия Рея
    std::string dray_dir;
    /// Имя файла лога Дмитрия Рея
    std::string dray_log;
    /// Путь к куке YouTube
    std::string cookie_path;
  };

  /// Память под конфиг папок из ini в формате Fs
  Fs fs = {0755, "video_dir", "audio_dir", "dray_dir", "dray_log.txt", ""};

  /**
   * @brief Структура для конфигурации yt-dlp вычитанной из config.ini
   *
   * Это C-like описание куска памяти для типа Yt, память ещё не выделена
   */
  struct Yt {
    /// Команда для списка плейлиста
    std::string ytids;
    /// Команда для скачки
    std::string ytcmd;
    /// Опции режима 1/3
    std::string mode1;
    /// Опции режима 2/4
    std::string mode2;
    /// Допопции плейлистовых режимов 3/4
    std::string modep;
    /// Шаблон имени файла
    std::string fname;
    /// Шаблон папки и файлов для плейлиста
    std::string pname;
    /// Число попыток закачки
    int         retr;
  };

  /// Память под опции yt-dlp из ini в формате Yt
  Yt yt = {"", "", "", "", "", "", "", 3};

  /**
   * @brief Конструктор объекта класса Cfg
   *
   * Анализирует опции командной строки, читает ini, заполняет структуры данными
   *
   * @param argc Количество параметров командной строки
   * @param argv Массив указателей на строки с параметрами
   */
  Cfg(int argc, char* argv[]);

 private:
  /**
   * @brief Анализирует опции командной строки, заполняет структуру opt
   *
   * @param argc Количество параметров командной строки
   * @param argv Массив указателей на строки с параметрами
   */
  void termOpts(int argc, char* argv[]);

  /**
   * @brief Анализирует ini, заполняет структуры fs и yt
   *
   * @param file Указатель на строку с именем файла ini
   */
  void loadIni(std::string file);
};

/// Память под глобальную переменную-указатель на config типа/класса Cfg
extern Cfg* config;

