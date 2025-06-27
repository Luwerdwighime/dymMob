#include "Yt.hpp"

// Загрузка функций в текущую область видимости, чтобы длинно не писать
using std::chrono::seconds;
using std::this_thread::sleep_for;

void Yt::yt_dlp(std::string url, char mode) {
  std::string opts;
  switch (mode) {
    case '1': // Скачивание видео
      run_yt_dlp(url, config->yt.mode1, config->fs.video_dir, config->yt.fname);
      return;
    case '2': // Скачивание аудио
      run_yt_dlp(url, config->yt.mode2, config->fs.audio_dir, config->yt.fname);
      return;
    case '3': // Скачивание видеоплейлиста
      opts = config->yt.mode1 + " " + config->yt.modep;
      run_yt_dlp(url, opts, config->fs.video_dir, config->yt.pname);
      return;
    case '4': // Скачивание аудиоплейлиста
      opts = config->yt.mode2 + " " + config->yt.modep;
      run_yt_dlp(url, opts, config->fs.audio_dir, config->yt.pname);
      return;
    case '5': // Докачивание плейлиста Дмитрия Рея
      process_playlist_ids(url);
      return;
  }
}

void Yt::run_yt_dlp(std::string url, std::string opts, std::string out_dir, std::string out_tmpl) {
  std::string cmd = config->yt.ytcmd + " " + opts
    + " -o '" + out_dir + "/" + out_tmpl + "' "
    + "'" + url + "'";
  // Видеть команду yt-dlp, если дебажим
  if (DEBUG) std::cout << "Debug: " << cmd << std::endl;

  // Пробуем выполнить команду с заданным количеством попыток
  int retries = config->yt.retr;
  while (retries--) {
    if (std::system(cmd.c_str()) == 0) {
      std::cout << "Готово, файлы в " << out_dir << std::endl;
      return;
    }
    std::cerr << "Ошибка скачивания, повтор через 10 секунд. Попыток осталось: "
      << retries << std::endl;
    sleep_for(seconds(10)); // Сон промеж повторов сорванной закачки
  }
  std::cerr << "Не удалось скачать после " << config->yt.retr
    << " попыток url: " << url << std::endl;
}

void Yt::process_playlist_ids(std::string url) {
  std::string cmd = config->yt.ytids + " '" + url + "'";
  // Видеть команду yt-dlp, если дебажим
  if (DEBUG) std::cout << "Debug: " << cmd << std::endl;


  // Открываем pipe (| в shell) для чтения вывода команды
  // C-style popen() запускает команду в shell и возвращает FILE* для чтения вывода
  std::FILE* pipe = popen(cmd.c_str(), "r");
  if (!pipe) {
    std::cerr << "Ошибка получения ID видео" << std::endl;
    exit(ERR_YTID); // Критический выход
  }

  // Буфер в стэке (т.к. мало данных, не опасно) для чтения строк
  char buffer[128];
  std::string video_id;

  // Читаем вывод построчно
  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    video_id = buffer; // Конвертация типа из char* в std::string

    // Удаляем возможные завершающие \n или \r
    video_id.erase(video_id.find_last_not_of("\r\n") + 1);

    // Проверяем, не скачано ли видео ранее
    if (!Fs::is_video_downloaded(video_id)) {
      // Не скачано
      run_yt_dlp( // Качаем
        "https://www.youtube.com/watch?v=" + video_id,
        config->yt.mode2, config->fs.dray_dir, config->yt.fname
      );
      Fs::log_video_id(video_id); // Логируем ID видео в DRAY_LOG
      sleep_for(seconds(5)); // Задержка 5 секунд между элементами плейлиста
    }
  }

  // Не забываем закрывать за собой файлы, особенно виртуальные,
  // чтобы не схватить утечку памяти и SIGKILL от ядра
  pclose(pipe);
}

