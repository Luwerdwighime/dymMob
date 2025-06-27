#include "Cfg.hpp"

Cfg::Cfg(int argc, char* argv[]) {
  // Анализим опции командной строки
  termOpts(argc, argv);
  // Если нет багов в опциях, то анализим ini-шку
  if (!opt.bug) loadIni(opt.config);
}

void Cfg::termOpts(int argc, char *argv[]) {
  // Короткие опции
  static const char* shOpts = "12345c:h";

  // Длинные опции
  static const struct option lOpts[] = {
    {"config", required_argument, 0, 'c'},
    {"help",   no_argument,       0, 'h'},
    {0, 0, 0, 0}
  };

  // Читаем опции поштучно
  int optCh;      // Символ опции (короткой или длинной)
  int oEnabl = 0; // Счётчик числа запрошенных режимов (валидно только 0 и 1)
  while(true) {
    optCh = getopt_long(argc, argv, shOpts, lOpts, NULL); // Анализим
    if (optCh == -1) break; // Нет больше опций в строке

    // Разбираем ответы
    switch (optCh) {
      case '1': opt.mode = optCh; oEnabl++; break;
      case '2': opt.mode = optCh; oEnabl++; break;
      case '3': opt.mode = optCh; oEnabl++; break;
      case '4': opt.mode = optCh; oEnabl++; break;
      case '5': opt.mode = optCh; oEnabl++; break;
      case 'c': opt.config = optarg; break;
      case 'h': opt.mode = optCh; oEnabl++; break;
      default: opt.bug = true;
    }
  }

  // Все опции режимные, кроме "--config", их может быть не больше одной штуки
  if (oEnabl > 1) opt.bug = true;

  // Проверяем, есть ли следующий неопционный аргумент (URL)
  if (optind < argc) opt.url = argv[optind];
  // Дальше не читаем даже если что-то есть - не интересно
}

void Cfg::loadIni(std::string file) {
  // Читаем файл в объект ini
  INIReader ini(file);
  if (ini.ParseError() < 0) {
    std::cerr << "Не могу загрузить конфиг из '" << file << "'\n";
    std::exit(ERR_INI);
  }

  // Выковыриваем данные, все нужные параметры быть обязаны, иначе std::exit()
  fs.dir_rights = ini.GetInteger("fs", "dir_rights", -1);
  if (fs.dir_rights == -1) {
    std::cerr << "В ini нет fs.dir_rights\n";
    std::exit(ERR_INI);
  }
  fs.video_dir = ini.Get("fs", "video_dir", "");
  if (fs.video_dir == "") {
    std::cerr << "В ini нет fs.video_dir\n";
    std::exit(ERR_INI);
  }
  fs.audio_dir = ini.Get("fs", "audio_dir", "");
  if (fs.audio_dir == "") {
    std::cerr << "В ini нет fs.audio_dir\n";
    std::exit(ERR_INI);
  }
  fs.dray_dir = ini.Get("fs", "dray_dir", "");
  if (fs.dray_dir == "") {
    std::cerr << "В ini нет fs.dray_dir\n";
    std::exit(ERR_INI);
  }
  fs.dray_log = ini.Get("fs", "dray_log", "");
  if (fs.dray_log == "") {
    std::cerr << "В ini нет fs.dray_log\n";
    std::exit(ERR_INI);
  }
  fs.cookie_path = ini.Get("fs", "cookie_path", "");
  if (fs.cookie_path == "") {
    std::cerr << "В ini нет fs.cookie_path\n";
    std::exit(ERR_INI);
  }
  yt.ytids = ini.Get("yt-dlp", "ytids", "");
  if (yt.ytids == "") {
    std::cerr << "В ini нет yt-dlp.ytids\n";
    std::exit(ERR_INI);
  }
  yt.ytcmd = ini.Get("yt-dlp", "ytcmd", "");
  if (yt.ytcmd == "") {
    std::cerr << "В ini нет yt-dlp.ytcmd\n";
    std::exit(ERR_INI);
  }
  yt.mode1 = ini.Get("yt-dlp", "mode1", "");
  if (yt.mode1 == "") {
    std::cerr << "В ini нет yt-dlp.mode1\n";
    std::exit(ERR_INI);
  }
  yt.mode2 = ini.Get("yt-dlp", "mode2", "");
  if (yt.mode2 == "") {
    std::cerr << "В ini нет yt-dlp.mode2\n";
    std::exit(ERR_INI);
  }
  yt.modep = ini.Get("yt-dlp", "modep", "");
  if (yt.modep == "") {
    std::cerr << "В ini нет yt-dlp.modep\n";
    std::exit(ERR_INI);
  }
  yt.fname = ini.Get("yt-dlp", "fname", "");
  if (yt.fname == "") {
    std::cerr << "В ini нет yt-dlp.fname\n";
    std::exit(ERR_INI);
  }
  yt.pname = ini.Get("yt-dlp", "pname", "");
  if (yt.pname == "") {
    std::cerr << "В ini нет yt-dlp.pname\n";
    std::exit(ERR_INI);
  }
  yt.retr = ini.GetInteger("yt-dlp", "retr", -1);
  if (yt.retr == -1) {
    std::cerr << "В ini нет yt-dlp.retr\n";
    std::exit(ERR_INI);
  }
}

// Выделяем память под глобальную переменную-указатель на config
Cfg* config;

