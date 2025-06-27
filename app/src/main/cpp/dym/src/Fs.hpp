/**
 * @file Fs.hpp
 * @brief Класс Fs как коллекция функций для работы с файловой системой
 */

#pragma once
#include <cstdlib>    // Для std::exit()
#include <filesystem> // Для std::filesystem
#include <fstream>    // Для std::ofstream, std::ifstream
#include <iostream>   // Для std::ios::app, std::cerr
#include <string>     // Для std::string
#include "Cfg.hpp"    // Для класса Cfg и глобального объекта config типа Cfg
#include "config.hpp" // Константы

/**
 * @brief Класс-коллекция функций для работы с файловой системой
 */
class Fs {
 public:
  /**
   * @brief Создаёт папку (целый путь), если её ещё нет
   *
   * Функция юзает вызов системной проги "mkdir -p", чтобы без гемора
   * создавать весь путь целиком со всеми родительскими папками.
   * Ошибок не возвращает, сразу падает в std::exit(ERR_DIR)
   *
   * @param path Путь до папки
   */
  static void mkdir_p(std::string path);

  /**
   * @brief Создаёт нужные для работы проги папки
   */
  static void initDirs();

  /**
   * @brief Возвращает путь к DRAY_LOG
   *
   * @return Полный путь к DRAY_LOG
   */
  static std::string drayLogPath();

  /**
   * @brief Запись ID видео в DRAY_LOG
   *
   * @param video_id ID видео на YouTube
   */
  static void log_video_id(std::string video_id);

  /**
   * @brief Проверка, есть ли ID видео в DRAY_LOG
   *
   * @param video_id ID видео на YouTube
   *
   * @return false если нет, true если да
   */
  static bool is_video_downloaded(std::string video_id);
};

