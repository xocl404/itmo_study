import pandas as pd
from config import *
from khl_match_collector import KHLMatchCollector
from khl_match_parser import KHLMatchParser


class KHLDataPipeline:
    def __init__(self):
        self.collector = KHLMatchCollector()
        self.parser = KHLMatchParser(self.collector.session)
        self.dataset = []
    
    def run_crawling_stage(self) -> list:
        self.collector.get_seasons_calendars()
        all_match_urls = self.collector.get_all_match_urls()
        return all_match_urls
    
    def run_parsing_stage(self, match_urls: list):
        # запускаем этап парсинга - обработка матчей               
        for i, match_url in enumerate(match_urls, 1):
            self._process_single_match(match_url, i, len(match_urls))           
            # Случайная задержка после каждого матча
            if i < len(match_urls):
                self.parser._random_delay()
    
    def _process_single_match(self, match_url: str, current: int, total: int):
        # обрабатываем текущий матч      
        match_data = self.parser.parse_match_page(match_url)
        self.dataset.append(match_data)
    
    def run_saving_stage(self):
        self._save_to_csv(self._create_dataframe())

    
    def _create_dataframe(self) -> pd.DataFrame:
        # создаём DataFrame из собранных данных
        df = pd.DataFrame(self.dataset)
        required_columns = self.parser.get_required_columns()       
        for col in required_columns:
            if col not in df.columns:
                df[col] = None       
        return df
    
    def _save_to_csv(self, df: pd.DataFrame):
        # сохраняем DataFrame в CSV файл
        required_columns = self.parser.get_required_columns()
        df[required_columns].to_csv(OUTPUT_CSV, index=False, encoding=ENCODING)
