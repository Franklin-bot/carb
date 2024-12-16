import asyncio
from kraken.spot import KrakenSpotWSClientV2

API_KEY = "D01pQEZl5Z9zvFBxcONyk4KP3pG0P5SrVrUy8gXXtGaFwDJbiZFkTSdb"
SECRET_KEY = "AGj7IUOplyh4Q+DIYk1S0lFZ+tjBaVvs9LwHoBI8NvmtOi6BH6Y+tg4HsuWWdCjy3swoVeXiXNncP0VUIyZ1Uw=="


async def main():

    # print(client.active_public_subscriptions) # to list active subscriptions

    # AS default, the authenticated client starts two websocket connections,
    # one for authenticated and one for public messages. If there is no need
    # for a public connection, it can be disabled using the ``no_public``
    # parameter.
    client_auth = KrakenSpotWSClientV2(key=API_KEY, secret=SECRET_KEY, no_public=True)
    await client_auth.
    await client_auth.subscribe(
        params={"channel": "level3", "symbol": ["BTC/USD"]}
    )
    await asyncio.sleep(6)


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass
        # The websocket client will send {'event': 'asyncio.CancelledError'}
        # via on_message so you can handle the behavior/next actions
        # individually within your strategy.g