/**
 * @file Yt.hpp
 * @brief Класс Yt как коллекция функций для работы с yt-dlp
 */

#pragma once
#include <chrono>             // Для std::chrono::seconds
#include <cstdio>             // Для popen(), pclose()
#include <cstdlib>            // Для std::exit()
#include <iostream>           // Для std::cout, std::cerr
#include <string>             // Для std::string
#include <thread>             // Для std::this_thread::sleep_for
#include "Cfg.hpp"            // Для класса Cfg и глобального объекта config типа Cfg
#include "Fs.hpp"             // Для класса Fs
#include "config.hpp"         // Константы

/**
 * @brief Класс-коллекция функций для работы с yt-dlp
 */
class Yt {
 public:
  /**
   * @brief Скачка url с запрошенным режимом
   *
   * @param url  Строка с url
   * @param mode Один из пяти режимов работы, букво-цифрами от '1' до '5'
   */
  static void yt_dlp(std::string url, char mode);

  /**
   * @brief Обёртка вокруг консольной команды yt-dlp
   *
   * @param url      Что качать
   * @param opts     С какими опциями
   * @param out_dir  Куда складывать
   * @param out_tmpl Как называть
   */
  static void run_yt_dlp(
    std::string url,     std::string opts,
    std::string out_dir, std::string out_tmpl
  );

  /**
   * @brief Получение и обработка ID видео из плейлиста
   *
   * @param url Url плейлиста
   */
  static void process_playlist_ids(std::string url);
};

