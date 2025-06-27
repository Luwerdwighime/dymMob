/**
 * @file config.hpp
 * @brief Константы
 */

#pragma once
/// Флаг дебага
#define DEBUG true

/// Путь поумолчанию до конфига
#define INI_CFG "config.ini"

/// Ошибка опций командной строки
#define ERR_OPTS    1
/// Ошибка в ini конфиге или его отсутствии
#define ERR_INI     2
/// Ошибка создания рабочих папок
#define ERR_DIR     3
/// Ошибка создания лога Дмитрия Рея
#define ERR_DRAYLOG 4
/// Ошибка при получении плейлиста из сети
#define ERR_YTID    5

