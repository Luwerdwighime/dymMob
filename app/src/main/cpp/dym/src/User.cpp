#include "User.hpp"

char User::menu() {
  const std::string text
    = "Что скачать?\n"
      "(1) Видео\n"
      "(2) Аудио\n"
      "(3) Плейлист видео\n"
      "(4) Плейлист аудио\n"
      "(5) Дмитрия Рея\n"
      "Выбери (1-5): ";

  // Цикл меню (бесконечный)
  char choice;
  while (true) {
    std::cout << text;   // Пишем текст
    std::cin  >> choice; // Читаем один символ с stdin
    std::cin.ignore(     // Пропускаем символ \n от кнопки Enter
      std::numeric_limits<std::streamsize>::max(), '\n'
    ); 

    // Проверяем юзера
    if (choice >= '1' && choice <= '5') return choice; // Умный юзер покидает цикл
    std::cout << "Неверный выбор\n"; // Глупый юзер уходит на следуюший круг
  }
}

std::string User::getUrl() {
  std::string url; // Память под url
  while (true) {
    std::cout << "Вставь ссылку: ";
    std::getline(std::cin, url); // Читаем из stdin в url
    if (!url.empty()) return url; // Покидаем цикл
  }
}

void User::help() {
  const std::string text
    = "dym [-1] [-2] [-3] [-4] [-5] [-c|--config] [-h|--help] [url]\n"
      "dym можно выполнить в одном из режимов:\n"
      "-1 - закачка видео\n"
      "-2 - закачка аудио\n"
      "-3 - закачка видеоплейлиста\n"
      "-4 - закачка аудиоплейлиста\n"
      "-5 - докачка Дмитрия Рея\n"
      "-c | --config - путь до ini конфига\n"
      "-h | --help - этот хэлп\n"
      "Если режим не указан, то программа его интерактивно спросит\n"
      "Если url не указан, то программа тоже его интерактивно спросит\n";
  std::cout << text;
}

