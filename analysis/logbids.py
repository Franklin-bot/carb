# %%
import requests
import pandas as pd
import numpy as np
from coinbase.rest import RESTClient
import datetime
import json
import time
import os
import plotly.express as px



# %%
fdump = 'test.csv'
import csv
file =  open(fdump, mode="w", newline="")
writer = csv.writer(file)
writer.writerow(["time", "bid diff", "ask diff", "cb bid", "cb ask", "kk bid", "kk ask"])

# %%

prod = "1INCH-USD"

api_key = os.environ.get("COINBASE_API_TOKEN")
api_secret = os.environ.get("COINBASE_PRIVATE_TOKEN")

client = RESTClient(api_key=api_key, api_secret=api_secret)

prodkk=''.join(char for char in prod if char.isalnum())
url = "https://api.kraken.com/0/public/Depth?pair={}".format(prodkk)

payload = {}
headers = {
  'Accept': 'application/json'
}


while(True):

    # %%
    response = requests.request("GET", url, headers=headers, data=payload)
    ts = time.time()
    cb_pb = client.get_public_product_book(prod, 100)['pricebook']

    # %%
    kk_m = json.loads(response.text)
    cb_bids = cb_pb['bids']
    cb_asks = cb_pb['asks']

    for ii in range(len(cb_bids)):
        cb_bids[ii] = cb_bids[ii].__dict__
    for ii in range(len(cb_asks)):
        cb_asks[ii] = cb_asks[ii].__dict__

    # %%

    cb_bids = pd.DataFrame.from_dict(cb_bids)
    cb_asks = pd.DataFrame.from_dict(cb_asks)

    cb_bids['price'] = cb_bids['price'].astype(float)
    cb_bids['size'] = cb_bids['size'].astype(float)

    cb_asks['price'] = cb_asks['price'].astype(float)
    cb_asks['size'] = cb_asks['size'].astype(float)

    # %%
    kk_bids = pd.DataFrame(kk_m['result'][prodkk]['bids'])
    kk_bids = kk_bids.drop(2, axis=1)
    kk_bids.columns=['price', 'size']
    kk_bids['price'] = kk_bids['price'].astype(float)
    kk_bids['size'] = kk_bids['size'].astype(float)

    kk_asks = pd.DataFrame(kk_m['result'][prodkk]['asks'])
    kk_asks = kk_asks.drop(2, axis=1)
    kk_asks.columns=['price', 'size']
    kk_asks['price'] = kk_asks['price'].astype(float)
    kk_asks['size'] = kk_asks['size'].astype(float)

    # %%
    from scipy.stats  import hmean
    def weighted_sum(df):
        return hmean(df['price'], weights=df['size'])


    # %%
    # print("cb bids\t", weighted_sum(cb_bids))
    # print("cb asks\t", weighted_sum(cb_asks))


    # print()
    # print("kk bids\t", weighted_sum(kk_bids))
    # print("kk asks\t", weighted_sum(kk_asks))


    # print()
    # print("cb\t", (weighted_sum(cb_bids) + weighted_sum(cb_asks))/2)
    # print("kk\t", (weighted_sum(kk_bids) + weighted_sum(kk_asks))/2)

    # %%


    cbb = np.max(cb_bids['price'])
    cba = np.min(cb_asks['price'])
    kkb = np.max(kk_bids['price'])
    kka = np.min(kk_asks['price'])
    writer.writerow([
        ts,
        np.abs(cbb-kkb),
        np.abs(cba-kka),
        cbb,
        cba,
        kkb,
        kka,
    ])




