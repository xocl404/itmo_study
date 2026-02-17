# Настройки запросов
REQUEST_HEADERS = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
    'Accept-Language': 'ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3',
}

# Случайные задержки между запросами
MIN_DELAY = 1.5
MAX_DELAY = 4.0
SEASON_DELAY = 3.0

# Таймауты запросов
REQUEST_TIMEOUT = 15
MAX_RETRIES = 2

# URL для краулинга
SEASON_URLS = {
    "2022/2023": "https://www.championat.com/hockey/_superleague/tournament/5077/calendar/",
    "2023/2024": "https://www.championat.com/hockey/_superleague/tournament/5383/calendar/", 
    "2024/2025": "https://www.championat.com/hockey/_superleague/tournament/5974/calendar/"
}

# Настройки csv файла
OUTPUT_CSV = "khl_matches.csv"
ENCODING = "utf-8"
