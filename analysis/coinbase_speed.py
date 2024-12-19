from coinbase.rest import RESTClient
import json
import time
import os

client = RESTClient() # Uses environment variables for API key and secret

from coinbase.websocket import WSClient

api_key = os.environ.get("COINBASE_API_TOKEN")
api_secret = os.environ.get("COINBASE_PRIVATE_TOKEN")

delta=0

def on_message(msg):
    global msg_count
    msg_count += 1
    print(msg)
    # print(msg_count, " ====================================== ")
    # print(msg)
    m = json.loads(msg)
    # print(m)
    try:
        print(msg_count, " ====================================== ")
        event = m['events'][0]
        info = event['tickers'][0]
        print(m['timestamp'], end='\t')
        print(info['price'], end='\n')
    except:
        pass

client = WSClient(api_key=api_key, api_secret=api_secret, on_message=on_message)

# channels = ['heartbeats', 'ticker', 'ticker_batch', 'level2',  'market_trades', 'futures_balance_summary']
# for channel in channels:
prod = "POL-USD"
channel = 'market_trades'
msg_count = 0
client.open()
start_time = time.time()
client.subscribe(product_ids=[prod], channels=[channel])
time.sleep(10)
end_time = time.time()
delta = end_time - start_time
client.unsubscribe(product_ids=[prod], channels=[channel])
client.close()
    

print("{} Latency: {}".format(channel, delta/msg_count))