from khl_data_pipeline import KHLDataPipeline

def main():
    pipeline = KHLDataPipeline()
    match_urls = pipeline.run_crawling_stage()
    pipeline.run_parsing_stage(match_urls)
    pipeline.run_saving_stage()
    
if __name__ == "__main__":
    main()