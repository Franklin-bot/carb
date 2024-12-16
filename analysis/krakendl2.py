from typing import Any

from kraken.spot import OrderbookClient

import asyncio

async def main():
    orderbook = OrderbookClient(depth=10)
    await orderbook.start()
    await orderbook.subscribe(
        params={"channel": "level3", "symbol": ["BTC/USD"]}
    )
    orderbook.on_book_update("BTC/USD", )