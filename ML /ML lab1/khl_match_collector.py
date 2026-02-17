import requests
from bs4 import BeautifulSoup
import time
import random
import re
from urllib.parse import urljoin
from config import REQUEST_HEADERS, SEASON_DELAY, SEASON_URLS, REQUEST_TIMEOUT, MAX_RETRIES


class KHLMatchCollector:
    def __init__(self):
        self.session = requests.Session()
        self.session.headers.update(REQUEST_HEADERS)
        self.collected_matches = {}
    
    def get_seasons_calendars(self):
        all_matches = {}
        for season_name, calendar_url in SEASON_URLS.items():
            season_matches = self._process_season_calendar(calendar_url)
            all_matches[season_name] = season_matches          
            # задержка между сезонами
            if season_name != list(SEASON_URLS.keys())[-1]:
                time.sleep(SEASON_DELAY)      
        self.collected_matches = all_matches

    
    def _process_season_calendar(self, calendar_url: str) -> list:
        # обрабатываем календарь одного сезона        
        for attempt in range(MAX_RETRIES):
            try:
                soup = self._load_calendar_page(calendar_url)
                season_matches = self._extract_match_urls(soup)              
                return season_matches
                
            except requests.RequestException:
                if attempt < MAX_RETRIES - 1:
                    retry_delay = random.uniform(5, 10)
                    time.sleep(retry_delay)
                else:
                    return []
    
    def _load_calendar_page(self, url: str) -> BeautifulSoup:
        # загружаем страницу календаря
        response = self.session.get(url, timeout=REQUEST_TIMEOUT)
        response.raise_for_status()
        return BeautifulSoup(response.content, 'html.parser')
    
    def _extract_match_urls(self, soup: BeautifulSoup) -> list:
        # извлекаем url матчей из страницы
        season_matches = []
        match_links = soup.find_all('a', href=re.compile(r'/match/\d+'))
        
        for link in match_links:
            href = link.get('href')
            if href and '/match/' in href:
                match_url = urljoin("https://www.championat.com", href)
                if match_url not in season_matches:
                    season_matches.append(match_url)
        
        return season_matches
    
    def get_all_match_urls(self) -> list:
        # возвращаем все url матчей
        all_urls = []
        for season_matches in self.collected_matches.values():
            all_urls.extend(season_matches)
        return all_urls
    