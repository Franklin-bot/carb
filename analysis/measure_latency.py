import requests
from coinbase.rest import RESTClient
import json
import time
import os

count = 1000

tstart = int(time.time()) - 60*60 # an hour ago

api_key = os.environ.get("COINBASE_API_TOKEN")
api_secret = os.environ.get("COINBASE_PRIVATE_TOKEN")

client = RESTClient(api_key=api_key, api_secret=api_secret)
prod = "MATIC-USD"

print(client.get_public_market_trades(prod,2,start=tstart))


url = "https://api.kraken.com/0/public/Trades?pair={}&since={}".format("MATICUSD",tstart)
print(url)

payload = {}
headers = {
  'Accept': 'application/json'
}

response = requests.request("GET", url, headers=headers, data=payload)

m = json.loads(response.text)
print(m)