/**
 * @file User.hpp
 * @brief Класс User как коллекция функций пользовательского интерфейса
 */

#pragma once
#include <iostream> // Для std::cout, std::cin
#include <limits>   // Для std::numeric_limits
#include <string>   // Для std::string, std::getline()

/**
 * @brief Класс-коллекция функций для общения с юзером
 */
class User {
 public:
  /**
   * @brief Показывает главное меню
   *
   * @return Символ выбранного режима
   */
  static char menu();

  /**
   * @brief Вытряхивает url с юзера
   *
   * @return URL
   */
  static std::string getUrl();

  /**
   * @brief Выводит хэлп
   */
  static void help();
};

