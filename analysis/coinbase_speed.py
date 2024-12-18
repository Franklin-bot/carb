from coinbase.rest import RESTClient
import time
import os

client = RESTClient() # Uses environment variables for API key and secret

from coinbase.websocket import WSClient

api_key = os.environ.get("COINBASE_API_TOKEN")
api_secret = os.environ.get("COINBASE_PRIVATE_TOKEN")

def on_message(msg):
    global msg_count
    msg_count += 1

client = WSClient(api_key=api_key, api_secret=api_secret, on_message=on_message)

channels = ['heartbeats', 'candles', 'status', 'ticker', 'ticker_batch', 'level2', 'user', 'market_trades', 'futures_balance_summary']
for channel in channels:
    msg_count = 0
    client.open()
    start_time = time.time()
    client.subscribe(product_ids=["ETH-USD"], channels=["level2"])
    time.sleep(10)
    end_time = time.time()
    delta = end_time - start_time
    client.unsubscribe(product_ids=["ETH-USD"], channels=["level2"])
    client.close()
    

    print("{} Latency: {}".format(channel, delta/msg_count))