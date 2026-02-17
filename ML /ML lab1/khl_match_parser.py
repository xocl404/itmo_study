import re
import random
import time
from bs4 import BeautifulSoup
from config import *
import requests


class KHLMatchParser:

    def __init__(self, session=None):
        self.session = session or requests.Session()
        if not session:
            self.session.headers.update(REQUEST_HEADERS)
    
    def _random_delay(self):
        # случайная задержка между запросами
        delay = random.uniform(MIN_DELAY, MAX_DELAY)
        time.sleep(delay)
    
    def parse_match_page(self, match_url: str) -> dict:
        # парсим страницу матча и возвращаем словарь с данными
        for attempt in range(MAX_RETRIES):
            try:
                soup = self._load_match_page(match_url)
                data = self._extract_all_data(soup, match_url)
                return data
                    
            except requests.RequestException:
                if attempt < MAX_RETRIES - 1:
                    retry_delay = random.uniform(5, 10)
                    time.sleep(retry_delay)
                else:
                    return None

            
    def _load_match_page(self, url: str) -> BeautifulSoup:
        # загружаем страницу матча
        response = self.session.get(url, timeout=REQUEST_TIMEOUT)
        response.raise_for_status()
        return BeautifulSoup(response.content, 'html.parser')
    
    def _extract_all_data(self, soup: BeautifulSoup, match_url: str) -> dict:
        # извлекаем все признаки из HTML
        data = {'match_url': match_url}
        
        self._extract_basic_info(soup, data)
        self._extract_statistics(soup, data)
        self._calculate_derived_features(data)
        
        return data
    
    def _extract_basic_info(self, soup: BeautifulSoup, data: dict):
        # извлекаем основную информацию о матче
        self._extract_teams(soup, data)
        self._extract_score(soup, data)
        self._extract_stadium_info(soup, data)

    def _extract_teams(self, soup: BeautifulSoup, data: dict):
        # извлекаем названия команд
        teams = soup.find_all('div', class_='match-info__team-name')
        if len(teams) >= 2:
            data['home_team'] = teams[0].get_text().strip()
            data['away_team'] = teams[1].get_text().strip()
        else:
            team_links = soup.find_all('a', class_='match-info__team-link')
            if len(team_links) >= 2:
                data['home_team'] = team_links[0].get_text().strip()
                data['away_team'] = team_links[1].get_text().strip()

    def _extract_score(self, soup: BeautifulSoup, data: dict):
        # извлекаем счёт матча
        score_elem = soup.find('div', class_='match-info__score-total')
        if score_elem:
            score_text = score_elem.get_text().strip()
            clean_text = re.sub(r'[БОТ]\s*$', '', score_text)
            clean_text = re.sub(r'\s+', ' ', clean_text).strip()          
            scores = clean_text.split(':')
            if len(scores) == 2:
                data['home_goals'] = int(scores[0].strip())
                data['away_goals'] = int(scores[1].strip())
                data['home_win'] = 1 if data['home_goals'] > data['away_goals'] else 0

    def _extract_stadium_info(self, soup: BeautifulSoup, data: dict):
        # извлекаем информацию о стадионе и зрителях
        extra_info = soup.find('div', class_='match-info__extra')
        text = extra_info.get_text()
        self._extract_attendance(text, data)
        self._extract_capacity(text, data)

    def _extract_attendance(self, text: str, data: dict):
        # извлекаем количество зрителей
        pattern = r'(\d[\d\s]*)\s*зрителей'
        match = re.search(pattern, text)
        if match:
            attendance_str = match.group(1).replace(' ', '')
            if attendance_str.isdigit():
                data['attendance'] = int(attendance_str)
                return
    
    def _extract_capacity(self, text: str, data: dict):
        # извлекаем вместимость стадиона
        pattern = r'вместимости\s*(\d[\d\s]*)'
        match = re.search(pattern, text)
        if match:
            capacity_str = match.group(1).replace(' ', '')
            if capacity_str.isdigit():
                data['capacity'] = int(capacity_str)
                return
 
    def _extract_statistics(self, soup: BeautifulSoup, data: dict):
         # извлекаем статистические данные
        stats_block = self._find_statistics_block(soup)
        all_titles = stats_block.find_all('div', class_='stat-graph__title')
        for title in all_titles:
            print(f"     - '{title.get_text().strip()}'")  
        self._extract_shots_data(stats_block, data)
        self._extract_faceoffs_data(stats_block, data)

    
    def _find_statistics_block(self, soup: BeautifulSoup):
        # ищем блок статистики
        stats_header = soup.find('h2', class_='tournament-title', text=re.compile(r'Статистика', re.IGNORECASE))      
        if stats_header:
            next_div = stats_header.find_next('div', class_='stat-graph')
            if next_div:
                return next_div
            parent = stats_header.find_parent('div')
            if parent and parent.find('div', class_='stat-graph__row'):
                return parent
        stat_graph = soup.find('div', class_='stat-graph')
        if stat_graph:
            return stat_graph
        stat_rows = soup.find_all('div', class_='stat-graph__row')
        if stat_rows:
            return stat_rows[0].find_parent('div')
        return None
    
    def _extract_shots_data(self, stats_block, data: dict):
         # извлекаем данные о бросках
        shots_row = self._find_stat_row_by_title(stats_block, 'Броски в створ')
        self._extract_numbers_from_row(shots_row, 'shots', data)
    
    def _extract_faceoffs_data(self, stats_block, data: dict):
        # извлекаем данные о вбрасываниях
        faceoffs_row = self._find_stat_row_by_title(stats_block, 'Вбрасывания')
        self._extract_numbers_from_row(faceoffs_row, 'faceoffs', data)

    def _find_stat_row_by_title(self, stats_block, title_text: str):
        # находим строку статистики по заголовку
        titles = stats_block.find_all('div', class_='stat-graph__title', 
                                    text=re.compile(title_text, re.IGNORECASE))
        for title in titles:
            row = title.find_parent('div', class_='stat-graph__row')
            if row:
                return row
        return None
    
    def _extract_numbers_from_row(self, row, stat_type: str, data: dict):
        # извлекаем числа из строки статистики
        # ищем значения для домашней команды
        home_value = row.find('div', class_='stat-graph__value _left')
        if home_value:
            home_strong = home_value.find('strong')
            if home_strong:
                home_text = home_strong.get_text().strip()
                data[f'home_{stat_type}'] = int(home_text)

        if f'home_{stat_type}' not in data and home_value:
            home_text = home_value.get_text().strip()
            numbers = re.findall(r'\d+', home_text)
            data[f'home_{stat_type}'] = int(numbers[0])
        
        # ищем значения для гостевой команды
        away_value = row.find('div', class_='stat-graph__value _right')
        if away_value:
            away_strong = away_value.find('strong')
            if away_strong:
                away_text = away_strong.get_text().strip()
                data[f'away_{stat_type}'] = int(away_text)
        
        if f'away_{stat_type}' not in data and away_value:
            away_text = away_value.get_text().strip()
            numbers = re.findall(r'\d+', away_text)
            data[f'away_{stat_type}'] = int(numbers[0])

    def _calculate_derived_features(self, data: dict):
        # вычисляем производные признаки
        self._calculate_shot_efficiency(data)
        self._calculate_faceoff_efficiency(data)
        self._calculate_attendance_rate(data)

    def _calculate_shot_efficiency(self, data: dict):
        # вычисляем эффективность бросков
        home_shots = data.get('home_shots', 0)
        away_shots = data.get('away_shots', 0)
        home_goals = data.get('home_goals', 0)
        away_goals = data.get('away_goals', 0)      
        data['home_shot_efficiency'] = home_goals / home_shots if home_shots > 0 else 0.0
        data['away_shot_efficiency'] = away_goals / away_shots if away_shots > 0 else 0.0
    
    def _calculate_faceoff_efficiency(self, data: dict):
        # вычисляем эффективность вбрасываний
        home_faceoffs = data.get('home_faceoffs', 0)
        away_faceoffs = data.get('away_faceoffs', 0)
        total_faceoffs = home_faceoffs + away_faceoffs       
        data['home_faceoff_efficiency'] = home_faceoffs / total_faceoffs
        data['away_faceoff_efficiency'] = away_faceoffs / total_faceoffs

    def _calculate_attendance_rate(self, data: dict):
         # вычисляем посещаемость
        attendance = data.get('attendance', 0)
        capacity = data.get('capacity', 1)
        data['attendance_rate'] = attendance / capacity if capacity > 0 else 0.0
            
    def get_required_columns(self) -> list:
        # возвращаем список всех признаков
        return [
            'home_team', 'away_team', 'home_goals', 'away_goals',
            'home_shots', 'away_shots', 'home_shot_efficiency', 'away_shot_efficiency',
            'home_faceoffs', 'away_faceoffs', 'home_faceoff_efficiency', 'away_faceoff_efficiency',
            'attendance', 'capacity', 'attendance_rate', 'home_win', 'match_url'
        ]