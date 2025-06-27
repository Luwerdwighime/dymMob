#include "Fs.hpp"

void Fs::mkdir_p(std::string path) {
  try {
    std::filesystem::create_directories(path);
  } catch (const std::filesystem::filesystem_error& e) {
    std::cerr << "Ошибка создания папки: " << path << " (" << e.what() << ")" << std::endl;
    std::exit(ERR_DIR);
  }
}

void Fs::initDirs() {
  mkdir_p(config->fs.video_dir);
  mkdir_p(config->fs.audio_dir);
  mkdir_p(config->fs.dray_dir);
}

std::string Fs::drayLogPath() {
  return config->fs.dray_dir + "/" + config->fs.dray_log;
}

void Fs::log_video_id(std::string video_id) {
  std::string path = drayLogPath(); // Получаем путь к логу
  std::ofstream log(path, std::ios::app); // Открываем лог на append
  if (!log) {
    std::cerr << "Ошибка открытия и создания лога Дмитрия Рея: " << path << std::endl;
    std::exit(ERR_DRAYLOG); // Сваливаем с программы
  }
  log << video_id << std::endl; // Дописываем video_id в лог
  log.close(); // Закрываем файл
}

bool Fs::is_video_downloaded(std::string video_id) {
  std::string path = drayLogPath(); // Получаем путь к логу
  std::ifstream log(path); // Открываем лог на чтение
  if (!log) return false; // Лог не существует, считаем, что видео не скачано

  std::string line; // Буффер под строчку динамического размера в куче
  // Читаем в line построчечно, пока std::getline() не вернёт EOF
  while (std::getline(log, line)) {
    // Удаляем \n или \r (для совместимости с Mac/Win)
    line.erase(line.find_last_not_of("\n\r") + 1);

    if (line == video_id) { // Нашли!
      log.close(); // Закрываем файл
      return true; // Успех
    }
  }
  log.close();  // Закрываем файл
  return false; // Все перерыли и не нашли
}

